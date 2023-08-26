#include <iostream>
#include <vector>
#include <random>
#include <algorithm>

using namespace std;

class Solution {
 public:
  // arr[L..R]上，以arr[R]位置的数做划分值
  // <= X > X
  // <= X X
  static int partition(vector<int> &v, int L, int R) {
    if (L > R) return -1;

    if (L == R) return L;

    int i{L};
    int j{L - 1};
    while (i < R) {
      if (v[i] <= v[R])
        swap(v[i], v[++j]);

      ++i;
    }

    swap(v[++j], v[R]);
    return j;
  }

  // arr[L...R] 玩荷兰国旗问题的划分，以arr[R]做划分值
  // <arr[R] =arr[R] >arr[R]
  static vector<int> netherlandsFlag(vector<int> &v, int L, int R) {
    if (L > R) return {-1, -1};

    if (L == R) return {L, R};

    int i{L - 1}; // < 区 右边界
    int j{R}; // > 区 左边界
    int k{L};

    while (k < j) { // 当前位置，不能和 >区的左边界撞上
      if (v[k] == v[R])
        ++k;
      else if (v[k] < v[R])
        swap(v[k++], v[++i]);
      else
        swap(v[k], v[--j]);
    }

    swap(v[j], v[R]);
    return {i + 1, j};
  }

  static void quickSort1(vector<int> &v) {
    if (v.empty() || v.size() < 2)
      return;

    process1(v, 0, v.size() - 1);
  }

  static void quickSort2(vector<int> &v) {
    if (v.empty() || v.size() < 2)
      return;

    process2(v, 0, v.size() - 1);
  }

  static void quickSort3(vector<int> &v) {
    if (v.empty() || v.size() < 2)
      return;

    process3(v, 0, v.size() - 1);
  }

 private:
  static void process1(vector<int> &v, int L, int R) {
    if (L >= R) return;

    int M = partition(v, L, R);
    process1(v, L, M - 1);
    process1(v, M + 1, R);
  }

  static void process2(vector<int> &v, int L, int R) {
    if (L >= R) return;

    auto p = netherlandsFlag(v, L, R);
    process1(v, L, p[0] - 1);
    process1(v, p[1] + 1, R);
  }

  static void process3(vector<int> &v, int L, int R) {
    if (L >= R) return;

    srand(time(nullptr));
    swap(v[R], v[rand() % (R - L + 1) + L]);
    auto p = netherlandsFlag(v, L, R);
    process1(v, L, p[0] - 1);
    process1(v, p[1] + 1, R);
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

    Solution::quickSort3(v1);
    sort(v2.begin(), v2.end());
    if (v1 != v2) {
      flag = false;
      break;
    }
  }

  cout << (flag ? "Nice" : "Fucking fucked") << endl;
  return 0;
}
