#include "unity.h"

void setUp(void)   {}
void tearDown(void) {}

void test_all_passed(void)
{
    TEST_ASSERT_EQUAL_INT(2, 1 + 1);
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_all_passed);
    return UNITY_END();
}