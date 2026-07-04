#include <algorithm>
#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
#include <iterator>
#include <memory>
#include <tuple>
#include <vector>

using namespace std;

// https://leetcode.cn/problems/search-in-rotated-sorted-array/

namespace SearchInRotatedSortedArray {
class Solution {
public:
  int search(vector<int> &nums, int target) {
    if (nums.empty()) {
      return -1;
    }
    if (nums.size() == 1) {
      return nums[0] == target ? 0 : -1;
    }
    if (nums.size() < 4) {
      if (auto i = find(nums.begin(), nums.end(), target); i != nums.end()) {
        return distance(nums.begin(), i);
      } else {
        return -1;
      }
    }
    auto left = nums.begin();
    auto right = nums.end() - 1;
    do {
      auto middle = left + (right + 1 - left) / 2;
      if (*middle == target) {
        return distance(nums.begin(), middle);
      }
      if (*left == target) {
        return distance(nums.begin(), left);
      }
      if (*left <= *middle) {
        if (*left == target) {
          return distance(nums.begin(), left);
        } else if (*right == target) {
          return distance(nums.begin(), right);
        } else if (*left > target) {
          left = middle + 1;
          continue;
        } else if (*middle < target) {
          left = middle + 1;
          continue;
        } else {
          ++left;
          right = middle;
          continue;
        }
      } else {
        if (*middle < *right) {
          if (*middle < target) {
            if (*right < target) {
              right = middle - 1;
              continue;
            } else {
              left = middle;
              continue;
            }
          } else {
            right = middle - 1;
            continue;
          }
        }
        if (*right == target) {
          return distance(nums.begin(), right);
        } else if (*middle < target) {
          right = middle - 1;
          continue;
        } else {
          ++left;
          right = middle - 1;
          continue;
        }
      }
    } while (left < right);
    return -1;
  }
};
} // namespace SearchInRotatedSortedArray

struct SearchInRotatedSortedArrayCase {
  vector<int> nums;
  int target;
};

namespace Catch {
template <> struct StringMaker<SearchInRotatedSortedArrayCase> {
  static string convert(SearchInRotatedSortedArrayCase const &value) {
    stringstream buffer;
    buffer << "<[";
    if (!value.nums.empty()) {
      buffer << value.nums[0];
      for (size_t i = 1; i < value.nums.size(); ++i) {
        buffer << ", " << value.nums[i];
      }
    }
    buffer << "], " << value.target << ">";
    return buffer.str();
  }
};

} // namespace Catch

TEST_CASE("Case 1", "[search-in-rotated-sorted-array]") {
  using Solution = SearchInRotatedSortedArray::Solution;
  auto solution = make_unique<Solution>();
  SECTION("search-in-rotated-sorted-array official cases") {
    SearchInRotatedSortedArrayCase input;
    int expect;
    tie(input, expect) = GENERATE(table<SearchInRotatedSortedArrayCase, int>(
        {make_tuple(
             SearchInRotatedSortedArrayCase{
                 vector<int>{2, 3, 4, 5, 6, 7, 8, 9, 1}, 9},
             7),
         make_tuple(
             SearchInRotatedSortedArrayCase{
                 vector<int>{9, 1, 2, 3, 4, 5, 6, 7, 8}, 9},
             0),
         make_tuple(
             SearchInRotatedSortedArrayCase{vector<int>{5, 1, 2, 3, 4}, 1}, 1),
         make_tuple(
             SearchInRotatedSortedArrayCase{vector<int>{6, 7, 1, 2, 3, 4, 5},
                                            6},
             0),
         make_tuple(
             SearchInRotatedSortedArrayCase{vector<int>{8, 1, 2, 3, 4, 5, 6, 7},
                                            6},
             6),
         make_tuple(
             SearchInRotatedSortedArrayCase{vector<int>{4, 5, 6, 7, 0, 1, 2},
                                            0},
             4),
         make_tuple(
             SearchInRotatedSortedArrayCase{vector<int>{4, 5, 6, 7, 0, 1, 2},
                                            3},
             -1),
         make_tuple(SearchInRotatedSortedArrayCase{vector<int>{1}, 0}, -1),
         make_tuple(
             SearchInRotatedSortedArrayCase{vector<int>{4, 5, 6, 7, 0, 1, 2},
                                            2},
             6),
         make_tuple(
             SearchInRotatedSortedArrayCase{vector<int>{1, 2, 3, 4, 5, 6}, 4},
             3),
         make_tuple(
             SearchInRotatedSortedArrayCase{vector<int>{7, 8, 1, 2, 3, 4, 5, 6},
                                            2},
             3)}));
    auto got = solution->search(input.nums, input.target);
    CAPTURE(input);
    REQUIRE(got == expect);
  }
}
