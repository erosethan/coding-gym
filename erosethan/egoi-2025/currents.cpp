#include <iostream>
#include <queue>
#include <vector>
using namespace std;

constexpr int kInfinite = 1e9;

using PriorityQueue = priority_queue<pair<int, int>, vector<pair<int, int>>,
                                     greater<pair<int, int>>>;

struct Graph {
  Graph(int n) : edges(n) {}

  void Connect(int u, int v) { edges[u].push_back(v); }

  vector<int> BFS() {
    vector<int> dist(edges.size(), kInfinite);

    dist[0] = 0;
    queue<int> q({0});

    while (!q.empty()) {
      int u = q.front();
      q.pop();

      for (int v : edges[u]) {
        if (dist[v] != kInfinite) continue;
        dist[v] = dist[u] + 1;
        q.push(v);
      }
    }
    return dist;
  }

  vector<int> Dijkstra(const vector<int>& reverse_dist) {
    vector<int> dist(edges.size(), kInfinite);
    PriorityQueue pq;

    dist.back() = 0;
    pq.push({0, edges.size() - 1});

    while (!pq.empty()) {
      auto [dist_u, u] = pq.top();
      pq.pop();

      if (dist[u] < dist_u) continue;

      for (int v : edges[u]) {
        int dist_v = max(reverse_dist[v], dist_u + 1);
        if (dist[v] < dist_v) continue;
        pq.push({dist_v, v});
        dist[v] = dist_v;
      }
    }
    return dist;
  }

  vector<vector<int>> edges;
};

int main() {
  cin.tie(0);
  ios_base::sync_with_stdio(0);

  int n, m;
  cin >> n >> m;

  Graph caves(n), reverse_caves(n);
  for (int i = 0; i < m; ++i) {
    int a, b;
    cin >> a >> b;
    caves.Connect(a, b);
    reverse_caves.Connect(b, a);
  }

  auto dist = reverse_caves.Dijkstra(caves.BFS());
  for (int d : dist)
    if (d) cout << d << ' ';
  cout << '\n';
}
