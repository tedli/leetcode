#include "list-node.h"
#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
#include <climits>
#include <memory>
#include <tuple>
#include <vector>

using namespace Utils;
using namespace std;

// https://leetcode.cn/problems/merge-two-sorted-lists

class Solution {
public:
  ListNode *mergeTwoLists(ListNode *list1, ListNode *list2) {
    auto p1 = new ListNode(0, list1);
    auto head = p1;
    auto p2 = new ListNode(0, list2);
    while (p1->next != nullptr && p2->next != nullptr) {
      auto c1 = p1->next;
      auto c2 = p2->next;
      if (c2->val < c1->val) {
        auto t = p1->next;
        p1->next = c2;
        auto t2 = c2->next;
        c2->next = t;
        p1 = c2;
        p2->next = t2;
      } else {
        p1 = c1;
      }
    }
    if (p2->next != nullptr) {
      p1->next = p2->next;
    }
    return head->next;
  };
};

struct MergeTwoSortedLists {
  ListNode *list1;
  ListNode *list2;
  bool initialized;

  ListNode *makeList(vector<int> &&nums) {
    if (nums.empty())
      return nullptr;
    return new ListNode(std::move(nums));
  };

  MergeTwoSortedLists(vector<int> a, vector<int> b) {
    list1 = makeList(std::move(a));
    list2 = makeList(std::move(b));
    initialized = true;
  }
  MergeTwoSortedLists() : list1(nullptr), list2(nullptr), initialized(true) {}

  ~MergeTwoSortedLists() {
    list1 = nullptr;
    list2 = nullptr;
    initialized = false;
  }
};

ostream &operator<<(ostream &out, const MergeTwoSortedLists &value) {
  if (!value.initialized) {
    return out;
  }
  out << "<";
  out << value.list1;
  out << ", ";
  out << value.list2;
  out << ">";
  return out;
}

TEST_CASE("Case 1", "[merge-two-sorted-lists]") {
  auto solution = make_unique<Solution>();
  SECTION("merge-two-sorted-lists official cases") {
    MergeTwoSortedLists input;
    ListNode *expect;
    tie(input, expect) = GENERATE(table<MergeTwoSortedLists, ListNode *>(
        {make_tuple(
             MergeTwoSortedLists(vector<int>{1, 2, 4}, vector<int>{1, 3, 4}),
             new ListNode(vector<int>{1, 1, 2, 3, 4, 4})),
         make_tuple(MergeTwoSortedLists(), nullptr),
         make_tuple(MergeTwoSortedLists(vector<int>(), vector<int>{0}),
                    new ListNode(vector<int>{0}))}));
    auto got = solution->mergeTwoLists(input.list1, input.list2);
    CAPTURE(input);
    REQUIRE(listEqualThenRelease(got, expect));
  }
}
