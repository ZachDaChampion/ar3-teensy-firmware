/*
 *  This file is generated with Embedded Proto, PLEASE DO NOT EDIT!
 *  source: request.proto
 */

// This file is generated. Please do not edit!
#ifndef REQUEST_H
#define REQUEST_H

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
#include "log.h"

namespace cobot {

template<
    uint32_t Request_override_Override_new_angles_REP_LENGTH, 
    uint32_t Request_move_to_MoveTo_joint_settings_REP_LENGTH, 
    uint32_t Request_move_speed_MoveSpeed_speeds_REP_LENGTH
>
class Request final: public ::EmbeddedProto::MessageInterface
{
  public:
    Request() = default;
    Request(const Request& rhs )
    {
      set_message_id(rhs.get_message_id());
      if(rhs.get_which_payload() != which_payload_)
      {
        // First delete the old object in the oneof.
        clear_payload();
      }

      switch(rhs.get_which_payload())
      {
        case FieldNumber::INIT:
          set_init(rhs.get_init());
          break;

        case FieldNumber::CALIBRATE:
          set_calibrate(rhs.get_calibrate());
          break;

        case FieldNumber::OVERRIDE:
          set_override(rhs.get_override());
          break;

        case FieldNumber::GET_JOINTS:
          set_get_joints(rhs.get_get_joints());
          break;

        case FieldNumber::MOVE_TO:
          set_move_to(rhs.get_move_to());
          break;

        case FieldNumber::MOVE_SPEED:
          set_move_speed(rhs.get_move_speed());
          break;

        case FieldNumber::STOP:
          set_stop(rhs.get_stop());
          break;

        case FieldNumber::GO_HOME:
          set_go_home(rhs.get_go_home());
          break;

        case FieldNumber::RESET:
          set_reset(rhs.get_reset());
          break;

        case FieldNumber::SET_LOG_LEVEL:
          set_set_log_level(rhs.get_set_log_level());
          break;

        default:
          break;
      }

    }

    Request(const Request&& rhs ) noexcept
    {
      set_message_id(rhs.get_message_id());
      if(rhs.get_which_payload() != which_payload_)
      {
        // First delete the old object in the oneof.
        clear_payload();
      }

      switch(rhs.get_which_payload())
      {
        case FieldNumber::INIT:
          set_init(rhs.get_init());
          break;

        case FieldNumber::CALIBRATE:
          set_calibrate(rhs.get_calibrate());
          break;

        case FieldNumber::OVERRIDE:
          set_override(rhs.get_override());
          break;

        case FieldNumber::GET_JOINTS:
          set_get_joints(rhs.get_get_joints());
          break;

        case FieldNumber::MOVE_TO:
          set_move_to(rhs.get_move_to());
          break;

        case FieldNumber::MOVE_SPEED:
          set_move_speed(rhs.get_move_speed());
          break;

        case FieldNumber::STOP:
          set_stop(rhs.get_stop());
          break;

        case FieldNumber::GO_HOME:
          set_go_home(rhs.get_go_home());
          break;

        case FieldNumber::RESET:
          set_reset(rhs.get_reset());
          break;

        case FieldNumber::SET_LOG_LEVEL:
          set_set_log_level(rhs.get_set_log_level());
          break;

        default:
          break;
      }

    }

    ~Request() override = default;

    class Calibrate final: public ::EmbeddedProto::MessageInterface
    {
      public:
        Calibrate() = default;
        Calibrate(const Calibrate& rhs )
        {
          set_joints_bitfield(rhs.get_joints_bitfield());
        }

        Calibrate(const Calibrate&& rhs ) noexcept
        {
          set_joints_bitfield(rhs.get_joints_bitfield());
        }

        ~Calibrate() override = default;

        enum class FieldNumber : uint32_t
        {
          NOT_SET = 0,
          JOINTS_BITFIELD = 1
        };

        Calibrate& operator=(const Calibrate& rhs)
        {
          set_joints_bitfield(rhs.get_joints_bitfield());
          return *this;
        }

        Calibrate& operator=(const Calibrate&& rhs) noexcept
        {
          set_joints_bitfield(rhs.get_joints_bitfield());
          return *this;
        }

        static constexpr char const* JOINTS_BITFIELD_NAME = "joints_bitfield";
        inline void clear_joints_bitfield() { joints_bitfield_.clear(); }
        inline void set_joints_bitfield(const uint32_t& value) { joints_bitfield_ = value; }
        inline void set_joints_bitfield(const uint32_t&& value) { joints_bitfield_ = value; }
        inline uint32_t& mutable_joints_bitfield() { return joints_bitfield_.get(); }
        inline const uint32_t& get_joints_bitfield() const { return joints_bitfield_.get(); }
        inline uint32_t joints_bitfield() const { return joints_bitfield_.get(); }


