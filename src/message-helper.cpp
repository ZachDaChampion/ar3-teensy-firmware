/**
 * @file message-helper.cpp
 * @author Zach Champion (zachchampion79@gmail.com)
 *
 * @version 1.0
 * @date 2023-09-05
 */

#include "message-helper.h"

#include <framing.h>

int msg_helper::write_log(uint8_t* dest, size_t dest_size, flatbuffers::FlatBufferBuilder& builder,
                          CobotMsgs::LogLevel level, const char* message)
{
  builder.Clear();
  auto log_msg_str = builder.CreateString(message);
  auto log_msg = CobotMsgs::CreateLogMessage(builder, level, log_msg_str);
  auto outgoing_msg = CobotMsgs::CreateOutgoingMessage(
    builder, CobotMsgs::OutgoingMessagePayload_LogMessage, log_msg.Union());
  builder.Finish(outgoing_msg);

  return framing::frame_message(dest, dest_size, builder.GetBufferPointer(), builder.GetSize());
}

int msg_helper::write_ack(uint8_t* dest, size_t dest_size, flatbuffers::FlatBufferBuilder& builder,
                          uint32_t msg_id)
{
  builder.Clear();
  auto ack = CobotMsgs::Response::CreateAck(builder);
  auto response = CobotMsgs::Response::CreateResponse(
    builder, msg_id, CobotMsgs::Response::ResponsePayload_Ack, ack.Union());
  auto outgoing_msg = CobotMsgs::CreateOutgoingMessage(
    builder, CobotMsgs::OutgoingMessagePayload_Response, response.Union());
  builder.Finish(outgoing_msg);

  return framing::frame_message(dest, dest_size, builder.GetBufferPointer(), builder.GetSize());
}

int msg_helper::write_done(uint8_t* dest, size_t dest_size, flatbuffers::FlatBufferBuilder& builder,
                           uint32_t msg_id)
{
  builder.Clear();
  auto done = CobotMsgs::Response::CreateDone(builder);
  auto response = CobotMsgs::Response::CreateResponse(
    builder, msg_id, CobotMsgs::Response::ResponsePayload_Done, done.Union());
  auto outgoing_msg = CobotMsgs::CreateOutgoingMessage(
    builder, CobotMsgs::OutgoingMessagePayload_Response, response.Union());
  builder.Finish(outgoing_msg);

  return framing::frame_message(dest, dest_size, builder.GetBufferPointer(), builder.GetSize());
}

int msg_helper::write_error_response(uint8_t* dest, size_t dest_size,
                                     flatbuffers::FlatBufferBuilder& builder, uint32_t msg_id,
                                     CobotMsgs::ErrorCode error_code, const char* error_msg)
{
  builder.Clear();
  auto error_msg_str = builder.CreateString(error_msg);
  auto error = CobotMsgs::Response::CreateError(builder, error_code, error_msg_str);
  auto response = CobotMsgs::Response::CreateResponse(
    builder, msg_id, CobotMsgs::Response::ResponsePayload_Error, error.Union());
  auto outgoing_msg = CobotMsgs::CreateOutgoingMessage(
    builder, CobotMsgs::OutgoingMessagePayload_Response, response.Union());
  builder.Finish(outgoing_msg);

  return framing::frame_message(dest, dest_size, builder.GetBufferPointer(), builder.GetSize());
}
