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

// https://leetcode.cn/problems/swap-nodes-in-pairs

class Solution {
public:
  ListNode *swapPairs(ListNode *head) {
    if (head == nullptr || head->next == nullptr)
      return head;
    auto p = make_unique<ListNode>(INT_MAX, head);
    for (ListNode *i = p.get(); i != nullptr; i = i->next->next) {
      if (i->next == nullptr || i->next->next == nullptr)
        break;
      auto a = i->next->next->next;
      i->next->next->next = i->next;
      i->next = i->next->next;
      i->next->next->next = a;
    }
    return p->next;
  }
};

TEST_CASE("Case 1", "[swap-nodes-in-pairs]") {
  auto solution = make_unique<Solution>();
  SECTION("swap-nodes-in-pairs official cases") {
    ListNode *input;
    ListNode *expect;
    tie(input, expect) = GENERATE(table<ListNode *, ListNode *>(
        {make_tuple(new ListNode({1, 2, 3, 4}), new ListNode({2, 1, 4, 3}))}));
    auto got = solution->swapPairs(input);
    CAPTURE(input);
    REQUIRE(listEqualThenRelease(got, expect));
  }
}
