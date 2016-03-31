//
// Copyright 2016 imai hiroyuki.
// All rights reserved.
//
// SPDX-License-Identifier: BSL-1.0
//
#ifndef PETTYSTRING_PETTY_STRING_H_
#define PETTYSTRING_PETTY_STRING_H_

#include <stdarg.h>
#include <string.h>
#include <cstddef>
#include <limits>
#include <string>
#include <utility>
#include <vector>

/// Non-copyable class macro.
/// Macro name is with reference to the Google Style Guides.
///
#ifndef DISALLOW_COPY_AND_ASSIGN
# define DISALLOW_COPY_AND_ASSIGN(TypeName) \
 private: \
  TypeName(const TypeName&); \
  void operator=(const TypeName&)
#endif

/// va_copy macro for MSVC.
///
#if defined(_MSC_VER) && !defined(va_copy)
# define va_copy(dest, src)  ((dest) = (src))
#endif

namespace pettystring {

/// Null option.
///
/// @param data   source data pointer.
/// @param option option data.
/// @return source data if source data pointer is not null,
///         or option data otherwise.
///
template <typename T>
inline T NullOption(T* data, T option) {
  return (data != nullptr) ? *data : std::move(option);
}

/// Null pointer option.
///
/// @param data   source data pointer.
/// @param option option data pointer.
/// @return source data pointer if source data pointer is not null,
///         or option data pointer otherwise.
///
template <typename T>
inline T* NullOptionPtr(T* data, T* option) {
  return (data != nullptr) ? data : option;
}

/// String format.
///
/// @param format string format.
/// @param args   argument.
/// @return string.
///
inline std::string StringFormatV(const char* format, va_list args) {
  // resize buffer
  va_list args_temp;
  va_copy(args_temp, args);
  int length = ::vsnprintf(0, 0, format, args_temp);
  va_end(args_temp);

  if (length > 0) {
    std::vector<char> buffer(length + 1, '\0');

    // string format
    ::vsnprintf(&buffer[0], buffer.size(), format, args);

    return std::string(&buffer[0]);
  } else {
    return std::string();
  }
}

/// String format.
///
/// @param format string format.
/// @return string.
///
inline std::string StringFormat(const char* format, ...) {
  va_list args;
  va_start(args, format);
  std::string value = StringFormatV(format, args);
  va_end(args);

  return std::move(value);
}

/// String front whitespace length.
///
/// @param source source string.
/// @return whitespace length.
///
inline std::string::size_type StringFrontWhitespaceLength(const char* source) {
  std::string::size_type length = 0;

  if (source != nullptr) {
    char character;
    while ((character = source[length]) != '\0') {
      if (((character >= 0x09) && (character <= 0x0d)) || (character == 0x20)) {
        length++;
      } else {
        break;
      }
    }
  }

  return length;
}

/// String back whitespace length.
///
/// @param source source string.
/// @return whitespace length.
///
inline std::string::size_type StringBackWhitespaceLength(const char* source) {
  std::size_t length = 0;

  if (source != nullptr) {
    length = ::strlen(source);
    while (length > 0) {
      char character = source[length - 1];
      if (((character >= 0x09) && (character <= 0x0d)) || (character == 0x20)) {
        length--;
      } else {
        break;
      }
    }
  }

  return length;
}

/// String front whitespace trim.
///
/// @param source source string.
/// @return trim string.
///
inline std::string StringFrontTrim(const char* source) {
  const char* front_trim = source + StringFrontWhitespaceLength(source);
  return std::string(front_trim);
}

/// String back whitespace trim.
///
/// @param str string.
/// @return trim string.
///
inline std::string StringBackTrim(const char* str) {
  return std::string(str, StringBackWhitespaceLength(str));
}

/// String both ends whitespace trim.
///
/// @param source source string.
/// @return trim string.
///
inline std::string StringTrim(const char* str) {
  const char* front_trim = str + StringFrontWhitespaceLength(str);
  return std::string(front_trim, StringBackWhitespaceLength(front_trim));
}

/// Try convert string to integer.
///
/// @param source numeric string.
/// @param radix  radix.
/// @param value  output value.
/// @return true if convert successful, otherwise false.
///
template <typename Integer>
inline bool TryStringToInteger(const char* source, int radix, Integer* value) {
  if (source == nullptr) {
    return false;
  }

  // front trim
  source = source + StringFrontWhitespaceLength(source);

  // sign
  Integer sign;
  Integer limit;
  if (*source == '-') {
    if (std::numeric_limits<Integer>::min() == 0) {
      // is unsigned
      return false;
    }
    source++;
    sign = static_cast<Integer>(-1);
    limit = std::numeric_limits<Integer>::max() - 1;
  } else {
    if (*source == '+') {
      source++;
    }
    sign = static_cast<Integer>(1);
    limit = std::numeric_limits<Integer>::max();
  }

  // radix
  if (source[0] == '0') {
    if ((source[1] | 0x20) == 'x') {
      if ((radix == 0) || (radix == 16)) {
        source += 2;
        radix = 16;
      }
    } else if (radix == 0) {
      radix = 8;
    }
  } else if (radix == 0) {
    radix = 10;
  }

  // back trim
  std::size_t length = StringBackWhitespaceLength(source);
  if (length == 0) {
    return false;
  }

  // convert string to integer
  Integer result = 0;
  for (std::size_t i = 0; i < length; i++, source++) {
    Integer digit;

    char code = *source | 0x20;
    if ((*source >= '0') && (*source <= '9')) {
      digit = *source - '0';
    } else if ((code >= 'a') && (code <= 'z')) {
      digit = 10 + (code - 'a');
    } else {
      return false;
    }

    if ((digit >= static_cast<Integer>(radix))
        || (result > ((limit - digit) / static_cast<Integer>(radix)))) {
      return false;
    }

    result = (result * static_cast<Integer>(radix)) + digit;
  }

  if (value != nullptr) {
    *value = result * sign;
  }

  return true;
}

/// Convert string to integer.
///
/// @param source numeric string.
/// @param radix  radix.
/// @return integer value.
///
template <typename Integer>
inline Integer StringToInteger(const char* source, int radix) {
  Integer value;

  if (TryStringToInteger(source, radix, &value)) {
    return value;
  } else {
    return 0;
  }
}

/// Starts with string.
///
/// @param source source string.
/// @param prefix prefix string.
/// @return ture if value string is starts with prefix string, otherwise false.
///
inline bool StringStartsWith(const char* source,
                             const char* prefix) {
  if ((source != nullptr) && (prefix != nullptr)) {
    return (::strncmp(source, prefix, ::strlen(prefix)) == 0);
  } else {
    return false;
  }
}

/// Ends with string.
///
/// @param source source string.
/// @param suffix suffix string.
/// @return ture if value string is ends with suffix string.
///
inline bool StringEndsWith(const char* source,
                           const char* suffix) {
  if ((source != nullptr) && (suffix != nullptr)) {
    std::size_t value_length = ::strlen(source);
    std::size_t suffix_length = ::strlen(suffix);
    return ((value_length >= suffix_length)
        && (::strncmp(source + (value_length - suffix_length),
                      suffix,
                      suffix_length) == 0));
  } else {
    return false;
  }
}

/// String replace all.
///
/// @param source     source string.
/// @param old_string string to be replaced.
/// @param new_string string to replace all occurrences of old_string.
/// @return replace string.
///
inline std::string StringReplaceAll(const char* source,
                                    const char* old_string,
                                    const char* new_string) {
  if ((source != nullptr) && (old_string != nullptr)) {
    std::string buffer;
    std::size_t old_length = ::strlen(old_string);

    new_string = NullOptionPtr(new_string, "");
    while (const char* found = ::strstr(source, old_string)) {
      buffer.append(source, found - source).append(new_string);
      source = found + old_length;
    }
    buffer.append(source);

    return std::move(buffer);
  } else {
    return std::string();
  }
}

/// String split.
///
/// @param source    string string.
/// @param delimiter delimiter function object.
/// @return split strings.
///
template <class Delimiter>
inline std::vector<std::string> StringSplit(const char* source,
                                            Delimiter delimiter) {
  std::vector<std::string> splits;

  if (source != nullptr) {
    std::string buffer;

    std::string::size_type delimit_length = 1;
    while (const char* found = delimiter(source, &delimit_length)) {
      splits.push_back(std::string(source, found - source));
      source = found + delimit_length;
    }
    splits.push_back(std::string(source));
  }

  return std::move(splits);
}

/// Single charactor delimiter function class.
///
class IsAnyOf {
 public:
  /// Construct delimiter.
  ///
  /// @param delimit delimiters.
  ///
  inline explicit IsAnyOf(const char* delimit)
      : delimit_(NullOptionPtr(delimit, "")) {}

