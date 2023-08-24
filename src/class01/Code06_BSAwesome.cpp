#include <iostream>
#include <vector>
#include <random>
#include <algorithm>

using namespace std;

class Solution {
 public:
  static int getLessIndex(const vector<int> &v) {
    if (v.empty())
      return -1;

    if (v.size() == 1 || v[0] < v[1])
      return 0;

    if (v[v.size() - 1] < v[v.size() - 2])
      return v.size() - 1;

    int L = 1;
    int R = v.size() - 2;
    int M = -1;

    while (L <= R) {
      M = L + ((R - L) >> 1);

      if (v[M] > v[M - 1])
        R = M - 1;
      else if (v[M] > v[M + 1])
        L = M + 1;
      else
        break;
    }

    return M;
  }
};

bool isRight(const vector<int> &v, int i) {
  if (v.size() == 1)
    return i == 0;

  if (i == 0)
    return v[i] < v[i + 1];

  if (i == v.size() - 1)
    return v[i] < v[i - 1];

  return v[i] < v[i - 1] && v[i] < v[i + 1];
}

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

    v.resize(distance(v.begin(), unique(v.begin(), v.end())));
    int j = Solution::getLessIndex(v);

    if (!isRight(v, j)) {
      succeed = false;
      break;
    }
  }

  cout << (succeed ? "Nice" : "Fucking fucked") << endl;
  return 0;
}
