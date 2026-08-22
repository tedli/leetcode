#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
#include <climits>
#include <memory>
#include <stack>
#include <tuple>
#include <unordered_map>

using namespace std;

// https://leetcode.cn/problems/valid-parentheses/

class Solution {
public:
  bool isValid(string s) {
    const static unordered_map<char, char> mapping{
        {'(', ')'}, {'[', ']'}, {'{', '}'}};
    auto open = stack<char>();
    for (auto c : s) {
      auto i = mapping.find(c);
      if (i != mapping.end()) {
        open.push(i->second);
      } else {
        if (open.empty())
          return false;
        if (c != open.top())
          return false;
        open.pop();
      }
    }
    return open.empty();
  };
};

TEST_CASE("Case 1", "[valid-parentheses]") {
  auto solution = make_unique<Solution>();
  SECTION("valid-parentheses official cases") {
    string input;
    bool expect;
    tie(input, expect) = GENERATE(table<string, bool>(
        {make_tuple("()", true), make_tuple("()[]{}", true),
         make_tuple("(]", false), make_tuple("([])", true)}));
    auto got = solution->isValid(input);
    CAPTURE(input);
    REQUIRE(got == expect);
  }
}
