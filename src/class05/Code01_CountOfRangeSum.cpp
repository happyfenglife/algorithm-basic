#include <vector>

using namespace std;

#define ll long long

class Solution {
 public:
  static int countRangeSum(vector<int> &v, int lower, int upper) {
    vector<ll> sum(v.size());
    sum[0] = v[0];
    for (int i = 1; i < sum.size(); ++i)
      sum[i] = v[i] + sum[i - 1];

    return process(sum, 0, sum.size() - 1, lower, upper);
  }

 private:
  static ll process(vector<ll> &v, ll L, ll R, ll lower, ll upper) {
    if (L == R) {
      return (v[L] >= lower && v[L] <= upper ? 1 : 0);
    }

    ll M = L + ((R - L) >> 1);
    return process(v, L, M, lower, upper) + process(v, M + 1, R, lower, upper)
        + merge(v, L, M, R, lower, upper);
  }

  static ll merge(vector<ll> &v, ll L, ll M, ll R, ll lower, ll upper) {
    ll a{};
    ll wL{L};
    ll wR{L};

    for (ll i = M + 1; i <= R; ++i) {
      // [lower, upper] => [l, u]
      ll l = v[i] - upper;
      ll u = v[i] - lower;

      // [wL, wR)
      while (wL <= M && v[wL] < l)
        wL++;
      while (wR <= M && v[wR] <= u)
        wR++;

      a += wR - wL;
    }

    vector<ll> aux(R - L + 1);
    ll i{};
    ll p1{L};
    ll p2{M + 1};
    while (p1 <= M && p2 <= R)
      aux[i++] = (v[p1] <= v[p2] ? v[p1++] : v[p2++]);

    while (p1 <= M)
      aux[i++] = v[p1++];

    while (p2 <= R)
      aux[i++] = v[p2++];

    copy(aux.begin(), aux.end(), v.begin() + L);
    return a;
  }
};
