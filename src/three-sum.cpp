#include <algorithm>
#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
#include <climits>
#include <memory>
#include <set>
#include <tuple>
#include <unordered_map>
#include <vector>

using namespace std;

// https://leetcode.cn/problems/3sum/description/

class Solution {
public:
  vector<vector<int>> threeSum(vector<int> &nums) {
    unordered_multimap<int, int> index;
    const int size = nums.size();
    for (int i = 0; i < size; ++i) {
      index.insert({nums[i], i});
    }
    set<vector<int>> result;
    set<tuple<int, int>> known;
    for (int i = 0; i < size; ++i) {
      int v = nums[i];
      for (int j = i + 1; j < size; ++j) {
        int a = nums[j];
        tuple<int, int> key;
        if (v > a) {
          key = make_tuple(a, v);
        } else {
          key = make_tuple(v, a);
        }
        if (auto ki = known.find(key); ki != known.end()) {
          continue;
        }
        known.insert(key);
        int want = INT_MIN;
        if (v == 0) {
          if (a == 0) {
            want = 0;
          } else {
            want = -a;
          }
        } else {
          if (a == 0) {
            want = -v;
          } else {
            want = -(v + a);
          }
        }
        auto b = index.equal_range(want);
        for (auto bi = b.first; bi != b.second; ++bi) {
          if (auto bii = bi->second; bii > j) {
            auto bv = nums[bii];
            auto triple = vector<int>{v, a, bv};
            sort(triple.begin(), triple.end());
            result.insert(triple);
            if (v > bv) {
              key = make_tuple(bv, v);
            } else {
              key = make_tuple(v, bv);
            }
            known.insert(key);
            if (a > bv) {
              key = make_tuple(bv, a);
            } else {
              key = make_tuple(a, bv);
            }
            known.insert(key);
          }
        }
      }
    }
    return vector<vector<int>>(result.begin(), result.end());
  }
};

TEST_CASE("Case 1", "[3sum-prefix]") {
  auto solution = make_unique<Solution>();
  SECTION("3sum-prefix official cases") {
    vector<int> input;
    vector<vector<int>> expect;
    tie(input, expect) = GENERATE(table<vector<int>, vector<vector<int>>>(
        {make_tuple(vector<int>{-1, 0, 1, 2, -1, -4},
                    vector<vector<int>>{{-1, -1, 2}, {-1, 0, 1}}),
         make_tuple(vector<int>{0, 1, 1}, vector<vector<int>>{}),
         make_tuple(vector<int>{0, 0, 0}, vector<vector<int>>{{0, 0, 0}})}));
    auto got = solution->threeSum(input);
    CAPTURE(input);
    sort(got.begin(), got.end());
    sort(expect.begin(), expect.end());
    REQUIRE(got == expect);
  }
}
