#include <stdlib.h>
#include <assert.h>
#include "../../munit/munit.h"
#include "snekstack.h"

// Helper to free stack
void free_stack(snek_stack_t *stack) {
    stack_free(stack);
}

// Test stack creation
static MunitResult test_stack_new(const MunitParameter params[], void *data) {
    snek_stack_t *stack = stack_new(2);
    munit_assert_not_null(stack);
    munit_assert_size(stack->capacity, ==, 2);
    munit_assert_size(stack->count, ==, 0);
    munit_assert_not_null(stack->data);

    free_stack(stack);
    return MUNIT_OK;
}

// Test pushing and popping a single item
static MunitResult test_push_pop_single(const MunitParameter params[], void *data) {
    snek_stack_t *stack = stack_new(1);
    int x = 10;

    stack_push(stack, &x);
    munit_assert_size(stack->count, ==, 1);

    void *popped = stack_pop(stack);
    munit_assert_ptr_equal(popped, &x);
    munit_assert_size(stack->count, ==, 0);

    free_stack(stack);
    return MUNIT_OK;
}

// Test popping from empty stack returns NULL
static MunitResult test_pop_empty(const MunitParameter params[], void *data) {
    snek_stack_t *stack = stack_new(2);

    void *popped = stack_pop(stack);
    munit_assert_ptr_null(popped);
    munit_assert_size(stack->count, ==, 0);

    free_stack(stack);
    return MUNIT_OK;
}

// Test pushing more elements than capacity triggers resize and preserves data
static MunitResult test_push_resize(const MunitParameter params[], void *data) {
    snek_stack_t *stack = stack_new(2);
    int vals[3] = {1, 2, 3};

    stack_push(stack, &vals[0]);
    stack_push(stack, &vals[1]);
    // This push should trigger resize
    stack_push(stack, &vals[2]);

    munit_assert_size(stack->capacity, >=, 3);
    munit_assert_size(stack->count, ==, 3);

    void *popped = stack_pop(stack);
    munit_assert_ptr_equal(popped, &vals[2]);
    popped = stack_pop(stack);
    munit_assert_ptr_equal(popped, &vals[1]);
    popped = stack_pop(stack);
    munit_assert_ptr_equal(popped, &vals[0]);
    munit_assert_size(stack->count, ==, 0);

    free_stack(stack);
    return MUNIT_OK;
}

// Test stack_free on NULL stack does nothing (no crash)
static MunitResult test_free_null_stack(const MunitParameter params[], void *data) {
    stack_free(NULL); // Should not crash or segfault
    return MUNIT_OK;
}

static MunitTest tests[] = {
    { "/new", test_stack_new, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/push_pop_single", test_push_pop_single, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/pop_empty", test_pop_empty, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/push_resize", test_push_resize, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/free_null", test_free_null_stack, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

static const MunitSuite suite = {
    .prefix = "snekstack/",
    .tests = tests,
    .suites = NULL,
    .iterations = 1,
    .options = MUNIT_SUITE_OPTION_NONE,
};

int main(int argc, char *argv[]) {
    return munit_suite_main(&suite, NULL, argc, argv);
}
