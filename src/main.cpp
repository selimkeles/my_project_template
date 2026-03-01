#include "BitManipulator/bitManipulator.h"
#include "CircularBuffer/circ_buff.h"
#include "TrafficLight/trafficLight.h"
#include "externcdeneme/externc.h"

#include <iostream>

#ifdef __cplusplus
extern "C"
{
#endif

    int sub(int a, int b);

#ifdef __cplusplus
}
#endif

int main()
{
    // taskOneMain();
    // taskTwoMain();
    // taskThreeMain();
    // int res = add(3, 5);
    int res = sub(5, 3);

    std::cout << res;
    return 0;
}

int sub(int a, int b)
{
    return a - b;
}
