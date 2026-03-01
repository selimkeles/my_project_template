#ifndef BITMANIPULATOR
#define BITMANIPULATOR
#include <cstdint>

void taskTwoMain(void);

class bitman
{
  public:
    uint32_t setBit(uint32_t reg, int pos);
    uint32_t clearBit(uint32_t reg, int pos);
    uint32_t toggleBit(uint32_t reg, int pos);
    bool testBit(uint32_t reg, int pos);
    uint32_t setBitfield(uint32_t reg, int start, int width, uint32_t val);
    uint32_t getBitfield(uint32_t reg, int start, int width);
};
#endif
