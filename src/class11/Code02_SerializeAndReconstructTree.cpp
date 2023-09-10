#include <iostream>
#include <queue>
#include <stack>

using namespace std;

#define EXIT_SUCCESS 0

struct Node
{
  int val;
  Node *left;
  Node *right;

  Node(int _val)
      : val{_val}, left{nullptr}, right{nullptr} {}

  ~Node()
  {
    delete left;
    delete right;
  }
};

/**
 * 二叉树可以通过先序、后序或者按层遍历的方式序列化和反序列化，
 * 以下代码全部实现了。
 * 但是，二叉树无法通过中序遍历的方式实现序列化和反序列化
 * 因为不同的两棵树，可能得到同样的中序序列，即便补了空位置也可能一样。
 * 比如如下两棵树
 *         __2
 *        /
 *       1
 *       和
 *       1__
 *          \
 *           2
 * 补足空位置的中序遍历结果都是{ null, 1, null, 2, null}
 *
 * */
class Solution
{
public:
  static queue<string> preSerial(Node *h)
  {
    queue<string> q;
    pres(h, q);
    return q;
  }

  static Node *buildByPreQueue(queue<string> &q)
  {
    if (q.empty())
    {
      return nullptr;
    }

    return preb(q);
  }

  static queue<string> posSerial(Node *h)
  {
    queue<string> q;
    poss(h, q);
    return q;
  }

  static Node *buildByPosQueue(queue<string> &q)
  {
    if (q.empty())
    {
      return nullptr;
    }

    stack<string> s;
    while (!q.empty())
    {
      s.push(q.front());
      q.pop();
    }

    return posb(s);
  }

  static queue<string> levelSerial(Node *h)
  {
    queue<string> q;

    if (!h)
    {
      q.push("null");
    }
    else
    {
      q.push(to_string(h->val));
      queue<Node *> tmp;
      tmp.push(h);

      while (!tmp.empty())
      {
        h = tmp.front();
        tmp.pop();

        if (h->left)
        {
          q.push(to_string(h->left->val));
          tmp.push(h->left);
        }
        else
        {
          q.push("null");
        }

        if (h->right)
        {
          q.push(to_string(h->right->val));
          tmp.push(h->right);
        }
        else
        {
          q.push("null");
        }
      }
    }

    return q;
  }

  static Node *buildByLevelQueue(queue<string> &q)
  {
    if (q.empty())
    {
      return nullptr;
    }

    Node *h = generateNode(q.front());
    q.pop();

    queue<Node *> tmp;
    if (h)
    {
      tmp.push(h);
    }

    Node *c{nullptr};
    while (!tmp.empty())
    {
      c = tmp.front();
      tmp.pop();

      c->left = generateNode(q.front());
      q.pop();
      c->right = generateNode(q.front());
      q.pop();

      if (c->left)
      {
        tmp.push(c->left);
      }
      if (c->right)
      {
        tmp.push(c->right);
      }
    }

    return h;
  }

  // Preorder traversal print all nodes
  static void pre(Node *h)
  {
    if (!h)
    {
      return;
    }

    cout << h->val << endl;
    pre(h->left);
    pre(h->right);
  }

private:
  static void pres(Node *h, queue<string> &q)
  {
    if (!h)
    {
      q.push("null");
    }
    else
    {
      q.push(to_string(h->val));
      pres(h->left, q);
      pres(h->right, q);
    }
  }

  static Node *preb(queue<string> &q)
  {
    string s = q.front();
    q.pop();

    if (s == "null")
    {
      return nullptr;
    }

    Node *h = new Node(stoi(s));
    h->left = preb(q);
    h->right = preb(q);

    return h;
  }

  static void poss(Node *h, queue<string> &q)
  {
    if (!h)
    {
      q.push("null");
    }
    else
    {
      poss(h->left, q);
      poss(h->right, q);
      q.push(to_string(h->val));
    }
  }

  static Node *posb(stack<string> &s)
  {
    string val = s.top();
    s.pop();

    if (val == "null")
    {
      return nullptr;
    }

    Node *h = new Node(stoi(val));
    h->right = posb(s);
    h->left = posb(s);

    return h;
  }

  static Node *generateNode(const string &s)
  {
    return (s == "null" ? nullptr : new Node(stoi(s)));
  }
};

int main()
{
  Node *h = new Node(1);
  h->left = new Node(2);
  h->right = new Node(3);
  h->left->left = new Node(4);
  h->left->right = new Node(5);
  h->right->left = new Node(6);
  h->right->right = new Node(7);

  // auto back = Solution::preSerial(h);
  // Node *c = Solution::buildByPreQueue(back);
  // auto back = Solution::posSerial(h);
  // Node *c = Solution::buildByPosQueue(back);
  auto back = Solution::levelSerial(h);
  Node *c = Solution::buildByLevelQueue(back);

  Solution::pre(c);
  delete h;
  delete c;

  return EXIT_SUCCESS;
}