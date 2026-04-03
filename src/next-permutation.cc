#include <algorithm>
#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
#include <memory>
#include <optional>
#include <tuple>
#include <vector>

using namespace std;

// https://leetcode.cn/problems/next-permutation/

namespace NextPermutation {

class Solution {
public:
  void nextPermutation(vector<int> &nums) {
    optional<vector<int>::iterator> left;
    for (auto i = nums.rbegin() + 1; i != nums.rend(); ++i) {
      if (*i < *(i - 1)) {
        left = (++i).base();
        break;
      }
    }
    if (!left.has_value()) {
      reverse(nums.begin(), nums.end());
      return;
    }
    auto right = nums.end() - 1;
    for (auto i = nums.rbegin(); i != nums.rend(); ++i) {
      if (*left.value() < *i) {
        right = (++i).base();
        break;
      }
    }
    iter_swap(left.value(), right);
    reverse(left.value() + 1, nums.end());
  }
};

} // namespace NextPermutation

TEST_CASE("Case 1", "[next-permutation]") {
  using Solution = NextPermutation::Solution;
  auto solution = make_unique<Solution>();
  SECTION("next-permutation official cases") {
    vector<int> input;
    vector<int> expect;
    tie(input, expect) = GENERATE(table<vector<int>, vector<int>>(
        {make_tuple(vector<int>{1, 2, 3}, vector<int>{1, 3, 2}),
         make_tuple(vector<int>{3, 2, 1}, vector<int>{1, 2, 3}),
         make_tuple(vector<int>{1, 1, 5}, vector<int>{1, 5, 1})}));
    solution->nextPermutation(input);
    vector<int> got = input;
    CAPTURE(input);
    REQUIRE(got == expect);
  }
}
