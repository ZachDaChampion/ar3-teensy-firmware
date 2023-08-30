/*
 *  This file is generated with Embedded Proto, PLEASE DO NOT EDIT!
 *  source: response.proto
 */

// This file is generated. Please do not edit!
#ifndef RESPONSE_H
#define RESPONSE_H

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
#include "errors.h"

namespace cobot {

template<
    uint32_t Response_error_Error_error_message_LENGTH, 
    uint32_t Response_joints_Joints_positions_REP_LENGTH
>
class Response final: public ::EmbeddedProto::MessageInterface
{
  public:
    Response() = default;
    Response(const Response& rhs )
    {
      set_message_id(rhs.get_message_id());
      if(rhs.get_which_payload() != which_payload_)
      {
        // First delete the old object in the oneof.
        clear_payload();
      }

      switch(rhs.get_which_payload())
      {
        case FieldNumber::ACK:
          set_ack(rhs.get_ack());
          break;

        case FieldNumber::ERROR:
          set_error(rhs.get_error());
          break;

        case FieldNumber::DONE:
          set_done(rhs.get_done());
          break;

        case FieldNumber::JOINTS:
          set_joints(rhs.get_joints());
          break;

        default:
          break;
      }

    }

    Response(const Response&& rhs ) noexcept
    {
      set_message_id(rhs.get_message_id());
      if(rhs.get_which_payload() != which_payload_)
      {
        // First delete the old object in the oneof.
        clear_payload();
      }

      switch(rhs.get_which_payload())
      {
        case FieldNumber::ACK:
          set_ack(rhs.get_ack());
          break;

        case FieldNumber::ERROR:
          set_error(rhs.get_error());
          break;

        case FieldNumber::DONE:
          set_done(rhs.get_done());
          break;

        case FieldNumber::JOINTS:
          set_joints(rhs.get_joints());
          break;

        default:
          break;
      }

    }

    ~Response() override = default;

    class Ack final: public ::EmbeddedProto::MessageInterface
    {
      public:
        Ack() = default;
        Ack(const Ack& rhs )
        {
        }

        Ack(const Ack&& rhs ) noexcept
        {
        }

        ~Ack() override = default;

        enum class FieldNumber : uint32_t
        {
          NOT_SET = 0,
        };

        Ack& operator=(const Ack& rhs)
        {
          return *this;
        }

        Ack& operator=(const Ack&& rhs) noexcept
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

    class Done final: public ::EmbeddedProto::MessageInterface
    {
      public:
        Done() = default;
        Done(const Done& rhs )
        {
        }

        Done(const Done&& rhs ) noexcept
        {
        }

        ~Done() override = default;

        enum class FieldNumber : uint32_t
        {
          NOT_SET = 0,
        };

        Done& operator=(const Done& rhs)
        {
          return *this;
        }

        Done& operator=(const Done&& rhs) noexcept
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

    template<
        uint32_t Error_error_message_LENGTH
    >
    class Error final: public ::EmbeddedProto::MessageInterface
    {
      public:
        Error() = default;
        Error(const Error& rhs )
        {
          set_error_code(rhs.get_error_code());
          set_error_message(rhs.get_error_message());
        }

        Error(const Error&& rhs ) noexcept
        {
          set_error_code(rhs.get_error_code());
          set_error_message(rhs.get_error_message());
        }

        ~Error() override = default;

        enum class FieldNumber : uint32_t
        {
          NOT_SET = 0,
          ERROR_CODE = 1,
          ERROR_MESSAGE = 2
        };

        Error& operator=(const Error& rhs)
        {
          set_error_code(rhs.get_error_code());
          set_error_message(rhs.get_error_message());
          return *this;
        }

        Error& operator=(const Error&& rhs) noexcept
        {
          set_error_code(rhs.get_error_code());
          set_error_message(rhs.get_error_message());
          return *this;
        }

        static constexpr char const* ERROR_CODE_NAME = "error_code";
        inline void clear_error_code() { error_code_.clear(); }
        inline void set_error_code(const ErrorCode& value) { error_code_ = value; }
        inline void set_error_code(const ErrorCode&& value) { error_code_ = value; }
        inline const ErrorCode& get_error_code() const { return error_code_.get(); }
        inline ErrorCode error_code() const { return error_code_.get(); }

