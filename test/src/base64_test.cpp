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
#include "pettystring/base64.h"

namespace {

namespace pettys = pettystring;

/// pettystring::EncodeBase64 encode test.
///
TEST(EncodeBase64Test, Encode) {
  std::vector<std::uint8_t> test_data;
  for (int i = 0; i < 0x100; i++) {
    test_data.push_back(i);
  }

  auto base64 = pettys::EncodeBase64(test_data.begin(), test_data.end());
  EXPECT_STREQ(
      "AAECAwQFBgcICQoLDA0ODxAREhMUFRYXGBkaGxwdHh8gISIjJCUmJygpKissLS4v"
      "MDEyMzQ1Njc4OTo7PD0+P0BBQkNERUZHSElKS0xNTk9QUVJTVFVWV1hZWltcXV5f"
      "YGFiY2RlZmdoaWprbG1ub3BxcnN0dXZ3eHl6e3x9fn+AgYKDhIWGh4iJiouMjY6P"
      "kJGSk5SVlpeYmZqbnJ2en6ChoqOkpaanqKmqq6ytrq+wsbKztLW2t7i5uru8vb6/"
      "wMHCw8TFxsfIycrLzM3Oz9DR0tPU1dbX2Nna29zd3t/g4eLj5OXm5+jp6uvs7e7v"
      "8PHy8/T19vf4+fr7/P3+/w==",
      base64.c_str());
}

/// pettystring::IsBase64 true test.
///
TEST(IsBase64Test, True) {
  bool test1 = pettys::IsBase64(
      "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/");
  EXPECT_TRUE(test1);

  bool test2 = pettys::IsBase64("AQ==");
  EXPECT_TRUE(test2);
}

/// pettystring::IsBase64 false test.
///
TEST(IsBase64Test, False) {
  bool test1 = pettys::IsBase64("ABCDE");
  EXPECT_FALSE(test1);

  bool test2 = pettys::IsBase64("ABC*");
  EXPECT_FALSE(test2);

  bool test3 = pettys::IsBase64("ABCDE===");
  EXPECT_FALSE(test3);
}

/// pettystring::DecodeBase64 decode test.
///
TEST(DecodeBase64Test, Decode) {
  std::vector<std::uint8_t> output_data;
  bool test = pettys::DecodeBase64(
      "AAECAwQFBgcICQoLDA0ODxAREhMUFRYXGBkaGxwdHh8gISIjJCUmJygpKissLS4v"
      "MDEyMzQ1Njc4OTo7PD0+P0BBQkNERUZHSElKS0xNTk9QUVJTVFVWV1hZWltcXV5f"
      "YGFiY2RlZmdoaWprbG1ub3BxcnN0dXZ3eHl6e3x9fn+AgYKDhIWGh4iJiouMjY6P"
      "kJGSk5SVlpeYmZqbnJ2en6ChoqOkpaanqKmqq6ytrq+wsbKztLW2t7i5uru8vb6/"
      "wMHCw8TFxsfIycrLzM3Oz9DR0tPU1dbX2Nna29zd3t/g4eLj5OXm5+jp6uvs7e7v"
      "8PHy8/T19vf4+fr7/P3+/w==",
      std::back_inserter(output_data));

  EXPECT_TRUE(test);
  ASSERT_EQ(static_cast<std::size_t>(0x100), output_data.size());
  for (int i = 0; i < 0x100; i++) {
    EXPECT_EQ(i, output_data.at(i));
  }
}

}  // namespace
