#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

struct Employee
{
  int happy;
  vector<Employee *> nexts;

  Employee(int h)
      : happy{h} {}

  ~Employee()
  {
    for (auto &e : nexts)
      delete e;
  }
};

struct Info
{
  int no;
  int yes;

  Info(int n, int y)
      : no{n}, yes{y} {}
};

class Solution
{
public:
  // 当前来到的节点叫cur，
  // up表示cur的上级是否来，
  // 该函数含义：
  // 如果up为true，表示在cur上级已经确定来，的情况下，cur整棵树能够提供最大的快乐值是多少？
  // 如果up为false，表示在cur上级已经确定不来，的情况下，cur整棵树能够提供最大的快乐值是多少？
  static int maxHappy1(Employee *boss)
  {
    if (!boss)
      return 0;

    return dfs1(boss, false);
  }

  static int maxHappy2(Employee *e)
  {
    Info *info = dfs2(e);
    int ans{max(info->no, info->yes)};
    delete info;

    return ans;
  }

private:
  static int dfs1(Employee *cur, bool up)
  {
    int ans{};
    if (up) // 如果cur的上级来的话，cur没得选，只能不来
    {
      ans = accumulate(cur->nexts.begin(), cur->nexts.end(), 0, [](int init, auto &e)
                       { return init + dfs1(e, false); });
    }
    else // 如果cur的上级不来的话，cur可以选，可以来也可以不来
    {
      int p1{accumulate(cur->nexts.begin(), cur->nexts.end(), cur->happy, [](int init, auto &e)
                        { return init + dfs1(e, true); })};
      int p2{accumulate(cur->nexts.begin(), cur->nexts.end(), 0, [](int init, auto &e)
                        { return init + dfs1(e, false); })};

      ans = max(p1, p2);
    }

    return ans;
  }

  static Info *dfs2(Employee *e)
  {
    if (!e)
      return new Info{0, 0};

    int no{};
    int yes{e->happy};
    for (auto next : e->nexts)
    {
      Info *info = dfs2(next);
      no += max(info->no, info->yes);
      yes += info->no;
      delete info;
    }

    return new Info{no, yes};
  }
};

void generateNexts(Employee *e, int level, int maxLevel, int maxNexts, int maxHappy)
{
  if (level > maxLevel)
  {
    return;
  }
  int nextsSize = rand() % (maxNexts + 1);
  for (int i = 0; i < nextsSize; i++)
  {
    Employee *next = new Employee(rand() % (maxHappy + 1));
    e->nexts.push_back(next);
    generateNexts(next, level + 1, maxLevel, maxNexts, maxHappy);
  }
}

Employee *generateBoss(int maxLevel, int maxNexts, int maxHappy)
{
  if ((double)rand() / RAND_MAX < 0.02)
    return nullptr;

  Employee *boss = new Employee(rand() % (maxHappy + 1));
  generateNexts(boss, 1, maxLevel, maxNexts, maxHappy);
  return boss;
}

int main()
{
  int maxLevel = 4;
  int maxNexts = 7;
  int maxHappy = 100;
  int testTimes = 100000;

  srand(time(nullptr));

  for (int i = 0; i < testTimes; i++)
  {
    Employee *boss = generateBoss(maxLevel, maxNexts, maxHappy);
    if (Solution::maxHappy1(boss) != Solution::maxHappy2(boss))
      cout << "Oops!" << endl;

    delete boss;
  }

  cout << "finish!" << endl;

  return EXIT_SUCCESS;
}