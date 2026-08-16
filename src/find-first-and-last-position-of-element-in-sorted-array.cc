#include "nums-target.h"
#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
#include <memory>
#include <tuple>
#include <vector>

using namespace std;

// https://leetcode.cn/problems/find-first-and-last-position-of-element-in-sorted-array/

namespace FindFirstAndLastPositionOfElementInSortedArray {
class Solution {
public:
  vector<int> searchRange(vector<int> &nums, int target) {
    if (nums.empty()) {
      return {-1, -1};
    }
    if (nums.size() == 1) {
      return nums[0] == target ? vector<int>{0, 0} : vector<int>{-1, -1};
    }
    if (nums[0] > target) {
      return {-1, -1};
    }
    if (nums.size() < 4) {
      auto begin = -1;
      auto end = -1;
      for (auto i = nums.begin(); i < nums.end(); ++i) {
        if (*i == target) {
          if (begin == -1) {
            begin = distance(nums.begin(), i);
          }
          end = distance(nums.begin(), i);
        }
      }
      return {begin, end};
    }
    auto begin = nums.begin();
    auto end = nums.end();
    while (begin < end) {
      auto middle = begin + (end - begin) / 2;
      if (target < *middle) {
        end = middle;
        continue;
      }
      if (target > *middle) {
        begin = middle + 1;
        continue;
      }
      auto left = middle;
      auto right = middle;
      while (left > nums.begin() && *(left - 1) == target) {
        --left;
      }
      while (right < nums.end() - 1 && *(right + 1) == target) {
        ++right;
      }
      return {int(distance(nums.begin(), left)),
              int(distance(nums.begin(), right))};
    }
    return {-1, -1};
  }
};
} // namespace FindFirstAndLastPositionOfElementInSortedArray

TEST_CASE("Case 1",
          "[find-first-and-last-position-of-element-in-sorted-array]") {
  using Solution = FindFirstAndLastPositionOfElementInSortedArray::Solution;
  using FindFirstAndLastPositionOfElementInSortedArrayCase =
      Utils::NumsTargetInput;
  auto solution = make_unique<Solution>();
  SECTION("find-first-and-last-position-of-element-in-sorted-array official "
          "cases") {
    FindFirstAndLastPositionOfElementInSortedArrayCase input;
    vector<int> expect;
    tie(input, expect) = GENERATE(
        table<FindFirstAndLastPositionOfElementInSortedArrayCase, vector<int>>(
            {make_tuple(
                 FindFirstAndLastPositionOfElementInSortedArrayCase{
                     vector<int>{5, 7, 7, 8, 8, 10}, 8},
                 vector<int>{3, 4}),
             make_tuple(
                 FindFirstAndLastPositionOfElementInSortedArrayCase{
                     vector<int>{5, 7, 7, 8, 8, 10}, 6},
                 vector<int>{-1, -1}),
             make_tuple(
                 FindFirstAndLastPositionOfElementInSortedArrayCase{
                     vector<int>{}, 0},
                 vector<int>{-1, -1})}));
    auto got = solution->searchRange(input.nums, input.target);
    CAPTURE(input);
    REQUIRE(got == expect);
  }
}
