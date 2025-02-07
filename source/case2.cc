#include <catch2/catch_test_macros.hpp>
#include <string>
#include <unordered_map>

// https://leetcode.cn/problems/longest-substring-without-repeating-characters/

using std::string;
using iterator = std::string::iterator;

class Solution {
public:
  int lengthOfLongestSubstring(string s) {
    if (s.length() == 1) {
      return 1;
    }
    int max = 0;
    std::unordered_map<char, iterator> chars;
    auto i = s.begin();
    auto j = i + 1;
    while (i != s.end()) {
      chars.insert({*i, i});
      j = i + 1;
      while (j != s.end()) {
        if (*j == *(j - 1)) {
          int distance = j - i;
          if (distance > max) {
            max = distance;
          }
          i = j - 1;
          ++j;
          chars.clear();
          break;
        }
        auto index = chars.find(*j);
        if (index != chars.end()) {
          int distance = j - i;
          if (distance > max) {
            max = distance;
          }
          i = index->second;
          ++j;
          chars.clear();
          break;
        }
        chars.insert({*j, j});
        ++j;
        if (j == s.end()) {
          int distance = j - i;
          if (distance > max) {
            max = distance;
          }
          break;
        }
      }
      ++i;
    }
    return max;
  }
};

TEST_CASE("Case 1", "[longest sub string]") {
  Solution s;
  int length = s.lengthOfLongestSubstring("abcabcbb");
  REQUIRE(length == 3);
  length = s.lengthOfLongestSubstring("pwwkew");
  REQUIRE(length == 3);
  length = s.lengthOfLongestSubstring("bbbbb");
  REQUIRE(length == 1);
}