        ::EmbeddedProto::Error serialize(::EmbeddedProto::WriteBufferInterface& buffer) const override
        {
          ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;

          if((0U != joints_bitfield_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
          {
            return_value = joints_bitfield_.serialize_with_id(static_cast<uint32_t>(FieldNumber::JOINTS_BITFIELD), buffer, false);
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
              case FieldNumber::JOINTS_BITFIELD:
                return_value = joints_bitfield_.deserialize_check_type(buffer, wire_type);
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
          clear_joints_bitfield();

        }

        static char const* field_number_to_name(const FieldNumber fieldNumber)
        {
          char const* name = nullptr;
          switch(fieldNumber)
          {
            case FieldNumber::JOINTS_BITFIELD:
              name = JOINTS_BITFIELD_NAME;
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

          left_chars = joints_bitfield_.to_string(left_chars, indent_level + 2, JOINTS_BITFIELD_NAME, true);
      
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


          EmbeddedProto::uint32 joints_bitfield_ = 0U;

    };

    class GetJoints final: public ::EmbeddedProto::MessageInterface
    {
      public:
        GetJoints() = default;
        GetJoints(const GetJoints& rhs )
        {
        }

        GetJoints(const GetJoints&& rhs ) noexcept
        {
        }

        ~GetJoints() override = default;

        enum class FieldNumber : uint32_t
        {
          NOT_SET = 0,
        };

        GetJoints& operator=(const GetJoints& rhs)
        {
          return *this;
        }

        GetJoints& operator=(const GetJoints&& rhs) noexcept
        {
          return *this;
        }


        ::EmbeddedProto::Error serialize(::EmbeddedProto::WriteBufferInterface& buffer) const override
        {
          ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;

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

        }

        static char const* field_number_to_name(const FieldNumber fieldNumber)
        {
          char const* name = nullptr;
          switch(fieldNumber)
          {
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



    };

    class GoHome final: public ::EmbeddedProto::MessageInterface
    {
      public:
        GoHome() = default;
        GoHome(const GoHome& rhs )
        {
          set_joints_bitfield(rhs.get_joints_bitfield());
        }

        GoHome(const GoHome&& rhs ) noexcept
        {
          set_joints_bitfield(rhs.get_joints_bitfield());
        }

        ~GoHome() override = default;

        enum class FieldNumber : uint32_t
        {
          NOT_SET = 0,
          JOINTS_BITFIELD = 1
        };

        GoHome& operator=(const GoHome& rhs)
        {
          set_joints_bitfield(rhs.get_joints_bitfield());
          return *this;
        }

        GoHome& operator=(const GoHome&& rhs) noexcept
        {
          set_joints_bitfield(rhs.get_joints_bitfield());
          return *this;
        }

        static constexpr char const* JOINTS_BITFIELD_NAME = "joints_bitfield";
        inline void clear_joints_bitfield() { joints_bitfield_.clear(); }
        inline void set_joints_bitfield(const uint32_t& value) { joints_bitfield_ = value; }
        inline void set_joints_bitfield(const uint32_t&& value) { joints_bitfield_ = value; }
        inline uint32_t& mutable_joints_bitfield() { return joints_bitfield_.get(); }
        inline const uint32_t& get_joints_bitfield() const { return joints_bitfield_.get(); }
        inline uint32_t joints_bitfield() const { return joints_bitfield_.get(); }


        ::EmbeddedProto::Error serialize(::EmbeddedProto::WriteBufferInterface& buffer) const override
        {
          ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;

          if((0U != joints_bitfield_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
          {
            return_value = joints_bitfield_.serialize_with_id(static_cast<uint32_t>(FieldNumber::JOINTS_BITFIELD), buffer, false);
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
              case FieldNumber::JOINTS_BITFIELD:
                return_value = joints_bitfield_.deserialize_check_type(buffer, wire_type);
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
          clear_joints_bitfield();

        }

        static char const* field_number_to_name(const FieldNumber fieldNumber)
        {
          char const* name = nullptr;
          switch(fieldNumber)
          {
            case FieldNumber::JOINTS_BITFIELD:
              name = JOINTS_BITFIELD_NAME;
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

          left_chars = joints_bitfield_.to_string(left_chars, indent_level + 2, JOINTS_BITFIELD_NAME, true);
      
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


          EmbeddedProto::uint32 joints_bitfield_ = 0U;

    };

    class Init final: public ::EmbeddedProto::MessageInterface
    {
      public:
        Init() = default;
        Init(const Init& rhs )
        {
          set_expected_fw_version(rhs.get_expected_fw_version());
        }

        Init(const Init&& rhs ) noexcept
        {
          set_expected_fw_version(rhs.get_expected_fw_version());
        }

        ~Init() override = default;

        enum class FieldNumber : uint32_t
        {
          NOT_SET = 0,
          EXPECTED_FW_VERSION = 1
        };

        Init& operator=(const Init& rhs)
        {
          set_expected_fw_version(rhs.get_expected_fw_version());
          return *this;
        }

        Init& operator=(const Init&& rhs) noexcept
        {
          set_expected_fw_version(rhs.get_expected_fw_version());
          return *this;
        }

        static constexpr char const* EXPECTED_FW_VERSION_NAME = "expected_fw_version";
        inline void clear_expected_fw_version() { expected_fw_version_.clear(); }
        inline void set_expected_fw_version(const uint32_t& value) { expected_fw_version_ = value; }
        inline void set_expected_fw_version(const uint32_t&& value) { expected_fw_version_ = value; }
        inline uint32_t& mutable_expected_fw_version() { return expected_fw_version_.get(); }
        inline const uint32_t& get_expected_fw_version() const { return expected_fw_version_.get(); }
        inline uint32_t expected_fw_version() const { return expected_fw_version_.get(); }


        ::EmbeddedProto::Error serialize(::EmbeddedProto::WriteBufferInterface& buffer) const override
        {
          ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;

          if((0U != expected_fw_version_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
          {
            return_value = expected_fw_version_.serialize_with_id(static_cast<uint32_t>(FieldNumber::EXPECTED_FW_VERSION), buffer, false);
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
              case FieldNumber::EXPECTED_FW_VERSION:
                return_value = expected_fw_version_.deserialize_check_type(buffer, wire_type);
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
          clear_expected_fw_version();

        }

        static char const* field_number_to_name(const FieldNumber fieldNumber)
        {
          char const* name = nullptr;
          switch(fieldNumber)
          {
            case FieldNumber::EXPECTED_FW_VERSION:
              name = EXPECTED_FW_VERSION_NAME;
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

          left_chars = expected_fw_version_.to_string(left_chars, indent_level + 2, EXPECTED_FW_VERSION_NAME, true);
      
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


          EmbeddedProto::uint32 expected_fw_version_ = 0U;

    };

    template<
        uint32_t MoveSpeed_speeds_REP_LENGTH
    >
    class MoveSpeed final: public ::EmbeddedProto::MessageInterface
    {
      public:
        MoveSpeed() = default;
        MoveSpeed(const MoveSpeed& rhs )
        {
          set_speeds(rhs.get_speeds());
        }

        MoveSpeed(const MoveSpeed&& rhs ) noexcept
        {
          set_speeds(rhs.get_speeds());
        }

        ~MoveSpeed() override = default;

        class SpeedsEntry final: public ::EmbeddedProto::MessageInterface
        {
          public:
            SpeedsEntry() = default;
            SpeedsEntry(const SpeedsEntry& rhs )
            {
              set_key(rhs.get_key());
              set_value(rhs.get_value());
            }

            SpeedsEntry(const SpeedsEntry&& rhs ) noexcept
            {
              set_key(rhs.get_key());
              set_value(rhs.get_value());
            }

            ~SpeedsEntry() override = default;

            enum class FieldNumber : uint32_t
            {
              NOT_SET = 0,
              KEY = 1,
              VALUE = 2
            };

            SpeedsEntry& operator=(const SpeedsEntry& rhs)
            {
              set_key(rhs.get_key());
              set_value(rhs.get_value());
              return *this;
            }

            SpeedsEntry& operator=(const SpeedsEntry&& rhs) noexcept
            {
              set_key(rhs.get_key());
              set_value(rhs.get_value());
              return *this;
            }

            static constexpr char const* KEY_NAME = "key";
            inline void clear_key() { key_.clear(); }
            inline void set_key(const uint32_t& value) { key_ = value; }
            inline void set_key(const uint32_t&& value) { key_ = value; }
            inline uint32_t& mutable_key() { return key_.get(); }
            inline const uint32_t& get_key() const { return key_.get(); }
            inline uint32_t key() const { return key_.get(); }

            static constexpr char const* VALUE_NAME = "value";
            inline void clear_value() { value_.clear(); }
            inline void set_value(const float& value) { value_ = value; }
            inline void set_value(const float&& value) { value_ = value; }
            inline float& mutable_value() { return value_.get(); }
            inline const float& get_value() const { return value_.get(); }
            inline float value() const { return value_.get(); }


            ::EmbeddedProto::Error serialize(::EmbeddedProto::WriteBufferInterface& buffer) const override
            {
              ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;

              if((0U != key_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
              {
                return_value = key_.serialize_with_id(static_cast<uint32_t>(FieldNumber::KEY), buffer, false);
              }

              if((0.0 != value_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
              {
                return_value = value_.serialize_with_id(static_cast<uint32_t>(FieldNumber::VALUE), buffer, false);
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
                  case FieldNumber::KEY:
                    return_value = key_.deserialize_check_type(buffer, wire_type);
                    break;

                  case FieldNumber::VALUE:
                    return_value = value_.deserialize_check_type(buffer, wire_type);
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
              clear_key();
              clear_value();

            }

            static char const* field_number_to_name(const FieldNumber fieldNumber)
            {
              char const* name = nullptr;
              switch(fieldNumber)
              {
                case FieldNumber::KEY:
                  name = KEY_NAME;
                  break;
                case FieldNumber::VALUE:
                  name = VALUE_NAME;
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

              left_chars = key_.to_string(left_chars, indent_level + 2, KEY_NAME, true);
              left_chars = value_.to_string(left_chars, indent_level + 2, VALUE_NAME, false);
          
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


              EmbeddedProto::uint32 key_ = 0U;
              EmbeddedProto::floatfixed value_ = 0.0;

        };

        enum class FieldNumber : uint32_t
        {
          NOT_SET = 0,
          SPEEDS = 1
        };

        MoveSpeed& operator=(const MoveSpeed& rhs)
        {
          set_speeds(rhs.get_speeds());
          return *this;
        }

        MoveSpeed& operator=(const MoveSpeed&& rhs) noexcept
        {
          set_speeds(rhs.get_speeds());
          return *this;
        }

        static constexpr char const* SPEEDS_NAME = "speeds";
        inline const SpeedsEntry& speeds(uint32_t index) const { return speeds_[index]; }
        inline void clear_speeds() { speeds_.clear(); }
        inline void set_speeds(uint32_t index, const SpeedsEntry& value) { speeds_.set(index, value); }
        inline void set_speeds(uint32_t index, const SpeedsEntry&& value) { speeds_.set(index, value); }
        inline void set_speeds(const ::EmbeddedProto::RepeatedFieldFixedSize<SpeedsEntry, MoveSpeed_speeds_REP_LENGTH>& values) { speeds_ = values; }
        inline void add_speeds(const SpeedsEntry& value) { speeds_.add(value); }
        inline ::EmbeddedProto::RepeatedFieldFixedSize<SpeedsEntry, MoveSpeed_speeds_REP_LENGTH>& mutable_speeds() { return speeds_; }
        inline SpeedsEntry& mutable_speeds(uint32_t index) { return speeds_[index]; }
        inline const ::EmbeddedProto::RepeatedFieldFixedSize<SpeedsEntry, MoveSpeed_speeds_REP_LENGTH>& get_speeds() const { return speeds_; }
        inline const ::EmbeddedProto::RepeatedFieldFixedSize<SpeedsEntry, MoveSpeed_speeds_REP_LENGTH>& speeds() const { return speeds_; }


        ::EmbeddedProto::Error serialize(::EmbeddedProto::WriteBufferInterface& buffer) const override
        {
          ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;

          if(::EmbeddedProto::Error::NO_ERRORS == return_value)
          {
            return_value = speeds_.serialize_with_id(static_cast<uint32_t>(FieldNumber::SPEEDS), buffer, false);
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
              case FieldNumber::SPEEDS:
                return_value = speeds_.deserialize_check_type(buffer, wire_type);
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
          clear_speeds();

        }

        static char const* field_number_to_name(const FieldNumber fieldNumber)
        {
          char const* name = nullptr;
          switch(fieldNumber)
          {
            case FieldNumber::SPEEDS:
              name = SPEEDS_NAME;
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

          left_chars = speeds_.to_string(left_chars, indent_level + 2, SPEEDS_NAME, true);
      
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


          ::EmbeddedProto::RepeatedFieldFixedSize<SpeedsEntry, MoveSpeed_speeds_REP_LENGTH> speeds_;

    };

    template<
        uint32_t MoveTo_joint_settings_REP_LENGTH
    >
    class MoveTo final: public ::EmbeddedProto::MessageInterface
    {
      public:
        MoveTo() = default;
        MoveTo(const MoveTo& rhs )
        {
          set_joint_settings(rhs.get_joint_settings());
        }

        MoveTo(const MoveTo&& rhs ) noexcept
        {
          set_joint_settings(rhs.get_joint_settings());
        }

        ~MoveTo() override = default;

        class MoveToConfig final: public ::EmbeddedProto::MessageInterface
        {
          public:
            MoveToConfig() = default;
            MoveToConfig(const MoveToConfig& rhs )
            {
              set_angle(rhs.get_angle());
              set_speed(rhs.get_speed());
            }

            MoveToConfig(const MoveToConfig&& rhs ) noexcept
            {
              set_angle(rhs.get_angle());
              set_speed(rhs.get_speed());
            }

            ~MoveToConfig() override = default;

            enum class FieldNumber : uint32_t
            {
              NOT_SET = 0,
              ANGLE = 1,
              SPEED = 2
            };

            MoveToConfig& operator=(const MoveToConfig& rhs)
            {
              set_angle(rhs.get_angle());
              set_speed(rhs.get_speed());
              return *this;
            }

            MoveToConfig& operator=(const MoveToConfig&& rhs) noexcept
            {
              set_angle(rhs.get_angle());
              set_speed(rhs.get_speed());
              return *this;
            }

            static constexpr char const* ANGLE_NAME = "angle";
            inline void clear_angle() { angle_.clear(); }
            inline void set_angle(const float& value) { angle_ = value; }
            inline void set_angle(const float&& value) { angle_ = value; }
            inline float& mutable_angle() { return angle_.get(); }
            inline const float& get_angle() const { return angle_.get(); }
            inline float angle() const { return angle_.get(); }

            static constexpr char const* SPEED_NAME = "speed";
            inline void clear_speed() { speed_.clear(); }
            inline void set_speed(const float& value) { speed_ = value; }
            inline void set_speed(const float&& value) { speed_ = value; }
            inline float& mutable_speed() { return speed_.get(); }
            inline const float& get_speed() const { return speed_.get(); }
            inline float speed() const { return speed_.get(); }


            ::EmbeddedProto::Error serialize(::EmbeddedProto::WriteBufferInterface& buffer) const override
            {
              ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;

              if((0.0 != angle_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
              {
                return_value = angle_.serialize_with_id(static_cast<uint32_t>(FieldNumber::ANGLE), buffer, false);
              }

              if((0.0 != speed_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
              {
                return_value = speed_.serialize_with_id(static_cast<uint32_t>(FieldNumber::SPEED), buffer, false);
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
                  case FieldNumber::ANGLE:
                    return_value = angle_.deserialize_check_type(buffer, wire_type);
                    break;

                  case FieldNumber::SPEED:
                    return_value = speed_.deserialize_check_type(buffer, wire_type);
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
              clear_angle();
              clear_speed();

            }

            static char const* field_number_to_name(const FieldNumber fieldNumber)
            {
              char const* name = nullptr;
              switch(fieldNumber)
              {
                case FieldNumber::ANGLE:
                  name = ANGLE_NAME;
                  break;
                case FieldNumber::SPEED:
                  name = SPEED_NAME;
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

              left_chars = angle_.to_string(left_chars, indent_level + 2, ANGLE_NAME, true);
              left_chars = speed_.to_string(left_chars, indent_level + 2, SPEED_NAME, false);
          
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


              EmbeddedProto::floatfixed angle_ = 0.0;
              EmbeddedProto::floatfixed speed_ = 0.0;

        };

        class JointSettingsEntry final: public ::EmbeddedProto::MessageInterface
        {
          public:
            JointSettingsEntry() = default;
            JointSettingsEntry(const JointSettingsEntry& rhs )
            {
              set_key(rhs.get_key());
              set_value(rhs.get_value());
            }

            JointSettingsEntry(const JointSettingsEntry&& rhs ) noexcept
            {
              set_key(rhs.get_key());
              set_value(rhs.get_value());
            }

            ~JointSettingsEntry() override = default;

            enum class FieldNumber : uint32_t
            {
              NOT_SET = 0,
              KEY = 1,
              VALUE = 2
            };

            JointSettingsEntry& operator=(const JointSettingsEntry& rhs)
            {
              set_key(rhs.get_key());
              set_value(rhs.get_value());
              return *this;
            }

            JointSettingsEntry& operator=(const JointSettingsEntry&& rhs) noexcept
            {
              set_key(rhs.get_key());
              set_value(rhs.get_value());
              return *this;
            }

            static constexpr char const* KEY_NAME = "key";
            inline void clear_key() { key_.clear(); }
            inline void set_key(const uint32_t& value) { key_ = value; }
            inline void set_key(const uint32_t&& value) { key_ = value; }
            inline uint32_t& mutable_key() { return key_.get(); }
            inline const uint32_t& get_key() const { return key_.get(); }
            inline uint32_t key() const { return key_.get(); }

            static constexpr char const* VALUE_NAME = "value";
            inline void clear_value() { value_.clear(); }
            inline void set_value(const MoveToConfig& value) { value_ = value; }
            inline void set_value(const MoveToConfig&& value) { value_ = value; }
            inline MoveToConfig& mutable_value() { return value_; }
            inline const MoveToConfig& get_value() const { return value_; }
            inline const MoveToConfig& value() const { return value_; }


            ::EmbeddedProto::Error serialize(::EmbeddedProto::WriteBufferInterface& buffer) const override
            {
              ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;

              if((0U != key_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
              {
                return_value = key_.serialize_with_id(static_cast<uint32_t>(FieldNumber::KEY), buffer, false);
              }

              if(::EmbeddedProto::Error::NO_ERRORS == return_value)
              {
                return_value = value_.serialize_with_id(static_cast<uint32_t>(FieldNumber::VALUE), buffer, false);
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
                  case FieldNumber::KEY:
                    return_value = key_.deserialize_check_type(buffer, wire_type);
                    break;

                  case FieldNumber::VALUE:
                    return_value = value_.deserialize_check_type(buffer, wire_type);
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
              clear_key();
              clear_value();

            }

            static char const* field_number_to_name(const FieldNumber fieldNumber)
            {
              char const* name = nullptr;
              switch(fieldNumber)
              {
                case FieldNumber::KEY:
                  name = KEY_NAME;
                  break;
                case FieldNumber::VALUE:
                  name = VALUE_NAME;
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

              left_chars = key_.to_string(left_chars, indent_level + 2, KEY_NAME, true);
              left_chars = value_.to_string(left_chars, indent_level + 2, VALUE_NAME, false);
          
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


              EmbeddedProto::uint32 key_ = 0U;
              MoveToConfig value_;

        };

        enum class FieldNumber : uint32_t
        {
          NOT_SET = 0,
          JOINT_SETTINGS = 1
        };

        MoveTo& operator=(const MoveTo& rhs)
        {
          set_joint_settings(rhs.get_joint_settings());
          return *this;
        }

        MoveTo& operator=(const MoveTo&& rhs) noexcept
        {
          set_joint_settings(rhs.get_joint_settings());
          return *this;
        }

        static constexpr char const* JOINT_SETTINGS_NAME = "joint_settings";
        inline const JointSettingsEntry& joint_settings(uint32_t index) const { return joint_settings_[index]; }
        inline void clear_joint_settings() { joint_settings_.clear(); }
        inline void set_joint_settings(uint32_t index, const JointSettingsEntry& value) { joint_settings_.set(index, value); }
        inline void set_joint_settings(uint32_t index, const JointSettingsEntry&& value) { joint_settings_.set(index, value); }
        inline void set_joint_settings(const ::EmbeddedProto::RepeatedFieldFixedSize<JointSettingsEntry, MoveTo_joint_settings_REP_LENGTH>& values) { joint_settings_ = values; }
        inline void add_joint_settings(const JointSettingsEntry& value) { joint_settings_.add(value); }
        inline ::EmbeddedProto::RepeatedFieldFixedSize<JointSettingsEntry, MoveTo_joint_settings_REP_LENGTH>& mutable_joint_settings() { return joint_settings_; }
        inline JointSettingsEntry& mutable_joint_settings(uint32_t index) { return joint_settings_[index]; }
        inline const ::EmbeddedProto::RepeatedFieldFixedSize<JointSettingsEntry, MoveTo_joint_settings_REP_LENGTH>& get_joint_settings() const { return joint_settings_; }
        inline const ::EmbeddedProto::RepeatedFieldFixedSize<JointSettingsEntry, MoveTo_joint_settings_REP_LENGTH>& joint_settings() const { return joint_settings_; }


        ::EmbeddedProto::Error serialize(::EmbeddedProto::WriteBufferInterface& buffer) const override
        {
          ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;

          if(::EmbeddedProto::Error::NO_ERRORS == return_value)
          {
            return_value = joint_settings_.serialize_with_id(static_cast<uint32_t>(FieldNumber::JOINT_SETTINGS), buffer, false);
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
              case FieldNumber::JOINT_SETTINGS:
                return_value = joint_settings_.deserialize_check_type(buffer, wire_type);
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
          clear_joint_settings();

        }

        static char const* field_number_to_name(const FieldNumber fieldNumber)
        {
          char const* name = nullptr;
          switch(fieldNumber)
          {
            case FieldNumber::JOINT_SETTINGS:
              name = JOINT_SETTINGS_NAME;
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

          left_chars = joint_settings_.to_string(left_chars, indent_level + 2, JOINT_SETTINGS_NAME, true);
      
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


          ::EmbeddedProto::RepeatedFieldFixedSize<JointSettingsEntry, MoveTo_joint_settings_REP_LENGTH> joint_settings_;

    };

    template<
        uint32_t Override_new_angles_REP_LENGTH
    >
    class Override final: public ::EmbeddedProto::MessageInterface
    {
      public:
        Override() = default;
        Override(const Override& rhs )
        {
          set_new_angles(rhs.get_new_angles());
        }

        Override(const Override&& rhs ) noexcept
        {
          set_new_angles(rhs.get_new_angles());
        }

        ~Override() override = default;

        class NewAnglesEntry final: public ::EmbeddedProto::MessageInterface
        {
          public:
            NewAnglesEntry() = default;
            NewAnglesEntry(const NewAnglesEntry& rhs )
            {
              set_key(rhs.get_key());
              set_value(rhs.get_value());
            }

            NewAnglesEntry(const NewAnglesEntry&& rhs ) noexcept
            {
              set_key(rhs.get_key());
              set_value(rhs.get_value());
            }

            ~NewAnglesEntry() override = default;

            enum class FieldNumber : uint32_t
            {
              NOT_SET = 0,
              KEY = 1,
              VALUE = 2
            };

            NewAnglesEntry& operator=(const NewAnglesEntry& rhs)
            {
              set_key(rhs.get_key());
              set_value(rhs.get_value());
              return *this;
            }

            NewAnglesEntry& operator=(const NewAnglesEntry&& rhs) noexcept
            {
              set_key(rhs.get_key());
              set_value(rhs.get_value());
              return *this;
            }

            static constexpr char const* KEY_NAME = "key";
            inline void clear_key() { key_.clear(); }
            inline void set_key(const uint32_t& value) { key_ = value; }
            inline void set_key(const uint32_t&& value) { key_ = value; }
            inline uint32_t& mutable_key() { return key_.get(); }
            inline const uint32_t& get_key() const { return key_.get(); }
            inline uint32_t key() const { return key_.get(); }

            static constexpr char const* VALUE_NAME = "value";
            inline void clear_value() { value_.clear(); }
            inline void set_value(const float& value) { value_ = value; }
            inline void set_value(const float&& value) { value_ = value; }
            inline float& mutable_value() { return value_.get(); }
            inline const float& get_value() const { return value_.get(); }
            inline float value() const { return value_.get(); }


            ::EmbeddedProto::Error serialize(::EmbeddedProto::WriteBufferInterface& buffer) const override
            {
              ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;

              if((0U != key_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
              {
                return_value = key_.serialize_with_id(static_cast<uint32_t>(FieldNumber::KEY), buffer, false);
              }

              if((0.0 != value_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
              {
                return_value = value_.serialize_with_id(static_cast<uint32_t>(FieldNumber::VALUE), buffer, false);
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
                  case FieldNumber::KEY:
                    return_value = key_.deserialize_check_type(buffer, wire_type);
                    break;

                  case FieldNumber::VALUE:
                    return_value = value_.deserialize_check_type(buffer, wire_type);
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
              clear_key();
              clear_value();

            }

            static char const* field_number_to_name(const FieldNumber fieldNumber)
            {
              char const* name = nullptr;
              switch(fieldNumber)
              {
                case FieldNumber::KEY:
                  name = KEY_NAME;
                  break;
                case FieldNumber::VALUE:
                  name = VALUE_NAME;
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

              left_chars = key_.to_string(left_chars, indent_level + 2, KEY_NAME, true);
              left_chars = value_.to_string(left_chars, indent_level + 2, VALUE_NAME, false);
          
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


              EmbeddedProto::uint32 key_ = 0U;
              EmbeddedProto::floatfixed value_ = 0.0;

        };

        enum class FieldNumber : uint32_t
        {
          NOT_SET = 0,
          NEW_ANGLES = 1
        };

        Override& operator=(const Override& rhs)
        {
          set_new_angles(rhs.get_new_angles());
          return *this;
        }

        Override& operator=(const Override&& rhs) noexcept
        {
          set_new_angles(rhs.get_new_angles());
          return *this;
        }

        static constexpr char const* NEW_ANGLES_NAME = "new_angles";
        inline const NewAnglesEntry& new_angles(uint32_t index) const { return new_angles_[index]; }
        inline void clear_new_angles() { new_angles_.clear(); }
        inline void set_new_angles(uint32_t index, const NewAnglesEntry& value) { new_angles_.set(index, value); }
        inline void set_new_angles(uint32_t index, const NewAnglesEntry&& value) { new_angles_.set(index, value); }
        inline void set_new_angles(const ::EmbeddedProto::RepeatedFieldFixedSize<NewAnglesEntry, Override_new_angles_REP_LENGTH>& values) { new_angles_ = values; }
        inline void add_new_angles(const NewAnglesEntry& value) { new_angles_.add(value); }
        inline ::EmbeddedProto::RepeatedFieldFixedSize<NewAnglesEntry, Override_new_angles_REP_LENGTH>& mutable_new_angles() { return new_angles_; }
        inline NewAnglesEntry& mutable_new_angles(uint32_t index) { return new_angles_[index]; }
        inline const ::EmbeddedProto::RepeatedFieldFixedSize<NewAnglesEntry, Override_new_angles_REP_LENGTH>& get_new_angles() const { return new_angles_; }
        inline const ::EmbeddedProto::RepeatedFieldFixedSize<NewAnglesEntry, Override_new_angles_REP_LENGTH>& new_angles() const { return new_angles_; }


        ::EmbeddedProto::Error serialize(::EmbeddedProto::WriteBufferInterface& buffer) const override
        {
          ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;

          if(::EmbeddedProto::Error::NO_ERRORS == return_value)
          {
            return_value = new_angles_.serialize_with_id(static_cast<uint32_t>(FieldNumber::NEW_ANGLES), buffer, false);
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
              case FieldNumber::NEW_ANGLES:
                return_value = new_angles_.deserialize_check_type(buffer, wire_type);
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
          clear_new_angles();

        }

        static char const* field_number_to_name(const FieldNumber fieldNumber)
        {
          char const* name = nullptr;
          switch(fieldNumber)
          {
            case FieldNumber::NEW_ANGLES:
              name = NEW_ANGLES_NAME;
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

          left_chars = new_angles_.to_string(left_chars, indent_level + 2, NEW_ANGLES_NAME, true);
      
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


          ::EmbeddedProto::RepeatedFieldFixedSize<NewAnglesEntry, Override_new_angles_REP_LENGTH> new_angles_;

    };

    class Reset final: public ::EmbeddedProto::MessageInterface
    {
      public:
        Reset() = default;
        Reset(const Reset& rhs )
        {
        }

        Reset(const Reset&& rhs ) noexcept
        {
        }

        ~Reset() override = default;

        enum class FieldNumber : uint32_t
        {
          NOT_SET = 0,
        };

        Reset& operator=(const Reset& rhs)
        {
          return *this;
        }

        Reset& operator=(const Reset&& rhs) noexcept
        {
          return *this;
        }


        ::EmbeddedProto::Error serialize(::EmbeddedProto::WriteBufferInterface& buffer) const override
        {
          ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;

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

        }

        static char const* field_number_to_name(const FieldNumber fieldNumber)
        {
          char const* name = nullptr;
          switch(fieldNumber)
          {
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



    };

    class SetLogLevel final: public ::EmbeddedProto::MessageInterface
    {
      public:
        SetLogLevel() = default;
        SetLogLevel(const SetLogLevel& rhs )
        {
          set_log_level(rhs.get_log_level());
        }

        SetLogLevel(const SetLogLevel&& rhs ) noexcept
        {
          set_log_level(rhs.get_log_level());
        }

        ~SetLogLevel() override = default;

        enum class FieldNumber : uint32_t
        {
          NOT_SET = 0,
          LOG_LEVEL = 1
        };

        SetLogLevel& operator=(const SetLogLevel& rhs)
        {
          set_log_level(rhs.get_log_level());
          return *this;
        }

        SetLogLevel& operator=(const SetLogLevel&& rhs) noexcept
        {
          set_log_level(rhs.get_log_level());
          return *this;
        }

        static constexpr char const* LOG_LEVEL_NAME = "log_level";
        inline void clear_log_level() { log_level_.clear(); }
        inline void set_log_level(const LogLevel& value) { log_level_ = value; }
        inline void set_log_level(const LogLevel&& value) { log_level_ = value; }
        inline const LogLevel& get_log_level() const { return log_level_.get(); }
        inline LogLevel log_level() const { return log_level_.get(); }


        ::EmbeddedProto::Error serialize(::EmbeddedProto::WriteBufferInterface& buffer) const override
        {
          ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;

          if((static_cast<LogLevel>(0) != log_level_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
          {
            return_value = log_level_.serialize_with_id(static_cast<uint32_t>(FieldNumber::LOG_LEVEL), buffer, false);
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
              case FieldNumber::LOG_LEVEL:
                return_value = log_level_.deserialize_check_type(buffer, wire_type);
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
          clear_log_level();

        }

        static char const* field_number_to_name(const FieldNumber fieldNumber)
        {
          char const* name = nullptr;
          switch(fieldNumber)
          {
            case FieldNumber::LOG_LEVEL:
              name = LOG_LEVEL_NAME;
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

          left_chars = log_level_.to_string(left_chars, indent_level + 2, LOG_LEVEL_NAME, true);
      
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


          EmbeddedProto::enumeration<LogLevel> log_level_ = static_cast<LogLevel>(0);

    };

    class Stop final: public ::EmbeddedProto::MessageInterface
    {
      public:
        Stop() = default;
        Stop(const Stop& rhs )
        {
          set_immediate(rhs.get_immediate());
          set_joints_bitfield(rhs.get_joints_bitfield());
        }

        Stop(const Stop&& rhs ) noexcept
        {
          set_immediate(rhs.get_immediate());
          set_joints_bitfield(rhs.get_joints_bitfield());
        }

        ~Stop() override = default;

        enum class FieldNumber : uint32_t
        {
          NOT_SET = 0,
          IMMEDIATE = 1,
          JOINTS_BITFIELD = 2
        };

        Stop& operator=(const Stop& rhs)
        {
          set_immediate(rhs.get_immediate());
          set_joints_bitfield(rhs.get_joints_bitfield());
          return *this;
        }

        Stop& operator=(const Stop&& rhs) noexcept
        {
          set_immediate(rhs.get_immediate());
          set_joints_bitfield(rhs.get_joints_bitfield());
          return *this;
        }

        static constexpr char const* IMMEDIATE_NAME = "immediate";
        inline void clear_immediate() { immediate_.clear(); }
        inline void set_immediate(const bool& value) { immediate_ = value; }
        inline void set_immediate(const bool&& value) { immediate_ = value; }
        inline bool& mutable_immediate() { return immediate_.get(); }
        inline const bool& get_immediate() const { return immediate_.get(); }
        inline bool immediate() const { return immediate_.get(); }

        static constexpr char const* JOINTS_BITFIELD_NAME = "joints_bitfield";
        inline void clear_joints_bitfield() { joints_bitfield_.clear(); }
        inline void set_joints_bitfield(const uint32_t& value) { joints_bitfield_ = value; }
        inline void set_joints_bitfield(const uint32_t&& value) { joints_bitfield_ = value; }
        inline uint32_t& mutable_joints_bitfield() { return joints_bitfield_.get(); }
        inline const uint32_t& get_joints_bitfield() const { return joints_bitfield_.get(); }
        inline uint32_t joints_bitfield() const { return joints_bitfield_.get(); }


        ::EmbeddedProto::Error serialize(::EmbeddedProto::WriteBufferInterface& buffer) const override
        {
          ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;

          if((false != immediate_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
          {
            return_value = immediate_.serialize_with_id(static_cast<uint32_t>(FieldNumber::IMMEDIATE), buffer, false);
          }

          if((0U != joints_bitfield_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
          {
            return_value = joints_bitfield_.serialize_with_id(static_cast<uint32_t>(FieldNumber::JOINTS_BITFIELD), buffer, false);
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
              case FieldNumber::IMMEDIATE:
                return_value = immediate_.deserialize_check_type(buffer, wire_type);
                break;

              case FieldNumber::JOINTS_BITFIELD:
                return_value = joints_bitfield_.deserialize_check_type(buffer, wire_type);
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
          clear_immediate();
          clear_joints_bitfield();

        }

        static char const* field_number_to_name(const FieldNumber fieldNumber)
        {
          char const* name = nullptr;
          switch(fieldNumber)
          {
            case FieldNumber::IMMEDIATE:
              name = IMMEDIATE_NAME;
              break;
            case FieldNumber::JOINTS_BITFIELD:
              name = JOINTS_BITFIELD_NAME;
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

          left_chars = immediate_.to_string(left_chars, indent_level + 2, IMMEDIATE_NAME, true);
          left_chars = joints_bitfield_.to_string(left_chars, indent_level + 2, JOINTS_BITFIELD_NAME, false);
      
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


          EmbeddedProto::boolean immediate_ = false;
          EmbeddedProto::uint32 joints_bitfield_ = 0U;

    };

    enum class FieldNumber : uint32_t
    {
      NOT_SET = 0,
      MESSAGE_ID = 1,
      INIT = 3,
      CALIBRATE = 4,
      OVERRIDE = 5,
      GET_JOINTS = 6,
      MOVE_TO = 7,
      MOVE_SPEED = 8,
      STOP = 9,
      GO_HOME = 10,
      RESET = 11,
      SET_LOG_LEVEL = 12
    };

    Request& operator=(const Request& rhs)
    {
      set_message_id(rhs.get_message_id());
      if(rhs.get_which_payload() != which_payload_)
      {
        // First delete the old object in the oneof.
        clear_payload();
      }

      switch(rhs.get_which_payload())
      {
        case FieldNumber::INIT:
          set_init(rhs.get_init());
          break;

        case FieldNumber::CALIBRATE:
          set_calibrate(rhs.get_calibrate());
          break;

        case FieldNumber::OVERRIDE:
          set_override(rhs.get_override());
          break;

        case FieldNumber::GET_JOINTS:
          set_get_joints(rhs.get_get_joints());
          break;

        case FieldNumber::MOVE_TO:
          set_move_to(rhs.get_move_to());
          break;

        case FieldNumber::MOVE_SPEED:
          set_move_speed(rhs.get_move_speed());
          break;

        case FieldNumber::STOP:
          set_stop(rhs.get_stop());
          break;

        case FieldNumber::GO_HOME:
          set_go_home(rhs.get_go_home());
          break;

        case FieldNumber::RESET:
          set_reset(rhs.get_reset());
          break;

        case FieldNumber::SET_LOG_LEVEL:
          set_set_log_level(rhs.get_set_log_level());
          break;

        default:
          break;
      }

      return *this;
    }

    Request& operator=(const Request&& rhs) noexcept
    {
      set_message_id(rhs.get_message_id());
      if(rhs.get_which_payload() != which_payload_)
      {
        // First delete the old object in the oneof.
        clear_payload();
      }

      switch(rhs.get_which_payload())
      {
        case FieldNumber::INIT:
          set_init(rhs.get_init());
          break;

        case FieldNumber::CALIBRATE:
          set_calibrate(rhs.get_calibrate());
          break;

        case FieldNumber::OVERRIDE:
          set_override(rhs.get_override());
          break;

        case FieldNumber::GET_JOINTS:
          set_get_joints(rhs.get_get_joints());
          break;

        case FieldNumber::MOVE_TO:
          set_move_to(rhs.get_move_to());
          break;

        case FieldNumber::MOVE_SPEED:
          set_move_speed(rhs.get_move_speed());
          break;

        case FieldNumber::STOP:
          set_stop(rhs.get_stop());
          break;

        case FieldNumber::GO_HOME:
          set_go_home(rhs.get_go_home());
          break;

        case FieldNumber::RESET:
          set_reset(rhs.get_reset());
          break;

        case FieldNumber::SET_LOG_LEVEL:
          set_set_log_level(rhs.get_set_log_level());
          break;

        default:
          break;
      }

      return *this;
    }

    static constexpr char const* MESSAGE_ID_NAME = "message_id";
    inline void clear_message_id() { message_id_.clear(); }
    inline void set_message_id(const uint32_t& value) { message_id_ = value; }
    inline void set_message_id(const uint32_t&& value) { message_id_ = value; }
    inline uint32_t& mutable_message_id() { return message_id_.get(); }
    inline const uint32_t& get_message_id() const { return message_id_.get(); }
    inline uint32_t message_id() const { return message_id_.get(); }

    FieldNumber get_which_payload() const { return which_payload_; }

    static constexpr char const* INIT_NAME = "init";
    inline bool has_init() const
    {
      return FieldNumber::INIT == which_payload_;
    }
    inline void clear_init()
    {
      if(FieldNumber::INIT == which_payload_)
      {
        which_payload_ = FieldNumber::NOT_SET;
        payload_.init_.~Init();
      }
    }
    inline void set_init(const Init& value)
    {
      if(FieldNumber::INIT != which_payload_)
      {
        init_payload(FieldNumber::INIT);
      }
      payload_.init_ = value;
    }
    inline void set_init(const Init&& value)
    {
      if(FieldNumber::INIT != which_payload_)
      {
        init_payload(FieldNumber::INIT);
      }
      payload_.init_ = value;
    }
    inline Init& mutable_init()
    {
      if(FieldNumber::INIT != which_payload_)
      {
        init_payload(FieldNumber::INIT);
      }
      return payload_.init_;
    }
    inline const Init& get_init() const { return payload_.init_; }
    inline const Init& init() const { return payload_.init_; }

    static constexpr char const* CALIBRATE_NAME = "calibrate";
    inline bool has_calibrate() const
    {
      return FieldNumber::CALIBRATE == which_payload_;
    }
    inline void clear_calibrate()
    {
      if(FieldNumber::CALIBRATE == which_payload_)
      {
        which_payload_ = FieldNumber::NOT_SET;
        payload_.calibrate_.~Calibrate();
      }
    }
    inline void set_calibrate(const Calibrate& value)
    {
      if(FieldNumber::CALIBRATE != which_payload_)
      {
        init_payload(FieldNumber::CALIBRATE);
      }
      payload_.calibrate_ = value;
    }
    inline void set_calibrate(const Calibrate&& value)
    {
      if(FieldNumber::CALIBRATE != which_payload_)
      {
        init_payload(FieldNumber::CALIBRATE);
      }
      payload_.calibrate_ = value;
    }
    inline Calibrate& mutable_calibrate()
    {
      if(FieldNumber::CALIBRATE != which_payload_)
      {
        init_payload(FieldNumber::CALIBRATE);
      }
      return payload_.calibrate_;
    }
    inline const Calibrate& get_calibrate() const { return payload_.calibrate_; }
    inline const Calibrate& calibrate() const { return payload_.calibrate_; }

    static constexpr char const* OVERRIDE_NAME = "override";
    inline bool has_override() const
    {
      return FieldNumber::OVERRIDE == which_payload_;
    }
    inline void clear_override()
    {
      if(FieldNumber::OVERRIDE == which_payload_)
      {
        which_payload_ = FieldNumber::NOT_SET;
        payload_.override_.~Override<Request_override_Override_new_angles_REP_LENGTH>();
      }
    }
    inline void set_override(const Override<Request_override_Override_new_angles_REP_LENGTH>& value)
    {
      if(FieldNumber::OVERRIDE != which_payload_)
      {
        init_payload(FieldNumber::OVERRIDE);
      }
      payload_.override_ = value;
    }
    inline void set_override(const Override<Request_override_Override_new_angles_REP_LENGTH>&& value)
    {
      if(FieldNumber::OVERRIDE != which_payload_)
      {
        init_payload(FieldNumber::OVERRIDE);
      }
      payload_.override_ = value;
    }
    inline Override<Request_override_Override_new_angles_REP_LENGTH>& mutable_override()
    {
      if(FieldNumber::OVERRIDE != which_payload_)
      {
        init_payload(FieldNumber::OVERRIDE);
      }
      return payload_.override_;
    }
    inline const Override<Request_override_Override_new_angles_REP_LENGTH>& get_override() const { return payload_.override_; }
    inline const Override<Request_override_Override_new_angles_REP_LENGTH>& override() const { return payload_.override_; }

    static constexpr char const* GET_JOINTS_NAME = "get_joints";
    inline bool has_get_joints() const
    {
      return FieldNumber::GET_JOINTS == which_payload_;
    }
    inline void clear_get_joints()
    {
      if(FieldNumber::GET_JOINTS == which_payload_)
      {
        which_payload_ = FieldNumber::NOT_SET;
        payload_.get_joints_.~GetJoints();
      }
    }
    inline void set_get_joints(const GetJoints& value)
    {
      if(FieldNumber::GET_JOINTS != which_payload_)
      {
        init_payload(FieldNumber::GET_JOINTS);
      }
      payload_.get_joints_ = value;
    }
    inline void set_get_joints(const GetJoints&& value)
    {
      if(FieldNumber::GET_JOINTS != which_payload_)
      {
        init_payload(FieldNumber::GET_JOINTS);
      }
      payload_.get_joints_ = value;
    }
    inline GetJoints& mutable_get_joints()
    {
      if(FieldNumber::GET_JOINTS != which_payload_)
      {
        init_payload(FieldNumber::GET_JOINTS);
      }
      return payload_.get_joints_;
    }
    inline const GetJoints& get_get_joints() const { return payload_.get_joints_; }
    inline const GetJoints& get_joints() const { return payload_.get_joints_; }

    static constexpr char const* MOVE_TO_NAME = "move_to";
    inline bool has_move_to() const
    {
      return FieldNumber::MOVE_TO == which_payload_;
    }
    inline void clear_move_to()
    {
      if(FieldNumber::MOVE_TO == which_payload_)
      {
        which_payload_ = FieldNumber::NOT_SET;
        payload_.move_to_.~MoveTo<Request_move_to_MoveTo_joint_settings_REP_LENGTH>();
      }
    }
    inline void set_move_to(const MoveTo<Request_move_to_MoveTo_joint_settings_REP_LENGTH>& value)
    {
      if(FieldNumber::MOVE_TO != which_payload_)
      {
        init_payload(FieldNumber::MOVE_TO);
      }
      payload_.move_to_ = value;
    }
    inline void set_move_to(const MoveTo<Request_move_to_MoveTo_joint_settings_REP_LENGTH>&& value)
    {
      if(FieldNumber::MOVE_TO != which_payload_)
      {
        init_payload(FieldNumber::MOVE_TO);
      }
      payload_.move_to_ = value;
    }
    inline MoveTo<Request_move_to_MoveTo_joint_settings_REP_LENGTH>& mutable_move_to()
    {
      if(FieldNumber::MOVE_TO != which_payload_)
      {
        init_payload(FieldNumber::MOVE_TO);
      }
      return payload_.move_to_;
    }
    inline const MoveTo<Request_move_to_MoveTo_joint_settings_REP_LENGTH>& get_move_to() const { return payload_.move_to_; }
    inline const MoveTo<Request_move_to_MoveTo_joint_settings_REP_LENGTH>& move_to() const { return payload_.move_to_; }

    static constexpr char const* MOVE_SPEED_NAME = "move_speed";
    inline bool has_move_speed() const
    {
      return FieldNumber::MOVE_SPEED == which_payload_;
    }
    inline void clear_move_speed()
    {
      if(FieldNumber::MOVE_SPEED == which_payload_)
      {
        which_payload_ = FieldNumber::NOT_SET;
        payload_.move_speed_.~MoveSpeed<Request_move_speed_MoveSpeed_speeds_REP_LENGTH>();
      }
    }
    inline void set_move_speed(const MoveSpeed<Request_move_speed_MoveSpeed_speeds_REP_LENGTH>& value)
    {
      if(FieldNumber::MOVE_SPEED != which_payload_)
      {
        init_payload(FieldNumber::MOVE_SPEED);
      }
      payload_.move_speed_ = value;
    }
    inline void set_move_speed(const MoveSpeed<Request_move_speed_MoveSpeed_speeds_REP_LENGTH>&& value)
    {
      if(FieldNumber::MOVE_SPEED != which_payload_)
      {
        init_payload(FieldNumber::MOVE_SPEED);
      }
      payload_.move_speed_ = value;
    }
    inline MoveSpeed<Request_move_speed_MoveSpeed_speeds_REP_LENGTH>& mutable_move_speed()
    {
      if(FieldNumber::MOVE_SPEED != which_payload_)
      {
        init_payload(FieldNumber::MOVE_SPEED);
      }
      return payload_.move_speed_;
    }
    inline const MoveSpeed<Request_move_speed_MoveSpeed_speeds_REP_LENGTH>& get_move_speed() const { return payload_.move_speed_; }
    inline const MoveSpeed<Request_move_speed_MoveSpeed_speeds_REP_LENGTH>& move_speed() const { return payload_.move_speed_; }

    static constexpr char const* STOP_NAME = "stop";
    inline bool has_stop() const
    {
      return FieldNumber::STOP == which_payload_;
    }
    inline void clear_stop()
    {
      if(FieldNumber::STOP == which_payload_)
      {
        which_payload_ = FieldNumber::NOT_SET;
        payload_.stop_.~Stop();
      }
    }
    inline void set_stop(const Stop& value)
    {
      if(FieldNumber::STOP != which_payload_)
      {
        init_payload(FieldNumber::STOP);
      }
      payload_.stop_ = value;
    }
    inline void set_stop(const Stop&& value)
    {
      if(FieldNumber::STOP != which_payload_)
      {
        init_payload(FieldNumber::STOP);
      }
      payload_.stop_ = value;
    }
    inline Stop& mutable_stop()
    {
      if(FieldNumber::STOP != which_payload_)
      {
        init_payload(FieldNumber::STOP);
      }
      return payload_.stop_;
    }
    inline const Stop& get_stop() const { return payload_.stop_; }
    inline const Stop& stop() const { return payload_.stop_; }

    static constexpr char const* GO_HOME_NAME = "go_home";
    inline bool has_go_home() const
    {
      return FieldNumber::GO_HOME == which_payload_;
    }
    inline void clear_go_home()
    {
      if(FieldNumber::GO_HOME == which_payload_)
      {
        which_payload_ = FieldNumber::NOT_SET;
        payload_.go_home_.~GoHome();
      }
    }
    inline void set_go_home(const GoHome& value)
    {
      if(FieldNumber::GO_HOME != which_payload_)
      {
        init_payload(FieldNumber::GO_HOME);
      }
      payload_.go_home_ = value;
    }
    inline void set_go_home(const GoHome&& value)
    {
      if(FieldNumber::GO_HOME != which_payload_)
      {
        init_payload(FieldNumber::GO_HOME);
      }
      payload_.go_home_ = value;
    }
    inline GoHome& mutable_go_home()
    {
      if(FieldNumber::GO_HOME != which_payload_)
      {
        init_payload(FieldNumber::GO_HOME);
      }
      return payload_.go_home_;
    }
    inline const GoHome& get_go_home() const { return payload_.go_home_; }
    inline const GoHome& go_home() const { return payload_.go_home_; }

    static constexpr char const* RESET_NAME = "reset";
    inline bool has_reset() const
    {
      return FieldNumber::RESET == which_payload_;
    }
    inline void clear_reset()
    {
      if(FieldNumber::RESET == which_payload_)
      {
        which_payload_ = FieldNumber::NOT_SET;
        payload_.reset_.~Reset();
      }
    }
    inline void set_reset(const Reset& value)
    {
      if(FieldNumber::RESET != which_payload_)
      {
        init_payload(FieldNumber::RESET);
      }
      payload_.reset_ = value;
    }
    inline void set_reset(const Reset&& value)
    {
      if(FieldNumber::RESET != which_payload_)
      {
        init_payload(FieldNumber::RESET);
      }
      payload_.reset_ = value;
    }
    inline Reset& mutable_reset()
    {
      if(FieldNumber::RESET != which_payload_)
      {
        init_payload(FieldNumber::RESET);
      }
      return payload_.reset_;
    }
    inline const Reset& get_reset() const { return payload_.reset_; }
    inline const Reset& reset() const { return payload_.reset_; }

    static constexpr char const* SET_LOG_LEVEL_NAME = "set_log_level";
    inline bool has_set_log_level() const
    {
      return FieldNumber::SET_LOG_LEVEL == which_payload_;
    }
    inline void clear_set_log_level()
    {
      if(FieldNumber::SET_LOG_LEVEL == which_payload_)
      {
        which_payload_ = FieldNumber::NOT_SET;
        payload_.set_log_level_.~SetLogLevel();
      }
    }
    inline void set_set_log_level(const SetLogLevel& value)
    {
      if(FieldNumber::SET_LOG_LEVEL != which_payload_)
      {
        init_payload(FieldNumber::SET_LOG_LEVEL);
      }
      payload_.set_log_level_ = value;
    }
    inline void set_set_log_level(const SetLogLevel&& value)
    {
      if(FieldNumber::SET_LOG_LEVEL != which_payload_)
      {
        init_payload(FieldNumber::SET_LOG_LEVEL);
      }
      payload_.set_log_level_ = value;
    }
    inline SetLogLevel& mutable_set_log_level()
    {
      if(FieldNumber::SET_LOG_LEVEL != which_payload_)
      {
        init_payload(FieldNumber::SET_LOG_LEVEL);
      }
      return payload_.set_log_level_;
    }
    inline const SetLogLevel& get_set_log_level() const { return payload_.set_log_level_; }
    inline const SetLogLevel& set_log_level() const { return payload_.set_log_level_; }


    ::EmbeddedProto::Error serialize(::EmbeddedProto::WriteBufferInterface& buffer) const override
    {
      ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;

      if((0U != message_id_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = message_id_.serialize_with_id(static_cast<uint32_t>(FieldNumber::MESSAGE_ID), buffer, false);
      }

      switch(which_payload_)
      {
        case FieldNumber::INIT:
          if(has_init() && (::EmbeddedProto::Error::NO_ERRORS == return_value))
          {
            return_value = payload_.init_.serialize_with_id(static_cast<uint32_t>(FieldNumber::INIT), buffer, true);
          }
          break;

        case FieldNumber::CALIBRATE:
          if(has_calibrate() && (::EmbeddedProto::Error::NO_ERRORS == return_value))
          {
            return_value = payload_.calibrate_.serialize_with_id(static_cast<uint32_t>(FieldNumber::CALIBRATE), buffer, true);
          }
          break;

        case FieldNumber::OVERRIDE:
          if(has_override() && (::EmbeddedProto::Error::NO_ERRORS == return_value))
          {
            return_value = payload_.override_.serialize_with_id(static_cast<uint32_t>(FieldNumber::OVERRIDE), buffer, true);
          }
          break;

        case FieldNumber::GET_JOINTS:
          if(has_get_joints() && (::EmbeddedProto::Error::NO_ERRORS == return_value))
          {
            return_value = payload_.get_joints_.serialize_with_id(static_cast<uint32_t>(FieldNumber::GET_JOINTS), buffer, true);
          }
          break;

        case FieldNumber::MOVE_TO:
          if(has_move_to() && (::EmbeddedProto::Error::NO_ERRORS == return_value))
          {
            return_value = payload_.move_to_.serialize_with_id(static_cast<uint32_t>(FieldNumber::MOVE_TO), buffer, true);
          }
          break;

        case FieldNumber::MOVE_SPEED:
          if(has_move_speed() && (::EmbeddedProto::Error::NO_ERRORS == return_value))
          {
            return_value = payload_.move_speed_.serialize_with_id(static_cast<uint32_t>(FieldNumber::MOVE_SPEED), buffer, true);
          }
          break;

        case FieldNumber::STOP:
          if(has_stop() && (::EmbeddedProto::Error::NO_ERRORS == return_value))
          {
            return_value = payload_.stop_.serialize_with_id(static_cast<uint32_t>(FieldNumber::STOP), buffer, true);
          }
          break;

        case FieldNumber::GO_HOME:
          if(has_go_home() && (::EmbeddedProto::Error::NO_ERRORS == return_value))
          {
            return_value = payload_.go_home_.serialize_with_id(static_cast<uint32_t>(FieldNumber::GO_HOME), buffer, true);
          }
          break;

        case FieldNumber::RESET:
          if(has_reset() && (::EmbeddedProto::Error::NO_ERRORS == return_value))
          {
            return_value = payload_.reset_.serialize_with_id(static_cast<uint32_t>(FieldNumber::RESET), buffer, true);
          }
          break;

        case FieldNumber::SET_LOG_LEVEL:
          if(has_set_log_level() && (::EmbeddedProto::Error::NO_ERRORS == return_value))
          {
            return_value = payload_.set_log_level_.serialize_with_id(static_cast<uint32_t>(FieldNumber::SET_LOG_LEVEL), buffer, true);
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
          case FieldNumber::MESSAGE_ID:
            return_value = message_id_.deserialize_check_type(buffer, wire_type);
            break;

          case FieldNumber::INIT:
          case FieldNumber::CALIBRATE:
          case FieldNumber::OVERRIDE:
          case FieldNumber::GET_JOINTS:
          case FieldNumber::MOVE_TO:
          case FieldNumber::MOVE_SPEED:
          case FieldNumber::STOP:
          case FieldNumber::GO_HOME:
          case FieldNumber::RESET:
          case FieldNumber::SET_LOG_LEVEL:
            return_value = deserialize_payload(id_tag, buffer, wire_type);
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
      clear_message_id();
      clear_payload();

    }

    static char const* field_number_to_name(const FieldNumber fieldNumber)
    {
      char const* name = nullptr;
      switch(fieldNumber)
      {
        case FieldNumber::MESSAGE_ID:
          name = MESSAGE_ID_NAME;
          break;
        case FieldNumber::INIT:
          name = INIT_NAME;
          break;
        case FieldNumber::CALIBRATE:
          name = CALIBRATE_NAME;
          break;
        case FieldNumber::OVERRIDE:
          name = OVERRIDE_NAME;
          break;
        case FieldNumber::GET_JOINTS:
          name = GET_JOINTS_NAME;
          break;
        case FieldNumber::MOVE_TO:
          name = MOVE_TO_NAME;
          break;
        case FieldNumber::MOVE_SPEED:
          name = MOVE_SPEED_NAME;
          break;
        case FieldNumber::STOP:
          name = STOP_NAME;
          break;
        case FieldNumber::GO_HOME:
          name = GO_HOME_NAME;
          break;
        case FieldNumber::RESET:
          name = RESET_NAME;
          break;
        case FieldNumber::SET_LOG_LEVEL:
          name = SET_LOG_LEVEL_NAME;
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

      left_chars = message_id_.to_string(left_chars, indent_level + 2, MESSAGE_ID_NAME, true);
      left_chars = to_string_payload(left_chars, indent_level + 2, false);
  
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


      EmbeddedProto::fixed32 message_id_ = 0U;

      FieldNumber which_payload_ = FieldNumber::NOT_SET;
      union payload
      {
        payload() {}
        ~payload() {}
        Init init_;
        Calibrate calibrate_;
        Override<Request_override_Override_new_angles_REP_LENGTH> override_;
        GetJoints get_joints_;
        MoveTo<Request_move_to_MoveTo_joint_settings_REP_LENGTH> move_to_;
        MoveSpeed<Request_move_speed_MoveSpeed_speeds_REP_LENGTH> move_speed_;
        Stop stop_;
        GoHome go_home_;
        Reset reset_;
        SetLogLevel set_log_level_;
      };
      payload payload_;

      void init_payload(const FieldNumber field_id)
      {
        if(FieldNumber::NOT_SET != which_payload_)
        {
          // First delete the old object in the oneof.
          clear_payload();
        }

        // C++11 unions only support nontrivial members when you explicitly call the placement new statement.
        switch(field_id)
        {
          case FieldNumber::INIT:
            new(&payload_.init_) Init;
            break;

          case FieldNumber::CALIBRATE:
            new(&payload_.calibrate_) Calibrate;
            break;

          case FieldNumber::OVERRIDE:
            new(&payload_.override_) Override<Request_override_Override_new_angles_REP_LENGTH>;
            break;

          case FieldNumber::GET_JOINTS:
            new(&payload_.get_joints_) GetJoints;
            break;

          case FieldNumber::MOVE_TO:
            new(&payload_.move_to_) MoveTo<Request_move_to_MoveTo_joint_settings_REP_LENGTH>;
            break;

          case FieldNumber::MOVE_SPEED:
            new(&payload_.move_speed_) MoveSpeed<Request_move_speed_MoveSpeed_speeds_REP_LENGTH>;
            break;

          case FieldNumber::STOP:
            new(&payload_.stop_) Stop;
            break;

          case FieldNumber::GO_HOME:
            new(&payload_.go_home_) GoHome;
            break;

          case FieldNumber::RESET:
            new(&payload_.reset_) Reset;
            break;

          case FieldNumber::SET_LOG_LEVEL:
            new(&payload_.set_log_level_) SetLogLevel;
            break;

          default:
            break;
         }

         which_payload_ = field_id;
      }

      void clear_payload()
      {
        switch(which_payload_)
        {
          case FieldNumber::INIT:
            ::EmbeddedProto::destroy_at(&payload_.init_);
            break;
          case FieldNumber::CALIBRATE:
            ::EmbeddedProto::destroy_at(&payload_.calibrate_);
            break;
          case FieldNumber::OVERRIDE:
            ::EmbeddedProto::destroy_at(&payload_.override_);
            break;
          case FieldNumber::GET_JOINTS:
            ::EmbeddedProto::destroy_at(&payload_.get_joints_);
            break;
          case FieldNumber::MOVE_TO:
            ::EmbeddedProto::destroy_at(&payload_.move_to_);
            break;
          case FieldNumber::MOVE_SPEED:
            ::EmbeddedProto::destroy_at(&payload_.move_speed_);
            break;
          case FieldNumber::STOP:
            ::EmbeddedProto::destroy_at(&payload_.stop_);
            break;
          case FieldNumber::GO_HOME:
            ::EmbeddedProto::destroy_at(&payload_.go_home_);
            break;
          case FieldNumber::RESET:
            ::EmbeddedProto::destroy_at(&payload_.reset_);
            break;
          case FieldNumber::SET_LOG_LEVEL:
            ::EmbeddedProto::destroy_at(&payload_.set_log_level_);
            break;
          default:
            break;
        }
        which_payload_ = FieldNumber::NOT_SET;
      }

      ::EmbeddedProto::Error deserialize_payload(const FieldNumber field_id, 
                                    ::EmbeddedProto::ReadBufferInterface& buffer,
                                    const ::EmbeddedProto::WireFormatter::WireType wire_type)
      {
        ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;
        
        if(field_id != which_payload_)
        {
          init_payload(field_id);
        }

        switch(which_payload_)
        {
          case FieldNumber::INIT:
            return_value = payload_.init_.deserialize_check_type(buffer, wire_type);
            break;
          case FieldNumber::CALIBRATE:
            return_value = payload_.calibrate_.deserialize_check_type(buffer, wire_type);
            break;
          case FieldNumber::OVERRIDE:
            return_value = payload_.override_.deserialize_check_type(buffer, wire_type);
            break;
          case FieldNumber::GET_JOINTS:
            return_value = payload_.get_joints_.deserialize_check_type(buffer, wire_type);
            break;
          case FieldNumber::MOVE_TO:
            return_value = payload_.move_to_.deserialize_check_type(buffer, wire_type);
            break;
          case FieldNumber::MOVE_SPEED:
            return_value = payload_.move_speed_.deserialize_check_type(buffer, wire_type);
            break;
          case FieldNumber::STOP:
            return_value = payload_.stop_.deserialize_check_type(buffer, wire_type);
            break;
          case FieldNumber::GO_HOME:
            return_value = payload_.go_home_.deserialize_check_type(buffer, wire_type);
            break;
          case FieldNumber::RESET:
            return_value = payload_.reset_.deserialize_check_type(buffer, wire_type);
            break;
          case FieldNumber::SET_LOG_LEVEL:
            return_value = payload_.set_log_level_.deserialize_check_type(buffer, wire_type);
            break;
          default:
            break;
        }

        if(::EmbeddedProto::Error::NO_ERRORS != return_value)
        {
          clear_payload();
        }
        return return_value;
      }

#ifdef MSG_TO_STRING 
      ::EmbeddedProto::string_view to_string_payload(::EmbeddedProto::string_view& str, const uint32_t indent_level, const bool first_field) const
      {
        ::EmbeddedProto::string_view left_chars = str;

        switch(which_payload_)
        {
          case FieldNumber::INIT:
            left_chars = payload_.init_.to_string(left_chars, indent_level, INIT_NAME, first_field);
            break;
          case FieldNumber::CALIBRATE:
            left_chars = payload_.calibrate_.to_string(left_chars, indent_level, CALIBRATE_NAME, first_field);
            break;
          case FieldNumber::OVERRIDE:
            left_chars = payload_.override_.to_string(left_chars, indent_level, OVERRIDE_NAME, first_field);
            break;
          case FieldNumber::GET_JOINTS:
            left_chars = payload_.get_joints_.to_string(left_chars, indent_level, GET_JOINTS_NAME, first_field);
            break;
          case FieldNumber::MOVE_TO:
            left_chars = payload_.move_to_.to_string(left_chars, indent_level, MOVE_TO_NAME, first_field);
            break;
          case FieldNumber::MOVE_SPEED:
            left_chars = payload_.move_speed_.to_string(left_chars, indent_level, MOVE_SPEED_NAME, first_field);
            break;
          case FieldNumber::STOP:
            left_chars = payload_.stop_.to_string(left_chars, indent_level, STOP_NAME, first_field);
            break;
          case FieldNumber::GO_HOME:
            left_chars = payload_.go_home_.to_string(left_chars, indent_level, GO_HOME_NAME, first_field);
            break;
          case FieldNumber::RESET:
            left_chars = payload_.reset_.to_string(left_chars, indent_level, RESET_NAME, first_field);
            break;
          case FieldNumber::SET_LOG_LEVEL:
            left_chars = payload_.set_log_level_.to_string(left_chars, indent_level, SET_LOG_LEVEL_NAME, first_field);
            break;
          default:
            break;
        }

        return left_chars;
      }

#endif // End of MSG_TO_STRING
};

} // End of namespace cobot
#endif // REQUEST_H