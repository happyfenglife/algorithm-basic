#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <ctime>
#include <cstdlib>

using namespace std;

class Solution {
 public:
  static int maxCover1(const vector<vector<int>> &v) {
    int s{INT_MAX};
    int e{INT_MIN};

    for (const auto &o : v) {
      s = min(s, o[0]);
      e = max(e, o[1]);
    }

    int k{};
    for (double i = s + 0.5; i < e; i += 1.0) {
      int j{};

      for (const auto &l : v)
        if (l[0] < i && l[1] > i)
          ++j;

      k = max(k, j);
    }

    return k;
  }

  static int maxCover2(vector<vector<int>> &v) {
    sort(v.begin(), v.end(), [](const auto &o1, const auto &o2) {
      return o1[0] < o2[0];
    });

    priority_queue<int, vector<int>, greater<>> pq;
    int i{};

    for (const auto &o : v) {
      while (!pq.empty() && pq.top() <= o[0])
        pq.pop();

      pq.push(o[1]);
      i = max(i, (int) pq.size());
    }

    return i;
  }
};

vector<vector<int>> generateLines(int N, int L, int R) {
  int size = rand() % N + 1;
  vector<vector<int>> ans(size, vector<int>(2));
  for (int i = 0; i < size; i++) {
    int a = L + rand() % (R - L + 1);
    int b = L + rand() % (R - L + 1);
    if (a == b) {
      b = a + 1;
    }
    ans[i][0] = min(a, b);
    ans[i][1] = max(a, b);
  }
  return ans;
}

int main() {
  srand(time(nullptr)); // 设置随机数种子

  int N = 100;
  int L = 0;
  int R = 200;
  int testTimes = 200000;
  bool flag{true};

  for (int i = 0; i < testTimes; i++) {
    auto lines = generateLines(N, L, R);
    int ans1 = Solution::maxCover1(lines);
    int ans2 = Solution::maxCover2(lines);

    if (ans1 != ans2) {
      flag = false;
      break;
    }
  }

  cout << (flag ? "Nice" : "Fucking fucked") << endl;
  return 0;
}
