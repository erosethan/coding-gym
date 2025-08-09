#include <iostream>
#include <queue>
#include <vector>
using namespace std;

struct Area {
  bool operator<(const Area& other) const {
    return elevation < other.elevation;
  }

  int up, left, elevation{0};
};

struct MinStack {
  void Push(const Area& area, int index) {
    while (!stack.empty() && area < stack.back().first) stack.pop_back();
    stack.push_back({area, index});
  }

  void Remove(int index) {
    if (!stack.empty() && index == stack.front().second) stack.pop_front();
  }

  const Area& MinArea() { return stack.front().first; }

  deque<pair<Area, int>> stack;
};

struct Field {
  Field(int n, int m) : prefix_sum(n + 1, vector<int>(m + 1)) {
    for (int i = 1; i <= n; ++i) {
      int row_sum = 0;
      for (int j = 1; j <= m; ++j) {
        cin >> prefix_sum[i][j];
        prefix_sum[i][j] = (row_sum += prefix_sum[i][j]) + prefix_sum[i - 1][j];
      }
    }
  }

  int Sum(int r, int c, int h, int w) {
    return prefix_sum[r + h][c + w] - prefix_sum[r + h][c] -
           prefix_sum[r][c + w] + prefix_sum[r][c];
  }

  pair<Area, Area> LocatePyramid(int ph, int pw, int ch, int cw) {
    int n = prefix_sum.size() - 1, m = prefix_sum[0].size() - 1;

    vector<MinStack> column_min(m);
    for (int j = 1; j < m - cw; ++j)
      for (int i = 1; i < ph - ch; ++i)
        column_min[j].Push({i, j, Sum(i, j, ch, cw)}, i);

    Area best_pyramid, best_chamber;
    for (int i = 0; i <= n - ph; ++i) {
      MinStack min_chamber;
      for (int j = 1; j < pw - cw; ++j)
        min_chamber.Push(column_min[j].MinArea(), j);

      for (int j = 0; j <= m - pw; ++j) {
        Area this_chamber = min_chamber.MinArea();
        Area this_pyramid{i, j, Sum(i, j, ph, pw) - this_chamber.elevation};

        if (best_pyramid < this_pyramid) {
          best_chamber = this_chamber;
          best_pyramid = this_pyramid;
        }

        min_chamber.Push(column_min[pw - cw + j].MinArea(), pw - cw + j);
        min_chamber.Remove(j + 1);
      }

      for (int j = 1; j < m - cw; ++j) {
        column_min[j].Push({ph - ch + i, j, Sum(ph - ch + i, j, ch, cw)},
                           ph - ch + i);
        column_min[j].Remove(i + 1);
      }
    }
    return {best_pyramid, best_chamber};
  }

  vector<vector<int>> prefix_sum;
};

int main() {
  cin.tie(0);
  ios_base::sync_with_stdio(0);

  int n, m, a, b, c, d;
  cin >> m >> n >> b >> a >> d >> c;

  Field field(n, m);
  auto [pyramid, chamber] = field.LocatePyramid(a, b, c, d);
  cout << pyramid.left + 1 << ' ' << pyramid.up + 1 << '\n'
       << chamber.left + 1 << ' ' << chamber.up + 1 << '\n';
}
