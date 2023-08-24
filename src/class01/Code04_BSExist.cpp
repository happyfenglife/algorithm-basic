#include <iostream>
#include <vector>
#include <random>
#include <algorithm>

using namespace std;

class Solution {
 public:
  static bool exist(const vector<int> &v, int k) {
    int L = 0;
    int R = v.size() - 1;

    while (L <= R) {
      int M = L + ((R - L) >> 1);

      if (v[M] == k)
        return true;
      else if (v[M] < k)
        L = M + 1;
      else
        R = M - 1;
    }

    return false;
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
    vector<int> v(sdist(gen));
    for (auto &j : v)
      j = vdist(gen);

    sort(v.begin(), v.end());

    int k = vdist(gen);

    bool j = Solution::exist(v, k);
    bool t = count_if(v.begin(), v.end(), [&](auto p) {
      return p == k;
    }) != 0;

    if (j != t) {
      succeed = false;
      break;
    }
  }

  cout << (succeed ? "Nice" : "Fucking fucked") << endl;
  return 0;
}
