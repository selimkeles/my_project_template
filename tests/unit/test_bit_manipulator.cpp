#include "../unity/src/unity.h"
#include "BitManipulator/bitManipulator.h"

static bitman bm;

void setUp(void) {}
void tearDown(void) {}

void test_set_bit(void)
{
    TEST_ASSERT_EQUAL_UINT32(0x00000008, bm.setBit(0x00000000, 3));
    TEST_ASSERT_EQUAL_UINT32(0x000000FF, bm.setBit(0x0000007F, 7));
}

void test_clear_bit(void)
{
    TEST_ASSERT_EQUAL_UINT32(0xFFFFFFF7, bm.clearBit(0xFFFFFFFF, 3));
    TEST_ASSERT_EQUAL_UINT32(0x00000000, bm.clearBit(0x00000001, 0));
}

void test_toggle_bit(void)
{
    TEST_ASSERT_EQUAL_UINT32(0x00000008, bm.toggleBit(0x00000000, 3));
    TEST_ASSERT_EQUAL_UINT32(0x00000000, bm.toggleBit(0x00000008, 3));
}

void test_test_bit_true(void)
{
    TEST_ASSERT_TRUE(bm.testBit(0x00000008, 3));
    TEST_ASSERT_TRUE(bm.testBit(0xFFFFFFFF, 0));
}

void test_test_bit_false(void)
{
    TEST_ASSERT_FALSE(bm.testBit(0x00000000, 3));
    TEST_ASSERT_FALSE(bm.testBit(0xFFFFFFF7, 3));
}

void test_set_bitfield(void)
{
    // place value 5 (0b101) into bits [4:6] of 0x00
    TEST_ASSERT_EQUAL_UINT32(0x00000050, bm.setBitfield(0x00000000, 4, 3, 5));
}

void test_set_bitfield_no_side_effects(void)
{
    // bits outside [4:6] must be preserved
    uint32_t result = bm.setBitfield(0xFFFFFF0F, 4, 3, 5);
    TEST_ASSERT_EQUAL_UINT32(0xFFFFFF5F, result);
}

void test_get_bitfield(void)
{
    TEST_ASSERT_EQUAL_UINT32(5, bm.getBitfield(0x00000050, 4, 3));
    TEST_ASSERT_EQUAL_UINT32(7, bm.getBitfield(0x0000007F, 2, 3));
}

void test_set_get_bitfield_roundtrip(void)
{
    uint32_t reg = bm.setBitfield(0x00000000, 8, 4, 13);
    TEST_ASSERT_EQUAL_UINT32(13, bm.getBitfield(reg, 8, 4));
}

void test_out_of_range_returns_zero(void)
{
    TEST_ASSERT_EQUAL_UINT32(0, bm.setBitfield(0xFFFFFFFF, 30, 4, 0xF));
    TEST_ASSERT_EQUAL_UINT32(0, bm.getBitfield(0xFFFFFFFF, 30, 4));
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_set_bit);
    RUN_TEST(test_clear_bit);
    RUN_TEST(test_toggle_bit);
    RUN_TEST(test_test_bit_true);
    RUN_TEST(test_test_bit_false);
    RUN_TEST(test_set_bitfield);
    RUN_TEST(test_set_bitfield_no_side_effects);
    RUN_TEST(test_get_bitfield);
    RUN_TEST(test_set_get_bitfield_roundtrip);
    RUN_TEST(test_out_of_range_returns_zero);
    return UNITY_END();
}
