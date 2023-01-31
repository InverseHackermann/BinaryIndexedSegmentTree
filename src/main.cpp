#include <algorithm>
#include <cassert>
#include <chrono>
#include <iostream>
#include <random>

#include <seg_tree.hpp>

#ifdef USE_NORMAL_NAV
#include <normal_nav.hpp>
#endif

#ifdef USE_BINARY_NAV
#include <binary_nav.hpp>
#endif

int main(int argc, char* argv[]) {
  if (argc != 3) {
    std::cerr << "Usage: " << argv[0] << " range_length operations" << std::endl;
    return 1;
  }

  int n = std::atoi(argv[1]);
  int nops = std::atoi(argv[2]);

#ifdef USE_NORMAL_NAV
  SegTree<int, NormalNav> t1(n);
#endif
#ifdef USE_BINARY_NAV
  SegTree<int, BinaryNav> t2(n);
#endif
  std::default_random_engine rng{std::random_device()()};
  std::uniform_int_distribution<int> rand_idx(0, n - 1);
  std::uniform_int_distribution<int> rand_val(0, 1000);
  std::vector<std::tuple<int, int, int, int>> ops(nops);
  std::generate(ops.begin(), ops.end(), [&rng, &rand_idx, &rand_val]()
      -> std::tuple<int, int, int, int> {
        int set_idx = rand_idx(rng);
        int set_val = rand_val(rng);
        int get_idx_l = rand_idx(rng);
        int get_idx_r = rand_idx(rng);
        if (get_idx_l > get_idx_r) {
          std::swap(get_idx_l, get_idx_r);
        }
        return {set_idx, set_val, get_idx_l, get_idx_r};
      });
  auto start_time = std::chrono::steady_clock::now();
  int do_not_optimize = 0;
  for (const auto& [set_idx, set_val, get_idx_l, get_idx_r] : ops) {
#ifdef USE_NORMAL_NAV
    t1.set(set_idx, set_val);
    auto t1get = t1.get_range(get_idx_l, get_idx_r);
    do_not_optimize += t1get;
#endif
#ifdef USE_BINARY_NAV
    t2.set(set_idx, set_val);
    auto t2get = t2.get_range(get_idx_l, get_idx_r);
    do_not_optimize += t2get;
#endif
#if defined(USE_NORMAL_NAV) && defined(USE_BINARY_NAV)
    assert(t1get == t2get);
#endif
  }
  auto end_time = std::chrono::steady_clock::now();
  std::cout << ops.size() << " operations took " << std::chrono::duration<long double>(end_time - start_time).count() << " seconds." << std::endl;
}
