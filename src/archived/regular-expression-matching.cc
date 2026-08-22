#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
#include <memory>
#include <string>
#include <tuple>

using namespace std;

// https://leetcode.cn/problems/regular-expression-matching/

class Solution {
public:
  bool isMatch(string s, string p) {
    int m = s.size();
    int n = p.size();

    auto matches = [&](int i, int j) {
      if (i == 0) {
        return false;
      }
      if (p[j - 1] == '.') {
        return true;
      }
      return s[i - 1] == p[j - 1];
    };

    vector<vector<int>> f(m + 1, vector<int>(n + 1));
    f[0][0] = true;
    for (int i = 0; i <= m; ++i) {
      for (int j = 1; j <= n; ++j) {
        if (p[j - 1] == '*') {
          f[i][j] |= f[i][j - 2];
          if (matches(i, j - 1)) {
            f[i][j] |= f[i - 1][j];
          }
        } else {
          if (matches(i, j)) {
            f[i][j] |= f[i - 1][j - 1];
          }
        }
      }
    }
    return f[m][n];
  }
  bool isMatch2(string s, string p) {
    if (p == ".*")
      return true;
    auto j = p.begin();
    string::value_type previous;
    bool previousDot = false;
    for (auto i = s.begin(); i != s.end();) {
      if (j == p.end())
        return false;
      if (*i == *j) {
        previous = *i;
        ++j;
        ++i;
        previousDot = false;
      } else if (*j == '.') {
        previous = *i;
        ++j;
        ++i;
        previousDot = true;
      } else if (*j == '*') {
        if (*i != previous && !previousDot) {
          ++j;
        } else {
          ++i;
        }
      } else if (*(j + 1) == '*') {
        j += 2;
      } else {
        return false;
      }
      if (i == s.end()) {
        if (*j == '*' && j != p.end() && j + 1 == p.end()) {
          return true;
        } else if (j == p.end()) {
          return true;
        } else if (*j == '*') {
          if (*(j + 1) == previous && j + 2 == p.end()) {
            return true;
          }
          for (auto k = j + 1; k != p.end(); ++k) {
            if (*k == previous)
              continue;
            if (*k != previous && k + 1 != p.end() && *(k + 1) == '*') {
              ++k;
              continue;
            }
            return false;
          }
          return true;
        } else {
          if (j + 1 == p.end())
            return false;
          for (auto k = j + 1; k != p.end(); ++k) {
            if (*k == '*') {
              continue;
            } else if (*(k + 1) == '*') {
              ++k;
              continue;
            }
            return false;
          }
          return true;
        }
      }
    }
    return true;
  }
};

struct RegularExpressionMatchingCase {
  string s;
  string p;
};

namespace Catch {
template <> struct StringMaker<RegularExpressionMatchingCase> {
  static string convert(RegularExpressionMatchingCase const &value) {
    return "<\"" + value.s + "\", \"" + value.p + "\">";
  }
};
} // namespace Catch

TEST_CASE("Case 1", "[regular expression matching]") {
  auto solution = make_unique<Solution>();
  SECTION("regular expression matching official cases") {
    RegularExpressionMatchingCase input;
    bool expect;
    tie(input, expect) = GENERATE(table<RegularExpressionMatchingCase, bool>(
        {make_tuple(RegularExpressionMatchingCase{"aa", "a"}, false),
         make_tuple(RegularExpressionMatchingCase{"aa", "a*"}, true),
         make_tuple(RegularExpressionMatchingCase{"ab", ".*"}, true),
         make_tuple(RegularExpressionMatchingCase{"aab", "c*a*b"}, true),
         make_tuple(RegularExpressionMatchingCase{"mississippi", "mis*is*ip*."},
                    true),
         make_tuple(RegularExpressionMatchingCase{"ab", ".*c"}, false),
         make_tuple(RegularExpressionMatchingCase{"aaa", "a*a"}, true),
         make_tuple(RegularExpressionMatchingCase{"aaa", "ab*a*c*a"}, true),
         make_tuple(RegularExpressionMatchingCase{"a", "ab*"}, true),
         make_tuple(RegularExpressionMatchingCase{"aaa", "aaaa"}, false),
         make_tuple(RegularExpressionMatchingCase{"bbbba", ".*a*a"}, true)}));
    auto got = solution->isMatch(input.s, input.p);
    CAPTURE(input);
    REQUIRE(got == expect);
  }
}
