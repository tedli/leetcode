#include "list-node.h"
#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
#include <catch2/matchers/catch_matchers_predicate.hpp>
#include <climits>
#include <memory>
#include <tuple>
#include <vector>

using namespace Utils;
using namespace std;

// https://leetcode.cn/problems/remove-nth-node-from-end-of-list/

class Solution {
public:
  ListNode *removeNthFromEnd(ListNode *head, int n) {
    auto h = new ListNode(0, head);
    auto p = head;
    auto q = h;
    for (int i = 0; i < n; ++i) {
      p = p->next;
    }
    while (p != nullptr) {
      p = p->next;
      q = q->next;
    }
    auto r = q->next;
    q->next = q->next->next;
    auto s = h->next;
    delete h;
    delete r;
    return s;
  };
};

struct RemoveNthNodeFromEndOfList {
  ListNode *head;
  int n;
  bool initialized;
  RemoveNthNodeFromEndOfList() : head(nullptr), n(0), initialized(true) {}
  RemoveNthNodeFromEndOfList(ListNode *head, int n)
      : head(head), n(n), initialized(true) {}
  ~RemoveNthNodeFromEndOfList() {
    head = nullptr;
    initialized = false;
  }
};

ostream &operator<<(ostream &out, RemoveNthNodeFromEndOfList const &value) {
  if (!value.initialized) {
    return out;
  }
  out << "<";
  out << value.head;
  out << ", " << value.n << ">";
  return out;
}

tuple<RemoveNthNodeFromEndOfList, ListNode *>
makeCase(vector<int> &&nums, int n, vector<int> &&expect) {
  auto input = RemoveNthNodeFromEndOfList{new ListNode(std::move(nums)), n};
  if (expect.empty())
    return make_tuple(input, nullptr);
  return make_tuple(input, new ListNode(std::move(expect)));
}

TEST_CASE("Case 1", "[remove-nth-node-from-end-of-list]") {
  auto solution = make_unique<Solution>();
  SECTION("remove-nth-node-from-end-of-list official cases") {
    RemoveNthNodeFromEndOfList input;
    ListNode *expect;
    tie(input, expect) = GENERATE(table<RemoveNthNodeFromEndOfList, ListNode *>(
        {makeCase(vector<int>{1, 2, 3, 4, 5}, 2, vector<int>{1, 2, 3, 5}),
         makeCase(vector<int>{1}, 1, vector<int>{}),
         makeCase(vector<int>{1, 2}, 1, vector<int>{1})}));
    auto got = solution->removeNthFromEnd(input.head, input.n);
    CAPTURE(input);
    REQUIRE(listEqualThenRelease(got, expect));
  }
}
