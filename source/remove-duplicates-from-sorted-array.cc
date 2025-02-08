#include "list-node.h"
#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
#include <memory>
#include <tuple>

using namespace Utils;
using namespace std;

// https://leetcode.cn/problems/remove-duplicates-from-sorted-array

class Solution {
public:
  int removeDuplicates(vector<int> &nums) {
    if (nums.empty())
      return 0;
    int wrote = 1;
    int known = nums[0];
    for (int i = 1; i < nums.size(); ++i) {
      if (nums[i] == known)
        continue;
      known = nums[i];
      nums[wrote++] = known;
    }
    return wrote;
  }
};

TEST_CASE("Case 1", "[remove-duplicates-from-sorted-array]") {
  auto solution = make_unique<Solution>();
  SECTION("remove-duplicates-from-sorted-array official cases") {
    vector<int> input;
    int expect;
    tie(input, expect) = GENERATE(
        table<vector<int>, int>({make_tuple(vector<int>{1, 1, 2}, 2)}));
    auto got = solution->removeDuplicates(input);
    CAPTURE(input);
    REQUIRE(got == expect);
  }
}
