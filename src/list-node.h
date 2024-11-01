#include <ostream>
#include <vector>

namespace Utils {

class ListNode {
public:
  int val;
  ListNode *next;

  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode *next) : val(x), next(next) {}
  ListNode(std::vector<int> &&nums);
  ~ListNode();
  bool operator==(ListNode const &other) const;
};

} // namespace Utils

bool listEqual(Utils::ListNode *got, Utils::ListNode *expect);

std::ostream &operator<<(std::ostream &out, Utils::ListNode *const &value);

void releaseList(Utils::ListNode *head);

bool listEqualThenRelease(Utils::ListNode *got, Utils::ListNode *expect);
