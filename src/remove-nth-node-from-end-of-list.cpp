#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
#include <catch2/matchers/catch_matchers_predicate.hpp>
#include <climits>
#include <memory>
#include <tuple>
#include <vector>

using namespace std;

// https://leetcode.cn/problems/remove-nth-node-from-end-of-list/

struct ListNode {
  int val;
  ListNode *next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode *next) : val(x), next(next) {}
};

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
};

ostream &operator<<(ostream &out, ListNode *const &value) {
  out << "[";
  for (auto i = value; i != nullptr; i = i->next) {
    if (i != value)
      out << ", ";
    out << i->val;
  }
  out << "]";
  return out;
};

ostream &operator<<(ostream &out, RemoveNthNodeFromEndOfList const &value) {
  out << "<";
  out << value.head;
  out << ", " << value.n << ">";
  return out;
}

tuple<RemoveNthNodeFromEndOfList, ListNode *>
makeCase(vector<int> &&nums, int n, vector<int> &&expect) {
  auto head = new ListNode;
  RemoveNthNodeFromEndOfList input{head, n};
  for (auto i = nums.begin(); i != nums.end(); ++i) {
    if (i == nums.begin()) {
      head->val = *i;
      head->next = nullptr;
    } else {
      auto current = new ListNode(*i, nullptr);
      head->next = current;
      head = current;
    }
  }
  if (expect.empty())
    return make_tuple(input, nullptr);
  ListNode *expectList = new ListNode;
  auto result = make_tuple(input, expectList);
  for (auto i = expect.begin(); i != expect.end(); ++i) {
    if (i == expect.begin()) {
      expectList->val = *i;
      expectList->next = nullptr;
    } else {
      auto current = new ListNode(*i, nullptr);
      expectList->next = current;
      expectList = current;
    }
  }
  return result;
}

void releaseList(ListNode *head) {
  if (head == nullptr)
    return;
  ListNode *p = nullptr;
  do {
    p = head->next;
    delete head;
    head = p;
  } while (p != nullptr);
}

bool listEqual(ListNode *got, ListNode *expect) {
  while (true) {
    if (got == nullptr && expect == nullptr) {
      return true;
    } else if (got == nullptr && expect != nullptr) {
      return false;
    } else if (got != nullptr && expect == nullptr) {
      return false;
    } else if (got->next == nullptr && expect->next != nullptr) {
      return false;
    } else if (got->next != nullptr && expect->next == nullptr) {
      return false;
    } else {
      if (got->val != expect->val) {
        return false;
      }
      got = got->next;
      expect = expect->next;
    }
  }
}

bool listEqualThenRelease(ListNode *got, ListNode *expect) {
  bool equal = listEqual(got, expect);
  releaseList(got);
  releaseList(expect);
  return equal;
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
