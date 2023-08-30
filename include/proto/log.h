/*
 *  This file is generated with Embedded Proto, PLEASE DO NOT EDIT!
 *  source: log.proto
 */

// This file is generated. Please do not edit!
#ifndef LOG_H
#define LOG_H

#include <cstdint>
#include <MessageInterface.h>
#include <WireFormatter.h>
#include <Fields.h>
#include <MessageSizeCalculator.h>
#include <ReadBufferSection.h>
#include <RepeatedFieldFixedSize.h>
#include <FieldStringBytes.h>
#include <Errors.h>
#include <Defines.h>
#include <limits>

// Include external proto definitions

namespace cobot {

enum class LogLevel : uint32_t
{
  DEBUG = 0,
  INFO = 1,
  WARN = 2,
  ERROR = 3,
  NONE = 4
};

template<
    uint32_t LogMessage_message_LENGTH
>
class LogMessage final: public ::EmbeddedProto::MessageInterface
{
  public:
    LogMessage() = default;
    LogMessage(const LogMessage& rhs )
    {
      set_level(rhs.get_level());
      set_message(rhs.get_message());
    }

    LogMessage(const LogMessage&& rhs ) noexcept
    {
      set_level(rhs.get_level());
      set_message(rhs.get_message());
    }

    ~LogMessage() override = default;

    enum class FieldNumber : uint32_t
    {
      NOT_SET = 0,
      LEVEL = 1,
      MESSAGE = 2
    };

    LogMessage& operator=(const LogMessage& rhs)
    {
      set_level(rhs.get_level());
      set_message(rhs.get_message());
      return *this;
    }

    LogMessage& operator=(const LogMessage&& rhs) noexcept
    {
      set_level(rhs.get_level());
      set_message(rhs.get_message());
      return *this;
    }

    static constexpr char const* LEVEL_NAME = "level";
    inline void clear_level() { level_.clear(); }
    inline void set_level(const LogLevel& value) { level_ = value; }
    inline void set_level(const LogLevel&& value) { level_ = value; }
    inline const LogLevel& get_level() const { return level_.get(); }
    inline LogLevel level() const { return level_.get(); }

    static constexpr char const* MESSAGE_NAME = "message";
    inline void clear_message() { message_.clear(); }
    inline ::EmbeddedProto::FieldString<LogMessage_message_LENGTH>& mutable_message() { return message_; }
    inline void set_message(const ::EmbeddedProto::FieldString<LogMessage_message_LENGTH>& rhs) { message_.set(rhs); }
    inline const ::EmbeddedProto::FieldString<LogMessage_message_LENGTH>& get_message() const { return message_; }
    inline const char* message() const { return message_.get_const(); }


