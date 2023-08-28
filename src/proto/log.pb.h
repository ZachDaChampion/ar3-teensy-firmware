/* Automatically generated nanopb header */
/* Generated by nanopb-0.4.7 */

#ifndef PB_COBOT_LOG_PB_H_INCLUDED
#define PB_COBOT_LOG_PB_H_INCLUDED
#include <pb.h>

#if PB_PROTO_HEADER_VERSION != 40
#error Regenerate this file with the current version of nanopb generator.
#endif

/* Enum definitions */
/* A log level that can be used to filter log messages. */
typedef enum _cobot_LogLevel {
    cobot_LogLevel_DEBUG = 0, /* Debug level is not used in production. */
    cobot_LogLevel_INFO = 1, /* Info level is used for general information. */
    cobot_LogLevel_WARN = 2, /* Warn level is used for non-critical errors. */
    cobot_LogLevel_ERROR = 3, /* Error level is used for critical errors. */
    cobot_LogLevel_NONE = 4 /* None level is used to disable logging. Log messages will never use this level. */
} cobot_LogLevel;

/* Struct definitions */
/* A log message that can be sent to the host. */
typedef struct _cobot_LogMessage {
    /* The log level of the message. */
    cobot_LogLevel level;
    /* The message to log. */
    pb_callback_t message;
} cobot_LogMessage;


#ifdef __cplusplus
extern "C" {
#endif

/* Helper constants for enums */
#define _cobot_LogLevel_MIN cobot_LogLevel_DEBUG
#define _cobot_LogLevel_MAX cobot_LogLevel_NONE
#define _cobot_LogLevel_ARRAYSIZE ((cobot_LogLevel)(cobot_LogLevel_NONE+1))

#define cobot_LogMessage_level_ENUMTYPE cobot_LogLevel


/* Initializer values for message structs */
#define cobot_LogMessage_init_default            {_cobot_LogLevel_MIN, {{NULL}, NULL}}
#define cobot_LogMessage_init_zero               {_cobot_LogLevel_MIN, {{NULL}, NULL}}

/* Field tags (for use in manual encoding/decoding) */
#define cobot_LogMessage_level_tag               1
#define cobot_LogMessage_message_tag             2

/* Struct field encoding specification for nanopb */
#define cobot_LogMessage_FIELDLIST(X, a) \
X(a, STATIC,   SINGULAR, UENUM,    level,             1) \
X(a, CALLBACK, SINGULAR, STRING,   message,           2)
#define cobot_LogMessage_CALLBACK pb_default_field_callback
#define cobot_LogMessage_DEFAULT NULL

extern const pb_msgdesc_t cobot_LogMessage_msg;

/* Defines for backwards compatibility with code written before nanopb-0.4.0 */
#define cobot_LogMessage_fields &cobot_LogMessage_msg

/* Maximum encoded size of messages (where known) */
/* cobot_LogMessage_size depends on runtime parameters */

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
