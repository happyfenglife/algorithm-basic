#include <iostream>
#include <vector>
#include <random>
#include <algorithm>

using namespace std;

class Solution {
 public:
  // 堆排序额外空间复杂度O(1)
  static void heapSort(vector<int> &v) {
    if (v.empty() || v.size() < 2) return;

    // O(N * logN)
    // for (int i = 0; i < v.size(); ++i)
    //   heapInsert(v, i);

    // O(N)
    for (int i = v.size() - 1; i >= 0; --i)
      heapify(v, i, v.size());

    int N = v.size();
    swap(v[0], v[--N]);

    // O(N * logN)
    while (N > 0) {
      heapify(v, 0, N); // O(logN)
      swap(v[0], v[--N]); // O(1)
    }
  }

 private:
  // 新加进来的数，现在停在了index位置，请依次往上移动，
  // 移动到0位置，或者干不掉自己的父亲了，停！
  static void heapInsert(vector<int> &v, int i) {
    while (v[i] > v[(i - 1) / 2]) {
      swap(v[i], v[(i - 1) / 2]);
      i = (i - 1) / 2;
    }
  }

  // 从index位置，往下看，不断的下沉
  // 停：较大的孩子都不再比index位置的数大；已经没孩子了
  static void heapify(vector<int> &v, int i, int N) {
    int l = i * 2 + 1;
    while (l < N) { // 如果有左孩子，有没有右孩子，可能有可能没有！
      // 把较大孩子的下标，给largest
      int j = (l + 1 < N && v[l + 1] > v[l]) ? l + 1 : l;
      j = (v[j] > v[i] ? j : i);

      if (j == i)
        break;
      swap(v[j], v[i]);
      i = j;
      l = i * 2 + 1;
    }
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
  bool succeed = true;
  for (int i = 0; i < testTime; i++) {
    auto v1 = generateVec(maxSize, maxValue);
    auto v2(v1);

    Solution::heapSort(v1);
    sort(v2.begin(), v2.end());

    if (v1 != v2) {
      succeed = false;
      break;
    }
  }

  cout << (succeed ? "Nice!" : "Fucking fucked!") << endl;
  return 0;
}
