#include "test_helpers.h"


static int g_days_to_the_month[] =
{
    0, // Nothing
    0, // January
    31, // February
    31 + 28, // March
    31 + 28 + 31, // April
    31 + 28 + 31 + 30, // May
    31 + 28 + 31 + 30 + 31, // June
    31 + 28 + 31 + 30 + 31 + 30, // July
    31 + 28 + 31 + 30 + 31 + 30 + 31, // August
    31 + 28 + 31 + 30 + 31 + 30 + 31 + 31, // September
    31 + 28 + 31 + 30 + 31 + 30 + 31 + 31 + 30, // October
    31 + 28 + 31 + 30 + 31 + 30 + 31 + 31 + 30 + 31, // November
    31 + 28 + 31 + 30 + 31 + 30 + 31 + 31 + 30 + 31 + 30, // December
};

static inline int is_leap_year(int year)
{
    return (year % 4 == 0) && (year % 100 != 0 || year % 400 == 0);
}

static inline unsigned int to_doy(int year, unsigned int month, unsigned int day)
{
    // Extremely naive converter, only good for modern dates.
    unsigned int days = g_days_to_the_month[month] + day;
    if(is_leap_year(year))
    {
        days++;
    }
    return days;
}

inline void expect_memory_after_add_time(const int64_t time, std::vector<uint8_t> const& expected_memory)
{
    expect_memory_after_operation([&](struct cbe_encode_process* encode_process)
    {
        return cbe_encode_add_time(encode_process, time);
    }, expected_memory);
}

#define DEFINE_ADD_TIME_TEST(YEAR, MONTH, DAY, HOUR, MINUTE, SECOND, USEC, ...) \
TEST(TimeTest, time_ ## YEAR ## _ ## MONTH ## _ ## DAY ## _ ## HOUR ## _ ## MINUTE ## _ ## SECOND ## _ ## USEC) \
{ \
    int64_t time = smalltime_new(YEAR, to_doy(YEAR, MONTH, DAY), HOUR, MINUTE, SECOND, USEC); \
    std::vector<uint8_t> expected_memory = __VA_ARGS__; \
    expect_memory_after_add_time(time, expected_memory); \
    expect_decode_encode(expected_memory); \
}

#define DEFINE_ADD_TIME_INCOMPLETE_TEST(SIZE, YEAR, MONTH, DAY, HOUR, MINUTE, SECOND, USEC) \
TEST(TimeTest, incomplete_time_ ## YEAR ## _ ## MONTH ## _ ## DAY ## _ ## HOUR ## _ ## MINUTE ## _ ## SECOND ## _ ## USEC) \
{ \
    int64_t time = smalltime_new(YEAR, to_doy(YEAR, MONTH, DAY), HOUR, MINUTE, SECOND, USEC); \
    expect_incomplete_operation_decrementing(SIZE, [&](struct cbe_encode_process* encode_process) \
    { \
        return cbe_encode_add_time(encode_process, time); \
    }); \
}

DEFINE_ADD_TIME_TEST(1955, 11,  5,  8, 21,  0,      0, {0x78, 0x00, 0x00, 0x00, 0x54, 0xa8, 0xe6, 0xe8, 0x01})
DEFINE_ADD_TIME_TEST(2015, 10, 21, 14, 28,  9, 714000, {0x78, 0x10, 0xe5, 0x9a, 0x70, 0xce, 0xe4, 0xf7, 0x01})
DEFINE_ADD_TIME_TEST(1985, 10, 26,  8, 22, 16, 900142, {0x78, 0x2e, 0xbc, 0x0d, 0x59, 0x68, 0x65, 0xf0, 0x01})

DEFINE_ADD_TIME_INCOMPLETE_TEST(4, 1955, 11, 5, 8, 21, 0, 0)
DEFINE_ADD_TIME_INCOMPLETE_TEST(5, 2015, 10, 21, 14, 28, 9, 714000)
DEFINE_ADD_TIME_INCOMPLETE_TEST(7, 1985, 10, 26, 8, 22, 16, 900142)
