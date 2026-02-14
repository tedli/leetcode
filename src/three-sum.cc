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
    auto result = vector<vector<int>>();
    sort(nums.begin(), nums.end());
    for (auto i = nums.begin(); i != nums.end(); ++i) {
      if (i != nums.begin() && *i == *(i - 1))
        continue;
      auto k = nums.end() - 1;
      for (auto j = i + 1; j != nums.end(); ++j) {
        if (j != i + 1 && *j == *(j - 1))
          continue;
        while (j < k && *j + *k > -*i)
          --k;
        if (j == k)
          break;
        if (*j + *k == -*i)
          result.push_back({*i, *j, *k});
      }
    }
    return result;
  }

  vector<vector<int>> threeSum2(vector<int> &nums) {
    int n = nums.size();
    sort(nums.begin(), nums.end());
    vector<vector<int>> ans;
    // 枚举 a
    for (int first = 0; first < n; ++first) {
      // 需要和上一次枚举的数不相同
      if (first > 0 && nums[first] == nums[first - 1]) {
        continue;
      }
      // c 对应的指针初始指向数组的最右端
      int third = n - 1;
      int target = -nums[first];
      // 枚举 b
      for (int second = first + 1; second < n; ++second) {
        // 需要和上一次枚举的数不相同
        if (second > first + 1 && nums[second] == nums[second - 1]) {
          continue;
        }
        // 需要保证 b 的指针在 c 的指针的左侧
        while (second < third && nums[second] + nums[third] > target) {
          --third;
        }
        // 如果指针重合，随着 b 后续的增加
        // 就不会有满足 a+b+c=0 并且 b<c 的 c 了，可以退出循环
        if (second == third) {
          break;
        }
        if (nums[second] + nums[third] == target) {
          ans.push_back({nums[first], nums[second], nums[third]});
        }
      }
    }
    return ans;
  }

  vector<vector<int>> threeSum1(vector<int> &nums) {
    unordered_map<int, int> index;
    const int size = nums.size();
    for (int i = 0; i < size; ++i) {
      index.insert({nums[i], i});
    }
    set<tuple<int, int>> known;
    set<vector<int>> result;
    for (int i = 0; i < size; ++i) {
      for (int j = i + 1; j < size; ++j) {
        int a = nums[i];
        int b = nums[j];
        tuple<int, int> key;
        if (a > b) {
          key = make_tuple(b, a);
        } else {
          key = make_tuple(a, b);
        }
        if (auto ki = known.find(key); ki != known.end()) {
          continue;
        }
        known.insert(key);
        int c;
        if (a == 0) {
          if (b == 0) {
            c = 0;
          } else {
            c = -b;
          }
        } else {
          if (b == 0) {
            c = -a;
          } else {
            c = -(a + b);
          }
        }
        auto range = index.equal_range(c);
        for (auto ri = range.first; ri != range.second; ++ri) {
          if (int ci = ri->second; ci > j) {
            auto triple = vector<int>{a, b, c};
            sort(triple.begin(), triple.end());
            result.insert(triple);
            if (a > c) {
              key = make_tuple(c, a);
            } else {
              key = make_tuple(a, c);
            }
            known.insert(key);
            if (b > c) {
              key = make_tuple(c, b);
            } else {
              key = make_tuple(b, c);
            }
            known.insert(key);
            break;
          }
        }
      }
    }
    return vector<vector<int>>(result.begin(), result.end());
  }
};

TEST_CASE("Case 1", "[3sum]") {
  auto solution = make_unique<Solution>();
  SECTION("3sum official cases") {
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
