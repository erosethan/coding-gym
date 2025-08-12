#include <iostream>
#include <vector>
using namespace std;

const vector<pair<int, int>> kBlueprint[50] = {{{1, 1}},
                                               {{2, 1}},
                                               {{3, 2}},
                                               {{4, 3}},
                                               {{5, 4}},
                                               {{4, 2}},
                                               {{7, 6}},
                                               {{4, 3}, {4, 3}},
                                               {{4, 3}, {5, 4}},
                                               {{5, 3}},
                                               {{4, 3}, {7, 6}},
                                               {{5, 4}, {7, 6}},
                                               {{13, 12}},
                                               {{1, 1}, {13, 12}},
                                               {{6, 4}},
                                               {{1, 1}, {6, 4}},
                                               {{4, 3}, {13, 12}},
                                               {{5, 4}, {13, 12}},
                                               {{4, 3}, {6, 4}},
                                               {{6, 3}},
                                               {{1, 1}, {6, 3}},
                                               {{6, 4}, {7, 6}},
                                               {{5, 3}, {13, 12}},
                                               {{4, 3}, {6, 3}},
                                               {{5, 3}, {6, 4}},
                                               {{4, 2}, {6, 3}},
                                               {{6, 3}, {7, 6}},
                                               {{8, 6}},
                                               {{1, 1}, {8, 6}},
                                               {{2, 1}, {8, 6}},
                                               {{3, 2}, {8, 6}},
                                               {{4, 3}, {8, 6}},
                                               {{5, 4}, {8, 6}},
                                               {{4, 2}, {8, 6}},
                                               {{7, 4}},
                                               {{1, 1}, {7, 4}},
                                               {{2, 1}, {7, 4}},
                                               {{3, 2}, {7, 4}},
                                               {{4, 3}, {7, 4}},
                                               {{5, 4}, {7, 4}},
                                               {{4, 2}, {7, 4}},
                                               {{7, 6}, {7, 4}},
                                               {{6, 4}, {8, 6}},
                                               {{1, 1}, {6, 4}, {8, 6}},
                                               {{5, 3}, {7, 4}},
                                               {{5, 4}, {8, 6}, {13, 12}},
                                               {{5, 4}, {7, 4}, {7, 6}},
                                               {{6, 3}, {8, 6}},
                                               {{7, 4}, {7, 6}, {7, 6}},
                                               {{6, 4}, {7, 4}}};

int current_begin, group_size;
vector<long long> lists;

void GenerateCombinations(int n, int r, long long list) {
  if (!r) return lists.push_back(list);
  if (r < n) GenerateCombinations(n - 1, r, list);
  list |= (1LL << group_size) - 1 << current_begin + group_size * (n - 1);
  GenerateCombinations(n - 1, r - 1, list);
}

int main() {
  cin.tie(0);
  ios_base::sync_with_stdio(0);

  int n;
  cin >> n;

  for (auto [total, choose] : kBlueprint[n - 1]) {
    group_size = 12 / choose;
    GenerateCombinations(total, choose, 0);
    current_begin += group_size * total;
  }

  for (auto list : lists) {
    for (int i = 1; list; list >>= 1, ++i)
      if (list & 1) cout << i << ' ';
    cout << '\n';
  }
}
