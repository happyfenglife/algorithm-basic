#include <iostream>
#include <vector>

using namespace std;

#define EXIT_SUCCESS 0

class Solution
{
public:
  static void printAllFolds(int N)
  {
    dfs(1, N, true);
    cout << "\n";
  }

private:
  // 当前你来了一个节点，脑海中想象的！
  // 这个节点在第i层，一共有N层，N固定不变的
  // 这个节点如果是凹的话，down = T
  // 这个节点如果是凸的话，down = F
  // 函数的功能：中序打印以你想象的节点为头的整棵树！
  static void dfs(int i, int N, bool down)
  {
    if (i > N)
      return;

    dfs(i + 1, N, true);
    cout << (down ? "凹 " : "凸 ");
    dfs(i + 1, N, false);
  }
};

int main()
{
  int N{4};
  Solution::printAllFolds(N);

  return EXIT_SUCCESS;
}