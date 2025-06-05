#include "../../munit/munit.h"
#include <stdlib.h>
#include "exercise.h" // must define: int* allocate_scalar_array(int size, int multiplier);

// Test 1: Return value should not be NULL
static MunitResult test_allocate_scalar_array_size(const MunitParameter params[], void* data) {
  (void)params;
  (void)data;

  int size = 5;
  int multiplier = 2;
  int *result = allocate_scalar_array(size, multiplier);

  munit_assert_not_null(result);

  free(result);
  return MUNIT_OK;
}

// Test 2: Returned array values must match expected
static MunitResult test_allocate_scalar_array_values(const MunitParameter params[], void* data) {
  (void)params;
  (void)data;

  int size = 5;
  int multiplier = 2;
  int *result = allocate_scalar_array(size, multiplier);

  int expected[] = {0, 2, 4, 6, 8};

  for (int i = 0; i < size; i++) {
    munit_assert_int(result[i], ==, expected[i]);
  }

  free(result);
  return MUNIT_OK;
}

// Test 3: All elements should be 0 if multiplier is 0
static MunitResult test_allocate_scalar_array_zero_multiplier(const MunitParameter params[], void* data) {
  (void)params;
  (void)data;

  int size = 3;
  int multiplier = 0;
  int *result = allocate_scalar_array(size, multiplier);

  for (int i = 0; i < size; i++) {
    munit_assert_int(result[i], ==, 0);
  }

  free(result);
  return MUNIT_OK;
}

// Test 4: Very large allocation should return NULL
static MunitResult test_allocate_too_much(const MunitParameter params[], void* data) {
  (void)params;
  (void)data;

  int size = 1024 * 1024 * 100; // 100 million ints
  int multiplier = 1;

  int *result = allocate_scalar_array(size, multiplier);
  munit_assert_null(result);

  return MUNIT_OK;
}

// Register the test cases
static MunitTest tests[] = {
  { "/test_allocate_scalar_array_size", test_allocate_scalar_array_size, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
  { "/test_allocate_scalar_array_values", test_allocate_scalar_array_values, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
  { "/test_allocate_scalar_array_zero_multiplier", test_allocate_scalar_array_zero_multiplier, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
  { "/test_allocate_too_much", test_allocate_too_much, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
  { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

// Define the test suite
static const MunitSuite suite = {
  "/allocate_scalar_array",  // Suite name
  tests,                     // Test list
  NULL,                      // No nested suites
  1,                         // Iterations
  MUNIT_SUITE_OPTION_NONE
};

// Main function to run the test suite
int main(int argc, char* argv[]) {
  return munit_suite_main(&suite, NULL, argc, argv);
}
