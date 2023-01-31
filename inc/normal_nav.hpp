struct NormalNav {
  int n;

  NormalNav(int n) : n(n) {}
  int size() {
    return 2 * n;
  }
  int left(int node) {
    return node << 1;
  }
  int right(int node) {
    return (node << 1) | 1;
  }
  int leaf(int idx) {
    return idx + n;
  }
  bool is_root(int node) {
    return node <= 1;
  }
  int parent(int node) {
    return node >> 1;
  }
  int sibling(int node) {
    return node ^ 1;
  }
  bool is_left(int node) {
    return !is_right(node);
  }
  bool is_right(int node) {
    return node & 1;
  }
  int next(int node) {
    return ++node;
  }
  int prev(int node) {
    return --node;
  }
};
