#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
#include <memory>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>

using namespace std;

// https://leetcode.cn/problems/two-sum/description/

class Solution {
public:
  vector<int> twoSum(vector<int> &nums, int target) {
    for (int i = 0; i < nums.size(); ++i) {
      for (int j = i + 1; j < nums.size(); ++j) {
        if (nums[i] + nums[j] == target) {
          return vector<int>({i, j});
        }
      }
    }
    return vector<int>();
  }
};

struct TwoSumCase {
  TwoSumCase() = default;
  TwoSumCase(vector<int> nums, int target) : nums(nums), target(target) {}
  vector<int> nums;
  int target;
};

namespace Catch {
template <> struct StringMaker<TwoSumCase> {
  static string convert(TwoSumCase const &value) {
    stringstream buffer;
    buffer << "<[";
    if (value.nums.size() > 0) {
      buffer << *value.nums.begin();
      for (auto i = value.nums.begin() + 1; i != value.nums.end(); ++i) {
        buffer << ", " << *i;
      }
    }
    buffer << "], " << value.target << ">";
    return buffer.str();
  }
};
} // namespace Catch

TEST_CASE("Case 1", "[two sum]") {
  auto solution = make_unique<Solution>();
  SECTION("two sum official cases") {
    TwoSumCase input;
    vector<int> expect;
    tie(input, expect) = GENERATE(table<TwoSumCase, vector<int>>(
        {make_tuple(TwoSumCase({2, 7, 11, 15}, 9), vector<int>{0, 1}),
         make_tuple(TwoSumCase({3, 2, 4}, 6), vector<int>{1, 2}),
         make_tuple(TwoSumCase({3, 3}, 6), vector<int>{0, 1})}));
    auto got = solution->twoSum(input.nums, input.target);
    CAPTURE(input);
    REQUIRE(got == expect);
  }
}
