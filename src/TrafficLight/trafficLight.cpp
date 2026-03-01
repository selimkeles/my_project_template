#include "trafficLight.h"

#include <iostream>

void callBack(TrafficLights::State state)
{
    if (state == TrafficLights::State::RED)
    {
        std::cout << "Entering RED\n";
    }
    else if (state == TrafficLights::State::YELLOW)
    {
        std::cout << "Entering YELLOW\n";
    }
    else
    {
        std::cout << "Entering GREEN\n";
    }
}

void taskThreeMain(void)
{
    TrafficLights tl(&callBack);
    tl.FSM();
}

void TrafficLights::FSM(void)
{
    while (1)
    {
        tick(100);
    }
}

void TrafficLights::tick(uint16_t elapsed)
{
    time += elapsed;

    switch (state)
    {
        case State::RED:
            if (calcElapsedTime() > 5000)
            {
                setState(State::GREEN);
            }
            break;
        case State::YELLOW:
            if (calcElapsedTime() > 500)
            {
                setState(State::RED);
            }
            break;
        case State::GREEN:
            if (calcElapsedTime() > 4000)
            {
                setState(State::YELLOW);
            }
            break;
    }
}

void TrafficLights::setState(State new_state)
{
    state = new_state;
    setEnterTime();
    CB(new_state);
}

TrafficLights::State TrafficLights::getState()
{
    return state;
}

uint64_t TrafficLights::getTime()
{
    return time;
}

uint64_t TrafficLights::calcElapsedTime()
{
    return getTime() - getEnterTime();
}

void TrafficLights::setEnterTime()
{
    enterTime = getTime();
}

uint64_t TrafficLights::getEnterTime()
{
    return enterTime;
}
