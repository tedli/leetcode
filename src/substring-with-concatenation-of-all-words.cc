#include <algorithm>
#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
#include <memory>
#include <sstream>
#include <string>
#include <string_view>
#include <tuple>
#include <unordered_set>
#include <vector>

using namespace std;

// https://leetcode.cn/problems/substring-with-concatenation-of-all-words/description/

namespace SubstringWithConcatenationOfAllWords {

class Solution {
public:
  vector<int> findSubstring(string s, vector<string> &words) {
    const int kWordCount = words.size();
    const int kWordSize = words[0].size();
    const int kStringLength = s.size();
    const int kSubstringSize = kWordCount * kWordSize;
    const int kMaxTryIndex = kStringLength - kSubstringSize;
    auto word_set = unordered_multiset<string_view>();
    for (auto &word : words) {
      word_set.insert(word);
    }
    auto s_view = string_view(s);
    auto set = word_set;
    auto result = unordered_set<int>();
    for (auto i = 0; i <= kMaxTryIndex; ++i) {
      if (auto it = result.find(i); it != result.end())
        continue;
      auto part = s_view.substr(i, kWordSize);
      auto it = set.find(part);
      if (it == set.end())
        continue;
      set.erase(it);
      if (set.empty()) {
        result.insert(i);
        set = word_set;
        continue;
      }
      for (auto j = i + kWordSize; j < kStringLength;) {
        part = s_view.substr(j, kWordSize);
        it = set.find(part);
        if (it == set.end()) {
          set = word_set;
          break;
        }
        set.erase(it);
        if (set.empty()) {
          result.insert(i);
          for (auto k = i; k <= kMaxTryIndex; k += kWordSize) {
            auto left = s_view.substr(k, kWordSize);
            auto right = s_view.substr(k + kSubstringSize, kWordSize);
            if (left == right) {
              result.insert(k + kWordSize);
            } else {
              break;
            }
          }
          set = word_set;
          break;
        }
        j += kWordSize;
      }
    }
    return vector(result.begin(), result.end());
  }
};

struct Case {
  Case() {}
  Case(string &&s, vector<string> &&words) : s(s), words(words) {}
  string s;
  vector<string> words;
};

} // namespace SubstringWithConcatenationOfAllWords

namespace Catch {

using Case = SubstringWithConcatenationOfAllWords::Case;

template <> struct StringMaker<Case> {
  static string convert(Case const &c) {
    stringstream buffer;
    buffer << "<" << c.s << ", [";
    if (c.words.size() > 0) {
      auto begin = c.words.begin();
      buffer << *begin++;
      for (; begin != c.words.end(); ++begin)
        buffer << ", " << *begin;
    }
    buffer << "]> ";
    return buffer.str();
  }
};

} // namespace Catch

TEST_CASE("Case 1", "[substring-with-concatenation-of-all-words]") {
  using Case = SubstringWithConcatenationOfAllWords::Case;
  using Solution = SubstringWithConcatenationOfAllWords::Solution;
  auto solution = make_unique<Solution>();
  SECTION("substring-with-concatenation-of-all-words official cases") {
    Case input;
    vector<int> expect;
    tie(input, expect) = GENERATE(table<Case, vector<int>>(
        {{{"barfoothefoobarman", vector<string>{"foo", "bar"}},
          vector<int>{0, 9}},
         {{"wordgoodgoodgoodbestword",
           vector<string>{"word", "good", "best", "word"}},
          vector<int>()},
         {{"barfoofoobarthefoobarman", vector<string>{"foo", "bar", "the"}},
          vector<int>{6, 9, 12}},
         {{"lingmindraboofooowingdingbarrwingmonkeypoundcake",
           vector<string>{"fooo", "barr", "wing", "ding", "wing"}},
          vector<int>{13}},
         {{"a", vector<string>{"a"}}, vector<int>{0}},
         {{"mississippi", vector<string>{"is"}}, vector<int>{1, 4}}}));
    auto got = solution->findSubstring(input.s, input.words);
    CAPTURE(input);
    REQUIRE((got.size() == expect.size() &&
             is_permutation(got.begin(), got.end(), expect.begin())));
  }
}
