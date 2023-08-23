#include <iostream>
#include <vector>
#include <random>
#include <algorithm>

using namespace std;

class Solution {
 public:
  static void insertionSort(vector<int> &v) {
    if (v.empty())
      return;

    for (auto i = 1; i < v.size(); ++i) {
      for (auto j = i - 1; j >= 0; --j)
        if (v[j] > v[j + 1])
          swap(v[j], v[j + 1]);
    }
  }
};

int main() {
  int testTime = 500000;
  int maxSize = 100;
  int maxValue = 100;
  bool succeed = true;
  // 创建随机数引擎
  random_device rd;      // 用于获取种子
  mt19937 gen(rd()); // Mersenne Twister引擎，以rd()作为种子

  // 创建均匀分布
  uniform_int_distribution<> sdist(1, maxSize);
  uniform_int_distribution<> vdist(1, maxValue);

  for (int i = 0; i < testTime; ++i) {
    vector<int> v1(sdist(gen));
    for (auto &j : v1)
      j = vdist(gen);

    vector<int> v2(v1);

    Solution::insertionSort(v1);
    sort(v2.begin(), v2.end());

    if (v1 != v2) {
      succeed = false;
      break;
    }
  }

  cout << (succeed ? "Nice" : "Fucking fucked") << endl;
  return 0;
}
