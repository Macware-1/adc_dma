#include <stdint.h>

extern int main(void);

extern uint32_t _etext;  //end of rom 
extern uint32_t _sdata;  //start of initialized section
extern uint32_t _edata;  //end of initialized section
extern uint32_t _sbss;   //start of uninitialized section
extern uint32_t _ebss;   //end of uninitialized section
extern uint32_t _estack; //stack pointer

void Reset_Handler(void);
void Default_Handler(void);

void NMI_Handler(void)          __attribute__((weak, alias("Default_Handler")));
void HardFault_Handler(void)    __attribute__((weak, alias("Default_Handler")));
void MemManage_Handler(void)    __attribute__((weak, alias("Default_Handler")));
void BusFault_Handler(void)     __attribute__((weak, alias("Default_Handler")));
void UsageFault_Handler(void)   __attribute__((weak, alias("Default_Handler")));
void SVC_Handler(void)          __attribute__((weak, alias("Default_Handler")));
void DebugMon_Handler(void)     __attribute__((weak, alias("Default_Handler")));
void PendSV_Handler(void)       __attribute__((weak, alias("Default_Handler")));
void SysTick_Handler(void)      __attribute__((weak, alias("Default_Handler")));

// Vector table
__attribute__((section(".vector_table")))
const void *vector_table[] = {
    (void *)&_estack,
    Reset_Handler,
    NMI_Handler,
    HardFault_Handler,
    MemManage_Handler,
    BusFault_Handler,
    UsageFault_Handler,
    0, 0, 0, 0,  // Reserved
    SVC_Handler,
    DebugMon_Handler,
    0,
    PendSV_Handler,
    SysTick_Handler
};

void Reset_Handler(void)
{
    uint32_t *src = &_etext;
    uint32_t *dst = &_sdata;
    while (dst < &_edata) {   //copy from flash to ram
        *dst++ = *src++;
    }

    dst = &_sbss;
    while (dst < &_ebss) {  //make bss as zero
        *dst++ = 0;
    }

    main();     //go to app
    while (1);  // not called just for handling error
}

void Default_Handler(void)
{
    while (1);
}
