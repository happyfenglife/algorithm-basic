#include <iostream>
#include <vector>
#include <unordered_map>
#include <functional>

using namespace std;

template<typename T>
class HeapGreater {
 public:
  HeapGreater()
      : heapSize{0}, comp{greater<T>()} {}

  bool empty() const { return heapSize == 0; }

  size_t size() const { return heapSize; }

  bool contains(const T &t) const { return indexMap.find(t) != indexMap.end(); }

  const T &peek() const { return heap[0]; }

  void push(const T &t) {
    heap.push_back(t);
    indexMap.insert({t, heapSize});
    heapInsert(heapSize++);
  }

  T pop() {
    T t = heap[0];
    swp(0, heapSize - 1);
    indexMap.erase(t);
    heap.pop_back();
    --heapSize;
    heapify(0);
    return t;
  }

  void remove(const T &t) {
    T replace = heap[heapSize - 1];
    int i = indexMap[t];
    indexMap.erase(t);
    heap.pop_back();
    --heapSize;

    if (t != replace) {
      heap[i] = replace;
      indexMap[replace] = i;
      resign(i);
    }
  }

  void resign(int i) {
    heapInsert(i);
    heapify(i);
  }

 private:
  void heapInsert(int i) {
    while (i > 0 && comp(heap[i], heap[(i - 1) / 2])) {
      swp(i, (i - 1) / 2);
      i = (i - 1) / 2;
    }
  }

  void heapify(int i) {
    int l = i * 2 + 1;
    while (l < heapSize) {
      int larger = (l + 1 < heapSize && comp(heap[l + 1], heap[l]) ? l + 1 : l);
      larger = (comp(heap[larger], heap[i]) ? larger : i);

      if (larger == i) break;
      swp(i, larger);
      i = larger;
      l = i * 2 + 1;
    }
  }

  void swp(int i, int j) {
    T o1 = heap[i];
    T o2 = heap[j];
    heap[i] = o2;
    heap[j] = o1;
    indexMap[o1] = j;
    indexMap[o2] = i;
  }

 private:
  vector<T> heap;
  unordered_map<T, int> indexMap;
  size_t heapSize;
  function<bool(const T &, const T &)> comp;
};

int main() {
  HeapGreater<int> heap;

  heap.push(5);
  heap.push(2);
  heap.push(8);
  heap.push(3);

  while (!heap.empty()) {
    cout << heap.pop() << " ";
  }

  return 0;
}
