#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
#include <memory>
#include <tuple>
#include <unordered_set>
#include <vector>

using namespace std;

// https://leetcode.cn/problems/valid-sudoku/description/

namespace ValidSudoku {
class Solution {
public:
  bool isValidSudoku(vector<vector<char>> &board) {
    auto columns = []<size_t... Is>(index_sequence<Is...>) {
      return array<unordered_set<char>, 9>{
          ((void)Is, unordered_set<char>(9))...};
    }(make_index_sequence<9>{});
    for (auto i = board.begin(); i != board.end(); ++i) {
      auto row = unordered_set<char>(9);
      for (auto j = i->begin(); j != i->end(); ++j) {
        if (*j == '.') {
          continue;
        }
        if (row.find(*j) != row.end()) {
          return false;
        }
        row.insert(*j);
        auto &column = columns[distance(i->begin(), j)];
        if (column.find(*j) != column.end()) {
          return false;
        }
        column.insert(*j);
      }
    }
    for (int i = 0; i < 9; ++i) {
      auto box = unordered_set<char>(9);
      for (int j = 0; j < 9; ++j) {
        auto row = i / 3 * 3 + j / 3;
        auto column = i % 3 * 3 + j % 3;
        if (board[row][column] == '.') {
          continue;
        }
        if (box.find(board[row][column]) != box.end()) {
          return false;
        }
        box.insert(board[row][column]);
      }
    }
    return true;
  }
};
} // namespace ValidSudoku

TEST_CASE("Case 1", "[valid-sudoku]") {
  auto solution = make_unique<ValidSudoku::Solution>();
  SECTION("valid-sudoku official cases") {
    vector<vector<char>> input;
    bool expect;
    tie(input, expect) = GENERATE(table<vector<vector<char>>, bool>(
        {{{{'5', '3', '.', '.', '7', '.', '.', '.', '.'},
           {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
           {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
           {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
           {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
           {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
           {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
           {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
           {'.', '.', '.', '.', '8', '.', '.', '7', '9'}},
          true},
         {{{'8', '3', '.', '.', '7', '.', '.', '.', '.'},
           {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
           {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
           {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
           {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
           {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
           {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
           {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
           {'.', '.', '.', '.', '8', '.', '.', '7', '9'}},
          false},
         {{{'.', '.', '4', '.', '.', '.', '6', '3', '.'},
           {'.', '.', '.', '.', '.', '.', '.', '.', '.'},
           {'5', '.', '.', '.', '.', '.', '.', '9', '.'},
           {'.', '.', '.', '5', '6', '.', '.', '.', '.'},
           {'4', '.', '3', '.', '.', '.', '.', '.', '1'},
           {'.', '.', '.', '7', '.', '.', '.', '.', '.'},
           {'.', '.', '.', '5', '.', '.', '.', '.', '.'},
           {'.', '.', '.', '.', '.', '.', '.', '.', '.'},
           {'.', '.', '.', '.', '.', '.', '.', '.', '.'}},
          false}}));
    auto got = solution->isValidSudoku(input);
    CAPTURE(input);
    REQUIRE(got == expect);
  }
}
