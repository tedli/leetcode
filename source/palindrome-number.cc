#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
#include <memory>
#include <string>
#include <tuple>

using namespace std;

// https://leetcode.cn/problems/palindrome-number/description/

class Solution {
public:
  bool isPalindrome(int x) {
    if (x < 0)
      return false;
    if (x < 10)
      return true;
    auto str = to_string(x);
    auto i = str.begin();
    auto j = str.rbegin();
    do {
      if (*i != *j)
        return false;
      ++i;
      ++j;
    } while (i != str.end() && j != str.rend());
    return true;
  }
};

TEST_CASE("Case 1", "[palindrome number]") {
  auto solution = make_unique<Solution>();
  SECTION("palindrome number official cases") {
    int input;
    bool expect;
    tie(input, expect) = GENERATE(
        table<int, bool>({make_tuple(121, true), make_tuple(-121, false),
                          make_tuple(10, false)}));
    auto got = solution->isPalindrome(input);
    CAPTURE(input);
    REQUIRE(got == expect);
  }
}
