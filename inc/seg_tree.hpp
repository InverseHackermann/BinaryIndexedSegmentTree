#include <vector>

template <class T, class TreeNav>
class SegTree {
  TreeNav nav;
  std::vector<int> tree;

public:
  SegTree(int n);
  void set(int idx, T v);
  T get_range(int l, int r);
};

template<class T, class TreeNav>
SegTree<T, TreeNav>::SegTree(int n) : nav(n), tree(nav.size()) {}

template<class T, class TreeNav>
void SegTree<T, TreeNav>::set(int idx, T val) {
  int node = nav.leaf(idx);
  for (tree[node] = val; !nav.is_root(node); node = nav.parent(node)) {
    tree[nav.parent(node)] = tree[node] + tree[nav.sibling(node)];
  }
}

template<class T, class TreeNav>
T SegTree<T, TreeNav>::get_range(int l, int r) {
  T res_l{}, res_r{};
  for (int node_l = nav.leaf(l), node_r = nav.leaf(r); node_l <= node_r;
      node_l = nav.parent(node_l), node_r = nav.parent(node_r)) {
    if (nav.is_right(node_l)) {
      res_l = res_l + tree[node_l];
      node_l = nav.next(node_l);
    }
    if (nav.is_left(node_r)) {
      res_r = tree[node_r] + res_r;
      node_r = nav.prev(node_r);
    }
  }
  return res_l + res_r;
}
