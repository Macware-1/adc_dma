#include "adc.h"
#include "utils.h"
#include "gpio.h"


void stm32::ADC::adc_gpio_init(){
    auto gpioa = stm32::gpio::port_a::get();
    utils::set_reg(gpioa->MODER, 3UL, 0U);   //enable PA0 analog
    utils::set_reg(gpioa->MODER, 3UL, 2U);   //enable PA1 analog

    utils::clear_reg(gpioa->PUPDR, 3UL, 0U); //no push pull
    utils::clear_reg(gpioa->PUPDR, 3UL, 2U); //no push pull

    auto gpioc = stm32::gpio::port_c::get();
    utils::set_reg(gpioc->MODER, 3UL, 0U);   //enable PC0 analog
    utils::set_reg(gpioc->MODER, 3UL, 2U);   //enable PC1 analog

    utils::set_reg(gpioc->MODER, 3UL, 4U);   //enable PC2 analog
    utils::set_reg(gpioc->MODER, 3UL, 6U);   //enable PC3 analog

    utils::clear_reg(gpioc->PUPDR, 3UL, 0U); //no push pull
    utils::clear_reg(gpioc->PUPDR, 3UL, 2U); //no push pull

    utils::clear_reg(gpioc->PUPDR, 3UL, 4U); //no push pull
    utils::clear_reg(gpioc->PUPDR, 3UL, 6U); //no push pull

}

void stm32::ADC::adc_init(){
    auto adc1 = stm32::ADC::get();
    utils::clear_bit(adc1->CR, 29U); //exit deep powerdown mode
    utils::set_bit(adc1->CR, 28U);   //enable voltage regulator
    while(!utils::is_bit_set(adc1->CR, 28U));

    utils::set_bit(adc1->CR, 31U);           //start adc calibration
    
    while(utils::is_bit_set(adc1->CR, 31U)); //wait for calibration

    utils::set_bit(adc1->CFGR, 0U); //enable adc dma
    utils::set_bit(adc1->CFGR, 1U); //enable circular mode

    auto adc12 = stm32::ADC::get_adc_common();
    //utils::set_bit(adc12->CCR, 13U);
    //utils::set_bit(adc12->CCR, 15U);
    adc12->CCR = 0x20000U;

    utils::set_bit(adc1->ISR, 0U); //clear ADRDY
    utils::set_bit(adc1->CR, 0U); //set adc ready
    //while(!(utils::is_bit_set(adc1->ISR, 0U))); //wait till ADC ready
    while((adc1->ISR & 0x1U) == 0U);

    utils::write_reg(adc1->CFGR, 0UL, 3U, 2U); //12 bit resolution
    utils::clear_bit(adc1->CFGR,15U);          //right allign
    utils::set_bit(adc1->CFGR,13U);          //continuous conversion
    utils::set_bit(adc1->CFGR,31U);          //continuous conversion

    adc1->CFGR2 = 0u;
    utils::write_reg(adc1->SMPR1, 7UL, 3U, 3U); //640.5 cycles to avoid crosstalk 
    utils::write_reg(adc1->SMPR1, 7UL, 6U, 3U); //pa1

    //utils::write_reg(adc1->SMPR1, 2UL, 18U, 3U); //channel 6
    utils::write_reg(adc1->SMPR1, 7UL, 21U, 3U); //channel 7
    utils::write_reg(adc1->SMPR1, 7UL, 24U, 3U); //channel 8
    utils::write_reg(adc1->SMPR1, 7UL, 27U, 3U); //channel 9

    utils::write_reg(adc1->SQR1, 4UL, 0U, 4U); //5 conversions

    utils::set_bit(adc1->SQR1, 6U); //regular conversion
    utils::set_bit(adc1->SQR1, 13U); //regular conversion
    //utils::write_reg(adc1->SQR1, 6UL, 18U, 5U); //4 conversions
    utils::write_reg(adc1->SQR1, 7UL, 24U, 5U); //5 conversions

    utils::write_reg(adc1->SQR2, 8UL, 0U, 5U); //5 conversions
    utils::write_reg(adc1->SQR2, 9UL, 6U, 5U); //5 conversions
}

void stm32::ADC::start_adc(){
    auto adc1 = stm32::ADC::get();
    utils::set_bit(adc1->CR, 2U);   //start ADC
}

uint16_t stm32::ADC::get_adc_val(){
    auto adc1 = stm32::ADC::get();
    while (!(utils::is_bit_set(adc1->ISR, 2U)));  // Wait for conversion
    uint16_t adc_val1 = adc1->DR;
    return adc_val1;
}
