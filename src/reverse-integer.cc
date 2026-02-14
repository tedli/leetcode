#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
#include <climits>
#include <memory>
#include <tuple>

using namespace std;

// https://leetcode.cn/problems/reverse-integer/description/

class Solution {
public:
  int reverse(int x) {
    static int max = INT_MAX / 10;
    static int min = INT_MIN / 10;
    int result = 0;
    do {
      if (result > max || result < min)
        return 0;
      auto nearlyOverflow = result == max || result == min;
      result *= 10;
      auto remainder = x % 10;
      if (nearlyOverflow && (remainder > 1 || remainder < -1))
        return 0;
      result += remainder;
      x /= 10;
    } while (abs(x) > 0);
    return result;
  }
};

TEST_CASE("Case 1", "[reverse integer]") {
  auto solution = std::make_unique<Solution>();
  SECTION("reverse integer official cases") {
    int input, expect;
    std::tie(input, expect) = GENERATE(
        table<int, int>({std::make_tuple(123, 321), std::make_tuple(-123, -321),
                         std::make_tuple(1463847412, 2147483641)}));
    auto got = solution->reverse(input);
    CAPTURE(input);
    REQUIRE(got == expect);
  }
}
