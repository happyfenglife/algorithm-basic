#include <iostream>
#include <vector>
#include <random>
#include <algorithm>

using namespace std;

class Solution {
 public:
  static int smallSum(vector<int> &v) {
    if (v.empty() || v.size() < 2)
      return 0;

    return process(v, 0, v.size() - 1);
  }

  static int bruteForce(vector<int> &v) {
    int cnt{};
    for (int i = 1; i < v.size(); ++i)
      for (int j = 0; j < i; ++j)
        cnt += v[j] < v[i] ? v[j] : 0;

    return cnt;
  }

 private:
  // arr[L..R]既要排好序，也要求小和返回
  // 所有merge时，产生的小和，累加
  // 左 排序   merge
  // 右 排序  merge
  // merge
  static int process(vector<int> &v, int L, int R) {
    // base case
    if (L == R) return 0;

    int M = L + ((R - L) >> 1);
    return process(v, L, M) +
        process(v, M + 1, R) +
        merge(v, L, M, R);
  }

  static int merge(vector<int> &v, int L, int M, int R) {
    vector<int> aux(R - L + 1);
    int i{};
    int p1{L};
    int p2{M + 1};
    int k{};

    while (p1 <= M && p2 <= R) {
      k += (v[p1] < v[p2] ? (R - p2 + 1) * v[p1] : 0);
      aux[i++] = (v[p1] < v[p2] ? v[p1++] : v[p2++]);
    }

    while (p1 <= M)
      aux[i++] = v[p1++];

    while (p2 <= R)
      aux[i++] = v[p2++];

    copy(aux.begin(), aux.end(), v.begin() + L);
    return k;
  }
};

static vector<int> generateVec(int size, int val) {
  static random_device rd;
  static mt19937 gen(rd());
  static uniform_int_distribution<> sdist(1, size);
  static uniform_int_distribution<> vdist(1, val);

  vector<int> v(sdist(gen));
  for (auto &i : v)
    i = vdist(gen);

  return v;
}

int main() {
  int testTime = 500000;
  int maxSize = 100;
  int maxValue = 100;
  bool flag{true};

  cout << "test begin\n";
  for (int z = 0; z < testTime; z++) {
    vector<int> v1 = generateVec(maxSize, maxValue);
    vector<int> v2(v1);

    if (Solution::bruteForce(v1) != Solution::smallSum(v2)) {
      flag = false;
      cout << Solution::bruteForce(v1) << endl;
      cout << Solution::smallSum(v2) << endl;
      break;
    }
  }

  cout << (flag ? "Nice" : "Fucking fucked") << endl;
  return 0;
}
