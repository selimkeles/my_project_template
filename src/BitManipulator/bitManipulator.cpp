#include "bitManipulator.h"

#include <cstdint>
#include <iostream>

void taskTwoMain(void)
{
    uint32_t test = 127;
    bitman bitman;
    uint32_t res = bitman.getBitfield(test, 2, 3);
    std::cout << res;
}

uint32_t bitman::setBit(uint32_t reg, int pos)
{
    return (reg | (1 << pos));
}

uint32_t bitman::clearBit(uint32_t reg, int pos)
{
    return (reg & ~(1 << pos));
}

uint32_t bitman::toggleBit(uint32_t reg, int pos)
{
    return (reg ^ (1 << pos));
}

bool bitman::testBit(uint32_t reg, int pos)
{
    return (reg & (1 << pos));
}

uint32_t bitman::setBitfield(uint32_t reg, int start, int width, uint32_t val)
{
    if (start + width > 32)
    {
        return 0;
    }
    uint32_t mask = ((1u << width) - 1) << start;
    return (reg & ~mask) | ((val << start) & mask);
}

uint32_t bitman::getBitfield(uint32_t reg, int start, int width)
{
    if (start + width > 32)
    {
        return 0;
    }
    return (reg >> start) & ((1u << width) - 1);
}
