/********************************************//*
** File             gpio.h
** Date             09.09.2025    
** Description      gpio header file         
**********************************************/

#include "stm32f4g.h"

namespace stm32{
    namespace gpio{
        typedef struct
        {
            volatile uint32_t MODER;    
            volatile uint32_t OTYPER;   
            volatile uint32_t OSPEEDR;     
            volatile uint32_t PUPDR;      
            volatile uint32_t IDR;       
            volatile uint32_t ODR;       
            volatile uint32_t BSRR;   
            volatile uint32_t LCKR;      
            volatile uint32_t AFR[2];   
            volatile uint32_t BRR;         
        } gpio_struct;

        namespace port_a{
            constexpr uint32_t gpioa_base = (AHB2PERIPH_BASE + 0x0000UL); 

            inline gpio_struct* get(){
                return reinterpret_cast<gpio_struct*>(gpioa_base);
            }
        }//end namespace port_a

        namespace port_b{
            constexpr uint32_t gpiob_base = (AHB2PERIPH_BASE + 0x0400UL); 

            inline gpio_struct* get(){
                return reinterpret_cast<gpio_struct*>(gpiob_base);
            }
        }//end namespace port_b

        namespace port_c{
            constexpr uint32_t gpioc_base = (AHB2PERIPH_BASE + 0x0800UL); 

            inline gpio_struct* get(){
                return reinterpret_cast<gpio_struct*>(gpioc_base);
            }
        }//end namespace port_c

        namespace port_f{
            constexpr uint32_t gpiof_base = (AHB2PERIPH_BASE + 0x1400UL); 

            inline gpio_struct* get(){
                return reinterpret_cast<gpio_struct*>(gpiof_base);
            }
        }//end namespace port_c
        
    }//end namespace gpio
}//end namespace stm32

