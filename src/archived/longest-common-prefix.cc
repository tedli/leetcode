#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
#include <memory>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>

using namespace std;

// https://leetcode.cn/problems/longest-common-prefix/description/

class Solution {
public:
  string longestCommonPrefix(vector<string> &strs) {
    if (auto size = strs.size(); size == 1) {
      return strs[0];
    } else if (size == 0) {
      return "";
    }
    auto first = strs[0];
    stringstream result;
    for (int i = 0; i < first.size(); ++i) {
      char current = first[i];
      for (auto j = strs.begin() + 1; j != strs.end(); ++j) {
        if (i >= j->size() || (*j)[i] != current) {
          return result.str();
        }
      }
      result << current;
    }
    return result.str();
  }
};

TEST_CASE("Case 1", "[longest-common-prefix]") {
  auto solution = make_unique<Solution>();
  SECTION("longest-common-prefix official cases") {
    vector<string> input;
    string expect;
    tie(input, expect) = GENERATE(table<vector<string>, string>(
        {make_tuple(vector<string>{"flower", "flow", "flight"}, "fl"),
         make_tuple(vector<string>{"dog", "racecar", "car"}, "")}));
    auto got = solution->longestCommonPrefix(input);
    CAPTURE(input);
    REQUIRE(got == expect);
  }
}
