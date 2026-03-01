#include "../unity/src/unity.h"
#include "CircularBuffer/circ_buff.h"

void setUp(void) {}
void tearDown(void) {}

void test_peek_on_empty_returns_false(void)
{
    ringBuffer<int> buf;
    int out;
    TEST_ASSERT_FALSE(buf.peek(out));
}

void test_pop_on_empty_returns_false(void)
{
    ringBuffer<int> buf;
    int out;
    TEST_ASSERT_FALSE(buf.pop(out));
}

void test_push_then_peek_returns_correct_value(void)
{
    ringBuffer<int> buf;
    buf.push(42);
    int out;
    TEST_ASSERT_TRUE(buf.peek(out));
    TEST_ASSERT_EQUAL_INT(42, out);
}

void test_peek_does_not_remove_element(void)
{
    ringBuffer<int> buf;
    buf.push(10);
    int a, b;
    buf.peek(a);
    buf.peek(b);
    TEST_ASSERT_EQUAL_INT(a, b);
    TEST_ASSERT_EQUAL_INT(1, buf.size());
}

void test_fifo_order(void)
{
    ringBuffer<int> buf;
    buf.push(1);
    buf.push(2);
    buf.push(3);

    int out;
    buf.pop(out);
    TEST_ASSERT_EQUAL_INT(1, out);
    buf.pop(out);
    TEST_ASSERT_EQUAL_INT(2, out);
    buf.pop(out);
    TEST_ASSERT_EQUAL_INT(3, out);
}

void test_size_tracks_elements(void)
{
    ringBuffer<int> buf;
    TEST_ASSERT_EQUAL_INT(0, buf.size());
    buf.push(1);
    TEST_ASSERT_EQUAL_INT(1, buf.size());
    buf.push(2);
    TEST_ASSERT_EQUAL_INT(2, buf.size());
    int out;
    buf.pop(out);
    TEST_ASSERT_EQUAL_INT(1, buf.size());
}

void test_empty_and_full_flags(void)
{
    ringBuffer<int> buf;
    TEST_ASSERT_TRUE(buf.empty());
    TEST_ASSERT_FALSE(buf.full());

    // fill to capacity (BUFF_SIZE - 1 = 99 elements)
    for (int i = 0; i < 99; i++)
        buf.push(i);

    TEST_ASSERT_FALSE(buf.empty());
    TEST_ASSERT_TRUE(buf.full());
}

void test_overwrite_drops_oldest(void)
{
    ringBuffer<int> buf;

    // fill buffer: push values 0..98 (99 elements, buffer full)
    for (int i = 0; i < 99; i++)
        buf.push(i);

    // push one more — should overwrite oldest (0)
    buf.push(999);

    // oldest should now be 1, not 0
    int out;
    buf.pop(out);
    TEST_ASSERT_EQUAL_INT(1, out);
}

void test_interleaved_push_pop(void)
{
    ringBuffer<int> buf;
    int out;

    buf.push(10);
    buf.push(20);
    buf.pop(out);
    TEST_ASSERT_EQUAL_INT(10, out);

    buf.push(30);
    buf.pop(out);
    TEST_ASSERT_EQUAL_INT(20, out);
    buf.pop(out);
    TEST_ASSERT_EQUAL_INT(30, out);

    TEST_ASSERT_TRUE(buf.empty());
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_peek_on_empty_returns_false);
    RUN_TEST(test_pop_on_empty_returns_false);
    RUN_TEST(test_push_then_peek_returns_correct_value);
    RUN_TEST(test_peek_does_not_remove_element);
    RUN_TEST(test_fifo_order);
    RUN_TEST(test_size_tracks_elements);
    RUN_TEST(test_empty_and_full_flags);
    RUN_TEST(test_overwrite_drops_oldest);
    RUN_TEST(test_interleaved_push_pop);
    return UNITY_END();
}
