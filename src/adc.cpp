#include "adc.h"
#include "utils.h"
#include "gpio.h"


void stm32::ADC::adc_gpio_init(){
    auto gpioa = stm32::gpio::port_a::get();
    utils::set_reg(gpioa->MODER, 3UL, 0U);   //enable PA0 analog
    utils::set_reg(gpioa->MODER, 3UL, 2U);   //enable PA1 analog
    utils::clear_reg(gpioa->PUPDR, 3UL, 0U); //no push pull
    utils::clear_reg(gpioa->PUPDR, 3UL, 2U); //no push pull
}

void stm32::ADC::adc_init(){
    auto adc1 = stm32::ADC::get();
    utils::clear_bit(adc1->CR, 29U); //exit deep powerdown mode
    utils::set_bit(adc1->CR, 28U);   //enable voltage regulator
    while(!utils::is_bit_set(adc1->CR, 28U));

    utils::set_bit(adc1->CR, 31U);           //start adc calibration
    
    while(utils::is_bit_set(adc1->CR, 31U)); //wait for calibration

    utils::set_bit(adc1->ISR, 0U); //clear ADRDY
    utils::set_bit(adc1->CR, 0U); //set adc ready
    //while(!(utils::is_bit_set(adc1->ISR, 0U))); //wait till ADC ready
    while((adc1->ISR & 0x1U) == 0U);

    utils::write_reg(adc1->CFGR, 0UL, 3U, 2U); //12 bit resolution
    utils::clear_bit(adc1->CFGR,15U);          //right allign
    utils::clear_bit(adc1->CFGR,13U);          //continuous conversion
    utils::set_bit(adc1->CFGR,31U);          //continuous conversion

    adc1->CFGR2 = 0u;
    utils::write_reg(adc1->SMPR1, 2UL, 3U, 3U); //12.5 cycles for PA0,PA1
    utils::write_reg(adc1->SMPR1, 2UL, 6U, 3U);

    utils::set_bit(adc1->SQR1, 0U); //regular conversion
    utils::set_bit(adc1->SQR1, 6U); //regular conversion
    utils::set_bit(adc1->SQR1, 13U); //regular conversion
}

void stm32::ADC::start_adc(){
    auto adc1 = stm32::ADC::get();
    utils::set_bit(adc1->CR, 2U);   //start ADC
}

uint16_t stm32::ADC::get_adc_val(){
    auto adc1 = stm32::ADC::get();

    while (!(utils::is_bit_set(adc1->ISR, 2U)));  // Wait for conversion
    uint16_t adc_val1 = adc1->DR;

    //while (!(utils::is_bit_set(adc1->ISR, 3U)));  //wait for end of sequence conversion
    //adc1->ISR |= ADC_ISR_EOS; 
    //utils::set_bit(adc1->ISR, 3U); // Clear EOS flag
    return adc_val1;
}
