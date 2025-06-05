#include <stdio.h>
#include "exercise.h"
#include "../../munit/munit.h"

// Test case: formats an integer
static MunitResult test_formats_int1(const MunitParameter params[], void* data) {
  (void)params; (void)data;

  char buffer[100];
  snek_object_t i = new_integer(5);
  format_object(i, buffer);

  munit_assert_string_equal("int:5", buffer);
  return MUNIT_OK;
}

// Test case: formats a string
static MunitResult test_formats_string1(const MunitParameter params[], void* data) {
  (void)params; (void)data;

  char buffer[100];
  snek_object_t s = new_string("Hello!");
  format_object(s, buffer);

  munit_assert_string_equal("string:Hello!", buffer);
  return MUNIT_OK;
}

// Additional integer test
static MunitResult test_formats_int2(const MunitParameter params[], void* data) {
  (void)params; (void)data;

  char buffer[100];
  snek_object_t i = new_integer(2014);
  format_object(i, buffer);

  munit_assert_string_equal("int:2014", buffer);
  return MUNIT_OK;
}

// Additional string test
static MunitResult test_formats_string2(const MunitParameter params[], void* data) {
  (void)params; (void)data;

  char buffer[100];
  snek_object_t s = new_string("nvim btw");
  format_object(s, buffer);

  munit_assert_string_equal("string:nvim btw", buffer);
  return MUNIT_OK;
}

// Register test cases
static MunitTest tests[] = {
  { "/integer/5", test_formats_int1, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
  { "/string/hello", test_formats_string1, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
  { "/integer/2014", test_formats_int2, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
  { "/string/nvim", test_formats_string2, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
  { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL } // Terminator
};

// Define the test suite
static const MunitSuite suite = {
  "/format",    // Suite name
  tests,        // Test cases
  NULL,         // No sub-suites
  1,            // Number of iterations
  MUNIT_SUITE_OPTION_NONE
};

int main(int argc, char* argv[]) {
  return munit_suite_main(&suite, NULL, argc, argv);
}
