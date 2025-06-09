#include <stdlib.h>
#include <assert.h>
#include "../../munit/munit.h"
#include "snekstack.h"

// Helper function to free the stack
void free_stack(snek_stack_t *stack) {
    if (stack) {
        free(stack->data);
        free(stack);
    }
}

// Test pushing then popping one element
static MunitResult test_push_pop_single(const MunitParameter params[], void *data) {
    snek_stack_t *stack = stack_new(1);
    int x = 42;

    stack_push(stack, &x);
    assert(stack->count == 1);

    void *val = stack_pop(stack);
    assert(val == &x);
    assert(stack->count == 0);

    free_stack(stack);
    return MUNIT_OK;
}

// Test popping from empty stack returns NULL
static MunitResult test_pop_empty(const MunitParameter params[], void *data) {
    snek_stack_t *stack = stack_new(2);

    void *val = stack_pop(stack);
    assert(val == NULL);
    assert(stack->count == 0);

    free_stack(stack);
    return MUNIT_OK;
}

// Test popping from NULL stack returns NULL
static MunitResult test_pop_null_stack(const MunitParameter params[], void *data) {
    void *val = stack_pop(NULL);
    assert(val == NULL);
    return MUNIT_OK;
}

// Test pushing multiple items and popping them in LIFO order
static MunitResult test_push_pop_multiple(const MunitParameter params[], void *data) {
    snek_stack_t *stack = stack_new(2);
    int a = 1, b = 2, c = 3;

    stack_push(stack, &a);
    stack_push(stack, &b);
    stack_push(stack, &c);  // triggers realloc, if implemented

    assert(stack->count == 3);

    void *val = stack_pop(stack);
    assert(val == &c);
    val = stack_pop(stack);
    assert(val == &b);
    val = stack_pop(stack);
    assert(val == &a);
    assert(stack->count == 0);

    free_stack(stack);
    return MUNIT_OK;
}

static MunitTest tests[] = {
    { "/push_pop_single", test_push_pop_single, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/pop_empty", test_pop_empty, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/pop_null_stack", test_pop_null_stack, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/push_pop_multiple", test_push_pop_multiple, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
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
