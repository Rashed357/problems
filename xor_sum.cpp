
https://codeforces.com/problemset/problem/242/E

#include<bits/stdc++.h>
using namespace std;


const int N = 1e5 + 9, B = 20;

struct node {
  int on[B], off[B];
};

int a[N];
node t[4 * N];
int lazy[4 * N];

void push(int n, int b, int e) {
  if (lazy[n] == 0) {
    return;
  }

  for (int k = 0; k < B; k++) {
    if ((lazy[n] >> k) & 1) {
      swap(t[n].on[k], t[n].off[k]);
    }
  }

  // push to the childs
  if (b != e) {
    int mid = (b + e) / 2, l = 2 * n, r = 2 * n + 1;
    lazy[l] ^= lazy[n];
    lazy[r] ^= lazy[n];
  }

  lazy[n] = 0;
}

node merge(node l, node r) {
  node ans;
  for (int k = 0; k < B; k++) {
    ans.on[k] = l.on[k] + r.on[k];
    ans.off[k] = l.off[k] + r.off[k];
  }
  return ans;
}

void build(int n, int b, int e) {
  lazy[n] = 0;
  if (b == e) {
    for (int k = 0; k < B; k++) {
      if ((a[b] >> k) & 1) {
        t[n].on[k] = 1;
        t[n].off[k] = 0;
      }
      else {
        t[n].on[k] = 0;
        t[n].off[k] = 1;
      }
    }
    return;
  }
  int mid = (b + e) / 2, l = 2 * n, r = 2 * n + 1;
  build(l, b, mid);
  build(r, mid + 1, e);
  t[n] = merge(t[l], t[r]);
}

void upd(int n, int b, int e, int i, int j, int v) {
  push(n, b, e);
  if (e < i or j < b) return;
  if (b >= i and e <= j) {
    lazy[n] = v;
    push(n, b, e);
    return;
  }
  int mid = (b + e) / 2, l = 2 * n, r = 2 * n + 1;
  upd(l, b, mid, i, j, v);
  upd(r, mid + 1, e, i, j, v);
  t[n] = merge(t[l], t[r]);
}

node query(int n, int b, int e, int i, int j) {
  push(n, b, e);
  if (e < i or j < b) {
    node zero;
    memset(zero.on, 0, sizeof zero.on);
    memset(zero.off, 0, sizeof zero.off);
    return zero;
  }
  if (b >= i and e <= j) {
    return t[n];
  }
  int mid = (b + e) / 2, l = 2 * n, r = 2 * n + 1;
  return merge(query(l, b, mid, i, j), query(r, mid + 1, e, i, j));
}

int32_t main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int n; cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  build(1, 1, n);
  int q; cin >> q;
  while (q--) {
    int ty; cin >> ty;
    if (ty == 2) {
      int l, r, v; cin >> l >> r >> v;
      upd(1, 1, n, l, r, v);
    }
    else {
      int l, r; cin >> l >> r;
      node ans = query(1, 1, n, l, r);
      long long sum = 0;
      for (int k = 0; k < B; k++) {
        sum += 1LL * ans.on[k] * (1 << k);
      }
      cout << sum << '\n';
    }
  }
  return 0;
}
