#include <iostream>
#include <vector>
#include <random>
#include <algorithm>

using namespace std;

class Solution {
 public:
  static int reversePairNumber(vector<int> &v) {
    if (v.size() == 1)
      return 0;

    return process(v, 0, v.size() - 1);
  }

  static int bruteForce(vector<int> &v) {
    int k{};
    for (int i = 0; i < v.size(); i++)
      for (int j = i + 1; j < v.size(); j++)
        if (v[i] > v[j])
          k++;

    return k;
  }

 private:
  // arr[L..R]既要排好序，也要求逆序对数量返回
  // 所有merge时，产生的逆序对数量，累加，返回
  // 左 排序 merge并产生逆序对数量
  // 右 排序 merge并产生逆序对数量
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
    int wR{M + 1};

    for (int j = L; j <= M; ++j) {

      while (wR <= R && v[j] > v[wR])
        ++wR;

      k += wR - M - 1;
    }

    while (p1 <= M && p2 <= R) {
      aux[i++] = (v[p1] <= v[p2] ? v[p1++] : v[p2++]);
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

    if (Solution::bruteForce(v1) != Solution::reversePairNumber(v2)) {
      flag = false;
      break;
    }
  }

  cout << (flag ? "Nice" : "Fucking fucked") << endl;
  return 0;
}
