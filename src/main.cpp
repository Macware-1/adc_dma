#include "stm32f4g.h"
#include "rcc.h"
#include "gpio.h"
#include "utils.h"
#include "adc.h"
#include "uart.h"

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
    auto rcc = stm32::rcc::get();         
    rcc->CCIPR = 0x20000000U;          
    utils::set_bit(rcc->AHB2ENR, 13U);          //enable ADC clock
    utils::set_bit(rcc->APB1ENR2, 0U);          //enable lpuart1 clock
    
}

extern "C" int main()
{
    set_internal_clock();
    enable_peripheral_clocks();
    stm32::uart::uart_gpio_init();
    stm32::uart::uart_init();
    stm32::ADC::adc_gpio_init();
    stm32::ADC::adc_init();
    while (1)
    {
        //utils::set_bit(gpioa->BSRR, 5U);
        //delay(1000000);
        //utils::set_bit(gpioa->BSRR, 5U + 16U);
        stm32::ADC::start_adc();
        uint16_t val = stm32::ADC::get_adc_val();
        delay(1000000);
        stm32::uart::uart_send_string("ADC val:", val);
    }

    return 0;
}
