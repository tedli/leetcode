#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
#include <climits>
#include <memory>
#include <string>
#include <tuple>

using namespace std;

// https://leetcode.cn/problems/string-to-integer-atoi/description/

class Solution {
public:
  int myAtoi(string s) {
    const static int max_ = INT_MAX;
    const static int min_ = INT_MIN;
    const static bool true_ = true;
    const static bool false_ = false;
    long result = 0;
    const bool *negative = nullptr;
    bool alreadyContainsValue = false;
    for (auto i = s.begin(); i != s.end(); ++i) {
      if ((*i >= 'A' && *i <= 'Z') || (*i >= 'a' && *i <= 'z') || *i == '.')
        break;
      if (*i == '+') {
        if (alreadyContainsValue)
          break;
        if (negative == nullptr) {
          negative = &false_;
          continue;
        } else {
          break;
        }
      }
      if (*i == '-') {
        if (alreadyContainsValue)
          break;
        if (negative == nullptr) {
          negative = &true_;
          continue;
        } else {
          break;
        }
      }
      if (*i < '0' || *i > '9') {
        if (alreadyContainsValue) {
          break;
        } else if (negative != nullptr) {
          break;
        } else {
          continue;
        }
      }
      alreadyContainsValue = true;
      int value = *i - '0';
      result *= 10;
      if (result == 0) {
        if (negative != nullptr && *negative) {
          result -= value;
          if (result != 0) {
            negative = &false_;
          }
        } else {
          result += value;
        }
      } else if (result < 0) {
        result -= value;
      } else {
        result += value;
      }
      if (result > max_) {
        result = max_;
        break;
      }
      if (result < min_) {
        result = min_;
        break;
      }
    }
    return result;
  }
};

TEST_CASE("Case 1", "[string to integer atoi]") {
  auto solution = std::make_unique<Solution>();
  SECTION("string to integer atoi official cases") {
    string input;
    int expect;
    std::tie(input, expect) = GENERATE(table<string, int>(
        {std::make_tuple("42", 42), std::make_tuple("   -42", -42),
         std::make_tuple("4193 with words", 4193),
         std::make_tuple("00000-42a1234", 0),
         std::make_tuple("-000000000000001", -1)}));
    auto got = solution->myAtoi(input);
    CAPTURE(input);
    REQUIRE(got == expect);
  }
}
