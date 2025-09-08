#include "stm32f4g.h"
#include "rcc.h"
#include "gpio.h"
#include "utils.h"
#include "adc.h"
#include "uart.h"
#include "dma.h"

volatile uint16_t buffer[stm32::ADC::NO_OF_ADC_CONVERSIONS]={0U};

void delay(int time){
    for (volatile int i = 0; i < time; ++i){
        __asm__ volatile ("nop"); //to remove loop unrolling and branch prediction optimisation
    }
}

void set_internal_clock(){
    auto rcc = stm32::rcc::get(); 
    utils::set_bit(rcc->CR, 8U);                //HSI On
    while(!utils::is_bit_set(rcc->CR, 10U));    //wait till HSI on

    utils::write_reg(rcc->CFGR, 1UL, 0U, 2U);   //set HSI as system clock
    //while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_HSI); //check hsi
    delay(500000); //aprox 500ms

}

void enable_peripheral_clocks(){
    stm32::rcc::get()->AHB2ENR |= (1 << 0);     //enable gpioa clock
    stm32::rcc::get()->AHB2ENR |= (1 << 1);     //enable gpiob clock
    stm32::rcc::get()->AHB2ENR |= (1 << 2);     //enable gpioc clock
    stm32::rcc::get()->AHB2ENR |= (1 << 5);     //enable gpiof clock

    auto rcc = stm32::rcc::get();         
    rcc->CCIPR = 0x20000000U;          
    utils::set_bit(rcc->AHB2ENR, 13U);          //enable ADC clock
    utils::set_bit(rcc->APB1ENR2, 0U);          //enable lpuart1 clock
 
    rcc->AHB1ENR |= (1UL<<2U);                  //enable adc12
    utils::set_bit(rcc->AHB1ENR, 0U);           //enable dma1
    
}

extern "C" int main()
{
    set_internal_clock();
    enable_peripheral_clocks();
    stm32::uart::uart_gpio_init();
    stm32::uart::uart_init();
    stm32::dma_channel::init_dma_channel();
    stm32::ADC::adc_gpio_init();
    stm32::ADC::adc_init();
    stm32::ADC::start_adc();

#if defined LED_BLINK
    auto gpioa = stm32::gpio::port_a::get();
    gpioa->MODER &= ~(3 << (5 * 2));
    gpioa->MODER |=  (1 << (5 * 2));
#endif

    while (1)
    {
#if defined LED_BLINK
        utils::set_bit(gpioa->BSRR, 5U);
        delay(1000000);
        utils::set_bit(gpioa->BSRR, 5U + 16U);
        delay(1000000);
#else
        delay(1000000);
        //uint16_t val = stm32::ADC::get_adc_val();
        //stm32::uart::uart_send_string("val:", val);
        stm32::uart::uart_send_string("A0 buffer:", buffer[0]); //A0
        stm32::uart::uart_send_string("A1 buffer:", buffer[1]); //A1
        stm32::uart::uart_send_string("A4 buffer:", buffer[2]); //A4
        stm32::uart::uart_send_string("A5 buffer:", buffer[3]); //A5
        stm32::uart::uart_send_string("Pin 35", buffer[4]); //pin 35
#endif
    }

    return 0;
}
