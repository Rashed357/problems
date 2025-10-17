//https://codeforces.com/problemset/problem/616/C

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    if (!(cin >> n >> m)) return 0;
    vector<string> grid(n);
    for (int i = 0; i < n; ++i) cin >> grid[i];

    vector<vector<int>> compId(n, vector<int>(m, 0));
    vector<int> compSize; // compSize[compId-1] gives size
    compSize.reserve(n * m / 2);

    const int dx[4] = {1, -1, 0, 0};
    const int dy[4] = {0, 0, 1, -1};

    int curId = 0;
    // BFS to find connected components of '.'
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (grid[i][j] == '.' && compId[i][j] == 0) {
                ++curId;
                int size = 0;
                queue<pair<int,int>> q;
                q.emplace(i, j);
                compId[i][j] = curId;
                while (!q.empty()) {
                    auto [x, y] = q.front(); q.pop();
                    ++size;
                    for (int d = 0; d < 4; ++d) {
                        int nx = x + dx[d], ny = y + dy[d];
                        if (nx >= 0 && nx < n && ny >= 0 && ny < m) {
                            if (grid[nx][ny] == '.' && compId[nx][ny] == 0) {
                                compId[nx][ny] = curId;
                                q.emplace(nx, ny);
                            }
                        }
                    }
                }
                compSize.push_back(size); // index curId-1
            }
        }
    }

    // Prepare result lines
    vector<string> out(n, string(m, ' '));
    // For marking used component ids around a '*' without set overhead, use a timestamp array:
    vector<int> seen(compSize.size() + 1, 0);
    int timestamp = 1;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (grid[i][j] == '.') {
                out[i][j] = '.';
            } else {
                int sum = 1; // if we turn this '*' into '.', count this cell
                ++timestamp;
                for (int d = 0; d < 4; ++d) {
                    int nx = i + dx[d], ny = j + dy[d];
                    if (nx >= 0 && nx < n && ny >= 0 && ny < m) {
                        int id = compId[nx][ny];
                        if (id > 0 && seen[id] != timestamp) {
                            seen[id] = timestamp;
                            sum += compSize[id - 1];
                        }
                    }
                }
                out[i][j] = char('0' + (sum % 10));
            }
        }
    }

    // Print result
    for (int i = 0; i < n; ++i) {
        cout << out[i] << '\n';
    }
    return 0;
}
