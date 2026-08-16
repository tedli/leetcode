#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
#include <string>
#include <vector>

namespace Utils {

struct NumsTargetInput {
  std::vector<int> nums;
  int target;
};

} // namespace Utils

namespace Catch {

template <> struct StringMaker<Utils::NumsTargetInput> {
  static std::string convert(Utils::NumsTargetInput const &value) {
    std::stringstream buffer;
    buffer << "<[";
    if (!value.nums.empty()) {
      buffer << value.nums[0];
      for (size_t i = 1; i < value.nums.size(); ++i) {
        buffer << ", " << value.nums[i];
      }
    }
    buffer << "], " << value.target << ">";
    return buffer.str();
  }
};

} // namespace Catch
