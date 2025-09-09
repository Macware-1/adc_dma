/********************************************//*
** File             rcc.h
** Date             09.09.2025    
** Description      rcc clock header file         
**********************************************/

#include "stm32f4g.h"

namespace stm32{
    namespace rcc{
        typedef struct
        {
            volatile uint32_t CR;          /*!< RCC clock control register,                                              Address offset: 0x00 */
            volatile uint32_t ICSCR;       /*!< RCC internal clock sources calibration register,                         Address offset: 0x04 */
            volatile uint32_t CFGR;        /*!< RCC clock configuration register,                                        Address offset: 0x08 */
            volatile uint32_t PLLCFGR;     /*!< RCC system PLL configuration register,                                   Address offset: 0x0C */
            volatile uint32_t RESERVED0;   /*!< Reserved,                                                                Address offset: 0x10 */
            volatile uint32_t RESERVED1;   /*!< Reserved,                                                                Address offset: 0x14 */
            volatile uint32_t CIER;        /*!< RCC clock interrupt enable register,                                     Address offset: 0x18 */
            volatile uint32_t CIFR;        /*!< RCC clock interrupt flag register,                                       Address offset: 0x1C */
            volatile uint32_t CICR;        /*!< RCC clock interrupt clear register,                                      Address offset: 0x20 */
            volatile uint32_t RESERVED2;   /*!< Reserved,                                                                Address offset: 0x24 */
            volatile uint32_t AHB1RSTR;    /*!< RCC AHB1 peripheral reset register,                                      Address offset: 0x28 */
            volatile uint32_t AHB2RSTR;    /*!< RCC AHB2 peripheral reset register,                                      Address offset: 0x2C */
            volatile uint32_t AHB3RSTR;    /*!< RCC AHB3 peripheral reset register,                                      Address offset: 0x30 */
            volatile uint32_t RESERVED3;   /*!< Reserved,                                                                Address offset: 0x34 */
            volatile uint32_t APB1RSTR1;   /*!< RCC APB1 peripheral reset register 1,                                    Address offset: 0x38 */
            volatile uint32_t APB1RSTR2;   /*!< RCC APB1 peripheral reset register 2,                                    Address offset: 0x3C */
            volatile uint32_t APB2RSTR;    /*!< RCC APB2 peripheral reset register,                                      Address offset: 0x40 */
            volatile uint32_t RESERVED4;   /*!< Reserved,                                                                Address offset: 0x44 */
            volatile uint32_t AHB1ENR;     /*!< RCC AHB1 peripheral clocks enable register,                              Address offset: 0x48 */
            volatile uint32_t AHB2ENR;     /*!< RCC AHB2 peripheral clocks enable register,                              Address offset: 0x4C */
            volatile uint32_t AHB3ENR;     /*!< RCC AHB3 peripheral clocks enable register,                              Address offset: 0x50 */
            volatile uint32_t RESERVED5;   /*!< Reserved,                                                                Address offset: 0x54 */
            volatile uint32_t APB1ENR1;    /*!< RCC APB1 peripheral clocks enable register 1,                            Address offset: 0x58 */
            volatile uint32_t APB1ENR2;    /*!< RCC APB1 peripheral clocks enable register 2,                            Address offset: 0x5C */
            volatile uint32_t APB2ENR;     /*!< RCC APB2 peripheral clocks enable register,                              Address offset: 0x60 */
            volatile uint32_t RESERVED6;   /*!< Reserved,                                                                Address offset: 0x64 */
            volatile uint32_t AHB1SMENR;   /*!< RCC AHB1 peripheral clocks enable in sleep and stop modes register,      Address offset: 0x68 */
            volatile uint32_t AHB2SMENR;   /*!< RCC AHB2 peripheral clocks enable in sleep and stop modes register,      Address offset: 0x6C */
            volatile uint32_t AHB3SMENR;   /*!< RCC AHB3 peripheral clocks enable in sleep and stop modes register,      Address offset: 0x70 */
            volatile uint32_t RESERVED7;   /*!< Reserved,                                                                Address offset: 0x74 */
            volatile uint32_t APB1SMENR1;  /*!< RCC APB1 peripheral clocks enable in sleep mode and stop modes register 1, Address offset: 0x78 */
            volatile uint32_t APB1SMENR2;  /*!< RCC APB1 peripheral clocks enable in sleep mode and stop modes register 2, Address offset: 0x7C */
            volatile uint32_t APB2SMENR;   /*!< RCC APB2 peripheral clocks enable in sleep mode and stop modes register, Address offset: 0x80 */
            volatile uint32_t RESERVED8;   /*!< Reserved,                                                                Address offset: 0x84 */
            volatile uint32_t CCIPR;       /*!< RCC peripherals independent clock configuration register,                Address offset: 0x88 */
            volatile uint32_t RESERVED9;   /*!< Reserved,                                                                Address offset: 0x8C */
            volatile uint32_t BDCR;        /*!< RCC backup domain control register,                                      Address offset: 0x90 */
            volatile uint32_t CSR;         /*!< RCC clock control & status register,                                     Address offset: 0x94 */
            volatile uint32_t CRRCR;       /*!< RCC clock recovery RC register,                                          Address offset: 0x98 */
            volatile uint32_t CCIPR2;      /*!< RCC peripherals independent clock configuration register 2,              Address offset: 0x9C */
        } rcc_struct;

        constexpr uint32_t rcc_offset   = 0x1000UL;
        constexpr uint32_t rcc_base     = (AHB1PERIPH_BASE + rcc_offset);
        
        inline rcc_struct* get(){
            return reinterpret_cast<rcc_struct*>(rcc_base);
        }
    } //end namespace rcc
} //end namespace stm32
