#include <catch2/catch_test_macros.hpp>
#include <string>

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
  auto solution = new Solution;
  auto lp = solution->longestPalindrome("babad");
  REQUIRE("bab" == lp);
  lp = solution->longestPalindrome("cbbd");
  REQUIRE("bb" == lp);
  lp = solution->longestPalindrome("ccc");
  REQUIRE("ccc" == lp);
  lp = solution->longestPalindrome("aaaa");
  REQUIRE("aaaa" == lp);
  lp = solution->longestPalindrome("aaaab");
  REQUIRE("aaaa" == lp);
  lp = solution->longestPalindrome("aaaaa");
  REQUIRE("aaaaa" == lp);
}
