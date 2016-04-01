//
// Copyright 2016 imai hiroyuki.
// All rights reserved.
//
// SPDX-License-Identifier: BSL-1.0
//
#ifndef PETTYSTRING_JSON_H_
#define PETTYSTRING_JSON_H_

#include <string>
#include <vector>

#include "petty_string.h"

namespace pettystring {

class JsonArray;

/// JSON object.
///
class JsonObject {
 public:
  /// Destruct JSON object.
  ///
  virtual ~JsonObject() {}

  /// Parse from JSON string.
  ///
  /// @param json JSON string.
  /// @return JSON object if successful, or null otherwise.
  ///
  static c11::unique_ptr<JsonObject> Parse(const std::string& json);

  /// Serialize to JSON string.
  ///
  /// @return serialized JSON string.
  ///
  virtual std::string Serialize() const = 0;

  /// Has a mapping for name.
  ///
  /// @param name mapping name.
  /// @return true if this object has a mapping for name.
  ///
  virtual bool Has(const std::string& name) const = 0;

  /// Get mapping names.
  ///
  /// @return mapping name list.
  ///
  virtual std::vector<std::string> GetNames() const = 0;

  /// Is null the value mapped by name.
  ///
  /// @param name mapping name.
  /// @return true if this object has no mapping for name
  ///         or if it has a mapping whose value is null.
  ///
  virtual bool IsNull(const std::string& name) const = 0;

  /// Get boolean value mapped by name.
  ///
  /// @param name mapping name.
  /// @return the value mapped by name if it exists and is a boolean,
  ///         or null otherwise.
  ///
  virtual c11::unique_ptr<bool> GetBoolean(const std::string& name) const = 0;

  /// To boolean value mapped by name.
  ///
  /// @param name mapping name.
  /// @return the value mapped by name if it exists and is a boolean
  ///         or can be coerced to a boolean, or null otherwise.
  ///
  virtual c11::unique_ptr<bool> ToBoolean(const std::string& name) const = 0;

  /// Get string value mapped by name.
  ///
  /// @param name mapping name.
  /// @return the value mapped by name if it exists and is a string,
  ///         or null otherwise.
  ///
  virtual c11::unique_ptr<std::string> GetString(
      const std::string& name) const = 0;

  /// To string value mapped by name.
  ///
  /// @param name mapping name.
  /// @return the value mapped by name if it exists and is a string
  ///         or can be coerced to a string, or null otherwise.
  ///
  virtual c11::unique_ptr<std::string> ToString(
      const std::string& name) const = 0;

  /// Get 32bit integer value mapped by name.
  ///
  /// @param name mapping name.
  /// @return the value mapped by name if it exists and is a 32bit integer,
  ///         or null otherwise.
  ///
  virtual c11::unique_ptr<std::int32_t> GetInt32(
      const std::string& name) const = 0;

  /// To 32bit integer value mapped by name.
  ///
  /// @param name mapping name.
  /// @return the value mapped by name if it exists and is a 32bit integer
  ///         or can be coerced to a 32bit integer, or null otherwise.
  ///
  virtual c11::unique_ptr<std::int32_t> ToInt32(
      const std::string& name) const = 0;

  /// Get object value mapped by name.
  ///
  /// @param name mapping name.
  /// @return the value mapped by name if it exists and is a object,
  ///         or null otherwise.
  ///
  virtual const JsonObject* GetObject(const std::string& name) const = 0;

  /// Get array value mapped by name.
  ///
  /// @param name mapping name.
  /// @return the value mapped by name if it exists and is a array,
  ///         or null otherwise.
  ///
  virtual const JsonArray* GetArray(const std::string& name) const = 0;

  /// Put null value mapped by name.
  ///
  /// @param name mapping name.
  ///
  virtual void PutNull(const std::string& name) = 0;

  /// Put boolean value mapped by name.
  ///
  /// @param name  mapping name.
  /// @param value boolean value.
  ///
  virtual void PutBoolean(const std::string& name, bool value) = 0;

  /// Put string value mapped by name.
  ///
  /// @param name  mapping name.
  /// @param value string value.
  ///
  virtual void PutString(const std::string& name, const std::string& value) = 0;

  /// Put 32bit integer value mapped by name.
  ///
  /// @param name  mapping name.
  /// @param value 32bit integer value.
  ///
  virtual void PutInt32(const std::string& name, std::int32_t value) = 0;

  /// Put object value mapped by name.
  ///
  /// @param name  mapping name.
  /// @param value object value.
  ///
  virtual void PutObject(const std::string& name,
                         c11::unique_ptr<JsonObject> value) = 0;

