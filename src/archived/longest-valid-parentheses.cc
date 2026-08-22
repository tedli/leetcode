#include <algorithm>
#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
#include <memory>
#include <stack>
#include <tuple>

using namespace std;

// https://leetcode.cn/problems/longest-valid-parentheses/

namespace LongestValidParentheses {

class Solution {
public:
  int longestValidParentheses(string s) {
    auto ml = string::iterator::difference_type(0);
    auto stk = stack<string::iterator>();
    stk.push(s.end());
    for (auto i = s.begin(); i != s.end(); ++i) {
      if (*i == '(') {
        stk.push(i);
      } else {
        stk.pop();
        if (stk.empty()) {
          stk.push(i);
        } else {
          auto diff = i - stk.top();
          if (diff < 0) {
            diff = i - s.begin() + 1;
          }
          ml = max(ml, diff);
        }
      }
    }
    return ml;
  }
};

} // namespace LongestValidParentheses

TEST_CASE("Case 1", "[longest-valid-parentheses]") {
  using Solution = LongestValidParentheses::Solution;
  auto solution = make_unique<Solution>();
  SECTION("longest-valid-parentheses official cases") {
    string input;
    int expect;
    tie(input, expect) = GENERATE(
        table<string, int>({make_tuple("(()", 2), make_tuple(")()())", 4),
                            make_tuple("", 0), make_tuple("()", 2)}));
    auto got = solution->longestValidParentheses(input);
    CAPTURE(input);
    REQUIRE(got == expect);
  }
}
