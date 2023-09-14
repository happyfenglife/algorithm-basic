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
  bool isBalanced;
  int height;

  Info(bool i, int h)
      : isBalanced{i}, height{h}
  {
  }

  ~Info() = default;
};

class Solution
{
public:
  static bool isBalanced1(Node *h)
  {
    bool ans{true};
    dfs1(h, ans);
    return ans;
  }

  static bool isBalanced2(Node *h)
  {
    Info *info = dfs2(h);
    bool ans = info->isBalanced;
    delete info;
    return ans;
  }

private:
  static int dfs1(Node *h, bool &ans)
  {
    if (!ans || !h)
      return -1;

    int leftHeight = dfs1(h->left, ans);
    int rightHeight = dfs1(h->right, ans);

    if (abs(leftHeight - rightHeight) > 1)
      ans = false;

    return max(leftHeight, rightHeight) + 1;
  }

  static Info *dfs2(Node *h)
  {
    if (!h)
      return new Info{true, 0};

    Info *leftInfo = dfs2(h->left);
    Info *rightInfo = dfs2(h->right);

    int height = max(leftInfo->height, rightInfo->height) + 1;
    bool isBalanced{true};
    if (!leftInfo->isBalanced || !rightInfo->isBalanced || abs(leftInfo->height - rightInfo->height) > 1)
      isBalanced = false;

    delete leftInfo;
    delete rightInfo;
    return new Info{isBalanced, height};
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
    if (Solution::isBalanced1(head) != Solution::isBalanced2(head))
    {
      cout << "Oops!" << endl;
    }
  }

  cout << "finish!" << endl;
  return 0;
}