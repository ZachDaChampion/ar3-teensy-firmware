// automatically generated by the FlatBuffers compiler, do not modify


#ifndef FLATBUFFERS_GENERATED_MAIN_COBOTMSGS_H_
#define FLATBUFFERS_GENERATED_MAIN_COBOTMSGS_H_

#include "flatbuffers/flatbuffers.h"

// Ensure the included flatbuffers.h is the same version as when this file was
// generated, otherwise it may not be compatible.
static_assert(FLATBUFFERS_VERSION_MAJOR == 23 &&
              FLATBUFFERS_VERSION_MINOR == 5 &&
              FLATBUFFERS_VERSION_REVISION == 26,
             "Non-compatible flatbuffers version included");

#include "_errors_generated.h"
#include "_log_generated.h"
#include "_request_generated.h"
#include "_response_generated.h"

namespace CobotMsgs {

struct OutgoingMessage;
struct OutgoingMessageBuilder;

struct IncomingMessage;
struct IncomingMessageBuilder;

enum OutgoingMessagePayload : uint8_t {
  OutgoingMessagePayload_NONE = 0,
  OutgoingMessagePayload_Response = 1,
  OutgoingMessagePayload_LogMessage = 2,
  OutgoingMessagePayload_MIN = OutgoingMessagePayload_NONE,
  OutgoingMessagePayload_MAX = OutgoingMessagePayload_LogMessage
};

inline const OutgoingMessagePayload (&EnumValuesOutgoingMessagePayload())[3] {
  static const OutgoingMessagePayload values[] = {
    OutgoingMessagePayload_NONE,
    OutgoingMessagePayload_Response,
    OutgoingMessagePayload_LogMessage
  };
  return values;
}

inline const char * const *EnumNamesOutgoingMessagePayload() {
  static const char * const names[4] = {
    "NONE",
    "Response",
    "LogMessage",
    nullptr
  };
  return names;
}

inline const char *EnumNameOutgoingMessagePayload(OutgoingMessagePayload e) {
  if (::flatbuffers::IsOutRange(e, OutgoingMessagePayload_NONE, OutgoingMessagePayload_LogMessage)) return "";
  const size_t index = static_cast<size_t>(e);
  return EnumNamesOutgoingMessagePayload()[index];
}

template<typename T> struct OutgoingMessagePayloadTraits {
  static const OutgoingMessagePayload enum_value = OutgoingMessagePayload_NONE;
};

template<> struct OutgoingMessagePayloadTraits<CobotMsgs::Response::Response> {
  static const OutgoingMessagePayload enum_value = OutgoingMessagePayload_Response;
};

template<> struct OutgoingMessagePayloadTraits<CobotMsgs::LogMessage> {
  static const OutgoingMessagePayload enum_value = OutgoingMessagePayload_LogMessage;
};

bool VerifyOutgoingMessagePayload(::flatbuffers::Verifier &verifier, const void *obj, OutgoingMessagePayload type);
bool VerifyOutgoingMessagePayloadVector(::flatbuffers::Verifier &verifier, const ::flatbuffers::Vector<::flatbuffers::Offset<void>> *values, const ::flatbuffers::Vector<uint8_t> *types);

struct OutgoingMessage FLATBUFFERS_FINAL_CLASS : private ::flatbuffers::Table {
  typedef OutgoingMessageBuilder Builder;
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_PAYLOAD_TYPE = 4,
    VT_PAYLOAD = 6
  };
  CobotMsgs::OutgoingMessagePayload payload_type() const {
    return static_cast<CobotMsgs::OutgoingMessagePayload>(GetField<uint8_t>(VT_PAYLOAD_TYPE, 0));
  }
  const void *payload() const {
    return GetPointer<const void *>(VT_PAYLOAD);
  }
  template<typename T> const T *payload_as() const;
  const CobotMsgs::Response::Response *payload_as_Response() const {
    return payload_type() == CobotMsgs::OutgoingMessagePayload_Response ? static_cast<const CobotMsgs::Response::Response *>(payload()) : nullptr;
  }
  const CobotMsgs::LogMessage *payload_as_LogMessage() const {
    return payload_type() == CobotMsgs::OutgoingMessagePayload_LogMessage ? static_cast<const CobotMsgs::LogMessage *>(payload()) : nullptr;
  }
  bool Verify(::flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<uint8_t>(verifier, VT_PAYLOAD_TYPE, 1) &&
           VerifyOffset(verifier, VT_PAYLOAD) &&
           VerifyOutgoingMessagePayload(verifier, payload(), payload_type()) &&
           verifier.EndTable();
  }
};

