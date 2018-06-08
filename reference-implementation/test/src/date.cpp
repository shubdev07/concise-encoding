#include "test_helpers.h"


inline void expect_memory_after_add_date(const cbe_date* const date, std::vector<uint8_t> const& expected_memory)
{
    expect_memory_after_operation([&](cbe_buffer* buffer)
    {
        return cbe_add_date(buffer, date);
    }, expected_memory);
}

#define DEFINE_ADD_DATE_TEST(YEAR, MONTH, DAY, HOUR, MINUTE, SECOND, USEC, ...) \
TEST(DateTest, date_ ## YEAR ## _ ## MONTH ## _ ## DAY ## _ ## HOUR ## _ ## MINUTE ## _ ## SECOND ## _ ## USEC) \
{ \
    cbe_date date = \
    { \
        .year = YEAR, \
        .month = MONTH, \
        .day = DAY, \
        .hour = HOUR, \
        .minute = MINUTE, \
        .second = SECOND, \
        .microsecond = USEC \
    }; \
    std::vector<uint8_t> expected_memory = __VA_ARGS__; \
    expect_memory_after_add_date(&date, expected_memory); \
    expect_decode_encode(expected_memory); \
}

#define DEFINE_FAILED_ADD_DATE_TEST(SIZE, YEAR, MONTH, DAY, HOUR, MINUTE, SECOND, USEC) \
TEST(DateTest, failed_date_ ## YEAR ## _ ## MONTH ## _ ## DAY ## _ ## HOUR ## _ ## MINUTE ## _ ## SECOND ## _ ## USEC) \
{ \
    cbe_date date = \
    { \
        .year = YEAR, \
        .month = MONTH, \
        .day = DAY, \
        .hour = HOUR, \
        .minute = MINUTE, \
        .second = SECOND, \
        .microsecond = USEC \
    }; \
    expect_failed_operation_decrementing(SIZE, [&](cbe_buffer* buffer) \
    { \
        return cbe_add_date(buffer, &date); \
    }); \
}

DEFINE_ADD_DATE_TEST(1955, 11, 5, 8, 21, 0, 0, {0x69, 0x21, 0x34, 0x57, 0xe1, 0x0e})
DEFINE_ADD_DATE_TEST(2015, 10, 21, 14, 28, 9, 714000, {0x6a, 0x12, 0x55, 0xa3, 0x6b, 0xe8, 0x3b})
DEFINE_ADD_DATE_TEST(1985, 10, 26, 8, 22, 16, 900142, {0x6b, 0xae, 0xa3, 0x95, 0xf2, 0xb2, 0x88, 0xe6, 0x00})

DEFINE_FAILED_ADD_DATE_TEST(4, 1955, 11, 5, 8, 21, 0, 0)
DEFINE_FAILED_ADD_DATE_TEST(5, 2015, 10, 21, 14, 28, 9, 714000)
DEFINE_FAILED_ADD_DATE_TEST(7, 1985, 10, 26, 8, 22, 16, 900142)