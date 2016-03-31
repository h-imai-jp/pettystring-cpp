//
// Copyright 2016 imai hiroyuki.
// All rights reserved.
//
// SPDX-License-Identifier: BSL-1.0
//
#include <cstdint>
#include <string>
#include <vector>

#include "gtest/gtest.h"
#include "pettystring/json.h"
#include "pettystring/petty_string.h"

namespace {

/// pettyutil::JsonObject parse test.
///
TEST(JsonObjectTest, Parse) {
  using pettystring::NullOption;

  auto object = pettystring::JsonObject::Parse("{"
      "\"null\"        : null,"
      "\"true\"        : true,"
      "\"false\"       : false,"
      "\"string\"      : \"test \\u0041\\u0042\\u0043 \\\" \\\\ \\/ \\n\","
      "\"string empty\": \"\","
      "\"number\"      : 12345,"
      "\"number zero\" : 0,"
      "\"object\"      : {\"null\"  : null,"
      "                   \"true\"  : true,"
      "                   \"false\" : false,"
      "                   \"string\": \"string\","
      "                   \"number\": 12345,"
      "                   \"object\": { \"object\" : 0 },"
      "                   \"array\" : [ \"array\" ]},"
      "\"object empty\": {},"
      "\"array\"       : [null,"
      "                   true,"
      "                   false,"
      "                   \"string\","
      "                   12345,"
      "                   { \"object\" : 0 },"
      "                   [ \"array\" ]],"
      "\"array empty\" : []"
      "}");
  ASSERT_TRUE(static_cast<bool>(object));

  EXPECT_TRUE(object->Has("null"));
  EXPECT_FALSE(object->Has("notfound"));

  EXPECT_TRUE(object->IsNull("null"));
  EXPECT_TRUE(object->IsNull("notfound"));
  EXPECT_FALSE(object->IsNull("true"));

  EXPECT_TRUE(NullOption(object->GetBoolean("true").get(), false));
  EXPECT_FALSE(NullOption(object->GetBoolean("false").get(), true));
  EXPECT_FALSE(static_cast<bool>(object->GetBoolean("null")));
  EXPECT_FALSE(static_cast<bool>(object->GetBoolean("notfound")));

  EXPECT_STREQ("test ABC \" \\ / \n",
               NullOption(object->GetString("string").get(),
                          std::string("")).c_str());
  EXPECT_STREQ("", NullOption(object->GetString("string empty").get(),
                              std::string("option")).c_str());
  EXPECT_FALSE(static_cast<bool>(object->GetString("null")));
  EXPECT_FALSE(static_cast<bool>(object->GetString("notfound")));

  EXPECT_EQ(12345, NullOption(object->GetInt32("number").get(), 0));
  EXPECT_EQ(0, NullOption(object->GetInt32("number zero").get(), 1));
  EXPECT_FALSE(static_cast<bool>(object->GetInt32("null")));
  EXPECT_FALSE(static_cast<bool>(object->GetInt32("notfound")));

  const auto* object_value = object->GetObject("object");
  ASSERT_TRUE(object_value != nullptr);
  EXPECT_TRUE(object_value->IsNull("null"));
  EXPECT_TRUE(NullOption(object_value->GetBoolean("true").get(), false));
  EXPECT_FALSE(NullOption(object_value->GetBoolean("false").get(), true));
  EXPECT_STREQ("string", NullOption(object_value->GetString("string").get(),
                                    std::string("")).c_str());
  EXPECT_EQ(12345, NullOption(object_value->GetInt32("number").get(), 0));
  EXPECT_TRUE(object_value->GetObject("object") != nullptr);
  EXPECT_TRUE(object_value->GetArray("array") != nullptr);
  EXPECT_TRUE(object->GetObject("object empty") != nullptr);

  const auto* array_value = object->GetArray("array");
  ASSERT_TRUE(array_value != nullptr);
  EXPECT_TRUE(array_value->IsNull(0));
  EXPECT_TRUE(NullOption(array_value->GetBoolean(1).get(), false));
  EXPECT_FALSE(NullOption(array_value->GetBoolean(2).get(), true));
  EXPECT_STREQ("string", NullOption(array_value->GetString(3).get(),
                                    std::string("")).c_str());
  EXPECT_EQ(12345, NullOption(array_value->GetInt32(4).get(), 0));
  EXPECT_TRUE(array_value->GetObject(5) != nullptr);
  EXPECT_TRUE(array_value->GetArray(6) != nullptr);
  EXPECT_TRUE(object->GetArray("array empty") != nullptr);
}

}  // namespace
