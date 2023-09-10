#include <iostream>

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

    cout << h->val << endl;
    pre(h->left);
    pre(h->right);
  }

  // Inorder traversal print all nodes
  static void in(Node *h)
  {
    if (!h)
    {
      return;
    }

    in(h->left);
    cout << h->val << endl;
    in(h->right);
  }

  // Postorder traversal print all nodes
  static void pos(Node *h)
  {
    if (!h)
    {
      return;
    }

    pos(h->left);
    pos(h->right);
    cout << h->val << endl;
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