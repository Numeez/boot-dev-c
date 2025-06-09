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

// === TEST CASES ===

static MunitResult create_stack_small(const MunitParameter params[], void* data) {
    snek_stack_t *s = stack_new(3);
    assert(s != NULL);
    assert(s->capacity == 3);
    assert(s->count == 0);
    assert(s->data != NULL);
    free_stack(s);
    return MUNIT_OK;
}

static MunitResult create_stack_large(const MunitParameter params[], void* data) {
    snek_stack_t *s = stack_new(1000);
    assert(s != NULL);
    assert(s->capacity == 1000);
    assert(s->count == 0);
    assert(s->data != NULL);
    free_stack(s);
    return MUNIT_OK;
}

static MunitResult create_stack_zero_capacity(const MunitParameter params[], void* data) {
    snek_stack_t *s = stack_new(0);
    assert(s != NULL);
    assert(s->capacity == 0);
    assert(s->count == 0);
    // Depending on your implementation, data could be NULL or non-NULL
    free_stack(s);
    return MUNIT_OK;
}

// === MAIN TEST SUITE ===

static MunitTest tests[] = {
    { "/create_stack_small", create_stack_small, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/create_stack_large", create_stack_large, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/create_stack_zero_capacity", create_stack_zero_capacity, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

static const MunitSuite suite = {
    .prefix = "snekstack/",
    .tests = tests,
    .suites = NULL,
    .iterations = 1,
    .options = MUNIT_SUITE_OPTION_NONE
};

int main(int argc, char* argv[]) {
    return munit_suite_main(&suite, NULL, argc, argv);
}
