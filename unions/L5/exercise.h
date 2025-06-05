#include <stdint.h>

typedef union PacketHeader{
  struct{
    uint8_t src_port;
    uint8_t dest_port;
    uint16_t seq_num;
  }tcp_header;
  uint8_t raw[4];
  
} packet_header_t;
