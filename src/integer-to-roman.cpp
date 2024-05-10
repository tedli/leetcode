#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
#include <functional>
#include <map>
#include <memory>
#include <sstream>
#include <string>
#include <tuple>

using namespace std;

// https://leetcode.cn/problems/integer-to-roman/

class Solution {
public:
  string intToRoman(int num) {
    static const map<int, string, greater<int>> digits{
        {1000, "M"}, {900, "CM"}, {500, "D"}, {400, "CD"}, {100, "C"},
        {90, "XC"},  {50, "L"},   {40, "XL"}, {10, "X"},   {9, "IX"},
        {5, "V"},    {4, "IV"},   {1, "I"}};

    if (auto digit = digits.find(num); digit != digits.end()) {
      return digit->second;
    }
    stringstream result;
    if (num < 4) {
      for (int i = 0; i < num; ++i) {
        result << "I";
      }
      return result.str();
    }
    auto begin = digits.begin();
    if (num < 10) {
      begin = digits.find(5);
    } else if (num < 40) {
      begin = digits.find(10);
    } else if (num < 50) {
      begin = digits.find(40);
    } else if (num < 90) {
      begin = digits.find(50);
    } else if (num < 100) {
      begin = digits.find(90);
    } else if (num < 400) {
      begin = digits.find(100);
    } else if (num < 500) {
      begin = digits.find(400);
    } else if (num < 900) {
      begin = digits.find(500);
    } else if (num < 1000) {
      begin = digits.find(900);
    }
    for (auto i = begin; i != digits.end(); ++i) {
      int q = num / i->first;
      if (q > 0) {
        for (int c = 0; c < q; ++c) {
          result << i->second;
        }
        num -= q * i->first;
      }
    }
    return result.str();
  }
};

TEST_CASE("Case 1", "[integer-to-roman]") {
  auto solution = make_unique<Solution>();
  SECTION("integer-to-roman official cases") {
    int input;
    string expect;
    tie(input, expect) = GENERATE(table<int, string>(
        {make_tuple(1994, "MCMXCIV"), make_tuple(3, "III"), make_tuple(4, "IV"),
         make_tuple(9, "IX"), make_tuple(58, "LVIII")}));
    auto got = solution->intToRoman(input);
    CAPTURE(input);
    REQUIRE(got == expect);
  }
}
