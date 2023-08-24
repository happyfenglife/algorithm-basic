#include <iostream>
#include <vector>
#include <unordered_map>
#include <random>

using namespace std;

// 输入一定能够保证，数组中所有的数都出现了M次，只有一种数出现了K次
// 1 <= K < M
// 返回这种数
class Solution {
 public:
  static int bruteForce(const vector<int> &v, int k, int m) {
    unordered_map<int, int> record;
    for (auto i : v)
      if (record.count(i) == 0)
        record.insert({i, 1});
      else
        record[i]++;

    for (const auto &p : record)
      if (p.second == k)
        return p.first;

    return 0;
  }

  // 请保证arr中，只有一种数出现了K次，其他数都出现了M次
  static int onlyKTimes(const vector<int> &v, int k, int m) {
    vector<int> ones(32, 0);
    for (auto i : v)
      for (int j = 0; j < 32; ++j)
        ones[j] += ((i >> j) & 1);

    int a{};
    for (int i = 0; i < 32; ++i)
      if (ones[i] % m == k)
        a |= (1 << i);

    return a;
  }
};

int main() {
  vector<int> v{2, 2, 2, 4, 5, 5, 5, 3, 3, 3, 1, 1, 1};

  int a{Solution::bruteForce(v, 1, 3)};
  int b{Solution::onlyKTimes(v, 1, 3)};
  cout << a << endl;
  cout << b << endl;
  cout << (a == b ? "Nice" : "Fucking fucked") << endl;
  return 0;
}
