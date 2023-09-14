#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

using namespace std;

#define EXIT_SUCCESS 0

struct Node
{
  int val;
  Node *left;
  Node *right;

  Node() : val(0), left(nullptr), right(nullptr) {}
  Node(int x) : val(x), left(nullptr), right(nullptr) {}
  Node(int x, Node *left, Node *right) : val(x), left(left), right(right) {}
};

struct Info
{
  bool findA;
  bool findB;
  Node *ans;

  Info(bool fA, bool fB, Node *o)
      : findA{fA}, findB{fB}, ans{o} {}
};

class Solution
{
public:
  static Node *lowestAncestor1(Node *h, Node *o1, Node *o2)
  {
    if (!h)
      return nullptr;

    unordered_map<Node *, Node *> parentMap{{h, nullptr}};
    fillParentMap(h, parentMap);
    unordered_set<Node *> o1Set;
    Node *cur{o1};
    o1Set.insert(cur);
    while (parentMap[cur])
    {
      cur = parentMap[cur];
      o1Set.insert(cur);
    }

    cur = o2;
    while (!o1Set.count(cur))
    {
      cur = parentMap[cur];
    }

    return cur;
  }

  static Node *lowestAncestor2(Node *h, Node *o1, Node *o2)
  {
    Info *info = dfs(h, o1, o2);
    Node *ans{info->ans};
    delete info;

    return ans;
  }

private:
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

  static Info *dfs(Node *h, Node *o1, Node *o2)
  {
    if (!h)
      return new Info{false, false, nullptr};

    Info *leftInfo{dfs(h->left, o1, o2)};
    Info *rightInfo{dfs(h->right, o1, o2)};

    bool findA{(h == o1) || leftInfo->findA || rightInfo->findA};
    bool findB{(h == o2) || leftInfo->findB || rightInfo->findB};
    Node *ans{};

    if (leftInfo->ans)
      ans = leftInfo->ans;
    else if (rightInfo->ans)
      ans = rightInfo->ans;
    else if (findA && findB)
      ans = h;

    return new Info{findA, findB, ans};
  }
};

Node *generate(int level, int maxLevel, int maxValue)
{
  if (level > maxLevel || ((double)rand() / RAND_MAX) < 0.5)
  {
    return nullptr;
  }
  Node *head = new Node(rand() % (maxValue + 1));
  head->left = generate(level + 1, maxLevel, maxValue);
  head->right = generate(level + 1, maxLevel, maxValue);
  return head;
}

Node *generateRandomBST(int maxLevel, int maxValue)
{
  return generate(1, maxLevel, maxValue);
}

void fillPrelist(Node *head, vector<Node *> &arr)
{
  if (head == nullptr)
    return;

  arr.push_back(head);
  fillPrelist(head->left, arr);
  fillPrelist(head->right, arr);
}

Node *pickRandomOne(Node *head)
{
  if (head == nullptr)
  {
    return nullptr;
  }
  vector<Node *> arr;
  fillPrelist(head, arr);
  int randomIndex = rand() % arr.size();
  return arr[randomIndex];
}

int main()
{
  srand(time(nullptr));

  int maxLevel = 4;
  int maxValue = 100;
  int testTimes = 1000000;
  for (int i = 0; i < testTimes; i++)
  {
    Node *head = generateRandomBST(maxLevel, maxValue);
    Node *o1 = pickRandomOne(head);
    Node *o2 = pickRandomOne(head);
    if (Solution::lowestAncestor1(head, o1, o2) != Solution::lowestAncestor2(head, o1, o2))
    {
      cout << "Oops!" << endl;
      break;
    }
  }

  cout << "finish\n";

  return EXIT_SUCCESS;
}