#include<bits/stdc++.h>
using namespace std;

const int N = 3e4 + 9;
vector<pair<int, int>> g[N];
int d[N];
void dfs(int u, int p) {
  for (auto [v, w]: g[u]) {
    if (v != p) {
      d[v] = d[u] + w;
      dfs(v, u);
    }
  }
}
int32_t main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int t, cs = 0; cin >> t;
  while (t--) {
    int n; cin >> n;
    for (int i = 1; i < n; i++) {
      int u, v, w; cin >> u >> v >> w;
      ++u; ++v; // 1 indexing
      g[u].push_back({v, w});
      g[v].push_back({u, w});
    }
    d[1] = 0;
    dfs(1, 0);
    int mx_dis = 0, farthest_node = 1;
    for (int i = 1; i <= n; i++) {
      if (d[i] > mx_dis) {
        mx_dis = d[i];
        farthest_node = i;
      }
    }
    int s = farthest_node;
    d[s] = 0;
    dfs(s, 0);
    mx_dis = 0, farthest_node = s;
    for (int i = 1; i <= n; i++) {
      if (d[i] > mx_dis) {
        mx_dis = d[i];
        farthest_node = i;
      }
    }
    int e = farthest_node;
    // (s, e) is the diameter
    cout << "Case " << ++cs << ": " << d[e] << '\n';

    for (int i = 1; i <= n; i++) {
      g[i].clear();
      d[i] = 0;
    }
  }
  return 0;
}
