#include <iostream>
#include <stack>

using namespace std;

#define EXIT_SUCCESS 0

struct Node
{
  int val;
  Node *left;
  Node *right;

  Node(int _val)
      : val{_val} {}

  ~Node()
  {
    delete left;
    delete right;
  }
};

class Solution
{
public:
  // Preorder traversal print all nodes
  static void pre(Node *h)
  {
    if (!h)
    {
      return;
    }

    stack<Node *> s;
    s.push(h);

    while (!s.empty())
    {
      Node *cur = s.top();
      s.pop();

      cout << cur->val << " ";

      if (cur->right)
      {
        s.push(cur->right);
      }

      if (cur->left)
      {
        s.push(cur->left);
      }
    }

    cout << endl;
  }

  // Inorder traversal print all nodes
  static void in(Node *h)
  {
    if (!h)
    {
      return;
    }

    stack<Node *> s;

    while (!s.empty() || h)
    {
      if (h)
      {
        s.push(h);
        h = h->left;
      }
      else
      {
        h = s.top();
        s.pop();
        cout << h->val << " ";

        h = h->right;
      }
    }

    cout << endl;
  }

  // Postorder traversal print all nodes
  static void pos(Node *h)
  {
    if (!h)
    {
      return;
    }

    stack<Node *> s1;
    stack<Node *> s2;
    s1.push(h);

    while (!s1.empty())
    {
      h = s1.top();
      s1.pop();

      s2.push(h);
      if (h->left)
      {
        s1.push(h->left);
      }
      if (h->right)
      {
        s1.push(h->right);
      }
    }

    while (!s2.empty())
    {
      cout << s2.top()->val << " ";
      s2.pop();
    }

    cout << endl;
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

  Solution::pre(h);
  cout << "============================\n";
  Solution::in(h);
  cout << "============================\n";
  Solution::pos(h);
  cout << "============================\n";

  delete h;
  return EXIT_SUCCESS;
}