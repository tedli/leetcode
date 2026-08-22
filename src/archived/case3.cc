#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
#include <memory>
#include <string>
#include <tuple>

// https://leetcode.cn/problems/longest-palindromic-substring/

using std::string;

class Solution {
public:
  string longestPalindrome(string s) {
    if (s.length() <= 1)
      return s;
    int max = 0;
    string::iterator begin{}, end{};
    for (auto i = s.begin(); i != s.end(); ++i) {
      int delta = 0;
      auto next = i + 1;
      if (next != s.end()) {
        if (*next == *i) {
          delta = 1;
          if (max < 2) {
            max = 2;
            begin = i;
            end = next + 1;
          }
        }
      }
      if (i == s.begin()) {
        if (max < 1) {
          max = 1;
          begin = i;
          end = i + 1;
        }
        continue;
      }
      while (delta >= 0) {
        auto front = i - 1;
        if ((s.end() - i) <= (1 + delta)) {
          --delta;
          continue;
        }
        auto behind = i + (1 + delta);
        while (*front == *behind) {
          auto length = behind - front + 1;
          if (max < length) {
            max = length;
            begin = front;
            end = behind + 1;
          }
          if (front == s.begin())
            break;
          --front;
          ++behind;
          if (behind == s.end())
            break;
        }
        --delta;
      }
    }
    return string(begin, end);
  }
};

TEST_CASE("Case 1", "[longest palindrome]") {
  auto solution = std::make_unique<Solution>();
  SECTION("official cases") {
    string input, expect;
    std::tie(input, expect) = GENERATE(table<string, string>(
        {std::make_tuple("babad", "bab"), std::make_tuple("cbbd", "bb"),
         std::make_tuple("ccc", "ccc"), std::make_tuple("aaaa", "aaaa"),
         std::make_tuple("aaaab", "aaaa"), std::make_tuple("aaaaa", "aaaaa")}));
    auto got = solution->longestPalindrome(input);
    CAPTURE(input);
    REQUIRE(got == expect);
  }
}
