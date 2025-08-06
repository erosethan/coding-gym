#include <iostream>
#include <vector>
using namespace std;

int main() {
  int t, n;
  cin >> t >> n;

  vector<int> A(n);
  vector<int> count(t);
  int appear_more_than_once = 0;

  auto UpdateCount = [&](int Ai, int delta) {
    if (count[Ai] > 1) --appear_more_than_once;
    count[Ai] += delta;
    if (count[Ai] > 1) ++appear_more_than_once;
  };

  for (int& Ai : A) {
    cin >> Ai;
    UpdateCount(Ai, 1);
  }

  int r = 0, best_l = 0, best_r = n;
  for (int l = 0; l < n; ++l) {
    while (r < n && appear_more_than_once) {
      UpdateCount(A[r++], -1);
    }

    if (appear_more_than_once) break;
    if (best_r - best_l > r - l) best_l = l, best_r = r;
    UpdateCount(A[l], 1);
  }
  cout << best_l << ' ' << best_r - 1 << '\n';
}