  /// Copy delimiter.
  ///
  /// @param value source object.
  ///
  inline IsAnyOf(const IsAnyOf& value) {
    delimit_ = value.delimit_;
  }

  /// Assign delimiter.
  ///
  /// @param value source object.
  ///
  inline void operator=(const IsAnyOf& value) {
    delimit_ = value.delimit_;
  }

  /// Split string function.
  ///
  /// @param source         source string.
  /// @param delimit_length output delimiter length.
  /// @return next delimit.
  ///
  inline const char* operator()(const char* source,
                                std::string::size_type*) {
    return ::strpbrk(source, delimit_.c_str());
  }

 private:
  /// Delimiters.
  std::string delimit_;
};

/// Convert string to array.
///
/// @param source    source string.
/// @param converter value converter.
/// @return convert array.
///
template <typename T, class Converter>
inline std::vector<T> StringToArray(const char* source,
                                    Converter converter) {
  std::vector<T> buffer;

  while (source != nullptr) {
    source = converter(source, &buffer);
  }

  return std::move(buffer);
}

/// Convert array to string.
///
/// @param first     source data first.
/// @param last      source data last.
/// @param converter value converter.
/// @return convert string.
///
template <typename InputIterator, class Converter>
inline std::string ArrayToString(InputIterator first,
                                 InputIterator last,
                                 Converter converter) {
  std::string buffer;

  for (std::size_t index = 0; first != last; ++first, index++) {
    converter(*first, index, &buffer);
  }

  return std::move(buffer);
}

/// Hexadecimal byte string converter function class.
///
class ToHexByte {
 public:
  /// Construct converter.
  ///
  /// @param separator separate string.
  /// @param is_upper  is upper character.
  ///
  inline ToHexByte(const char* separator, bool is_upper)
      : separator_(NullOptionPtr(separator, "")),
        hex_(is_upper ? 'A' : 'a') {}

