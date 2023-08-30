/*
 *  This file is generated with Embedded Proto, PLEASE DO NOT EDIT!
 *  source: main.proto
 */

// This file is generated. Please do not edit!
#ifndef MAIN_H
#define MAIN_H

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
#include "request.h"
#include "response.h"
#include "log.h"

namespace cobot {

template<
    uint32_t CobotMessage_request_Request_override_Override_new_angles_REP_LENGTH, 
    uint32_t CobotMessage_request_Request_move_to_MoveTo_joint_settings_REP_LENGTH, 
    uint32_t CobotMessage_request_Request_move_speed_MoveSpeed_speeds_REP_LENGTH, 
    uint32_t CobotMessage_response_Response_error_Error_error_message_LENGTH, 
    uint32_t CobotMessage_response_Response_joints_Joints_positions_REP_LENGTH, 
    uint32_t CobotMessage_log_LogMessage_message_LENGTH
>
class CobotMessage final: public ::EmbeddedProto::MessageInterface
{
  public:
    CobotMessage() = default;
    CobotMessage(const CobotMessage& rhs )
    {
      if(rhs.get_which_message() != which_message_)
      {
        // First delete the old object in the oneof.
        clear_message();
      }

      switch(rhs.get_which_message())
      {
        case FieldNumber::REQUEST:
          set_request(rhs.get_request());
          break;

        case FieldNumber::RESPONSE:
          set_response(rhs.get_response());
          break;

        case FieldNumber::LOG:
          set_log(rhs.get_log());
          break;

        default:
          break;
      }

    }

    CobotMessage(const CobotMessage&& rhs ) noexcept
    {
      if(rhs.get_which_message() != which_message_)
      {
        // First delete the old object in the oneof.
        clear_message();
      }

      switch(rhs.get_which_message())
      {
        case FieldNumber::REQUEST:
          set_request(rhs.get_request());
          break;

        case FieldNumber::RESPONSE:
          set_response(rhs.get_response());
          break;

        case FieldNumber::LOG:
          set_log(rhs.get_log());
          break;

        default:
          break;
      }

    }

    ~CobotMessage() override = default;

    enum class FieldNumber : uint32_t
    {
      NOT_SET = 0,
      REQUEST = 1,
      RESPONSE = 2,
      LOG = 3
    };

    CobotMessage& operator=(const CobotMessage& rhs)
    {
      if(rhs.get_which_message() != which_message_)
      {
        // First delete the old object in the oneof.
        clear_message();
      }

      switch(rhs.get_which_message())
      {
        case FieldNumber::REQUEST:
          set_request(rhs.get_request());
          break;

        case FieldNumber::RESPONSE:
          set_response(rhs.get_response());
          break;

        case FieldNumber::LOG:
          set_log(rhs.get_log());
          break;

        default:
          break;
      }

      return *this;
    }

    CobotMessage& operator=(const CobotMessage&& rhs) noexcept
    {
      if(rhs.get_which_message() != which_message_)
      {
        // First delete the old object in the oneof.
        clear_message();
      }

      switch(rhs.get_which_message())
      {
        case FieldNumber::REQUEST:
          set_request(rhs.get_request());
          break;

        case FieldNumber::RESPONSE:
          set_response(rhs.get_response());
          break;

        case FieldNumber::LOG:
          set_log(rhs.get_log());
          break;

        default:
          break;
      }

      return *this;
    }

    FieldNumber get_which_message() const { return which_message_; }

    static constexpr char const* REQUEST_NAME = "request";
    inline bool has_request() const
    {
      return FieldNumber::REQUEST == which_message_;
    }
    inline void clear_request()
    {
      if(FieldNumber::REQUEST == which_message_)
      {
        which_message_ = FieldNumber::NOT_SET;
        message_.request_.~Request<CobotMessage_request_Request_override_Override_new_angles_REP_LENGTH, CobotMessage_request_Request_move_to_MoveTo_joint_settings_REP_LENGTH, CobotMessage_request_Request_move_speed_MoveSpeed_speeds_REP_LENGTH>();
      }
    }
    inline void set_request(const Request<CobotMessage_request_Request_override_Override_new_angles_REP_LENGTH, CobotMessage_request_Request_move_to_MoveTo_joint_settings_REP_LENGTH, CobotMessage_request_Request_move_speed_MoveSpeed_speeds_REP_LENGTH>& value)
    {
      if(FieldNumber::REQUEST != which_message_)
      {
        init_message(FieldNumber::REQUEST);
      }
      message_.request_ = value;
    }
    inline void set_request(const Request<CobotMessage_request_Request_override_Override_new_angles_REP_LENGTH, CobotMessage_request_Request_move_to_MoveTo_joint_settings_REP_LENGTH, CobotMessage_request_Request_move_speed_MoveSpeed_speeds_REP_LENGTH>&& value)
    {
      if(FieldNumber::REQUEST != which_message_)
      {
        init_message(FieldNumber::REQUEST);
      }
      message_.request_ = value;
    }
    inline Request<CobotMessage_request_Request_override_Override_new_angles_REP_LENGTH, CobotMessage_request_Request_move_to_MoveTo_joint_settings_REP_LENGTH, CobotMessage_request_Request_move_speed_MoveSpeed_speeds_REP_LENGTH>& mutable_request()
    {
      if(FieldNumber::REQUEST != which_message_)
      {
        init_message(FieldNumber::REQUEST);
      }
      return message_.request_;
    }
    inline const Request<CobotMessage_request_Request_override_Override_new_angles_REP_LENGTH, CobotMessage_request_Request_move_to_MoveTo_joint_settings_REP_LENGTH, CobotMessage_request_Request_move_speed_MoveSpeed_speeds_REP_LENGTH>& get_request() const { return message_.request_; }
    inline const Request<CobotMessage_request_Request_override_Override_new_angles_REP_LENGTH, CobotMessage_request_Request_move_to_MoveTo_joint_settings_REP_LENGTH, CobotMessage_request_Request_move_speed_MoveSpeed_speeds_REP_LENGTH>& request() const { return message_.request_; }

