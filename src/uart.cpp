#include "uart.h"
#include "utils.h"

void stm32::uart::uart_init(){
    auto uart = stm32::uart::lpuart::get();

    // Baud rate: 16 MHz / 115200 = ~138.888 * 16 = ~2222
    uart->BRR = 2222;
    utils::set_bit(uart->CR1, 3U); //enable TE
    utils::set_bit(uart->CR1, 2U); //enable RE
    utils::set_bit(uart->CR1, 0U); //enable uart

    while(!utils::is_bit_set(uart->ISR, 21U));
    while(!utils::is_bit_set(uart->ISR, 22U));
}

void stm32::uart::uart_send_char(char c){
    auto uart = stm32::uart::lpuart::get();
    while(!utils::is_bit_set(uart->ISR, 7U));
    uart->TDR = c;
}

void stm32::uart::uart_send_string(const char* s) {
    while (*s) {
        stm32::uart::uart_send_char(*s++);
    }
}