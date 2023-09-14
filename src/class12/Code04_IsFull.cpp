#include <iostream>
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

struct Info
{
  int height;
  int nodes;

  Info(int h, int n)
      : height{h}, nodes{n}
  {
  }

  ~Info() = default;
};

struct Data
{
  bool isFull;
  int height;

  Data()
      : isFull{true}, height{} {}

  Data(bool f, int h)
      : isFull{f}, height{h}
  {
  }
};

class Solution
{
public:
  // 第一种方法
  // 收集整棵树的高度h，和节点数n
  // 只有满二叉树满足 : 2 ^ h - 1 == n
  static bool isFull1(Node *h)
  {
    if (!h)
      return true;

    Info *info = dfs1(h);
    bool ans = (1 << info->height) - 1 == info->nodes;
    delete info;
    return ans;
  }

  // 第二种方法
  // 收集子树是否是满二叉树
  // 收集子树的高度
  // 左树满 && 右树满 && 左右树高度一样 -> 整棵树是满的
  static bool isFull2(Node *h)
  {
    if (!h)
      return true;

    Data *data = dfs2(h);
    bool ans = data->isFull;
    delete data;

    return ans;
  }

private:
  static Info *dfs1(Node *h)
  {
    if (!h)
      return new Info{0, 0};

    Info *leftInfo = dfs1(h->left);
    Info *rightInfo = dfs1(h->right);
    int height = max(leftInfo->height, rightInfo->height) + 1;
    int nodes = leftInfo->nodes + rightInfo->nodes + 1;

    delete leftInfo;
    delete rightInfo;
    return new Info{height, nodes};
  }

  static Data *dfs2(Node *h)
  {
    if (!h)
      return new Data;

    Data *leftData = dfs2(h->left);
    Data *rightData = dfs2(h->right);
    bool isFull = leftData->isFull && rightData->isFull && (leftData->height == rightData->height);
    int height = max(leftData->height, rightData->height) + 1;

    delete leftData;
    delete rightData;

    return new Data{isFull, height};
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
    if (Solution::isFull1(head) != Solution::isFull2(head))
    {
      cout << "Oops!" << endl;
    }
  }

  cout << "finish!" << endl;
  return 0;
}