    static constexpr char const* RESPONSE_NAME = "response";
    inline bool has_response() const
    {
      return FieldNumber::RESPONSE == which_message_;
    }
    inline void clear_response()
    {
      if(FieldNumber::RESPONSE == which_message_)
      {
        which_message_ = FieldNumber::NOT_SET;
        message_.response_.~Response<CobotMessage_response_Response_error_Error_error_message_LENGTH, CobotMessage_response_Response_joints_Joints_positions_REP_LENGTH>();
      }
    }
    inline void set_response(const Response<CobotMessage_response_Response_error_Error_error_message_LENGTH, CobotMessage_response_Response_joints_Joints_positions_REP_LENGTH>& value)
    {
      if(FieldNumber::RESPONSE != which_message_)
      {
        init_message(FieldNumber::RESPONSE);
      }
      message_.response_ = value;
    }
    inline void set_response(const Response<CobotMessage_response_Response_error_Error_error_message_LENGTH, CobotMessage_response_Response_joints_Joints_positions_REP_LENGTH>&& value)
    {
      if(FieldNumber::RESPONSE != which_message_)
      {
        init_message(FieldNumber::RESPONSE);
      }
      message_.response_ = value;
    }
    inline Response<CobotMessage_response_Response_error_Error_error_message_LENGTH, CobotMessage_response_Response_joints_Joints_positions_REP_LENGTH>& mutable_response()
    {
      if(FieldNumber::RESPONSE != which_message_)
      {
        init_message(FieldNumber::RESPONSE);
      }
      return message_.response_;
    }
    inline const Response<CobotMessage_response_Response_error_Error_error_message_LENGTH, CobotMessage_response_Response_joints_Joints_positions_REP_LENGTH>& get_response() const { return message_.response_; }
    inline const Response<CobotMessage_response_Response_error_Error_error_message_LENGTH, CobotMessage_response_Response_joints_Joints_positions_REP_LENGTH>& response() const { return message_.response_; }

    static constexpr char const* LOG_NAME = "log";
    inline bool has_log() const
    {
      return FieldNumber::LOG == which_message_;
    }
    inline void clear_log()
    {
      if(FieldNumber::LOG == which_message_)
      {
        which_message_ = FieldNumber::NOT_SET;
        message_.log_.~LogMessage<CobotMessage_log_LogMessage_message_LENGTH>();
      }
    }
    inline void set_log(const LogMessage<CobotMessage_log_LogMessage_message_LENGTH>& value)
    {
      if(FieldNumber::LOG != which_message_)
      {
        init_message(FieldNumber::LOG);
      }
      message_.log_ = value;
    }
    inline void set_log(const LogMessage<CobotMessage_log_LogMessage_message_LENGTH>&& value)
    {
      if(FieldNumber::LOG != which_message_)
      {
        init_message(FieldNumber::LOG);
      }
      message_.log_ = value;
    }
    inline LogMessage<CobotMessage_log_LogMessage_message_LENGTH>& mutable_log()
    {
      if(FieldNumber::LOG != which_message_)
      {
        init_message(FieldNumber::LOG);
      }
      return message_.log_;
    }
    inline const LogMessage<CobotMessage_log_LogMessage_message_LENGTH>& get_log() const { return message_.log_; }
    inline const LogMessage<CobotMessage_log_LogMessage_message_LENGTH>& log() const { return message_.log_; }


