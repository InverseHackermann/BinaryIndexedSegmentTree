struct BinaryNav {
  int n;

  BinaryNav(int n) : n(n) {}
  int size() {
    return 2 * n;
  }
  int left(int node) {
    int rmsb = node & -node;
    return (node ^ rmsb) | (rmsb >> 1);
  }
  int right(int node) {
    int rmsb = node & -node;
    return node | (rmsb >> 1);
  }
  int leaf(int idx) {
    return 2 * idx + 1;
  }
  bool is_root(int node) {
    return sibling(node) >= size();
  }
  int parent(int node) {
    int rmsb = node & -node;
    return (node ^ rmsb) | (rmsb << 1);
  }
  int sibling(int node) {
    int rmsb = node & -node;
    return node ^ (rmsb << 1);
  }
  bool is_left(int node) {
    return !is_right(node);
  }
  bool is_right(int node) {
    int rmsb = node & -node;
    return node & (rmsb << 1);
  }
  int next(int node) {
    int rmsb = node & -node;
    return node + (rmsb << 1);
  }
  int prev(int node) {
    int rmsb = node & -node;
    return node - (rmsb << 1);
  }
};
