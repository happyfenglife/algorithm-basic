#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>

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
  int maxBSTSubtreeSize;
  int allSize;
  int maxV;
  int minV;

  Info(int m, int a, int ma, int mi)
      : maxBSTSubtreeSize{m}, allSize{a}, maxV{ma}, minV{mi}
  {
  }

  ~Info() = default;
};

class Solution
{
public:
  static int bruteForce(Node *h)
  {
    if (!h)
      return 0;

    int size = getBSTSize(h);
    if (size)
      return size;

    return max(bruteForce(h->left), bruteForce(h->right));
  }

  static int largestBSTSubtree(Node *h)
  {
    if (!h)
      return 0;

    Info *info = dfs(h);
    int ans{info->maxBSTSubtreeSize};
    delete info;

    return ans;
  }

private:
  static int getBSTSize(Node *h)
  {
    if (!h)
      return 0;

    vector<int> v;
    in(h, v);
    for (int i = 1; i < v.size(); ++i)
      if (v[i] <= v[i - 1])
        return 0;

    return v.size();
  }

  static void in(Node *h, vector<int> &v)
  {
    if (!h)
      return;

    in(h->left, v);
    v.push_back(h->val);
    in(h->right, v);
  }

  static Info *dfs(Node *h)
  {
    if (!h)
      return nullptr;

    Info *leftInfo = dfs(h->left);
    Info *rightInfo = dfs(h->right);
    int maxV{h->val};
    int minV{h->val};
    int allSize{1};

    if (leftInfo)
    {
      maxV = max(leftInfo->maxV, maxV);
      minV = min(leftInfo->minV, minV);
      allSize += leftInfo->allSize;
    }

    if (rightInfo)
    {
      maxV = max(rightInfo->maxV, maxV);
      minV = min(rightInfo->minV, minV);
      allSize += rightInfo->allSize;
    }

    int p1 = (leftInfo ? leftInfo->maxBSTSubtreeSize : -1);
    int p2 = (rightInfo ? rightInfo->maxBSTSubtreeSize : -1);
    int p3{-1};

    bool leftBST = (!leftInfo ? true : (leftInfo->allSize == leftInfo->maxBSTSubtreeSize));
    bool rightBST = (!rightInfo ? true : (rightInfo->allSize == rightInfo->maxBSTSubtreeSize));

    if (leftBST && rightBST)
    {
      bool leftMaxLessX = (!leftInfo ? true : (leftInfo->maxV < h->val));
      bool rightMinMoreX = (!rightInfo ? true : (rightInfo->minV > h->val));

      if (leftMaxLessX && rightMinMoreX)
      {
        int leftSize = (!leftInfo ? 0 : leftInfo->allSize);
        int rightSize = (!rightInfo ? 0 : rightInfo->allSize);
        p3 = leftSize + rightSize + 1;
      }
    }

    delete leftInfo;
    delete rightInfo;

    return new Info{max({p1, p2, p3}), allSize, maxV, minV};
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
    if (Solution::bruteForce(head) != Solution::largestBSTSubtree(head))
    {
      cout << "Oops!" << endl;
    }

    delete head;
  }

  cout << "finish!" << endl;
  return 0;
}