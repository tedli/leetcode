#include <catch2/catch_test_macros.hpp>

// https://leetcode.cn/problems/add-two-numbers/description/

struct ListNode {
  int val;
  ListNode *next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
  ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) {
    ListNode *sum = nullptr;
    ListNode *previous = nullptr;
    ListNode *current = nullptr;
    int carry = 0;
    while (l1 != nullptr || l2 != nullptr) {
      int val = 0;
      int lv1 = 0;
      int lv2 = 0;
      if (l1 != nullptr) {
        lv1 = l1->val;
        l1 = l1->next;
      }
      if (l2 != nullptr) {
        lv2 = l2->val;
        l2 = l2->next;
      }
      val = carry + lv1 + lv2;
      if (val >= 10) {
        carry = val / 10;
        val = val % 10;
      } else {
        carry = 0;
      }
      if (sum == nullptr) {
        sum = new ListNode;
        sum->val = val;
        previous = sum;
        continue;
      }
      current = new ListNode;
      current->val = val;
      previous->next = current;
      previous = current;
      current = nullptr;
    }
    if (carry > 0) {
      current = new ListNode;
      current->val = carry;
      carry = 0;
      previous->next = current;
    }
    return sum;
  }
};

TEST_CASE("Case 1", "[sum]") {
  auto l1 = new ListNode;
  auto l2 = new ListNode;
  ListNode *head = nullptr;
  ListNode *temp = nullptr;
  head = l1;
  head->val = 2;
  temp = new ListNode;
  head->next = temp;
  temp->val = 4;
  head = temp;
  temp = new ListNode;
  temp->val = 3;
  head->next = temp;
  head = l2;
  head->val = 5;
  temp = new ListNode;
  temp->val = 6;
  head->next = temp;
  head = temp;
  temp = new ListNode;
  temp->val = 4;
  head->next = temp;
  auto sum = (new Solution)->addTwoNumbers(l1, l2);
  REQUIRE(sum->val == 7);
}
