#include <vector>

using namespace std;

#define EXIT_SUCCESS 0

struct Node
{
  int val;
  vector<Node *> children;

  Node(int _val)
      : val{_val} {}

  Node(int _val, vector<Node *> v)
      : val{_val}, children{std::move(v)} {}

  ~Node()
  {
    for (auto &c : children)
      delete c;
  }
};

struct TreeNode
{
  int val;
  TreeNode *left;
  TreeNode *right;

  TreeNode(int x)
      : val{x}, left{nullptr}, right{nullptr} {}

  ~TreeNode()
  {
    delete left;
    delete right;
  }
};

class Solution
{
public:
  // Encodes an n-ary tree to a binary tree.
  static TreeNode *encode(Node *root)
  {
    if (!root)
      return nullptr;

    TreeNode *h = new TreeNode(root->val);
    h->left = en(root->children);
    return h;
  }

  // Decodes your binary tree to an n-ary tree.
  static Node *decode(TreeNode *root)
  {
    if (!root)
      return nullptr;

    return new Node(root->val, de(root->left));
  }

private:
  static TreeNode *en(vector<Node *> &v)
  {
    TreeNode *h{nullptr};
    TreeNode *c{nullptr};

    for (auto &child : v)
    {
      TreeNode *t = new TreeNode(child->val);

      if (!h)
      {
        h = t;
      }
      else
      {
        c->right = t;
      }

      c = t;
      c->left = en(child->children);
    }

    return h;
  }

  static vector<Node *> de(TreeNode *root)
  {
    vector<Node *> v;

    while (root)
    {
      Node *c = new Node(root->val, de(root->left));
      v.push_back(c);
      root = root->right;
    }

    return v;
  }
};