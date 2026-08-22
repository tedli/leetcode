#include <algorithm>
#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
#include <climits>
#include <cstdint>
#include <memory>
#include <tuple>
#include <vector>

using namespace std;

// https://leetcode.cn/problems/4sum/

class Solution {
public:
  vector<vector<int>> fourSum(vector<int> &nums, int target) {
    auto result = vector<vector<int>>();
    sort(nums.begin(), nums.end());
    for (auto i = nums.begin(); i != nums.end(); ++i) {
      if (i != nums.begin() && *i == *(i - 1))
        continue;
      for (auto j = i + 1; j != nums.end(); ++j) {
        if (j > i + 1 && *j == *(j - 1))
          continue;
        for (auto k = j + 1; k != nums.end(); ++k) {
          if (k > j + 1 && *k == *(k - 1))
            continue;
          auto want = (int64_t)target - *i - *j - *k;
          for (auto f = k + 1; f != nums.end(); ++f) {
            if (f > k + 1 && *f == *(f - 1))
              continue;
            if (*f == want) {
              result.push_back({*i, *j, *k, *f});
              break;
            }
          }
        }
      }
    }
    return result;
  };
};

struct FourSumCase {
  vector<int> nums;
  int target;
};

std::ostream &operator<<(std::ostream &out, FourSumCase const &value) {
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

TEST_CASE("Case 1", "[4sum]") {
  auto solution = make_unique<Solution>();
  SECTION("4sum official cases") {
    FourSumCase input;
    vector<vector<int>> expect;
    tie(input, expect) = GENERATE(table<FourSumCase, vector<vector<int>>>(
        {make_tuple(
             FourSumCase{{1, 0, -1, 0, -2, 2}, 0},
             vector<vector<int>>{{-2, -1, 1, 2}, {-2, 0, 0, 2}, {-1, 0, 0, 1}}),
         make_tuple(FourSumCase{{2, 2, 2, 2, 2}, 8},
                    vector<vector<int>>{{2, 2, 2, 2}}),
         make_tuple(
             FourSumCase{{1000000000, 1000000000, 1000000000, 1000000000}, 0},
             vector<vector<int>>())}));
    auto got = solution->fourSum(input.nums, input.target);
    CAPTURE(input);
    sort(got.begin(), got.end());
    sort(expect.begin(), expect.end());
    REQUIRE(got == expect);
  }
}
