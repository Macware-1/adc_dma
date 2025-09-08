#include "stm32f4g.h"

namespace stm32{
    namespace uart{
        typedef struct
        {
            volatile uint32_t CR1;         
            volatile uint32_t CR2;       
            volatile uint32_t CR3;         
            volatile uint32_t BRR;         
            volatile uint32_t GTPR;       
            volatile uint32_t RTOR;       
            volatile uint32_t RQR;        
            volatile uint32_t ISR;        
            volatile uint32_t ICR;       
            volatile uint32_t RDR;     
            volatile uint32_t TDR;       
            volatile uint32_t PRESC;       
        }uart_struct;
        namespace lpuart{
            constexpr uint32_t lpuart_offset = 0x8000UL;
            constexpr uint32_t lpuart_base = (APB1PERIPH_BASE + 0x8000UL);

            inline uart_struct* get(){
                return reinterpret_cast<uart_struct*>(lpuart_base);
            }
        }//end namespace lpuart

        void uart_init();
        void uart_gpio_init();
        void uart_send_char(char c);
        void uart_send_string(const char* s);
        void uart_send_string(const char* s, uint16_t val);
    }//end namespace uart
}//end namespace stm32
