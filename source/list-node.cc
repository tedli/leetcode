#include "list-node.h"
#include <ostream>
#include <vector>

std::ostream &operator<<(std::ostream &out, Utils::ListNode *const &value) {
  out << "[";
  for (auto i = value; i != nullptr; i = i->next) {
    if (i != value)
      out << ", ";
    out << i->val;
  }
  out << "]";
  return out;
};

Utils::ListNode::ListNode(std::vector<int> &&nums) {
  ListNode *head = nullptr;
  for (auto i = nums.begin(); i != nums.end(); ++i) {
    if (i == nums.begin()) {
      val = *i;
      next = nullptr;
    } else {
      auto current = new ListNode(*i, nullptr);
      if (next == nullptr) {
        next = current;
        head = current;
      } else {
        head->next = current;
        head = current;
      }
    }
  }
}

Utils::ListNode::~ListNode() {
  val = 0;
  next = nullptr;
}

bool Utils::ListNode::operator==(ListNode const &other) const {
  auto got = this;
  auto expect = &other;
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

bool listEqual(Utils::ListNode *got, Utils::ListNode *expect) {
  if (got == nullptr && expect == nullptr) {
    return true;
  } else if (got == nullptr && expect != nullptr) {
    return false;
  } else if (got != nullptr && expect == nullptr) {
    return false;
  }
  return *got == *expect;
}

void releaseList(Utils::ListNode *head) {
  if (head == nullptr)
    return;
  Utils::ListNode *p = nullptr;
  do {
    p = head->next;
    delete head;
    head = p;
  } while (p != nullptr);
}

bool listEqualThenRelease(Utils::ListNode *got, Utils::ListNode *expect) {
  bool equal = listEqual(got, expect);
  releaseList(got);
  releaseList(expect);
  return equal;
}
