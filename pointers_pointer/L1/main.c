#include "../../munit/munit.h"
#include <stdlib.h>
#include "exercise.h"  // Should declare: void allocate_int(int **ptr, int value);

static MunitResult test_allocate(const MunitParameter params[], void* data) {
  (void)params;
  (void)data;

  int *pointer = NULL;
  allocate_int(&pointer, 10);

  munit_assert_not_null(pointer);
  munit_assert_int(*pointer, ==, 10);

  free(pointer);
  return MUNIT_OK;
}

static MunitResult test_does_not_overwrite(const MunitParameter params[], void* data) {
  (void)params;
  (void)data;

  int value = 5;
  int *pointer = &value;

  allocate_int(&pointer, 20);

  munit_assert_int(value, ==, 5);
  munit_assert_not_null(pointer);
  munit_assert_int(*pointer, ==, 20);

  free(pointer);
  return MUNIT_OK;
}

static MunitTest tests[] = {
  { "/allocate", test_allocate, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
  { "/does_not_overwrite", test_does_not_overwrite, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
  { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

static const MunitSuite suite = {
  "/allocate_int",    // name
  tests,              // test array
  NULL,               // no sub-suites
  1,                  // iterations
  MUNIT_SUITE_OPTION_NONE
};

int main(int argc, char* argv[]) {
  return munit_suite_main(&suite, NULL, argc, argv);
}
