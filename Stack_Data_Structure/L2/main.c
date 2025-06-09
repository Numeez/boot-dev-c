#include <stdlib.h>
#include <assert.h>
#include "../../munit/munit.h"
#include "snekstack.h"

// Helper
void free_stack(snek_stack_t *s) {
    if (s) {
        free(s->data);
        free(s);
    }
}

// Test 1: Push single element
static MunitResult test_push_single(const MunitParameter params[], void *data) {
    snek_stack_t *s = stack_new(1);
    int x = 42;
    stack_push(s, &x);

    assert(s->count == 1);
    assert(*(int *)(s->data[0]) == 42);

    free_stack(s);
    return MUNIT_OK;
}

// Test 2: Push multiple elements within capacity
static MunitResult test_push_multiple_within_capacity(const MunitParameter params[], void *data) {
    snek_stack_t *s = stack_new(3);
    int a = 1, b = 2, c = 3;

    stack_push(s, &a);
    stack_push(s, &b);
    stack_push(s, &c);

    assert(s->count == 3);
    assert(*(int *)(s->data[0]) == 1);
    assert(*(int *)(s->data[1]) == 2);
    assert(*(int *)(s->data[2]) == 3);

    free_stack(s);
    return MUNIT_OK;
}

// Test 3: Push beyond initial capacity (test resizing)
static MunitResult test_push_resize(const MunitParameter params[], void *data) {
    snek_stack_t *s = stack_new(2);
    int a = 10, b = 20, c = 30;

    stack_push(s, &a);
    stack_push(s, &b);
    stack_push(s, &c); // should trigger realloc

    assert(s->count == 3);
    assert(s->capacity >= 3);
    assert(*(int *)(s->data[0]) == 10);
    assert(*(int *)(s->data[1]) == 20);
    assert(*(int *)(s->data[2]) == 30);

    free_stack(s);
    return MUNIT_OK;
}

// Register tests
static MunitTest tests[] = {
    { "/stack_push_single", test_push_single, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/stack_push_multiple_within_capacity", test_push_multiple_within_capacity, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/stack_push_resize", test_push_resize, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

static const MunitSuite suite = {
    .prefix = "snekstack/",
    .tests = tests,
    .suites = NULL,
    .iterations = 1,
    .options = MUNIT_SUITE_OPTION_NONE,
};

int main(int argc, char* argv[]) {
    return munit_suite_main(&suite, NULL, argc, argv);
}
