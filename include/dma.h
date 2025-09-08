#include "stm32f4g.h"

namespace stm32{
    namespace dma_channel{
        typedef struct{
            volatile uint32_t CCR;
            volatile uint32_t CNDTR;
            volatile uint32_t CPAR;
            volatile uint32_t CMAR;
        }dma_channel_struct;
        
        constexpr uint32_t dma1_base = AHB1PERIPH_BASE;
        constexpr uint32_t dma1_channel1_base = (dma1_base + 0x0008UL);

        inline dma_channel_struct* get(){
            return reinterpret_cast<dma_channel_struct*>(dma1_channel1_base);
        }

        void init_dma_channel();
    }

    namespace dma_status{
        typedef struct{
            volatile uint32_t ISR;
            volatile uint32_t IFCR;
        }dma_status_struct;
    }

    namespace dma_mux{
        typedef struct{
            volatile uint32_t CCR;
        }dma_mux_struct;

        constexpr uint32_t dmamux1_base = (AHB1PERIPH_BASE + 0x0800UL);

        inline dma_mux_struct* get(){
            return reinterpret_cast<dma_mux_struct*>(dmamux1_base);
        }
    }
}