/*
 *  This file is generated with Embedded Proto, PLEASE DO NOT EDIT!
 *  source: errors.proto
 */

// This file is generated. Please do not edit!
#ifndef ERRORS_H
#define ERRORS_H

#include <cstdint>
// Include external proto definitions

namespace cobot {

enum class ErrorCode : uint32_t
{
  ERR_OTHER = 0,
  ERR_MALFORMED_REQUEST = 1,
  ERR_OUT_OF_RANGE = 2,
  ERR_INVALID_JOINT = 3,
  ERR_NOT_INITIALIZED = 4,
  ERR_NOT_CALIBRATED = 5,
  ERR_CANCELLED = 6
};

} // End of namespace cobot
#endif // ERRORS_H