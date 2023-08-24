#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  // arr中，只有一种数，出现奇数次
  static void printOddTimesNum1(const vector<int> &v) {
    int a{};
    for (auto i : v)
      a ^= i;

    cout << a << endl;
  }

  // arr中，有两种数，出现奇数次
  static void printOddTimesNum2(const vector<int> &v) {
    int a{};
    for (auto i : v)
      a ^= i;

    int rightOne = a & (-a);
    int b{};
    for (auto i : v)
      if ((i & rightOne) != 0)
        b ^= i;

    cout << (a ^ b) << endl;
    cout << b << endl;
  }
};

int main() {
  const vector<int> v1{3, 3, 2, 3, 1, 1, 1, 3, 1, 1, 1};
  Solution::printOddTimesNum1(v1);

  const vector<int> v2{4, 3, 4, 2, 2, 2, 4, 1, 1, 1, 3, 3, 1, 1, 1, 4, 2, 2};
  Solution::printOddTimesNum2(v2);

  return 0;
}
