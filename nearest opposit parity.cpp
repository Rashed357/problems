#include<bits/stdc++.h>
using namespace std;

const int N = 2e5 + 9, inf = 1e9;
vector<int> g[N];
int ans[N], a[N], n;
void solve(vector<int> even, vector<int> odd) {
  queue<int> q;
  vector<int> d(n + 1, inf);
  for (auto st: even) {
    q.push(st);
    d[st] = 0;
  }
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    for (auto v: g[u]) {
      if (d[u] + 1 < d[v]) {
        d[v] = d[u] + 1;
        q.push(v);
      }
    }
  }
  for (auto u: odd) {
    ans[u] = d[u];
  }
}
int32_t main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cin >> n;
  vector<int> even, odd;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    if (a[i] % 2 == 1) {
      odd.push_back(i);
    }
    else {
      even.push_back(i);
    }
  }
  for (int i = 1; i <= n; i++) {
    int j = i - a[i];
    if (j >= 1) g[j].push_back(i); // reverse edge
    j = i + a[i];
    if (j <= n) g[j].push_back(i); // reverse edge
  }

  for (int i = 1; i <= n; i++) {
    ans[i] = inf;
  }
  solve(even, odd);
  solve(odd, even);
  for (int i = 1; i <= n; i++) {
    if (ans[i] == inf) ans[i] = -1;
    cout << ans[i] << ' ';
  }
  cout << '\n';
  return 0;
}
