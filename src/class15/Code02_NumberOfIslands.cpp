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
  UnionFind(vector<vector<char>> &v)
      : col(v[0].size()), cnts{0}
  {
    int row = v.size();
    int len = row * col;
    parent = vector<int>(len);
    size = vector<int>(len);
    help = vector<int>(len);

    for (int r = 0; r < row; r++)
    {
      for (int c = 0; c < col; c++)
      {
        if (v[r][c] == '1')
        {
          int i = index(r, c);
          parent[i] = i;
          size[i] = 1;
          ++cnts;
        }
      }
    }
  }

  void connect(int r1, int c1, int r2, int c2)
  {
    int i1 = index(r1, c1);
    int i2 = index(r2, c2);

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

  int sets()
  {
    return cnts;
  }

private:
  // 原始下标 -> 下标
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
  int col;
  int cnts;
};

class Solution
{
public:
  int numIslands(vector<vector<char>> &grid)
  {
    int row = grid.size();
    int col = grid[0].size();

    UnionFind uf(grid);

    for (int j = 1; j < col; j++)
      if (grid[0][j - 1] == '1' && grid[0][j] == '1')
        uf.connect(0, j - 1, 0, j);

    for (int i = 1; i < row; i++)
      if (grid[i - 1][0] == '1' && grid[i][0] == '1')
        uf.connect(i - 1, 0, i, 0);

    for (int i = 1; i < row; i++)
    {
      for (int j = 1; j < col; j++)
      {
        if (grid[i][j] == '1')
        {
          if (grid[i][j - 1] == '1')
            uf.connect(i, j - 1, i, j);
          if (grid[i - 1][j] == '1')
            uf.connect(i - 1, j, i, j);
        }
      }
    }

    return uf.sets();
  }
};