  /// Construct converter.
  ///
  /// @param separator separate string.
  ///
  inline explicit ToHexByte(const char* separator)
      : separator_(NullOptionPtr(separator, "")),
        hex_('A') {}

  /// Copy converter.
  ///
  /// @param value source object.
  ///
  inline ToHexByte(const ToHexByte& value) {
    separator_ = value.separator_;
    hex_ = value.hex_;
  }

  /// Assign converter.
  ///
  /// @param value source object.
  ///
  inline void operator=(const ToHexByte& value) {
    separator_ = value.separator_;
    hex_ = value.hex_;
  }

  /// Convert string function.
  ///
  /// @param source      source value.
  /// @param index       index.
  /// @param destination destination string.
  ///
  template <typename T>
  inline void operator()(T source,
                         std::size_t index,
                         std::string* destination) {
    if (index != 0) {
      destination->append(separator_);
    }

    char high = (static_cast<char>(source) >> 4) & 0x0f;
    char low = static_cast<char>(source) & 0x0f;
    destination->push_back((high < 10) ? '0' + high : hex_ + (high - 10));
    destination->push_back((low < 10) ? '0' + low : hex_ + (low - 10));
  }

 private:
  /// Separate string.
  std::string separator_;
  /// Base hex character.
  char hex_;
};

/// Multi byte string converter function class.
///
struct ToMultiByte {
  /// Convert string function.
  ///
  /// @param source      source value.
  /// @param index       index.
  /// @param destination destination string.
  ///
  template <typename T>
  inline void operator()(T source, std::size_t, std::string* destination) {
    destination->push_back(static_cast<char>(source & 0xff));
  }
};

}  // namespace pettystring

#endif  // PETTYSTRING_PETTY_STRING_H_
