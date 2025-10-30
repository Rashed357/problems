//Given a tree (a connected graph with no cycles), you have to find the cost to go to the farthest node from each node. The edges of the tree are weighted and undirected.


#include<bits/stdc++.h>
using namespace std;

const int N = 3e4 + 9, inf = 1e9;
vector<pair<int, int>> g[N];
int n;
int farthest_node(int s, vector<long long> &d) {
  d.resize(n + 1);
  vector<bool> vis(n + 1, false);
  queue<int> q;
  q.push(s);
  d[s] = 0;
  vis[s] = true;
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    for (auto [v, w]: g[u]) {
      if (!vis[v]) {
        d[v] = d[u] + w;
        vis[v] = true;
        q.push(v);
      }
    }
  }
  int farthest = max_element(d.begin() + 1, d.end()) - d.begin();
  return farthest;
}
int32_t main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int t, cs = 0; cin >> t;
  while (t--) {
    cin >> n;
    for (int i = 1; i < n; i++) {
      int u, v, w; cin >> u >> v >> w;
      ++u; ++v; // 1 indexing
      g[u].push_back({v, w});
      g[v].push_back({u, w});
    }
    vector<long long> ds, de;
    int s = farthest_node(1, ds);
    int e = farthest_node(s, ds);
    farthest_node(e, de);

    cout << "Case " << ++cs << ":\n";
    for (int i = 1; i <= n; i++) {
      cout << max(ds[i], de[i]) << '\n';
    }

    for (int i = 1; i <= n; i++) {
      g[i].clear();
    }
  }
  return 0;
}
