/**
 * \file ar3_error.h
 * \author Zach Champion (zachchampion79@gmail.com)
 * 
 * \version 0.1
 * \date 2023-06-10
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef AR3_TEENSY_FIRMWARE__AR3_ERROR_H
#define AR3_TEENSY_FIRMWARE__AR3_ERROR_H

typedef enum {
  AR3_ERR_OK = 0,
  AR3_ERR_INVALID_COMMAND = 1,
  AR3_ERR_INVALID_ARG = 2,
  AR3_ERR_OOB = 3,
  AR3_ERR_NOT_CALIBRATED = 4,
  AR3_ERR_TIMEOUT = 5,
  AR3_ERR_PHYSICAL = 6,
  AR3_ERR_MALFORMED_ARG = 7,
  AR3_ERR_BUFFER_OVERFLOW = 8,
  AR3_ERR_INVALID_CHECKSUM = 9,
  AR3_ERR_UNKNOWN = -1,
} ar3_err_t;

#endif  // AR3_TEENSY_FIRMWARE__ERROR_H