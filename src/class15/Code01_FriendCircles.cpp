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
  UnionFind(int N)
      : parent(N), size(N, 1), help(N), cnt{N}
  {
    for (int i = 0; i < N; i++)
      parent[i] = i;
  }

  void connect(int i, int j)
  {
    int fi = find(i);
    int fj = find(j);

    if (fi != fj)
    {
      if (size[fi] >= size[fj])
      {
        size[fi] += size[fj];
        parent[fj] = fi;
      }
      else
      {
        size[fj] += size[fi];
        parent[fi] = fj;
      }

      --cnt;
    }
  }

  int sets()
  {
    return cnt;
  }

private:
  // 从i开始一直往上，往上到不能再往上，代表节点，返回
  // 这个过程要做路径压缩
  int find(int i)
  {
    int hi{};

    while (i != parent[i])
    {
      help[hi++] = i;
      i = parent[i];
    }

    for (hi--; hi >= 0; hi--)
      parent[help[hi]] = i;

    return i;
  }

private:
  vector<int> parent; // parent[i] = k ： i的父亲是k
  vector<int> size;   // size[i] = k ： 如果i是代表节点，size[i]才有意义，否则无意义
  vector<int> help;   // 辅助结构
  int cnt;            // 一共有多少个集合
};

class Solution
{
public:
  int findCircleNum(vector<vector<int>> &isConnected)
  {
    int N = isConnected.size();

    UnionFind unionFind(N);

    for (int i = 0; i < N; i++)
      for (int j = i + 1; j < N; j++)
        if (isConnected[i][j])
          unionFind.connect(i, j);

    return unionFind.sets();
  }
};