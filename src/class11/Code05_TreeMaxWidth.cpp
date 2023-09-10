#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>

using namespace std;

#define EXIT_SUCCESS 0

struct Node
{
  int val;
  Node *left;
  Node *right;

  Node(int x)
      : val{x}, left{nullptr}, right{nullptr} {}

  ~Node()
  {
    delete left;
    delete right;
  }
};

class Solution
{
public:
  static int maxWidthUseMap(Node *h)
  {
    if (!h)
      return 0;

    queue<Node *> q;
    q.push(h);

    unordered_map<Node *, int> levelMap;
    levelMap.insert({h, 1});
    int curLevel{1};
    int curLevelWidth{};
    int ans{};

    while (!q.empty())
    {
      Node *c = q.front();
      q.pop();
      int cLevel = levelMap[c];

      if (c->left)
      {
        levelMap.insert({c->left, cLevel + 1});
        q.push(c->left);
      }
      if (c->right)
      {
        levelMap.insert({c->right, cLevel + 1});
        q.push(c->right);
      }

      if (cLevel == curLevel)
        ++curLevelWidth;
      else
      {
        ans = max(ans, curLevelWidth);
        ++curLevel;
        curLevelWidth = 1;
      }
    }

    ans = max(ans, curLevelWidth);
    return ans;
  }

  static int maxWidthNoMap(Node *h)
  {
    if (!h)
      return 0;

    queue<Node *> q;
    q.push(h);

    Node *curEnd{h};        /* 当前层的最右节点 */
    Node *nextEnd{nullptr}; /* 下一层的最右节点 */
    int ans{};
    int curLevelWidth{};

    while (!q.empty())
    {
      Node *c = q.front();
      q.pop();

      if (c->left)
      {
        q.push(c->left);
        nextEnd = c->left;
      }
      if (c->right)
      {
        q.push(c->right);
        nextEnd = c->right;
      }

      ++curLevelWidth;

      if (c == curEnd)
      {
        ans = max(ans, curLevelWidth);
        curLevelWidth = 0;
        curEnd = nextEnd;
      }
    }

    return ans;
  }
};

Node *generate(int level, int maxLevel, int maxValue)
{
  if (level > maxLevel || (rand() % 2 == 0))
  {
    return nullptr;
  }

  Node *head = new Node(rand() % (maxValue + 1));
  head->left = generate(level + 1, maxLevel, maxValue);
  head->right = generate(level + 1, maxLevel, maxValue);

  return head;
}

Node *generateBST(int level, int value)
{
  return generate(1, level, value);
}

int main()
{
  srand(time(nullptr));

  int maxLevel = 10;
  int maxValue = 100;
  int testTimes = 1000000;
  for (int i = 0; i < testTimes; i++)
  {
    Node *head = generateBST(maxLevel, maxValue);
    if (Solution::maxWidthUseMap(head) != Solution::maxWidthNoMap(head))
    {
      cout << "Oops!\n";
    }
  }

  cout << "finish\n";
  return EXIT_SUCCESS;
}