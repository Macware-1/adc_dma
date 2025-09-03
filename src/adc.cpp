#include "adc.h"
#include "utils.h"

void stm32::ADC::start_adc(){
    auto adc1 = stm32::ADC::get();
    utils::set_bit(adc1->CR, 2U);   //start ADC
}