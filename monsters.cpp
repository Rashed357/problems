#include <bits/stdc++.h>
using namespace std;
 
#define fastio ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL)
#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define all(x) x.begin(), x.end()
 
const int mx = 1007;
char grid[mx][mx];
int dist[mx][mx]; // Distance from each cell
pair<int, int> parent[mx][mx]; // Parent tracking for path reconstruction
 
int n, m; // Dimensions of the grid
 
int dx[] = {-1, 1, 0, 0}; // Directions for movement
int dy[] = {0, 0, -1, 1};
char drc[] = {'U', 'D', 'L', 'R'}; // Directions corresponding to dx and dy
 
queue<pair<int, int>> q; // Queue for BFS
pair<int, int> src, dest; // Start (A) and destination (exit) points
bool possible = false; // Flag to indicate if a path is possible
bool me = false; // Flag to indicate BFS state
 
void bfs() {
    while (!q.empty()) {
        auto p = q.front();
        q.pop();
 
        int x = p.first; // Current x-coordinate
        int y = p.second; // Current y-coordinate
 
        // Explore all four possible directions
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i]; // New x-coordinate
            int ny = y + dy[i]; // New y-coordinate
 
            // Check boundaries and ensure it's not a wall
            if (nx >= 1 && nx <= n && ny >= 1 && ny <= m && grid[nx][ny] != '#') {
                int nw_dist = dist[x][y] + 1; // New distance from source
 
                // If found a shorter path
                if (nw_dist < dist[nx][ny]) {
                    dist[nx][ny] = nw_dist; // Update distance
                    q.push({nx, ny}); // Add to queue for BFS
                    parent[nx][ny] = {x, y}; // Set parent for path reconstruction
                }
            }
        }
 
        // Check if we reached the boundary
        if (me) {
            if (x==1 or x==n or y==1 or y==m) {
                possible = true; // Path to exit found
                dest = {x, y}; // Set destination
                return; // Exit BFS
            }
        }
    }
}
 
void solve() {
    cin >> n >> m;
 
    // Initialize grid and distances
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> grid[i][j]; // Read the grid character
 
            dist[i][j] = INT_MAX; // Initialize distance to "infinity"
 
            // Start BFS for monsters
            if (grid[i][j] == 'M') {
                q.push({i, j}); // Push monster's position
                dist[i][j] = 0; // Distance from monster is 0
            }
 
            // Capture starting point of 'A'
            if (grid[i][j] == 'A') {
                src = {i, j}; // Set source position
            }
        }
    }
 
    bfs(); // BFS for monsters
 
    // Mark cells adjacent to monsters as unsafe for A
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (grid[i][j] == 'M') {
                for (int d = 0; d < 4; d++) {
                    int nx = i + dx[d];
                    int ny = j + dy[d];
                    // Mark adjacent cells as walls if they are not the boundaries
                    if (nx >= 1 && nx <= n && ny >= 1 && ny <= m && grid[nx][ny] == '.') {
                        grid[nx][ny] = '#'; // Block this cell for 'A'
                    }
                }
            }
        }
    }
 
    me = true; // Now perform BFS for 'A'
    q.push(src); // Push 'A' starting point to queue
 
    dist[src.first][src.second] = 0; // Distance to itself is 0
    parent[src.first][src.second] = {-1, -1}; // Initialize parent for 'A'
 
    bfs(); // BFS for 'A'
 
    // If no path is found
    if (!possible) {
        cout << "NO" << endl;
        return;
    }
 
    cout<<"YES"<<endl;
 
    string way; // To hold the directions of the path
    pair<int, int> cur = dest; // Start from the destination
 
   // pair<int,int> pp = parent[dest.first][dest.second];
 
   // cout<<pp.first<<' '<<pp.second<<endl;
 
    // Path reconstruction
    while (cur != src) {
        pair<int, int> prev = parent[cur.first][cur.second]; // Get the parent
 
        // Find the direction from the parent to current cell
        for (int i = 0; i < 4; i++) {
            int nx = prev.first + dx[i];
            int ny = prev.second + dy[i];
 
            // If the current cell matches the new coordinates
            if (cur.first == nx && cur.second == ny) {
                way += drc[i]; // Add the direction to the path
            }
        }
 
        cur = prev; // Move to the previous node
    }
 
    reverse(all(way)); // Reverse the path to get it from 'A' to destination
 
    cout << dist[dest.first][dest.second] << endl; // Print distance to destination
    cout << way << endl; // Print the path
}
 
int main() {
    fastio; // Optimize input/output
    solve(); // Execute the solution
}
