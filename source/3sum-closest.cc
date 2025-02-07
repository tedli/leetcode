#include <algorithm>
#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
#include <climits>
#include <memory>
#include <tuple>
#include <vector>

using namespace std;

// https://leetcode.cn/problems/3sum-closest/

class Solution {
public:
  int threeSumClosest(vector<int> &nums, int target) {
    sort(nums.begin(), nums.end());
    int result = INT_MAX;
    auto update = [&](int current) {
      if (result == INT_MAX) {
        result = current;
        return;
      }
      if (abs(current - target) < abs(result - target)) {
        result = current;
      }
    };
    for (auto i = nums.begin(); i != nums.end(); ++i) {
      if (i != nums.begin() && *i == *(i - 1))
        continue;
      auto j = i + 1;
      auto k = nums.end() - 1;
      while (j < k) {
        int sum = *i + *j + *k;
        if (sum == target)
          return target;
        update(sum);
        if (sum > target) {
          auto p = k - 1;
          while (j < p && *p == *k)
            --p;
          k = p;
        } else {
          auto p = j + 1;
          while (p < k && *p == *j)
            ++p;
          j = p;
        }
      }
    }
    return result;
  }
};

struct ThreeSumClosestCase {
  vector<int> nums;
  int target;
};

ostream &operator<<(ostream &out, ThreeSumClosestCase const &value) {
  out << "<"
      << "[";
  for (auto i = value.nums.begin(); i != value.nums.end(); ++i) {
    if (i != value.nums.begin())
      out << ", ";
    out << *i;
  }
  out << "], " << value.target << ">";
  return out;
}

TEST_CASE("Case 1", "[3sum-closest]") {
  auto solution = make_unique<Solution>();
  SECTION("3sum-closest official cases") {
    ThreeSumClosestCase input;
    int expect;
    tie(input, expect) = GENERATE(table<ThreeSumClosestCase, int>(
        {make_tuple(ThreeSumClosestCase{{-1, 2, 1, -4}, 1}, 2),
         make_tuple(ThreeSumClosestCase{{0, 0, 0}, 1}, 0),
         make_tuple(ThreeSumClosestCase{{0, 1, 2}, 3}, 3)}));
    auto got = solution->threeSumClosest(input.nums, input.target);
    CAPTURE(input);
    REQUIRE(got == expect);
  }
}
