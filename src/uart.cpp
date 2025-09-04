#include "uart.h"
#include "utils.h"
#include "gpio.h"

void stm32::uart::uart_gpio_init(){
    auto gpioa = stm32::gpio::port_a::get();
    //gpioa->OSPEEDR = 0x0c000000; //reset value
    //gpioa->OTYPER = 0U;  //reset value
    //gpioa->PUPDR = 0x64000000u; //reset value
    utils::write_reg(gpioa->MODER, 2UL, 4U, 2U);  //afmode ->PA2
    utils::write_reg(gpioa->MODER, 2UL, 6U, 2U);  //afmode ->PA3

    gpioa->AFR[1] = 0U;
    utils::write_reg(gpioa->AFR[0], 12UL, 8U, 4U);  //af12 ->PA2
    utils::write_reg(gpioa->AFR[0], 12UL, 12U, 4U); //af12 ->PA3
}

void stm32::uart::uart_init(){
    auto uart = stm32::uart::lpuart::get();
    //uart->BRR = (256 * 16000000UL + (115200 / 2)) / 115200;
    uart->BRR = 35556;
    uart->CR1 = 0; // reset all
    uart->CR2 = 0;
    uart->CR3 = 0;
    utils::set_bit(uart->CR1, 3U); //enable TE
    utils::set_bit(uart->CR1, 2U); //enable RE
    utils::set_bit(uart->CR1, 0U); //enable uart
    // Set word length = 8 bits, no parity, oversampling by 16
    //uart->CR1 |= (1 << 3) | (1 << 2) | (1 << 0); // TE, RE, UE
    while(!utils::is_bit_set(uart->ISR, 21U));
    while(!utils::is_bit_set(uart->ISR, 22U));
}

void stm32::uart::uart_send_char(char c){
    auto uart = stm32::uart::lpuart::get();
    while (!utils::is_bit_set(uart->ISR, 7U)); // TXE
    uart->TDR = c;
    while (!utils::is_bit_set(uart->ISR, 6U)); // TC
}

    void uint16_to_char_array(uint16_t number, char* buffer) {

        if (number == 0) {
            buffer[0] = '0';
            buffer[1] = '\0';
            return;
        }

        char temp[6]; // max 5 digits for uint16_t + 1 for null
        int i = 0;

        // Extract digits in reverse
        while (number > 0) {
            uint16_t digit = number % 10;
            temp[i++] = '0' + digit; // convert digit to ASCII
            number /= 10;
        }

        // Reverse the digits into the final buffer
        int j = 0;
        while (i > 0) {
            buffer[j++] = temp[--i];
        }

        buffer[j] = '\0'; // Null-terminate
    }

void stm32::uart::uart_send_string(const char* s, uint16_t val) {
    while (*s) {
        stm32::uart::uart_send_char(*s++);
    }

    char adc_val[6];
    uint16_to_char_array(val,adc_val);

    for(uint8_t i=0; i<6; i++){
        stm32::uart::uart_send_char(adc_val[i]);
    }

    stm32::uart::uart_send_char('\r');
    stm32::uart::uart_send_char('\n');
}
