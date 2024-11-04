#include <algorithm>
#include <array>
#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
#include <climits>
#include <functional>
#include <memory>
#include <string>
#include <tuple>
#include <vector>

using namespace std;

// https://leetcode.cn/problems/generate-parentheses

class Solution {
public:
  vector<string> generateParenthesis(int n) {
    static array<vector<string>, 9> memory;
    static const function<reference_wrapper<vector<string>>(int)> generate(
        [](int n) -> reference_wrapper<vector<string>> {
          if (!memory[n].empty())
            return ref(memory[n]);
          if (n == 0) {
            memory[0] = vector<string>{""};
          } else {
            auto result = vector<string>();
            for (int i = 0; i != n; ++i) {
              auto lefts = generate(i).get();
              auto rights = generate(n - i - 1).get();
              for (auto left : lefts)
                for (auto right : rights)
                  result.push_back("(" + left + ")" + right);
            }
            memory[n] = result;
          }
          return ref(memory[n]);
        });
    return generate(n).get();
  }
};

TEST_CASE("Case 1", "[generate-parentheses]") {
  auto solution = make_unique<Solution>();
  SECTION("generate-parentheses official cases") {
    int input;
    vector<string> expect;
    tie(input, expect) = GENERATE(table<int, vector<string>>(
        {make_tuple(3, vector<string>{"((()))", "(()())", "(())()", "()(())",
                                      "()()()"}),
         make_tuple(1, vector<string>{"()"}),
         make_tuple(4, vector<string>{"(((())))", "((()()))", "((())())",
                                      "((()))()", "(()(()))", "(()()())",
                                      "(()())()", "(())(())", "(())()()",
                                      "()((()))", "()(()())", "()(())()",
                                      "()()(())", "()()()()"})}));
    auto got = solution->generateParenthesis(input);
    CAPTURE(input);
    sort(got.begin(), got.end());
    sort(expect.begin(), expect.end());
    REQUIRE(got == expect);
  }
}
