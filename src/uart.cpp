#include "uart.h"
#include "utils.h"

void stm32::uart::uart_init(){
    auto uart = stm32::uart::lpuart::get();

    // Baud rate: 16 MHz / 115200 = ~138.888 * 16 = ~2222
    //uart->BRR = (256 * 16000000UL + (115200 / 2)) / 115200;
    //uart->BRR = (256 * 16000000UL + (9600 / 2)) / 9600; 
    uart->BRR = 35556;


    uart->CR1 = 0; // reset all
    uart->CR2 = 0;
    uart->CR3 = 0;
    utils::set_bit(uart->CR1, 3U); //enable TE
    utils::set_bit(uart->CR1, 2U); //enable RE
    utils::set_bit(uart->CR1, 0U); //enable uart
    // Set word length = 8 bits, no parity, oversampling by 16
    uart->CR1 |= (1 << 3) | (1 << 2) | (1 << 0); // TE, RE, UE

    while(!utils::is_bit_set(uart->ISR, 21U));
    while(!utils::is_bit_set(uart->ISR, 22U));
}

void stm32::uart::uart_send_char(char c){
    auto uart = stm32::uart::lpuart::get();
    while (!utils::is_bit_set(uart->ISR, 7U)); // TXE
    uart->TDR = c;
    while (!utils::is_bit_set(uart->ISR, 6U)); // TC
}

void stm32::uart::uart_send_string(const char* s) {
    while (*s) {
        stm32::uart::uart_send_char(*s++);
    }
}