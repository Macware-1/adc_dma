#include "adc.h"
#include "utils.h"

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