    ::EmbeddedProto::Error serialize(::EmbeddedProto::WriteBufferInterface& buffer) const override
    {
      ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;

      switch(which_message_)
      {
        case FieldNumber::REQUEST:
          if(has_request() && (::EmbeddedProto::Error::NO_ERRORS == return_value))
          {
            return_value = message_.request_.serialize_with_id(static_cast<uint32_t>(FieldNumber::REQUEST), buffer, true);
          }
          break;

        case FieldNumber::RESPONSE:
          if(has_response() && (::EmbeddedProto::Error::NO_ERRORS == return_value))
          {
            return_value = message_.response_.serialize_with_id(static_cast<uint32_t>(FieldNumber::RESPONSE), buffer, true);
          }
          break;

        case FieldNumber::LOG:
          if(has_log() && (::EmbeddedProto::Error::NO_ERRORS == return_value))
          {
            return_value = message_.log_.serialize_with_id(static_cast<uint32_t>(FieldNumber::LOG), buffer, true);
          }
          break;

        default:
          break;
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
          case FieldNumber::REQUEST:
          case FieldNumber::RESPONSE:
          case FieldNumber::LOG:
            return_value = deserialize_message(id_tag, buffer, wire_type);
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
      clear_message();

    }

    static char const* field_number_to_name(const FieldNumber fieldNumber)
    {
      char const* name = nullptr;
      switch(fieldNumber)
      {
        case FieldNumber::REQUEST:
          name = REQUEST_NAME;
          break;
        case FieldNumber::RESPONSE:
          name = RESPONSE_NAME;
          break;
        case FieldNumber::LOG:
          name = LOG_NAME;
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

      left_chars = to_string_message(left_chars, indent_level + 2, true);
  
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



      FieldNumber which_message_ = FieldNumber::NOT_SET;
      union message
      {
        message() {}
        ~message() {}
        Request<CobotMessage_request_Request_override_Override_new_angles_REP_LENGTH, CobotMessage_request_Request_move_to_MoveTo_joint_settings_REP_LENGTH, CobotMessage_request_Request_move_speed_MoveSpeed_speeds_REP_LENGTH> request_;
        Response<CobotMessage_response_Response_error_Error_error_message_LENGTH, CobotMessage_response_Response_joints_Joints_positions_REP_LENGTH> response_;
        LogMessage<CobotMessage_log_LogMessage_message_LENGTH> log_;
      };
      message message_;

      void init_message(const FieldNumber field_id)
      {
        if(FieldNumber::NOT_SET != which_message_)
        {
          // First delete the old object in the oneof.
          clear_message();
        }

        // C++11 unions only support nontrivial members when you explicitly call the placement new statement.
        switch(field_id)
        {
          case FieldNumber::REQUEST:
            new(&message_.request_) Request<CobotMessage_request_Request_override_Override_new_angles_REP_LENGTH, CobotMessage_request_Request_move_to_MoveTo_joint_settings_REP_LENGTH, CobotMessage_request_Request_move_speed_MoveSpeed_speeds_REP_LENGTH>;
            break;

          case FieldNumber::RESPONSE:
            new(&message_.response_) Response<CobotMessage_response_Response_error_Error_error_message_LENGTH, CobotMessage_response_Response_joints_Joints_positions_REP_LENGTH>;
            break;

          case FieldNumber::LOG:
            new(&message_.log_) LogMessage<CobotMessage_log_LogMessage_message_LENGTH>;
            break;

          default:
            break;
         }

         which_message_ = field_id;
      }

      void clear_message()
      {
        switch(which_message_)
        {
          case FieldNumber::REQUEST:
            ::EmbeddedProto::destroy_at(&message_.request_);
            break;
          case FieldNumber::RESPONSE:
            ::EmbeddedProto::destroy_at(&message_.response_);
            break;
          case FieldNumber::LOG:
            ::EmbeddedProto::destroy_at(&message_.log_);
            break;
          default:
            break;
        }
        which_message_ = FieldNumber::NOT_SET;
      }

      ::EmbeddedProto::Error deserialize_message(const FieldNumber field_id, 
                                    ::EmbeddedProto::ReadBufferInterface& buffer,
                                    const ::EmbeddedProto::WireFormatter::WireType wire_type)
      {
        ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;
        
        if(field_id != which_message_)
        {
          init_message(field_id);
        }

        switch(which_message_)
        {
          case FieldNumber::REQUEST:
            return_value = message_.request_.deserialize_check_type(buffer, wire_type);
            break;
          case FieldNumber::RESPONSE:
            return_value = message_.response_.deserialize_check_type(buffer, wire_type);
            break;
          case FieldNumber::LOG:
            return_value = message_.log_.deserialize_check_type(buffer, wire_type);
            break;
          default:
            break;
        }

        if(::EmbeddedProto::Error::NO_ERRORS != return_value)
        {
          clear_message();
        }
        return return_value;
      }

#ifdef MSG_TO_STRING 
      ::EmbeddedProto::string_view to_string_message(::EmbeddedProto::string_view& str, const uint32_t indent_level, const bool first_field) const
      {
        ::EmbeddedProto::string_view left_chars = str;

        switch(which_message_)
        {
          case FieldNumber::REQUEST:
            left_chars = message_.request_.to_string(left_chars, indent_level, REQUEST_NAME, first_field);
            break;
          case FieldNumber::RESPONSE:
            left_chars = message_.response_.to_string(left_chars, indent_level, RESPONSE_NAME, first_field);
            break;
          case FieldNumber::LOG:
            left_chars = message_.log_.to_string(left_chars, indent_level, LOG_NAME, first_field);
            break;
          default:
            break;
        }

        return left_chars;
      }

#endif // End of MSG_TO_STRING
};

} // End of namespace cobot
#endif // MAIN_H