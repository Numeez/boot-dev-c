#include <stdint.h>
#include <string.h>
#include "../../munit/munit.h"
#include "exercise.h" // Defines packet_header_t

// Test: Size of the packet header
static MunitResult test_packet_header_size(const MunitParameter params[], void* data) {
  (void)params; (void)data;
  munit_assert_size(sizeof(packet_header_t), ==, 4);
  return MUNIT_OK;
}

// Test: Writing to struct fields and checking values
static MunitResult test_tcp_header_fields(const MunitParameter params[], void* data) {
  (void)params; (void)data;
  packet_header_t header;
  header.tcp_header.src_port = 0x12;
  header.tcp_header.dest_port = 0x34;
  header.tcp_header.seq_num = 0xABCD;

  munit_assert_uint8(header.tcp_header.src_port, ==, 0x12);
  munit_assert_uint8(header.tcp_header.dest_port, ==, 0x34);
  munit_assert_uint16(header.tcp_header.seq_num, ==, 0xABCD);
  return MUNIT_OK;
}

// Test: Raw memory should match struct field values (little endian)
static MunitResult test_raw_bytes_layout(const MunitParameter params[], void* data) {
  (void)params; (void)data;
  packet_header_t header = {0};
  header.tcp_header.src_port = 0x12;
  header.tcp_header.dest_port = 0x34;
  header.tcp_header.seq_num = 0xABCD;

  munit_assert_uint8(header.raw[0], ==, 0x12);
  munit_assert_uint8(header.raw[1], ==, 0x34);
  munit_assert_uint8(header.raw[2], ==, 0xCD); // low byte of 0xABCD
  munit_assert_uint8(header.raw[3], ==, 0xAB); // high byte
  return MUNIT_OK;
}

// Test: Write to raw bytes, check struct values
static MunitResult test_raw_to_struct(const MunitParameter params[], void* data) {
  (void)params; (void)data;
  packet_header_t header = { .raw = {0xAA, 0xBB, 0xCC, 0xDD} };

  munit_assert_uint8(header.tcp_header.src_port, ==, 0xAA);
  munit_assert_uint8(header.tcp_header.dest_port, ==, 0xBB);
  munit_assert_uint16(header.tcp_header.seq_num, ==, 0xDDCC); // little endian
  return MUNIT_OK;
}

// Test list
static MunitTest tests[] = {
  { "/packet_header/size", test_packet_header_size, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
  { "/packet_header/fields", test_tcp_header_fields, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
  { "/packet_header/raw_bytes", test_raw_bytes_layout, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
  { "/packet_header/from_raw", test_raw_to_struct, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
  { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL } // Terminator
};

// Test suite
static const MunitSuite suite = {
  "/packet_header", // Suite name
  tests,             // Test array
  NULL,              // No sub-suites
  1,                 // Iterations
  MUNIT_SUITE_OPTION_NONE
};

// Main function
int main(int argc, char* argv[]) {
  return munit_suite_main(&suite, NULL, argc, argv);
}
