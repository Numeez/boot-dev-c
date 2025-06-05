#include "../../munit/munit.h"
#include "exercise.h"  // Make sure this defines snek_type_t and your types

// ----------------- Test Cases -----------------

static MunitResult test_zero_out_integer(const MunitParameter params[], void* data) {
    snek_int_t integer;
    integer.value = 42;

    snek_zero_out(&integer, INTEGER);

    munit_assert_int(integer.value, ==, 0);
    return MUNIT_OK;
}

static MunitResult test_zero_out_float(const MunitParameter params[], void* data) {
    snek_float_t float_num;
    float_num.value = 3.14f;

    snek_zero_out(&float_num, FLOAT);

    munit_assert_double((double)float_num.value, ==, 0.0);  // cast to double
    return MUNIT_OK;
}

static MunitResult test_zero_out_bool(const MunitParameter params[], void* data) {
    snek_bool_t boolean;
    boolean.value = 1;

    snek_zero_out(&boolean, BOOL);

    munit_assert_int(boolean.value, ==, 0);
    return MUNIT_OK;
}

static MunitResult test_zero_out_nonzero_values(const MunitParameter params[], void* data) {
    snek_int_t integer = { .value = -100 };
    snek_float_t float_num = { .value = -99.99f };
    snek_bool_t boolean = { .value = 255 };

    snek_zero_out(&integer, INTEGER);
    snek_zero_out(&float_num, FLOAT);
    snek_zero_out(&boolean, BOOL);

    munit_assert_int(integer.value, ==, 0);
    munit_assert_double((double)float_num.value, ==, 0.0);
    munit_assert_int(boolean.value, ==, 0);

    return MUNIT_OK;
}

// ----------------- Test Suite -----------------

static MunitTest tests[] = {
    { "/zero_out/integer", test_zero_out_integer, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/zero_out/float", test_zero_out_float, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/zero_out/bool", test_zero_out_bool, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/zero_out/nonzero", test_zero_out_nonzero_values, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

static const MunitSuite suite = {
    "/snek_zero_out", tests, NULL, 1, MUNIT_SUITE_OPTION_NONE
};

// ----------------- Main -----------------

int main(int argc, char* argv[]) {
    return munit_suite_main(&suite, NULL, argc, argv);
}
