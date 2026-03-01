#include "circ_buff.h"

#include <iostream>

void taskOneMain(void)
{
    ringBuffer<int> buff;

    buff.push(50);
    buff.push(51);
    int res;
    buff.peek(res);
    std::cout << res;
}
