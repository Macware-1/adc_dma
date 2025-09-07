#include "dma.h"
#include "utils.h"
#include "adc.h"

extern volatile uint16_t buffer[2];

void stm32::dma_channel::init_dma_channel(){
    auto dma1_channel = stm32::dma_channel::get();
    utils::clear_bit(dma1_channel->CCR, 0U);         //diable dma
    //utils::clear_bit(dma1_channel->CCR, 4U);

    auto adc = stm32::ADC::get();
    dma1_channel->CPAR = reinterpret_cast<uint32_t>(&adc->DR); //set data register of ADC
    dma1_channel->CMAR = reinterpret_cast<uint32_t>(buffer);
    dma1_channel->CNDTR = 2;

    auto dmamux = stm32::dma_mux::get();
    dmamux->CCR |= (5U<<0);

    dma1_channel->CCR = 0U;  // clear register
    utils::set_bit(dma1_channel->CCR, 5U); //circular mode
    utils::set_bit(dma1_channel->CCR, 7U); //memory increment
    utils::set_bit(dma1_channel->CCR, 8U); //16bit peripheral size
    utils::set_bit(dma1_channel->CCR, 10U);//16 bit memory size
    //dma1_channel->CCR = 1440U;
    utils::set_bit(dma1_channel->CCR, 0U); //enable dma
}