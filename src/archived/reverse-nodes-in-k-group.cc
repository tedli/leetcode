#include "list-node.h"
#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
#include <climits>
#include <cstddef>
#include <memory>
#include <tuple>

using namespace Utils;
using namespace std;

// https://leetcode.cn/problems/reverse-nodes-in-k-group

class Solution {
public:
  ListNode *reverseKGroup(ListNode *head, int k) {
    static auto reverse = [](ListNode *begin, ListNode *end) {
      auto t = begin;
      auto p = make_unique<ListNode>(INT_MAX, begin);
      while (begin != end) {
        auto i = p->next;
        auto j = begin->next;
        p->next = begin;
        begin->next = i;
        begin = j;
      }
      t->next = end;
      return make_tuple(p->next, t);
    };
    static auto postN = [](ListNode *begin, int n) {
      auto t = begin;
      auto e = true;
      for (int i = 0; i < n; ++i) {
        if (!t) {
          e = false;
          break;
        }
        t = t->next;
      }
      return make_tuple(t, e);
    };
    ListNode *newBegin = nullptr;
    ListNode *previousEnd = nullptr;
    for (auto begin = head; begin != nullptr;) {
      auto [end, enough] = postN(begin, k);
      if (!enough) {
        break;
      }
      auto [nb, ne] = reverse(begin, end);
      if (newBegin == nullptr) {
        newBegin = nb;
      }
      if (previousEnd != nullptr) {
        previousEnd->next = nb;
      }
      previousEnd = ne;
      begin = end;
    }
    return newBegin;
  }
};

struct ReverseNodes {
  ListNode *head;
  int k;
  ReverseNodes(ListNode *head, int k) : head(head), k(k) {}
  ReverseNodes() : head(nullptr), k(0) {}
};

ostream &operator<<(ostream &out, const ReverseNodes &value) {
  out << "<" << value.head << ", " << value.k << ">";
  return out;
}

TEST_CASE("Case 1", "[reverse-nodes-in-k-group]") {
  auto solution = make_unique<Solution>();
  SECTION("reverse-nodes-in-k-group official cases") {
    ReverseNodes input;
    ListNode *expect;
    tie(input, expect) = GENERATE(table<ReverseNodes, ListNode *>(
        {make_tuple(ReverseNodes(new ListNode({1, 2, 3, 4, 5}), 2),
                    new ListNode({2, 1, 4, 3, 5})),
         make_tuple(ReverseNodes(new ListNode({1, 2, 3, 4, 5}), 3),
                    new ListNode({3, 2, 1, 4, 5}))}));
    auto got = solution->reverseKGroup(input.head, input.k);
    CAPTURE(input);
    REQUIRE(listEqualThenRelease(got, expect));
  }
}
