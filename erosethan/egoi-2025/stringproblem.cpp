#include <iostream>
#include <vector>
using namespace std;

struct Graph {
  Graph(int n) : attached(n), visited(n) {}

  void Attach(int u, int v, int string_index) {
    attached[u] = {v, string_index};
    attached[v] = {u, string_index};
  }

  void DFS(int u, int expected_slope) {
    if (visited[u]) return;

    auto& [v, string_index] = attached[u];
    visited[u] = visited[v] = true;

    int expected_pin = (expected_slope - u + visited.size()) % visited.size();
    if (expected_pin == v) return;

    cout << string_index << ' ' << v << ' ' << expected_pin << '\n';
    DFS(attached[expected_pin].first, expected_slope);
  }

  vector<pair<int, int>> attached;
  vector<bool> visited;
};

int main() {
  cin.tie(0);
  ios_base::sync_with_stdio(0);

  int n;
  cin >> n;

  Graph pins(2 * n);
  vector<int> parallel_strings(n);

  for (int i = 0; i < n; ++i) {
    int a, b;
    cin >> a >> b;
    pins.Attach(a, b, i);

    int slope = (a + b) % (2 *n);
    if (slope & 1) ++parallel_strings[slope / 2];
  }

  int max_parallel = parallel_strings[0], expected_slope = 1;
  for (int i = 1; i < n; ++i) {
    if (parallel_strings[i] > max_parallel) {
      max_parallel = parallel_strings[i];
      expected_slope = 2 * i + 1;
    }
  }

  cout << n - max_parallel << '\n';
  for (int i = 0; i < 2 * n; ++i) pins.DFS(i, expected_slope);
}
