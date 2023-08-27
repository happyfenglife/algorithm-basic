#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <stack>

using namespace std;

class Solution {
 public:
  static void quickSort(vector<int> &v) {
    if (v.empty() || v.size() < 2)
      return;

    srand(time(nullptr));
    int N = v.size();
    swap(v[N - 1], v[rand() % N]);
    vector<int> res = netherlandsFlag(v, 0, N - 1);
    stack<vector<int>> s;
    s.push({0, res[0] - 1});
    s.push({res[1] + 1, N - 1});

    while (!s.empty()) {
      int l = s.top()[0];
      int r = s.top()[1];
      s.pop();

      if (l < r) {
        swap(v[r], v[l + rand() % (r - l + 1)]);
        res = netherlandsFlag(v, l, r);
        s.push({l, res[0] - 1});
        s.push({res[1] + 1, r});
      }
    }
  }

 private:
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

    Solution::quickSort(v1);
    sort(v2.begin(), v2.end());
    if (v1 != v2) {
      flag = false;
      break;
    }
  }

  cout << (flag ? "Nice" : "Fucking fucked") << endl;
  return 0;
}
