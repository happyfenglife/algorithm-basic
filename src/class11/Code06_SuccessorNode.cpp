#include <iostream>
#include <vector>

using namespace std;

#define EXIT_SUCCESS 0

struct Node
{
  int value;
  Node *left;
  Node *right;
  Node *parent;

  Node(int x)
      : value{x}, left{nullptr}, right{nullptr}, parent{nullptr} {}

  ~Node()
  {
    delete left;
    delete right;
  }
};

class Solution
{
public:
  static Node *getSuccessor(Node *h)
  {
    if (!h)
      return nullptr;

    if (h->right)
    {
      return mostLeft(h->right);
    }
    else
    {
      Node *c = h->parent;

      while (c && c->right == h)
      {
        h = c;
        c = h->parent;
      }

      return c;
    }
  }

private:
  static Node *mostLeft(Node *h)
  {
    if (!h)
      return nullptr;

    while (h->left)
    {
      h = h->left;
    }

    return h;
  }
};

int main()
{
  Node *head = new Node(6);
  head->parent = nullptr;
  head->left = new Node(3);
  head->left->parent = head;
  head->left->left = new Node(1);
  head->left->left->parent = head->left;
  head->left->left->right = new Node(2);
  head->left->left->right->parent = head->left->left;
  head->left->right = new Node(4);
  head->left->right->parent = head->left;
  head->left->right->right = new Node(5);
  head->left->right->right->parent = head->left->right;
  head->right = new Node(9);
  head->right->parent = head;
  head->right->left = new Node(8);
  head->right->left->parent = head->right;
  head->right->left->left = new Node(7);
  head->right->left->left->parent = head->right->left;
  head->right->right = new Node(10);
  head->right->right->parent = head->right;

  Node *test = head->left->left;
  cout << test->value <<  " next: " << Solution::getSuccessor(test)->value << endl;
  test = head->left->left->right;
  cout << test->value <<  " next: " << Solution::getSuccessor(test)->value << endl;
  test = head->left;
  cout << test->value <<  " next: " << Solution::getSuccessor(test)->value << endl;
  test = head->left->right;
  cout << test->value <<  " next: " << Solution::getSuccessor(test)->value << endl;
  test = head->left->right->right;
  cout << test->value <<  " next: " << Solution::getSuccessor(test)->value << endl;
  test = head;
  cout << test->value <<  " next: " << Solution::getSuccessor(test)->value << endl;
  test = head->right->left->left;
  cout << test->value <<  " next: " << Solution::getSuccessor(test)->value << endl;
  test = head->right->left;
  cout << test->value <<  " next: " << Solution::getSuccessor(test)->value << endl;
  test = head->right;
  cout << test->value <<  " next: " << Solution::getSuccessor(test)->value << endl;
  test = head->right->right; // 10's next is null
  // cout << test->value <<  " next: " << Solution::getSuccessor(test)->value << endl;

  delete head;
  return EXIT_SUCCESS;
}