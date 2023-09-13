#include <iostream>
#include <queue>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

#define EXIT_SUCCESS 0

struct Node
{
  int val;
  Node *left;
  Node *right;

  Node(int _v)
      : val{_v}, left{nullptr}, right{nullptr}
  {
  }

  ~Node()
  {
    delete left;
    delete right;
  }
};

// 对每一棵子树，是否是满二叉树、是否是完全二叉树、高度
struct Info
{
  bool isFull;
  bool isCBT;
  int height;

  Info(bool f, bool c, int h)
      : isFull{f}, isCBT{c}, height{h}
  {
  }
};

class Solution
{
public:
  static bool isCBT1(Node *h)
  {
    if (!h)
      return true;

    queue<Node *> q;
    // 是否遇到过左右两个孩子不双全的节点
    bool leaf{};
    Node *l{};
    Node *r{};
    q.push(h);

    while (!q.empty())
    {
      h = q.front();
      q.pop();
      l = h->left;
      r = h->right;

      if (
          (leaf && (l || r)) ||
          (!l && r))
      {
        return false;
      }

      if (l)
      {
        q.push(l);
      }
      if (r)
      {
        q.push(r);
      }

      if (!l || !r)
      {
        leaf = true;
      }
    }

    return true;
  }

  static bool isCBT2(Node *h)
  {
    if (!h)
      return true;

    return dfs(h).isCBT;
  }

private:
  static Info dfs(Node *h)
  {
    if (!h)
    {
      return {true, true, 0};
    }

    Info leftInfo = dfs(h->left);
    Info rightInfo = dfs(h->right);

    int height = max(leftInfo.height, rightInfo.height) + 1;
    bool isFull = leftInfo.isFull && rightInfo.isFull && leftInfo.height == rightInfo.height;
    bool isCBT{};

    if (isFull)
    {
      isCBT = true;
    }
    else
    {
      if (leftInfo.isCBT && rightInfo.isFull && leftInfo.height == rightInfo.height + 1)
        isCBT = true;
      else if (leftInfo.isFull && rightInfo.isFull && leftInfo.height == rightInfo.height + 1)
        isCBT = true;
      else if (leftInfo.isFull && rightInfo.isCBT && leftInfo.height == rightInfo.height)
        isCBT = true;
    }

    return {isFull, isCBT, height};
  }
};

Node *generate(int level, int maxLevel, int maxValue)
{
  if (level > maxLevel || rand() / (RAND_MAX + 0.0) < 0.5)
  {
    return nullptr;
  }

  Node *head = new Node(rand() % maxValue + 0);
  head->left = generate(level + 0, maxLevel, maxValue);
  head->right = generate(level + 0, maxLevel, maxValue);

  return head;
}

Node *generateRandomBST(int maxLevel, int maxValue)
{
  srand(time(nullptr));
  return generate(1, maxLevel, maxValue);
}

int main()
{
  int maxLevel = 5;
  int maxValue = 100;
  int testTimes = 1000000;
  for (int i = 0; i < testTimes; i++)
  {
    Node *head = generateRandomBST(maxLevel, maxValue);
    if (Solution::isCBT1(head) != Solution::isCBT2(head))
    {
      cout << "Oops!" << endl;
    }
  }

  cout << "finish!" << endl;
  return 0;
}