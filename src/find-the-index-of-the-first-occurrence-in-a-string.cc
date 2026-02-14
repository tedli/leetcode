#include "list-node.h"
#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
#include <memory>
#include <string>
#include <tuple>

using namespace Utils;
using namespace std;

// https://leetcode.cn/problems/find-the-index-of-the-first-occurrence-in-a-string

class Solution {
public:
  int strStr(string haystack, string needle) { return haystack.find(needle); }
};

TEST_CASE("Case 1", "[find-the-index-of-the-first-occurrence-in-a-string]") {
  auto solution = make_unique<Solution>();
  SECTION("find-the-index-of-the-first-occurrence-in-a-string official cases") {
    tuple<string, string> input;
    int expect;
    tie(input, expect) = GENERATE(
        table<tuple<string, string>, int>({make_tuple(make_tuple("sadbutsad", "sad"), 0)}));
    auto got = solution->strStr(get<0>(input), get<1>(input));
    CAPTURE(input);
    REQUIRE(got == expect);
  }
}
