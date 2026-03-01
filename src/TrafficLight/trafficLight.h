#ifndef TRAFFICLIGHT_H
#define TRAFFICLIGHT_H

#include <cstdint>

void taskThreeMain(void);

class TrafficLights
{
  public:
    enum class State : uint8_t
    {
        RED,
        GREEN,
        YELLOW
    };
    typedef void (*onEnter)(State state);

    TrafficLights(onEnter cb) : CB(cb), state(State::RED), time(0), enterTime(0)
    {
        CB(state);
    }

    void tick(uint16_t elapsed);
    State getState();
    void FSM(void);

  private:
    onEnter CB;
    State state;
    uint64_t time;
    uint64_t enterTime;

    void setState(State new_state);
    void setEnterTime();
    uint64_t getTime();
    uint64_t getEnterTime();
    uint64_t calcElapsedTime();
};

#endif    // TRAFFICLIGHT_H