template<> inline const CobotMsgs::Response::Response *OutgoingMessage::payload_as<CobotMsgs::Response::Response>() const {
  return payload_as_Response();
}

template<> inline const CobotMsgs::LogMessage *OutgoingMessage::payload_as<CobotMsgs::LogMessage>() const {
  return payload_as_LogMessage();
}

struct OutgoingMessageBuilder {
  typedef OutgoingMessage Table;
  ::flatbuffers::FlatBufferBuilder &fbb_;
  ::flatbuffers::uoffset_t start_;
  void add_payload_type(CobotMsgs::OutgoingMessagePayload payload_type) {
    fbb_.AddElement<uint8_t>(OutgoingMessage::VT_PAYLOAD_TYPE, static_cast<uint8_t>(payload_type), 0);
  }
  void add_payload(::flatbuffers::Offset<void> payload) {
    fbb_.AddOffset(OutgoingMessage::VT_PAYLOAD, payload);
  }
  explicit OutgoingMessageBuilder(::flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  ::flatbuffers::Offset<OutgoingMessage> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = ::flatbuffers::Offset<OutgoingMessage>(end);
    return o;
  }
};

inline ::flatbuffers::Offset<OutgoingMessage> CreateOutgoingMessage(
    ::flatbuffers::FlatBufferBuilder &_fbb,
    CobotMsgs::OutgoingMessagePayload payload_type = CobotMsgs::OutgoingMessagePayload_NONE,
    ::flatbuffers::Offset<void> payload = 0) {
  OutgoingMessageBuilder builder_(_fbb);
  builder_.add_payload(payload);
  builder_.add_payload_type(payload_type);
  return builder_.Finish();
}

struct IncomingMessage FLATBUFFERS_FINAL_CLASS : private ::flatbuffers::Table {
  typedef IncomingMessageBuilder Builder;
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_PAYLOAD = 4
  };
  const CobotMsgs::Request::Request *payload() const {
    return GetPointer<const CobotMsgs::Request::Request *>(VT_PAYLOAD);
  }
  bool Verify(::flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyOffset(verifier, VT_PAYLOAD) &&
           verifier.VerifyTable(payload()) &&
           verifier.EndTable();
  }
};

struct IncomingMessageBuilder {
  typedef IncomingMessage Table;
  ::flatbuffers::FlatBufferBuilder &fbb_;
  ::flatbuffers::uoffset_t start_;
  void add_payload(::flatbuffers::Offset<CobotMsgs::Request::Request> payload) {
    fbb_.AddOffset(IncomingMessage::VT_PAYLOAD, payload);
  }
  explicit IncomingMessageBuilder(::flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  ::flatbuffers::Offset<IncomingMessage> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = ::flatbuffers::Offset<IncomingMessage>(end);
    return o;
  }
};

inline ::flatbuffers::Offset<IncomingMessage> CreateIncomingMessage(
    ::flatbuffers::FlatBufferBuilder &_fbb,
    ::flatbuffers::Offset<CobotMsgs::Request::Request> payload = 0) {
  IncomingMessageBuilder builder_(_fbb);
  builder_.add_payload(payload);
  return builder_.Finish();
}

inline bool VerifyOutgoingMessagePayload(::flatbuffers::Verifier &verifier, const void *obj, OutgoingMessagePayload type) {
  switch (type) {
    case OutgoingMessagePayload_NONE: {
      return true;
    }
    case OutgoingMessagePayload_Response: {
      auto ptr = reinterpret_cast<const CobotMsgs::Response::Response *>(obj);
      return verifier.VerifyTable(ptr);
    }
    case OutgoingMessagePayload_LogMessage: {
      auto ptr = reinterpret_cast<const CobotMsgs::LogMessage *>(obj);
      return verifier.VerifyTable(ptr);
    }
    default: return true;
  }
}

inline bool VerifyOutgoingMessagePayloadVector(::flatbuffers::Verifier &verifier, const ::flatbuffers::Vector<::flatbuffers::Offset<void>> *values, const ::flatbuffers::Vector<uint8_t> *types) {
  if (!values || !types) return !values && !types;
  if (values->size() != types->size()) return false;
  for (::flatbuffers::uoffset_t i = 0; i < values->size(); ++i) {
    if (!VerifyOutgoingMessagePayload(
        verifier,  values->Get(i), types->GetEnum<OutgoingMessagePayload>(i))) {
      return false;
    }
  }
  return true;
}

}  // namespace CobotMsgs

#endif  // FLATBUFFERS_GENERATED_MAIN_COBOTMSGS_H_
