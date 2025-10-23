//https://lightoj.com/problem/strongest-community
#include<bits/stdc++.h>
using namespace std;

const int N = 1e5 + 9;
int a[N];
struct node {
  int first_element, first_element_occ;
  int last_element, last_element_occ;
  int strongest_community_size;
};
node t[N * 4];

node merge(node l, node r) {
  if (l.first_element == -1) {
    return r;
  }
  if (r.first_element == -1) {
    return l;
  }
  node ans;
  ans.first_element = l.first_element;
  ans.first_element_occ = l.first_element_occ;
  if (l.first_element == r.first_element) {
    ans.first_element_occ += r.first_element_occ;
  }

  ans.last_element = r.last_element;
  ans.last_element_occ = r.last_element_occ;
  if (r.last_element == l.last_element) {
    ans.last_element_occ += l.last_element_occ;
  }

  ans.strongest_community_size = max(l.strongest_community_size, r.strongest_community_size);
  if (l.last_element == r.first_element) {
    ans.strongest_community_size = max(ans.strongest_community_size, l.last_element_occ + r.first_element_occ);
  }
  return ans;
}

void build(int n, int b, int e) {
  if (b == e) {
    t[n].first_element = t[n].last_element = a[b];
    t[n].first_element_occ = t[n].last_element_occ = 1;
    t[n].strongest_community_size = 1;
    return;
  }
  int mid = (b + e) / 2, l = 2 * n, r = 2 * n + 1;
  build(l, b, mid);
  build(r, mid + 1, e);
  t[n] = merge(t[l], t[r]);
}

node query(int n, int b, int e, int i, int j) {
  if (e < i or j < b) return {-1, -1, -1, -1, -1};
  if (b >= i and e <= j) {
    return t[n];
  }
  int mid = (b + e) / 2, l = 2 * n, r = 2 * n + 1;
  return merge(query(l, b, mid, i, j), query(r, mid + 1, e, i, j));
}

int32_t main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int t, cs = 0; cin >> t;
  while (t--) {
    int n, c, q; cin >> n >> c >> q;
    for (int i = 1; i <= n; i++) {
      cin >> a[i];
    }
    build(1, 1, n);
    cout << "Case " << ++cs << ":\n";
    while (q--) {
      int l, r; cin >> l >> r;
      node ans = query(1, 1, n, l, r);
      cout << ans.strongest_community_size << '\n';
    }
  }
  return 0;
}
