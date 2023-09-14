#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>

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
  int maxDistance;
  int height;

  Info(int m, int h)
      : maxDistance{m}, height{h}
  {
  }
};

class Solution
{
public:
  static int maxDistance1(Node *h)
  {
    if (!h)
      return 0;

    vector<Node *> v = getPrelist(h);
    unordered_map<Node *, Node *> parentMap = getParentMap(h);

    int ans{};
    for (int i = 0; i < v.size(); i++)
      for (int j = i; j < v.size(); ++j)
        ans = max(ans, distance(parentMap, v[i], v[j]));

    return ans;
  }

  static int maxDistance2(Node *h)
  {
    Info *info = dfs(h);
    int ans{info->maxDistance};
    delete info;

    return ans;
  }

private:
  static vector<Node *> getPrelist(Node *h)
  {
    vector<Node *> v;
    fillPrelist(h, v);
    return v;
  }

  static void fillPrelist(Node *h, vector<Node *> &v)
  {
    if (!h)
      return;

    v.push_back(h);
    fillPrelist(h->left, v);
    fillPrelist(h->right, v);
  }

  static unordered_map<Node *, Node *> getParentMap(Node *h)
  {
    unordered_map<Node *, Node *> parentMap;
    parentMap.insert({h, nullptr});
    fillParentMap(h, parentMap);

    return parentMap;
  }

  static void fillParentMap(Node *h, unordered_map<Node *, Node *> &parentMap)
  {
    if (h->left)
    {
      parentMap.insert({h->left, h});
      fillParentMap(h->left, parentMap);
    }
    if (h->right)
    {
      parentMap.insert({h->right, h});
      fillParentMap(h->right, parentMap);
    }
  }

  static int distance(unordered_map<Node *, Node *> &parentMap, Node *o1, Node *o2)
  {
    unordered_set<Node *> o1Set;
    Node *cur = o1;
    o1Set.insert(cur);

    while (parentMap[cur])
    {
      cur = parentMap[cur];
      o1Set.insert(cur);
    }

    cur = o2;
    while (!o1Set.count(cur))
      cur = parentMap[cur];

    Node *lowestAncestor{cur};
    cur = o1;
    int distance1{1};

    while (cur != lowestAncestor)
    {
      cur = parentMap[cur];
      ++distance1;
    }

    cur = o2;
    int distance2{1};

    while (cur != lowestAncestor)
    {
      cur = parentMap[cur];
      ++distance2;
    }

    return distance1 + distance2 - 1;
  }

  static Info *dfs(Node *h)
  {
    if (!h)
      return new Info{0, 0};

    Info *leftInfo = dfs(h->left);
    Info *rightInfo = dfs(h->right);

    int height = max(leftInfo->height, rightInfo->height) + 1;
    int maxDistance = max({leftInfo->maxDistance,
                           rightInfo->maxDistance,
                           leftInfo->height + rightInfo->height + 1});

    delete leftInfo;
    delete rightInfo;

    return new Info{maxDistance, height};
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
    if (Solution::maxDistance2(head) != Solution::maxDistance1(head))
    {
      cout << "Oops!" << endl;
    }

    delete head;
  }

  cout << "finish!" << endl;
  return 0;
}