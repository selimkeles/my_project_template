#include "../unity/src/unity.h"
#include "TrafficLight/trafficLight.h"

static TrafficLights::State lastEnteredState;
static int callbackCount;

static void testCallback(TrafficLights::State state)
{
    lastEnteredState = state;
    callbackCount++;
}

void setUp(void)
{
    lastEnteredState = TrafficLights::State::RED;
    callbackCount = 0;
}

void tearDown(void)
{
}

void test_initial_state_is_red(void)
{
    TrafficLights tl(testCallback);
    TEST_ASSERT_EQUAL_INT((int)TrafficLights::State::RED, (int)tl.getState());
}

void test_callback_fired_on_construction(void)
{
    TrafficLights tl(testCallback);
    TEST_ASSERT_EQUAL_INT(1, callbackCount);
    TEST_ASSERT_EQUAL_INT((int)TrafficLights::State::RED, (int)lastEnteredState);
}

void test_stays_red_before_threshold(void)
{
    TrafficLights tl(testCallback);
    tl.tick(4999);
    TEST_ASSERT_EQUAL_INT((int)TrafficLights::State::RED, (int)tl.getState());
}

void test_red_to_green_at_threshold(void)
{
    TrafficLights tl(testCallback);
    tl.tick(5001);
    TEST_ASSERT_EQUAL_INT((int)TrafficLights::State::GREEN, (int)tl.getState());
}

void test_green_to_yellow_at_threshold(void)
{
    TrafficLights tl(testCallback);
    tl.tick(5001);    // RED → GREEN
    tl.tick(4001);    // GREEN → YELLOW
    TEST_ASSERT_EQUAL_INT((int)TrafficLights::State::YELLOW, (int)tl.getState());
}

void test_yellow_to_red_at_threshold(void)
{
    TrafficLights tl(testCallback);
    tl.tick(5001);    // RED → GREEN
    tl.tick(4001);    // GREEN → YELLOW
    tl.tick(501);     // YELLOW → RED
    TEST_ASSERT_EQUAL_INT((int)TrafficLights::State::RED, (int)tl.getState());
}

void test_callback_fired_on_each_transition(void)
{
    TrafficLights tl(testCallback);    // fires once (RED)
    tl.tick(5001);                     // fires once (GREEN)
    tl.tick(4001);                     // fires once (YELLOW)
    tl.tick(501);                      // fires once (RED)
    TEST_ASSERT_EQUAL_INT(4, callbackCount);
}

void test_stays_green_before_threshold(void)
{
    TrafficLights tl(testCallback);
    tl.tick(5001);    // RED → GREEN
    tl.tick(3999);    // still GREEN
    TEST_ASSERT_EQUAL_INT((int)TrafficLights::State::GREEN, (int)tl.getState());
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_initial_state_is_red);
    RUN_TEST(test_callback_fired_on_construction);
    RUN_TEST(test_stays_red_before_threshold);
    RUN_TEST(test_red_to_green_at_threshold);
    RUN_TEST(test_green_to_yellow_at_threshold);
    RUN_TEST(test_yellow_to_red_at_threshold);
    RUN_TEST(test_callback_fired_on_each_transition);
    RUN_TEST(test_stays_green_before_threshold);
    return UNITY_END();
}
