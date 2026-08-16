#include "nums-target.h"
#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
#include <memory>
#include <tuple>
#include <vector>

using namespace std;

// https://leetcode.cn/problems/search-insert-position/

namespace SearchInsertPosition {
class Solution {
public:
  int searchInsert(vector<int> &nums, int target) {
    for (auto i = nums.begin(); i != nums.end(); ++i) {
      if (*i == target) {
        return distance(nums.begin(), i);
      }
      if (*i > target) {
        if (i == nums.begin()) {
          return 0;
        }
        return distance(nums.begin(), i);
      }
    }
    return nums.size();
  }
};
} // namespace SearchInsertPosition

TEST_CASE("Case 1", "[search-insert-position]") {
  using Solution = SearchInsertPosition::Solution;
  using SearchInsertPositionCase = Utils::NumsTargetInput;
  auto solution = make_unique<Solution>();
  SECTION("search-insert-position official cases") {
    SearchInsertPositionCase input;
    int expect;
    tie(input, expect) = GENERATE(table<SearchInsertPositionCase, int>(
        {make_tuple(SearchInsertPositionCase{vector<int>{1, 3, 5, 6}, 5}, 2),
         make_tuple(SearchInsertPositionCase{vector<int>{1, 3, 5, 6}, 2}, 1),
         make_tuple(SearchInsertPositionCase{vector<int>{1, 3, 5, 6}, 7}, 4)}));
    auto got = solution->searchInsert(input.nums, input.target);
    CAPTURE(input);
    REQUIRE(got == expect);
  }
}
