#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
#include <memory>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>

using namespace std;

// https://leetcode.cn/problems/median-of-two-sorted-arrays/description/

class Solution {
public:
  double findMedianSortedArrays(vector<int> &nums1, vector<int> &nums2) {
    vector<int> sorted(nums1.size() + nums2.size());
    auto i = nums1.begin();
    auto j = nums2.begin();
    auto k = sorted.begin();
    do {
      if (i == nums1.end()) {
        *k = *j;
        ++j;
      } else if (j == nums2.end()) {
        *k = *i;
        ++i;
      } else if (*i < *j) {
        *k = *i;
        ++i;
      } else {
        *k = *j;
        ++j;
      }
      ++k;
    } while (i != nums1.end() || j != nums2.end() || k != sorted.end());
    if (sorted.size() % 2 == 0) {
      int middle = sorted.size() / 2;
      return double(sorted[middle] + sorted[middle - 1]) / 2;
    } else {
      return sorted[sorted.size() / 2];
    }
  }
};

struct MedianOfTwoSortedArraysCase {
  MedianOfTwoSortedArraysCase() = default;
  MedianOfTwoSortedArraysCase(vector<int> nums1, vector<int> nums2)
      : nums1(nums1), nums2(nums2) {}
  vector<int> nums1;
  vector<int> nums2;
};

namespace Catch {
template <> struct StringMaker<MedianOfTwoSortedArraysCase> {
  static string convert(MedianOfTwoSortedArraysCase const &value) {
    stringstream buffer;
    buffer << "<";
    appendArray(buffer, value.nums1);
    buffer << ", ";
    appendArray(buffer, value.nums2);
    buffer << ">";
    return buffer.str();
  }
  static void appendArray(stringstream &buffer, vector<int> const &nums) {
    buffer << "[";
    if (nums.size() > 0) {
      buffer << *nums.begin();
      for (auto i = nums.begin() + 1; i != nums.end(); ++i) {
        buffer << ", " << *i;
      }
    }
    buffer << "]";
  }
};
} // namespace Catch

TEST_CASE("Case 1", "[median of two sorted arrays]") {
  auto solution = make_unique<Solution>();
  SECTION("median of two sorted arrays official cases") {
    MedianOfTwoSortedArraysCase input;
    double expect;
    tie(input, expect) = GENERATE(table<MedianOfTwoSortedArraysCase, double>(
        {make_tuple(MedianOfTwoSortedArraysCase({1, 3}, {2}), 2),
         make_tuple(MedianOfTwoSortedArraysCase({1, 2}, {3, 4}), 2.5)}));
    auto got = solution->findMedianSortedArrays(input.nums1, input.nums2);
    CAPTURE(input);
    REQUIRE(got == expect);
  }
}
