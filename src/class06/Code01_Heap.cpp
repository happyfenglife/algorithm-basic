#include <iostream>
#include <vector>

using namespace std;

class MaxHeap {
 public:
  MaxHeap(int l)
      : v(l), lim{l}, size{0} {
  }

  bool empty() {
    return size == 0;
  }

  bool full() {
    return size == lim;
  }

  void push(int val) {
    if (full())
      throw runtime_error("heap is full");

    v[size] = val;
    heapInsert(v, size++);
  }

  int pop() {
    if (empty())
      throw runtime_error("heap is empty");

    int ans = v[0];
    swap(v[0], v[--size]);
    heapify(v, 0);
    return ans;
  }

 private:
  // 新加进来的数，现在停在了index位置，请依次往上移动，
  // 移动到0位置，或者干不掉自己的父亲了，停！
  void heapInsert(vector<int> &v, int i) {
    while (v[i] > v[(i - 1) / 2]) {
      swap(v[i], v[(i - 1) / 2]);
      i = (i - 1) / 2;
    }
  }

  // 从index位置，往下看，不断的下沉
  // 停：较大的孩子都不再比index位置的数大；已经没孩子了
  void heapify(vector<int> &v, int i) {
    int l = i * 2 + 1;
    while (l < size) { // 如果有左孩子，有没有右孩子，可能有可能没有！
      // 把较大孩子的下标，给largest
      int j = (l + 1 < size && v[l + 1] > v[l]) ? l + 1 : l;
      j = (v[j] > v[i] ? j : i);

      if (j == i)
        break;
      swap(v[j], v[i]);
      i = j;
      l = i * 2 + 1;
    }
  }

 private:
  vector<int> v;
  const int lim;
  int size;
};

int main() {
  MaxHeap heap(500);

  heap.push(5);
  heap.push(0);
  heap.push(6);
  heap.push(7);
  heap.push(1);
  heap.push(4);

  while (!heap.empty())
    cout << heap.pop() << endl;

  return 0;
}
