#include <iostream>
#include <random>

using namespace std;

struct Node {
  int val;
  Node *next;

  Node(int v)
      : val{v}, next{nullptr} {}
};

struct DNode {
  int val;
  DNode *prev;
  DNode *next;

  DNode(int v)
      : val{v}, prev{nullptr}, next{nullptr} {}
};

class Solution {
 public:
  //  head
  //   a    ->   b    ->  c  ->  null
  //   c    ->   b    ->  a  ->  null
  static Node *reverseLinkedList(Node *head) {
    Node *pre{};
    Node *next{};

    while (head) {
      next = head->next;
      head->next = pre;
      pre = head;
      head = next;
    }

    return pre;
  }

  static DNode *reverseDLinkedList(DNode *head) {
    DNode *pre{};
    DNode *next{};

    while (head) {
      next = head->next;
      head->next = pre;
      head->prev = next;
      pre = head;
      head = next;
    }

    return pre;
  }
};

int main() {
  Node *head = new Node(1);
  head->next = new Node(2);
  head->next->next = new Node(3);

  Node *newNode = Solution::reverseLinkedList(head);
  cout << newNode->val << " " << newNode->next->val << " " << newNode->next->next->val << endl;
  return 0;
}
