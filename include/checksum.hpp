#ifndef AR3_TEENSY_FIRMWARE__CHECKSUM_H
#define AR3_TEENSY_FIRMWARE__CHECKSUM_H

uint8_t calc_checksum(char* msg)
{
  // TODO
  return 0;
}

bool verify_checksum(char* msg, char* checksum)
{
  uint8_t given = (uint8_t)strtol(checksum, NULL, 16);
  uint8_t calc = calc_checksum(msg);
  return given == calc;
}

#endif  // AR3_TEENSY_FIRMWARE__CHECKSUM_H