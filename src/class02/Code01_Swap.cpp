#include <iostream>

using namespace std;

class Solution {
 public:
  static void swap(int &a, int &b) {
    a = a ^ b;
    b = a ^ b;
    a = a ^ b;
  }
};

int main() {
  int a{5}, b{7};
  Solution::swap(a, b);
  cout << a << endl;
  cout << b << endl;
  return 0;
}
