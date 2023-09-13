#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <climits>

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
  bool isBST;
  int up;
  int down;

  Info(bool i, int u, int d)
      : isBST{i}, up{u}, down{d} {}
};

class Solution
{
public:
  static bool isBST1(Node *h)
  {
    if (!h)
      return true;

    vector<Node *> v;
    in(h, v);
    for (int i = 1; i < v.size(); i++)
      if (v[i]->val <= v[i - 1]->val)
        return false;

    return true;
  }

  static bool isBST2(Node *h)
  {
    if (!h)
      return true;

    Info *info = dfs(h);
    bool ans{info->isBST};
    delete info;

    return ans;
  }

private:
  static void in(Node *h, vector<Node *> &v)
  {
    if (!h)
      return;

    in(h->left, v);
    v.push_back(h);
    in(h->right, v);
  }

  static Info *dfs(Node *h)
  {
    if (!h)
      return nullptr;

    Info *leftInfo = dfs(h->left);
    Info *rightInfo = dfs(h->right);

    int maxVal{h->val};
    int minVal{h->val};

    if (leftInfo)
    {
      maxVal = max(maxVal, leftInfo->up);
      minVal = min(minVal, leftInfo->down);
    }
    if (rightInfo)
    {
      maxVal = max(maxVal, rightInfo->up);
      minVal = min(minVal, rightInfo->down);
    }

    bool isBST{true};
    if (leftInfo && (!leftInfo->isBST || leftInfo->up >= h->val))
    {
      isBST = false;
    }
    if (rightInfo && (!rightInfo->isBST || rightInfo->down <= h->val))
    {
      isBST = false;
    }

    delete leftInfo;
    delete rightInfo;
    return new Info{isBST, maxVal, minVal};
  }
};

Node *generate(int level, int maxLevel, int maxValue)
{
  if (level > maxLevel || rand() / (RAND_MAX + 1.0) < 0.5)
  {
    return nullptr;
  }

  Node *head = new Node(rand() % maxValue + 1);
  head->left = generate(level + 1, maxLevel, maxValue);
  head->right = generate(level + 1, maxLevel, maxValue);

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
    if (Solution::isBST1(head) != Solution::isBST2(head))
    {
      cout << "Oops!" << endl;
    }
  }

  cout << "finish!" << endl;
  return 0;
}