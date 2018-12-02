#include "test_helpers.h"

DEFINE_ENCODE_DECODE_ENCODE_TEST(Int32Test, _0,         (int32_t)          0, {0x00})
DEFINE_ENCODE_DECODE_ENCODE_TEST(Int32Test, _1,         (int32_t)          1, {0x01})
DEFINE_ENCODE_DECODE_ENCODE_TEST(Int32Test, _109,       (int32_t)        109, {0x6d})
DEFINE_ENCODE_DECODE_ENCODE_TEST(Int32Test, _n1,        (int32_t)         -1, {0xff})
DEFINE_ENCODE_DECODE_ENCODE_TEST(Int32Test, _n110,      (int32_t)       -110, {0x92})
DEFINE_ENCODE_DECODE_ENCODE_TEST(Int32Test, _110,       (int32_t)        110, {0x6e, 0x6e, 0x00})
DEFINE_ENCODE_DECODE_ENCODE_TEST(Int32Test, _n111,      (int32_t)       -111, {0x6e, 0x91, 0xff})
DEFINE_ENCODE_DECODE_ENCODE_TEST(Int32Test, _127,       (int32_t)        127, {0x6e, 0x7f, 0x00})
DEFINE_ENCODE_DECODE_ENCODE_TEST(Int32Test, _n128,      (int32_t)       -128, {0x6e, 0x80, 0xff})
DEFINE_ENCODE_DECODE_ENCODE_TEST(Int32Test, _7fff,      (int32_t)     0x7fff, {0x6e, 0xff, 0x7f})
DEFINE_ENCODE_DECODE_ENCODE_TEST(Int32Test, _n8000,     (int32_t)    -0x8000, {0x6e, 0x00, 0x80})
DEFINE_ENCODE_DECODE_ENCODE_TEST(Int32Test, _8000,      (int32_t)     0x8000, {0x6f, 0x00, 0x80, 0x00, 0x00})
DEFINE_ENCODE_DECODE_ENCODE_TEST(Int32Test, _n8001,     (int32_t)    -0x8001, {0x6f, 0xff, 0x7f, 0xff, 0xff})
DEFINE_ENCODE_DECODE_ENCODE_TEST(Int32Test, _7fffffff,  (int32_t) 0x7fffffff, {0x6f, 0xff, 0xff, 0xff, 0x7f})
DEFINE_ENCODE_DECODE_ENCODE_TEST(Int32Test, _n80000000, (int32_t)-0x80000000, {0x6f, 0x00, 0x00, 0x00, 0x80})

DEFINE_ADD_INCOMPLETE_TEST(Int32Test, add_incomplete, 3, 0x100000)
