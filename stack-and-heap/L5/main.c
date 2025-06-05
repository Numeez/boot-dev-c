#include "../../munit/munit.h"
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include "exercise.h"

bool is_on_stack(void *ptr) {
  void *stack_top = __builtin_frame_address(0);
  uintptr_t stack_top_addr = (uintptr_t)stack_top;
  uintptr_t ptr_addr = (uintptr_t)ptr;
  uintptr_t threshold = 1024 * 1024; // 1MB
  return ptr_addr >= (stack_top_addr - threshold) && ptr_addr <= (stack_top_addr + threshold);
}

// test_basic_greeting
static MunitResult test_basic_greeting(const MunitParameter params[], void* data) {
  (void)params;
  (void)data;

  char *result = get_full_greeting("Hello", "Alice", 20);
  munit_assert_not_null(result);
  munit_assert_string_equal(result, "Hello Alice");
  munit_assert_false(is_on_stack(result));
  free(result);

  return MUNIT_OK;
}

// test_short_buffer
static MunitResult test_short_buffer(const MunitParameter params[], void* data) {
  (void)params;
  (void)data;

  char *result = get_full_greeting("Hey", "Bob", 4);
  munit_assert_not_null(result);
  munit_assert_string_equal(result, "Hey");
  munit_assert_false(is_on_stack(result));
  free(result);

  return MUNIT_OK;
}

// Test array
static MunitTest tests[] = {
  {
    "/test_basic_greeting",  // name
    test_basic_greeting,     // function
    NULL,                    // setup
    NULL,                    // teardown
    MUNIT_TEST_OPTION_NONE,  // options
    NULL                     // parameters
  },
  {
    "/test_short_buffer",
    test_short_buffer,
    NULL,
    NULL,
    MUNIT_TEST_OPTION_NONE,
    NULL
  },
  { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL } // End marker
};

// Test suite
static const MunitSuite suite = {
  "/get_full_greeting",   // name
  tests,                  // tests
  NULL,                   // suites
  1,                      // iterations
  MUNIT_SUITE_OPTION_NONE
};

int main(int argc, char* argv[]) {
  return munit_suite_main(&suite, NULL, argc, argv);
}
