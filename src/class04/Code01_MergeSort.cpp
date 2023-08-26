#include <iostream>
#include <vector>
#include <random>
#include <algorithm>

using namespace std;

class Solution {
 public:
  // 递归方法实现
  static void mergeSort1(vector<int> &v) {
    if (v.empty() || v.size() < 2)
      return;

    process(v, 0, v.size() - 1);
  }

  // 非递归方法实现
  static void mergeSort2(vector<int> &v) {
    if (v.empty() || v.size() < 2)
      return;

    int N = v.size();
    // 步长
    int step = 1;
    while (step < N) {
      int L = 0;

      while (L < N) {
        if (L + step - 1 >= N)
          break;

        int M = L + step - 1;
        int R = min(M + step, N - 1);
        merge(v, L, M, R);
        L = R + 1;
      }

      if (step > N / 2)
        break;

      step <<= 1;
    }
  }

 private:
  static void process(vector<int> &v, int L, int R) {
    // base case
    if (L == R) return;

    int M = L + ((R - L) >> 1);
    process(v, L, M);
    process(v, M + 1, R);
    merge(v, L, M, R);
  }

  static void merge(vector<int> &v, int L, int M, int R) {
    vector<int> aux(R - L + 1);
    int i{};
    int p1{L};
    int p2{M + 1};

    while (p1 <= M && p2 <= R)
      aux[i++] = (v[p1] <= v[p2] ? v[p1++] : v[p2++]);

    while (p1 <= M)
      aux[i++] = v[p1++];

    while (p2 <= R)
      aux[i++] = v[p2++];

    copy(aux.begin(), aux.end(), v.begin() + L);
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

    Solution::mergeSort2(v1);
    sort(v2.begin(), v2.end());

    if (v1 != v2) {
      flag = false;
      break;
    }
  }

  cout << (flag ? "Nice" : "Fucking fucked") << endl;
  return 0;
}
