#include "stm32f4g.h"

namespace stm32{

    namespace dma_channel{
        typedef struct{
            volatile uint32_t CCR;
            volatile uint32_t CNDTR;
            volatile uint32_t CPAR;
            volatile uint32_t CMAR;
        }dma_channel_struct;
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
    }
}