  /// Put array value mapped by name.
  ///
  /// @param name  mapping name.
  /// @param value array value.
  ///
  virtual void PutArray(const std::string& name,
                        c11::unique_ptr<JsonArray> value) = 0;

  /// Remove value mapped by name.
  ///
  /// @param name mapping name.
  /// @return true if this object has mapping for name.
  ///
  virtual bool Remove(const std::string& name) = 0;

  /// Swap JSON object.
  ///
  /// @param object JSON object.
  ///
  virtual void Swap(JsonObject* object) = 0;
};

/// JSON array.
///
class JsonArray {
 public:
  /// Destruct JSON array.
  ///
  virtual ~JsonArray() {}

  /// Parse from JSON string.
  ///
  /// @param json JSON string.
  /// @return JSON array if successful, or null otherwise.
  ///
  static c11::unique_ptr<JsonArray> Parse(const std::string& json);

  /// Serialize to JSON string.
  ///
  /// @return serialized JSON string.
  ///
  virtual std::string Serialize() const = 0;

  /// Get array size.
  ///
  /// @return array size.
  ///
  virtual std::size_t GetSize() const = 0;

  /// Is null the value at index.
  ///
  /// @param index array index.
  /// @return true if this array has no value at index
  ///         or if its value is null.
  ///
  virtual bool IsNull(std::size_t index) const = 0;

  /// Get boolean value at index.
  ///
  /// @param index array index.
  /// @return the value at index if it exists and is a boolean,
  ///         or null otherwise.
  ///
  virtual c11::unique_ptr<bool> GetBoolean(std::size_t index) const = 0;

  /// To boolean value at index.
  ///
  /// @param index array index.
  /// @return the value at index if it exists and is a boolean
  ///         or can be coerced to a boolean, or null otherwise.
  ///
  virtual c11::unique_ptr<bool> ToBoolean(std::size_t index) const = 0;

  /// Get string value at index.
  ///
  /// @param index array index.
  /// @return the value at index if it exists and is a string,
  ///         or null otherwise.
  ///
  virtual c11::unique_ptr<std::string> GetString(std::size_t index) const = 0;

  /// To string value at index.
  ///
  /// @param index array index.
  /// @return the value at index if it exists and is a string
  ///         or can be coerced to a string, or null otherwise.
  ///
  virtual c11::unique_ptr<std::string> ToString(std::size_t index) const = 0;

  /// Get 32bit integer value at index.
  ///
  /// @param index array index.
  /// @return the value at index if it exists and is a 32bit integer,
  ///         or null otherwise.
  ///
  virtual c11::unique_ptr<std::int32_t> GetInt32(std::size_t index) const = 0;

  /// To 32bit integer value at index.
  ///
  /// @param index array index.
  /// @return the value at index if it exists and is a 32bit integer
  ///         or can be coerced to a 32bit integer, or null otherwise.
  ///
  virtual c11::unique_ptr<std::int32_t> ToInt32(std::size_t index) const = 0;

  /// Get object value at index.
  ///
  /// @param index array index.
  /// @return the value at index if it exists and is a object,
  ///         or null otherwise.
  ///
  virtual const JsonObject* GetObject(std::size_t index) const = 0;

  /// Get array value at index.
  ///
  /// @param index array index.
  /// @return the value at index if it exists and is a array,
  ///         or null otherwise.
  ///
  virtual const JsonArray* GetArray(std::size_t index) const = 0;

  /// Append null value.
  ///
  virtual void AppendNull() = 0;

  /// Append boolean value.
  ///
  /// @param value boolean value.
  ///
  virtual void AppendBoolean(bool value) = 0;

  /// Append string value.
  ///
  /// @param value string value.
  ///
  virtual void AppendString(const std::string& value) = 0;

  /// Append 32bit integer value.
  ///
  /// @param value 32bit integer value.
  ///
  virtual void AppendInt32(std::int32_t value) = 0;

  /// Append object value.
  ///
  /// @param value object value.
  ///
  virtual void AppendObject(c11::unique_ptr<JsonObject> value) = 0;

  /// Append array value.
  ///
  /// @param value array value.
  ///
  virtual void AppendArray(c11::unique_ptr<JsonArray> value) = 0;

  /// Remove value at index.
  ///
  /// @param index array index.
  /// @return true if this array has index.
  ///
  virtual bool Remove(std::size_t index) = 0;

  /// Swap JSON array.
  ///
  /// @param arr JSON array.
  ///
  virtual void Swap(JsonArray* arr) = 0;
};

}  // namespace pettystring

#endif  // PETTYSTRING_JSON_H_