        static constexpr char const* ERROR_MESSAGE_NAME = "error_message";
        inline void clear_error_message() { error_message_.clear(); }
        inline ::EmbeddedProto::FieldString<Error_error_message_LENGTH>& mutable_error_message() { return error_message_; }
        inline void set_error_message(const ::EmbeddedProto::FieldString<Error_error_message_LENGTH>& rhs) { error_message_.set(rhs); }
        inline const ::EmbeddedProto::FieldString<Error_error_message_LENGTH>& get_error_message() const { return error_message_; }
        inline const char* error_message() const { return error_message_.get_const(); }


        ::EmbeddedProto::Error serialize(::EmbeddedProto::WriteBufferInterface& buffer) const override
        {
          ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;

          if((static_cast<ErrorCode>(0) != error_code_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
          {
            return_value = error_code_.serialize_with_id(static_cast<uint32_t>(FieldNumber::ERROR_CODE), buffer, false);
          }

          if(::EmbeddedProto::Error::NO_ERRORS == return_value)
          {
            return_value = error_message_.serialize_with_id(static_cast<uint32_t>(FieldNumber::ERROR_MESSAGE), buffer, false);
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
              case FieldNumber::ERROR_CODE:
                return_value = error_code_.deserialize_check_type(buffer, wire_type);
                break;

              case FieldNumber::ERROR_MESSAGE:
                return_value = error_message_.deserialize_check_type(buffer, wire_type);
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
          clear_error_code();
          clear_error_message();

        }

        static char const* field_number_to_name(const FieldNumber fieldNumber)
        {
          char const* name = nullptr;
          switch(fieldNumber)
          {
            case FieldNumber::ERROR_CODE:
              name = ERROR_CODE_NAME;
              break;
            case FieldNumber::ERROR_MESSAGE:
              name = ERROR_MESSAGE_NAME;
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

          left_chars = error_code_.to_string(left_chars, indent_level + 2, ERROR_CODE_NAME, true);
          left_chars = error_message_.to_string(left_chars, indent_level + 2, ERROR_MESSAGE_NAME, false);
      
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


          EmbeddedProto::enumeration<ErrorCode> error_code_ = static_cast<ErrorCode>(0);
          ::EmbeddedProto::FieldString<Error_error_message_LENGTH> error_message_;

    };

    template<
        uint32_t Joints_positions_REP_LENGTH
    >
    class Joints final: public ::EmbeddedProto::MessageInterface
    {
      public:
        Joints() = default;
        Joints(const Joints& rhs )
        {
          set_positions(rhs.get_positions());
        }

        Joints(const Joints&& rhs ) noexcept
        {
          set_positions(rhs.get_positions());
        }

        ~Joints() override = default;

        class PositionsEntry final: public ::EmbeddedProto::MessageInterface
        {
          public:
            PositionsEntry() = default;
            PositionsEntry(const PositionsEntry& rhs )
            {
              set_key(rhs.get_key());
              set_value(rhs.get_value());
            }

            PositionsEntry(const PositionsEntry&& rhs ) noexcept
            {
              set_key(rhs.get_key());
              set_value(rhs.get_value());
            }

            ~PositionsEntry() override = default;

            enum class FieldNumber : uint32_t
            {
              NOT_SET = 0,
              KEY = 1,
              VALUE = 2
            };

            PositionsEntry& operator=(const PositionsEntry& rhs)
            {
              set_key(rhs.get_key());
              set_value(rhs.get_value());
              return *this;
            }

            PositionsEntry& operator=(const PositionsEntry&& rhs) noexcept
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
          POSITIONS = 1
        };

        Joints& operator=(const Joints& rhs)
        {
          set_positions(rhs.get_positions());
          return *this;
        }

        Joints& operator=(const Joints&& rhs) noexcept
        {
          set_positions(rhs.get_positions());
          return *this;
        }

        static constexpr char const* POSITIONS_NAME = "positions";
        inline const PositionsEntry& positions(uint32_t index) const { return positions_[index]; }
        inline void clear_positions() { positions_.clear(); }
        inline void set_positions(uint32_t index, const PositionsEntry& value) { positions_.set(index, value); }
        inline void set_positions(uint32_t index, const PositionsEntry&& value) { positions_.set(index, value); }
        inline void set_positions(const ::EmbeddedProto::RepeatedFieldFixedSize<PositionsEntry, Joints_positions_REP_LENGTH>& values) { positions_ = values; }
        inline void add_positions(const PositionsEntry& value) { positions_.add(value); }
        inline ::EmbeddedProto::RepeatedFieldFixedSize<PositionsEntry, Joints_positions_REP_LENGTH>& mutable_positions() { return positions_; }
        inline PositionsEntry& mutable_positions(uint32_t index) { return positions_[index]; }
        inline const ::EmbeddedProto::RepeatedFieldFixedSize<PositionsEntry, Joints_positions_REP_LENGTH>& get_positions() const { return positions_; }
        inline const ::EmbeddedProto::RepeatedFieldFixedSize<PositionsEntry, Joints_positions_REP_LENGTH>& positions() const { return positions_; }


        ::EmbeddedProto::Error serialize(::EmbeddedProto::WriteBufferInterface& buffer) const override
        {
          ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;

          if(::EmbeddedProto::Error::NO_ERRORS == return_value)
          {
            return_value = positions_.serialize_with_id(static_cast<uint32_t>(FieldNumber::POSITIONS), buffer, false);
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
              case FieldNumber::POSITIONS:
                return_value = positions_.deserialize_check_type(buffer, wire_type);
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
          clear_positions();

        }

        static char const* field_number_to_name(const FieldNumber fieldNumber)
        {
          char const* name = nullptr;
          switch(fieldNumber)
          {
            case FieldNumber::POSITIONS:
              name = POSITIONS_NAME;
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

          left_chars = positions_.to_string(left_chars, indent_level + 2, POSITIONS_NAME, true);
      
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


          ::EmbeddedProto::RepeatedFieldFixedSize<PositionsEntry, Joints_positions_REP_LENGTH> positions_;

    };

    enum class FieldNumber : uint32_t
    {
      NOT_SET = 0,
      MESSAGE_ID = 1,
      ACK = 3,
      ERROR = 4,
      DONE = 5,
      JOINTS = 6
    };

    Response& operator=(const Response& rhs)
    {
      set_message_id(rhs.get_message_id());
      if(rhs.get_which_payload() != which_payload_)
      {
        // First delete the old object in the oneof.
        clear_payload();
      }

      switch(rhs.get_which_payload())
      {
        case FieldNumber::ACK:
          set_ack(rhs.get_ack());
          break;

        case FieldNumber::ERROR:
          set_error(rhs.get_error());
          break;

        case FieldNumber::DONE:
          set_done(rhs.get_done());
          break;

        case FieldNumber::JOINTS:
          set_joints(rhs.get_joints());
          break;

        default:
          break;
      }

      return *this;
    }

    Response& operator=(const Response&& rhs) noexcept
    {
      set_message_id(rhs.get_message_id());
      if(rhs.get_which_payload() != which_payload_)
      {
        // First delete the old object in the oneof.
        clear_payload();
      }

      switch(rhs.get_which_payload())
      {
        case FieldNumber::ACK:
          set_ack(rhs.get_ack());
          break;

        case FieldNumber::ERROR:
          set_error(rhs.get_error());
          break;

        case FieldNumber::DONE:
          set_done(rhs.get_done());
          break;

        case FieldNumber::JOINTS:
          set_joints(rhs.get_joints());
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

    static constexpr char const* ACK_NAME = "ack";
    inline bool has_ack() const
    {
      return FieldNumber::ACK == which_payload_;
    }
    inline void clear_ack()
    {
      if(FieldNumber::ACK == which_payload_)
      {
        which_payload_ = FieldNumber::NOT_SET;
        payload_.ack_.~Ack();
      }
    }
    inline void set_ack(const Ack& value)
    {
      if(FieldNumber::ACK != which_payload_)
      {
        init_payload(FieldNumber::ACK);
      }
      payload_.ack_ = value;
    }
    inline void set_ack(const Ack&& value)
    {
      if(FieldNumber::ACK != which_payload_)
      {
        init_payload(FieldNumber::ACK);
      }
      payload_.ack_ = value;
    }
    inline Ack& mutable_ack()
    {
      if(FieldNumber::ACK != which_payload_)
      {
        init_payload(FieldNumber::ACK);
      }
      return payload_.ack_;
    }
    inline const Ack& get_ack() const { return payload_.ack_; }
    inline const Ack& ack() const { return payload_.ack_; }

    static constexpr char const* ERROR_NAME = "error";
    inline bool has_error() const
    {
      return FieldNumber::ERROR == which_payload_;
    }
    inline void clear_error()
    {
      if(FieldNumber::ERROR == which_payload_)
      {
        which_payload_ = FieldNumber::NOT_SET;
        payload_.error_.~Error<Response_error_Error_error_message_LENGTH>();
      }
    }
    inline void set_error(const Error<Response_error_Error_error_message_LENGTH>& value)
    {
      if(FieldNumber::ERROR != which_payload_)
      {
        init_payload(FieldNumber::ERROR);
      }
      payload_.error_ = value;
    }
    inline void set_error(const Error<Response_error_Error_error_message_LENGTH>&& value)
    {
      if(FieldNumber::ERROR != which_payload_)
      {
        init_payload(FieldNumber::ERROR);
      }
      payload_.error_ = value;
    }
    inline Error<Response_error_Error_error_message_LENGTH>& mutable_error()
    {
      if(FieldNumber::ERROR != which_payload_)
      {
        init_payload(FieldNumber::ERROR);
      }
      return payload_.error_;
    }
    inline const Error<Response_error_Error_error_message_LENGTH>& get_error() const { return payload_.error_; }
    inline const Error<Response_error_Error_error_message_LENGTH>& error() const { return payload_.error_; }

    static constexpr char const* DONE_NAME = "done";
    inline bool has_done() const
    {
      return FieldNumber::DONE == which_payload_;
    }
    inline void clear_done()
    {
      if(FieldNumber::DONE == which_payload_)
      {
        which_payload_ = FieldNumber::NOT_SET;
        payload_.done_.~Done();
      }
    }
    inline void set_done(const Done& value)
    {
      if(FieldNumber::DONE != which_payload_)
      {
        init_payload(FieldNumber::DONE);
      }
      payload_.done_ = value;
    }
    inline void set_done(const Done&& value)
    {
      if(FieldNumber::DONE != which_payload_)
      {
        init_payload(FieldNumber::DONE);
      }
      payload_.done_ = value;
    }
    inline Done& mutable_done()
    {
      if(FieldNumber::DONE != which_payload_)
      {
        init_payload(FieldNumber::DONE);
      }
      return payload_.done_;
    }
    inline const Done& get_done() const { return payload_.done_; }
    inline const Done& done() const { return payload_.done_; }

    static constexpr char const* JOINTS_NAME = "joints";
    inline bool has_joints() const
    {
      return FieldNumber::JOINTS == which_payload_;
    }
    inline void clear_joints()
    {
      if(FieldNumber::JOINTS == which_payload_)
      {
        which_payload_ = FieldNumber::NOT_SET;
        payload_.joints_.~Joints<Response_joints_Joints_positions_REP_LENGTH>();
      }
    }
    inline void set_joints(const Joints<Response_joints_Joints_positions_REP_LENGTH>& value)
    {
      if(FieldNumber::JOINTS != which_payload_)
      {
        init_payload(FieldNumber::JOINTS);
      }
      payload_.joints_ = value;
    }
    inline void set_joints(const Joints<Response_joints_Joints_positions_REP_LENGTH>&& value)
    {
      if(FieldNumber::JOINTS != which_payload_)
      {
        init_payload(FieldNumber::JOINTS);
      }
      payload_.joints_ = value;
    }
    inline Joints<Response_joints_Joints_positions_REP_LENGTH>& mutable_joints()
    {
      if(FieldNumber::JOINTS != which_payload_)
      {
        init_payload(FieldNumber::JOINTS);
      }
      return payload_.joints_;
    }
    inline const Joints<Response_joints_Joints_positions_REP_LENGTH>& get_joints() const { return payload_.joints_; }
    inline const Joints<Response_joints_Joints_positions_REP_LENGTH>& joints() const { return payload_.joints_; }


    ::EmbeddedProto::Error serialize(::EmbeddedProto::WriteBufferInterface& buffer) const override
    {
      ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;

      if((0U != message_id_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = message_id_.serialize_with_id(static_cast<uint32_t>(FieldNumber::MESSAGE_ID), buffer, false);
      }

      switch(which_payload_)
      {
        case FieldNumber::ACK:
          if(has_ack() && (::EmbeddedProto::Error::NO_ERRORS == return_value))
          {
            return_value = payload_.ack_.serialize_with_id(static_cast<uint32_t>(FieldNumber::ACK), buffer, true);
          }
          break;

        case FieldNumber::ERROR:
          if(has_error() && (::EmbeddedProto::Error::NO_ERRORS == return_value))
          {
            return_value = payload_.error_.serialize_with_id(static_cast<uint32_t>(FieldNumber::ERROR), buffer, true);
          }
          break;

        case FieldNumber::DONE:
          if(has_done() && (::EmbeddedProto::Error::NO_ERRORS == return_value))
          {
            return_value = payload_.done_.serialize_with_id(static_cast<uint32_t>(FieldNumber::DONE), buffer, true);
          }
          break;

        case FieldNumber::JOINTS:
          if(has_joints() && (::EmbeddedProto::Error::NO_ERRORS == return_value))
          {
            return_value = payload_.joints_.serialize_with_id(static_cast<uint32_t>(FieldNumber::JOINTS), buffer, true);
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

          case FieldNumber::ACK:
          case FieldNumber::ERROR:
          case FieldNumber::DONE:
          case FieldNumber::JOINTS:
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
        case FieldNumber::ACK:
          name = ACK_NAME;
          break;
        case FieldNumber::ERROR:
          name = ERROR_NAME;
          break;
        case FieldNumber::DONE:
          name = DONE_NAME;
          break;
        case FieldNumber::JOINTS:
          name = JOINTS_NAME;
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
        Ack ack_;
        Error<Response_error_Error_error_message_LENGTH> error_;
        Done done_;
        Joints<Response_joints_Joints_positions_REP_LENGTH> joints_;
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
          case FieldNumber::ACK:
            new(&payload_.ack_) Ack;
            break;

          case FieldNumber::ERROR:
            new(&payload_.error_) Error<Response_error_Error_error_message_LENGTH>;
            break;

          case FieldNumber::DONE:
            new(&payload_.done_) Done;
            break;

          case FieldNumber::JOINTS:
            new(&payload_.joints_) Joints<Response_joints_Joints_positions_REP_LENGTH>;
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
          case FieldNumber::ACK:
            ::EmbeddedProto::destroy_at(&payload_.ack_);
            break;
          case FieldNumber::ERROR:
            ::EmbeddedProto::destroy_at(&payload_.error_);
            break;
          case FieldNumber::DONE:
            ::EmbeddedProto::destroy_at(&payload_.done_);
            break;
          case FieldNumber::JOINTS:
            ::EmbeddedProto::destroy_at(&payload_.joints_);
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
          case FieldNumber::ACK:
            return_value = payload_.ack_.deserialize_check_type(buffer, wire_type);
            break;
          case FieldNumber::ERROR:
            return_value = payload_.error_.deserialize_check_type(buffer, wire_type);
            break;
          case FieldNumber::DONE:
            return_value = payload_.done_.deserialize_check_type(buffer, wire_type);
            break;
          case FieldNumber::JOINTS:
            return_value = payload_.joints_.deserialize_check_type(buffer, wire_type);
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
          case FieldNumber::ACK:
            left_chars = payload_.ack_.to_string(left_chars, indent_level, ACK_NAME, first_field);
            break;
          case FieldNumber::ERROR:
            left_chars = payload_.error_.to_string(left_chars, indent_level, ERROR_NAME, first_field);
            break;
          case FieldNumber::DONE:
            left_chars = payload_.done_.to_string(left_chars, indent_level, DONE_NAME, first_field);
            break;
          case FieldNumber::JOINTS:
            left_chars = payload_.joints_.to_string(left_chars, indent_level, JOINTS_NAME, first_field);
            break;
          default:
            break;
        }

        return left_chars;
      }

#endif // End of MSG_TO_STRING
};

} // End of namespace cobot
#endif // RESPONSE_H