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
    utils::set_bit(rcc->AHB2ENR, 13U);          //enable ADC clock
    utils::set_bit(rcc->APB1ENR2, 0U);          //enable lpuart1 clock
}

void adc_init(){
    auto gpioa = stm32::gpio::port_a::get();
    utils::set_reg(gpioa->MODER, 3UL, 0U);   //enable PA0 analog
    utils::set_reg(gpioa->MODER, 3UL, 2U);   //enable PA1 analog
    utils::clear_reg(gpioa->PUPDR, 3UL, 0U); //no push pull
    utils::clear_reg(gpioa->PUPDR, 3UL, 2U); //no push pull

    auto adc1 = stm32::ADC::get();
    utils::clear_bit(adc1->CR, 29U); //exit deep powerdown mode
    utils::set_bit(adc1->CR, 28U);   //enable voltage regulator
    delay(1000000); //1 second

    utils::set_bit(adc1->CR, 31U);           //start adc calibration
    while(utils::is_bit_set(adc1->CR, 31U)); //wait for calibration

    utils::set_bit(adc1->ISR, 0U); //clear ADRDY
    utils::set_bit(adc1->CR, 0U); //set adc ready
    while(!(utils::is_bit_set(adc1->ISR, 0U))); //wait till ADC ready

    utils::write_reg(adc1->CFGR, 0UL, 3U, 2U); //12 bit resolution
    utils::clear_bit(adc1->CFGR,15U);          //right allign
    utils::clear_bit(adc1->CFGR,13U);          //continuous conversion

    utils::write_reg(adc1->SMPR1, 2UL, 15U, 3U); //12.5 cycles for PA0,PA1
    utils::write_reg(adc1->SMPR1, 2UL, 18U, 3U);

    utils::set_bit(adc1->SQR1, 0U); //regular conversion
    utils::write_reg(adc1->SQR1, 5UL, 6U, 5U);  //1st conversion channel 5
    utils::write_reg(adc1->SQR1, 6UL, 12U, 5U); //2nd conversion channel 6
}

extern "C" int main()
{
    set_internal_clock();
    enable_peripheral_clocks();
    //adc_init();
    
    auto gpioa = stm32::gpio::port_a::get();
    gpioa->MODER &= ~(3 << (5 * 2));
    gpioa->MODER |=  (1 << (5 * 2));

    //for uart
    gpioa->MODER &= ~((3U << (2 * 2)) | (3U << (3 * 2)));
    gpioa->MODER |=  ((2U << (2 * 2)) | (2U << (3 * 2)));

    gpioa->AFR[0] &= ~((0xFU << (4 * 2)) | (0xFU << (4 * 3)));
    gpioa->AFR[0] |=  ((1U << (4 * 2)) | (1U << (4 * 3)));
    //gpio uart end
    stm32::uart::uart_init();
    while (1)
    {
        utils::set_bit(gpioa->BSRR, 5U);
        delay(1000000);

        utils::set_bit(gpioa->BSRR, 5U + 16U);
        delay(1000000);
        stm32::uart::uart_send_string("UART1 initialized with HSI @16MHz\r\n");
    }

    return 0;
}