    ::EmbeddedProto::Error serialize(::EmbeddedProto::WriteBufferInterface& buffer) const override
    {
      ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;

      if((static_cast<LogLevel>(0) != level_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = level_.serialize_with_id(static_cast<uint32_t>(FieldNumber::LEVEL), buffer, false);
      }

      if(::EmbeddedProto::Error::NO_ERRORS == return_value)
      {
        return_value = message_.serialize_with_id(static_cast<uint32_t>(FieldNumber::MESSAGE), buffer, false);
      }

      return return_value;
    };

    ::EmbeddedProto::Error deserialize(::EmbeddedProto::ReadBufferInterface& buffer) override
    {
      ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;
      ::EmbeddedProto::WireFormatter::WireType wire_type = ::EmbeddedProto::WireFormatter::WireType::VARINT;
      uint32_t id_number = 0;
      FieldNumber id_tag = FieldNumber::NOT_SET;

      ::EmbeddedProto::Error tag_value = ::EmbeddedProto::WireFormatter::DeserializeTag(buffer, wire_type, id_number);
      while((::EmbeddedProto::Error::NO_ERRORS == return_value) && (::EmbeddedProto::Error::NO_ERRORS == tag_value))
      {
        id_tag = static_cast<FieldNumber>(id_number);
        switch(id_tag)
        {
          case FieldNumber::LEVEL:
            return_value = level_.deserialize_check_type(buffer, wire_type);
            break;

          case FieldNumber::MESSAGE:
            return_value = message_.deserialize_check_type(buffer, wire_type);
            break;

          case FieldNumber::NOT_SET:
            return_value = ::EmbeddedProto::Error::INVALID_FIELD_ID;
            break;

          default:
            return_value = skip_unknown_field(buffer, wire_type);
            break;
        }

        if(::EmbeddedProto::Error::NO_ERRORS == return_value)
        {
          // Read the next tag.
          tag_value = ::EmbeddedProto::WireFormatter::DeserializeTag(buffer, wire_type, id_number);
        }
      }

      // When an error was detect while reading the tag but no other errors where found, set it in the return value.
      if((::EmbeddedProto::Error::NO_ERRORS == return_value)
         && (::EmbeddedProto::Error::NO_ERRORS != tag_value)
         && (::EmbeddedProto::Error::END_OF_BUFFER != tag_value)) // The end of the buffer is not an array in this case.
      {
        return_value = tag_value;
      }

      return return_value;
    };

    void clear() override
    {
      clear_level();
      clear_message();

    }

    static char const* field_number_to_name(const FieldNumber fieldNumber)
    {
      char const* name = nullptr;
      switch(fieldNumber)
      {
        case FieldNumber::LEVEL:
          name = LEVEL_NAME;
          break;
        case FieldNumber::MESSAGE:
          name = MESSAGE_NAME;
          break;
        default:
          name = "Invalid FieldNumber";
          break;
      }
      return name;
    }

#ifdef MSG_TO_STRING

    ::EmbeddedProto::string_view to_string(::EmbeddedProto::string_view& str) const
    {
      return this->to_string(str, 0, nullptr, true);
    }

    ::EmbeddedProto::string_view to_string(::EmbeddedProto::string_view& str, const uint32_t indent_level, char const* name, const bool first_field) const override
    {
      ::EmbeddedProto::string_view left_chars = str;
      int32_t n_chars_used = 0;

      if(!first_field)
      {
        // Add a comma behind the previous field.
        n_chars_used = snprintf(left_chars.data, left_chars.size, ",\n");
        if(0 < n_chars_used)
        {
          // Update the character pointer and characters left in the array.
          left_chars.data += n_chars_used;
          left_chars.size -= n_chars_used;
        }
      }

      if(nullptr != name)
      {
        if( 0 == indent_level)
        {
          n_chars_used = snprintf(left_chars.data, left_chars.size, "\"%s\": {\n", name);
        }
        else
        {
          n_chars_used = snprintf(left_chars.data, left_chars.size, "%*s\"%s\": {\n", indent_level, " ", name);
        }
      }
      else
      {
        if( 0 == indent_level)
        {
          n_chars_used = snprintf(left_chars.data, left_chars.size, "{\n");
        }
        else
        {
          n_chars_used = snprintf(left_chars.data, left_chars.size, "%*s{\n", indent_level, " ");
        }
      }
      
      if(0 < n_chars_used)
      {
        left_chars.data += n_chars_used;
        left_chars.size -= n_chars_used;
      }

      left_chars = level_.to_string(left_chars, indent_level + 2, LEVEL_NAME, true);
      left_chars = message_.to_string(left_chars, indent_level + 2, MESSAGE_NAME, false);
  
      if( 0 == indent_level) 
      {
        n_chars_used = snprintf(left_chars.data, left_chars.size, "\n}");
      }
      else 
      {
        n_chars_used = snprintf(left_chars.data, left_chars.size, "\n%*s}", indent_level, " ");
      }

      if(0 < n_chars_used)
      {
        left_chars.data += n_chars_used;
        left_chars.size -= n_chars_used;
      }

      return left_chars;
    }

#endif // End of MSG_TO_STRING

  private:


      EmbeddedProto::enumeration<LogLevel> level_ = static_cast<LogLevel>(0);
      ::EmbeddedProto::FieldString<LogMessage_message_LENGTH> message_;

};

} // End of namespace cobot
#endif // LOG_H