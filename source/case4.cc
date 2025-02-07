#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
#include <cstring>
#include <memory>
#include <numeric>
#include <string>
#include <tuple>

using std::string;

// https://leetcode.cn/problems/zigzag-conversion/

/*
输入：s = "PAYPALISHIRING", numRows = 4
输出："PINALSIGYAHRPI"
解释：
P    I    N
A  L S  I G
Y A  H R
P    I


0 1 2 3 4 5 6 7 8 9 10 11 12 13
P A Y P A L I S H I R  I  N  G

0     6      12
1   5 7   11 13
2 4   8 10
3     9

   6 6
  4 2 4 2
 2 4 2
6

P   A   H   N
A P L S I I G
Y   I   R


0   4   8    12
1 3 5 7 9 11 13
2   6   10

  4 4 4
 2 2 2 2 2 2
4 4 4


0 1 2 3 4 5 6 7 8 9 10 11 12 13
P A Y P A L I S H I R  I  N  G

P     H
A   S I
Y  I  R
P L   I G
A     N

0     8
1   7 9
2  6  10
3 5   11 13
4     12

    8
   6 2
  4 4
 2 6 2
8



*/

class Solution {
public:
  string convert(string s, int numRows) {
    if (numRows == 1)
      return s;
    int step = 2 * numRows - 2;
    std::vector<string> buffer(numRows);
    for (int i = 0; i < s.size(); ++i) {
      buffer[std::min(step - i % step, i % step)] += s[i];
    }
    return std::accumulate(buffer.begin(), buffer.end(), string(""));
  }
};

struct Case {
  string s;
  int rows;
};

std::ostream &operator<<(std::ostream &out, Case const &value) {
  out << "<\"" << value.s << "\", " << value.rows << ">";
  return out;
}

TEST_CASE("Case 1", "[z convert]") {
  auto solution = std::make_unique<Solution>();
  SECTION("z convert official cases") {
    Case input;
    string expect;
    std::tie(input, expect) = GENERATE(table<Case, string>(
        {std::make_tuple(Case{"PAYPALISHIRING", 3}, "PAHNAPLSIIGYIR")}));
    auto got = solution->convert(input.s, input.rows);
    CAPTURE(input);
    REQUIRE(got == expect);
  }
}
