#include "list-node.h"
#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
#include <climits>
#include <memory>
#include <queue>
#include <tuple>
#include <vector>

using namespace Utils;
using namespace std;

// https://leetcode.cn/problems/merge-k-sorted-lists

class Solution {
public:
  ListNode *mergeKLists(vector<ListNode *> &lists) {
    const static auto greater = [](ListNode *a, ListNode *b) {
      return a->val > b->val;
    };
    auto queue =
        priority_queue<ListNode *, vector<ListNode *>, decltype(greater)>(
            greater);
    for (auto list : lists) {
      if (list) {
        queue.push(list);
      }
    }
    auto head = ListNode();
    auto tail = &head;
    while (!queue.empty()) {
      auto top = queue.top();
      queue.pop();
      tail->next = top;
      tail = tail->next;
      if (top->next) {
        queue.push(top->next);
      }
    }
    return head.next;
  }
};

struct MergeKLists {
  vector<ListNode *> lists;
  bool initialized;

  ListNode *makeList(vector<int> &&nums) {
    if (nums.empty())
      return nullptr;
    return new ListNode(std::move(nums));
  };

  MergeKLists(vector<vector<int>> lists) {
    this->lists.reserve(lists.size());
    for (auto &list : lists) {
      this->lists.push_back(makeList(std::move(list)));
    }
    initialized = true;
  }
  MergeKLists() : lists({}), initialized(true) {}

  ~MergeKLists() {
    lists.clear();
    initialized = false;
  }
};

ostream &operator<<(ostream &out, const MergeKLists &value) {
  if (!value.initialized) {
    return out;
  }
  out << "<";
  auto first = true;
  for (auto &list : value.lists) {
    if (!first) {
      out << ", ";
    } else {
      first = false;
    }
    out << list;
  }
  out << ">";
  return out;
}

TEST_CASE("Case 1", "[merge-k-sorted-lists]") {
  auto solution = make_unique<Solution>();
  SECTION("merge-k-sorted-lists official cases") {
    MergeKLists input;
    ListNode *expect;
    tie(input, expect) = GENERATE(table<MergeKLists, ListNode *>(
        {make_tuple(
             MergeKLists(vector<vector<int>>{{1, 4, 5}, {1, 3, 4}, {2, 6}}),
             new ListNode({1, 1, 2, 3, 4, 4, 5, 6})),
         make_tuple(MergeKLists(), nullptr),
         make_tuple(MergeKLists(vector<vector<int>>{{}}), nullptr)}));
    auto got = solution->mergeKLists(input.lists);
    CAPTURE(input);
    REQUIRE(listEqualThenRelease(got, expect));
  }
}
