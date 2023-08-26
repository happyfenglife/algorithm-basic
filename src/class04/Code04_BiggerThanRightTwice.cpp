#include <vector>
#include <algorithm>

using namespace std;

class Solution {
 public:
  static int reversePairs(vector<int> &v) {
    if (v.size() == 1)
      return 0;

    return process(v, 0, v.size() - 1);
  }

 private:
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

      while (wR <= R && (long long) v[j] > (long long) v[wR] * 2)
        ++wR;

      k += wR - M - 1;
    }

    while (p1 <= M && p2 <= R) {
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
