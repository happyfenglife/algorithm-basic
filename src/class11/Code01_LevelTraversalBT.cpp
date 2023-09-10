#include <iostream>
#include <queue>

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
  // level traversal
  static void level(Node *h)
  {
    if (!h)
    {
      return;
    }

    queue<Node *> q;
    q.push(h);

    while (!q.empty())
    {
      Node *cur = q.front();
      cout << cur->val << " ";
      q.pop();

      if (cur->left) {
        q.push(cur->left);
      }

      if (cur->right) {
        q.push(cur->right);
      }
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

  Solution::level(h);
  delete h;
  return EXIT_SUCCESS;
}