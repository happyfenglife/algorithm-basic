#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

class Solution {
 public:
  static void sortedArrDistanceLessK(vector<int> &v, int k) {
    if (k == 0) return;

    priority_queue<int, vector<int>, greater<>> pq;
    int i{};

    // 0...k - 1
    for (; i < k; ++i)
      pq.push(v[i]);

    int j{};
    for (; i < v.size(); ++i, ++j) {
      pq.push(v[i]);
      v[j] = pq.top();
      pq.pop();
    }

    while (!pq.empty()) {
      v[j++] = pq.top();
      pq.pop();
    }
  }
};

int main() {
  vector<int> v{1, 2, 3, 4, 5, 6, 9, 7, 8};
  int k{2};

  Solution::sortedArrDistanceLessK(v, k);
  for_each(v.begin(), v.end(), [](auto i) {
    cout << i << endl;
  });
  return 0;
}
