#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
#include <functional>
#include <memory>
#include <set>
#include <sstream>
#include <string>
#include <tuple>
#include <unordered_map>

using namespace std;

// https://leetcode.cn/problems/roman-to-integer/description/

class Solution {
public:
  int romanToInt(string s) {
    static const unordered_map<string, int> digits{
        {"M", 1000}, {"CM", 900}, {"D", 500}, {"CD", 400}, {"C", 100},
        {"XC", 90},  {"L", 50},   {"XL", 40}, {"X", 10},   {"IX", 9},
        {"V", 5},    {"IV", 4},   {"I", 1}};
    static const unordered_map<char, set<char>> special{
        {'I', {'V', 'X'}}, {'X', {'L', 'C'}}, {'C', {'D', 'M'}}};
    if (auto digit = digits.find(s); digit != digits.end()) {
      return digit->second;
    }
    int value = 0;
    for (auto i = s.begin(); i != s.end(); i++) {
      string current;
      if (auto st = special.find(*i);
          st != special.end() && i + 1 != s.end() &&
          st->second.find(*(i + 1)) != st->second.end()) {
        current = string(i, i + 2);
        ++i;
      } else {
        current = string(i, i + 1);
      }
      if (auto cvi = digits.find(current); cvi != digits.end()) {
        value += cvi->second;
      }
    }
    return value;
  }
};

TEST_CASE("Case 1", "[roman-to-integer]") {
  auto solution = make_unique<Solution>();
  SECTION("roman-to-integer official cases") {
    string input;
    int expect;
    tie(input, expect) = GENERATE(table<string, int>(
        {make_tuple("MCMXCIV", 1994), make_tuple("III", 3), make_tuple("IV", 4),
         make_tuple("IX", 9), make_tuple("LVIII", 58)}));
    auto got = solution->romanToInt(input);
    CAPTURE(input);
    REQUIRE(got == expect);
  }
}
