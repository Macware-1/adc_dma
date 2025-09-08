#include <stdint.h>

namespace utils{

    inline void set_bit(volatile uint32_t &reg, uint32_t pos){
        reg |= (0x1UL << pos);
    }

    inline void clear_bit(volatile uint32_t &reg, uint32_t pos){
        reg &= ~(0x1UL << pos);
    }

    inline void set_reg(volatile uint32_t &reg, uint32_t val, uint32_t pos){
        reg |= (val << pos);
    }

    inline void clear_reg(volatile uint32_t &reg, uint32_t val, uint32_t pos){
        reg &= ~(val << pos);
    }

    inline void write_reg(volatile uint32_t &reg, uint32_t val, uint32_t pos, uint32_t width) {
        uint32_t mask = ((1U << width) - 1U) << pos;
        reg &= ~mask;
        reg |= ( (val << pos) & mask );
    }

    inline bool is_bit_set(volatile uint32_t &reg, uint32_t pos){
        return ((reg & (0x1UL << pos)) == (0x1UL << pos));
    }
}