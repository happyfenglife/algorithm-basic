#include <iostream>
#include <vector>

using namespace std;

auto __FAST_IO__ = []() noexcept
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  return 0;
}();

class UnionFind
{
public:
  UnionFind(int m, int n)
      : row{m}, col{n}, cnts{0}
  {
    int len = row * col;
    parent = vector<int>(len);
    size = vector<int>(len);
    help = vector<int>(len);
  }

  int connect(int r, int c)
  {
    int i = index(r, c);
    if (!size[i])
    {
      parent[i] = i;
      size[i] = 1;
      ++cnts;

      dfs(r - 1, c, r, c);
      dfs(r + 1, c, r, c);
      dfs(r, c - 1, r, c);
      dfs(r, c + 1, r, c);
    }

    return cnts;
  }

private:
  void dfs(int r1, int c1, int r2, int c2)
  {
    if ((r1 < 0 || r1 == row) || (r2 < 0 || r2 == row) || (c1 < 0 || c1 == col) || (c2 < 0 || c2 == col))
      return;

    int i1 = index(r1, c1);
    int i2 = index(r2, c2);

    if (!size[i1] || !size[i2])
      return;

    int f1 = find(i1);
    int f2 = find(i2);

    if (f1 != f2)
    {
      if (size[f1] >= size[f2])
      {
        size[f1] += size[f2];
        parent[f2] = f1;
      }
      else
      {
        size[f2] += size[f1];
        parent[f1] = f2;
      }
      --cnts;
    }
  }

  int find(int i)
  {
    int hi{};

    while (i != parent[i])
    {
      help[hi++] = i;
      i = parent[i];
    }

    for (--hi; hi >= 0; --hi)
      parent[help[hi]] = i;

    return i;
  }

  int index(int r, int c)
  {
    return r * col + c;
  }

private:
  vector<int> parent;
  vector<int> size;
  vector<int> help;

  const int row;
  const int col;
  int cnts;
};

class Solution
{
public:
  vector<int> numIslands(int m, int n, vector<vector<int>> &positions)
  {
    UnionFind uf(m, n);
    vector<int> ans(positions.size());

    for (int i = 0; i < positions.size(); i++)
      ans[i] = uf.connect(positions[i][0], positions[i][1]);

    return ans;
  }
};