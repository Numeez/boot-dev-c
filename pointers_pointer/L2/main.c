#include "../../munit/munit.h"
#include "exercise.h"
#include <stdlib.h>
#include <string.h>

static MunitResult test_create_token_pointer_array_single(const MunitParameter params[], void* data) {
  (void)params;
  (void)data;

  token_t token = {"hello", 1, 2};
  token_t** result = create_token_pointer_array(&token, 1);

  munit_assert_not_null(result);
  munit_assert_not_null(result[0]);
  munit_assert_string_equal(result[0]->literal, "hello");
  munit_assert_int(result[0]->line, ==, 1);
  munit_assert_int(result[0]->column, ==, 2);
  munit_assert_ptr_not_equal(result[0], &token);

  free(result[0]);
  free(result);
  return MUNIT_OK;
}

static MunitResult test_create_token_pointer_array_multiple(const MunitParameter params[], void* data) {
  (void)params;
  (void)data;

  token_t tokens[] = {
    {"one", 1, 1},
    {"two", 2, 2},
    {"three", 3, 3}
  };

  token_t** result = create_token_pointer_array(tokens, 3);
  for (int i = 0; i < 3; i++) {
    munit_assert_not_null(result[i]);
    munit_assert_string_equal(result[i]->literal, tokens[i].literal);
    munit_assert_int(result[i]->line, ==, tokens[i].line);
    munit_assert_int(result[i]->column, ==, tokens[i].column);
    munit_assert_ptr_not_equal(result[i], &tokens[i]);
  }

  for (int i = 0; i < 3; i++) {
    free(result[i]);
  }
  free(result);
  return MUNIT_OK;
}

static MunitResult test_literal_pointer_identity(const MunitParameter params[], void* data) {
  (void)params;
  (void)data;

  const char* shared_literal = "shared";
  token_t tokens[] = {
    {shared_literal, 1, 1},
    {shared_literal, 2, 2}
  };

  token_t** result = create_token_pointer_array(tokens, 2);

  munit_assert_ptr_equal(result[0]->literal, shared_literal);
  munit_assert_ptr_equal(result[1]->literal, shared_literal);

  free(result[0]);
  free(result[1]);
  free(result);
  return MUNIT_OK;
}

int main(int argc, char* argv[]) {
  static MunitTest tests[] = {
    {
      "/create_token_pointer_array_single",
      test_create_token_pointer_array_single,
      NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL
    },
    {
      "/create_token_pointer_array_multiple",
      test_create_token_pointer_array_multiple,
      NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL
    },
    {
      "/literal_pointer_identity",
      test_literal_pointer_identity,
      NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL
    },
    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
  };

  static const MunitSuite suite = {
    "/create_token_pointer_array",
    tests,
    NULL,
    1,
    MUNIT_SUITE_OPTION_NONE
  };

  return munit_suite_main(&suite, NULL, argc, argv);
}
