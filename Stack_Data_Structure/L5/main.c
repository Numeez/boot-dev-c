#include <stdlib.h>
#include <stdint.h>
#include "../../munit/munit.h"
#include "snekstack.h"
#include "exercise.h"  // make sure scary_double_push is declared here

// Test scary_double_push behavior
static MunitResult test_scary_double_push(const MunitParameter params[], void *data) {
    snek_stack_t *stack = stack_new(2);

    scary_double_push(stack);  // Pushes 1337 and 1024
    munit_assert_size(stack->count, ==, 2);

    // Top should be 1024
    void *top = stack_pop(stack);
    int val = *((int *)top);
    munit_assert_int(val, ==, 1024);
    free(top); // dynamically allocated

    // Next should be 1337
    top = stack_pop(stack);
    munit_assert_ptr_equal(top, (void *)1337);

    munit_assert_size(stack->count, ==, 0);
    stack_free(stack);
    return MUNIT_OK;
}

// Declare the test array
static MunitTest scary_tests[] = {
    {
        "/scary_double_push",     // Test path
        test_scary_double_push,   // Test function
        NULL,                     // Setup
        NULL,                     // Tear down
        MUNIT_TEST_OPTION_NONE,   // Options
        NULL                      // Parameters
    },
    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }  // Null terminator
};

// Main function to run the suite
int main(int argc, char* argv[]) {
    MunitSuite suite = {
        .prefix = "/snekstack",
        .tests = scary_tests,
        .suites = NULL,
        .iterations = 1,
        .options = MUNIT_SUITE_OPTION_NONE
    };

    return munit_suite_main(&suite, NULL, argc, argv);
}
