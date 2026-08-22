#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
#include <memory>
#include <tuple>
#include <vector>

using namespace std;

// https://leetcode.cn/problems/container-with-most-water/description/

class Solution {
public:
  int maxArea(vector<int> &height) {
    vector<int>::iterator i = height.begin();
    vector<int>::iterator j = height.end() - 1;
    int max = -1;
    while (i != j) {
      int d = j - i;
      int h = *i;
      if (h > *j) {
        h = *j;
        --j;
      } else {
        ++i;
      }
      int s = d * h;
      if (s > max) {
        max = s;
      }
    }
    return max;
  }
};

TEST_CASE("Case 1", "[container with most water]") {
  auto solution = make_unique<Solution>();
  SECTION("container with most water official cases") {
    vector<int> input;
    int expect;
    tie(input, expect) = GENERATE(table<vector<int>, int>(
        {make_tuple(vector<int>{1, 8, 6, 2, 5, 4, 8, 3, 7}, 49),
         make_tuple(vector<int>{1, 1}, 1)}));
    auto got = solution->maxArea(input);
    CAPTURE(input);
    REQUIRE(got == expect);
  }
}
