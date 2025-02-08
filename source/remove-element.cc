#include "list-node.h"
#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
#include <memory>
#include <tuple>

using namespace Utils;
using namespace std;

// https://leetcode.cn/problems/remove-element

class Solution {
public:
  int removeElement(vector<int> &nums, int val) {
    int wrote = 0;
    for (auto v : nums) {
        if (v == val)
            continue;
        nums[wrote++] = v;
    }
    return wrote;
  }
};

TEST_CASE("Case 1", "[remove-element]") {
  auto solution = make_unique<Solution>();
  SECTION("remove-element official cases") {
    vector<int> input;
    int expect;
    tie(input, expect) = GENERATE(
        table<vector<int>, int>({make_tuple(vector<int>{3, 2, 2, 3}, 2)}));
    auto got = solution->removeElement(input, 3);
    CAPTURE(input);
    REQUIRE(got == expect);
  }
}
