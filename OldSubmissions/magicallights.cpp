#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<long long, long long>;
const ll INF = numeric_limits<ll>::max();
const int inf = numeric_limits<int>::max();
const char nl = '\n', sp = ' ';

void dfs(int node, vector<vector<int>> &adj, vector<bool> &vis, vector<int> &dfsorder) {
    if (!vis[node]) {
        vis[node] = true;
        for (int child : adj[node]) {
            if (!vis[child]) {
                dfs(child, adj, vis, dfsorder);
            }
        }
        dfsorder.push_back(node);
    }
}

int getdfsranges(int n, vector<vector<int>> &adj, vector<pii> &ranges, map<int, int> &dfsid) {
    int start = dfsid[n];
    int end = start;
    for (int child : adj[n]) {
        int temp = getdfsranges(child, adj, ranges, dfsid);
        end = max(temp, end);
    }
    ranges[n] = {start, end};
    return end;
}

class FenwickTree {
private:
    vector<__int128> tree;
    int sz;
public:
    FenwickTree(int n, vector<int> &colors, map<int, int> &dfsid) {
        sz = 2 * n + 1;
        tree.resize(sz, 0);
        for (int i = 0; i < n; i++) {
            int node = dfsid[i];
            __int128 bitmask = 1;
            bitmask = bitmask << colors[i];
            tree[node] ^= bitmask;
        }
        for (int i = 1; i <= sz; i++) {
            int j = i + (i & -i);
            if (j <= sz) {
                tree[j] ^= tree[i];
            }
        }
    }

    int query(int i, int j) {
        __int128 mask1 = 0;
        __int128 mask2 = 0;
        int node = i;
        while (node > 0) {
            mask1 ^= tree[node];
            node -= node & -node;
        }
        node = j;
        while (node > 0) {
            mask2 ^= tree[node];
            node -= node & -node;
        }
        __int128 answer = mask1 ^ mask2;
        unsigned int aa = answer, bb = answer >> 32, cc = answer >> 64, dd = answer >> 96;
        // cout <<  __builtin_popcount(aa) << sp << __builtin_popcount(bb) << sp << __builtin_popcount(cc) << sp << __builtin_popcount(dd) << nl;
        return __builtin_popcount(aa) + __builtin_popcount(bb) + __builtin_popcount(cc) + __builtin_popcount(dd);
    }

    void update(int i, int col, int newcol) {
        int node = i;
        __int128 old_mask = 1, new_mask = 1;
        old_mask = old_mask << col;
        new_mask = new_mask << newcol;
        while (node < sz) {
            tree[node] ^= old_mask;
            tree[node] ^= new_mask;
            node += (node & (-node));
        }
    }
};

int main() {
    int N, Q;
    cin >> N >> Q;
    vector<int> color(N);
    for (int i = 0; i < N; i++) {
        cin >> color[i];
    }
    vector<vector<int>> adj(N);
    for (int i = 1; i < N; i++) {
        int num;
        cin >> num;
        adj[num - 1].push_back(i);
    }
    vector<bool> vis(N, false);
    vector<int> dfsorder;
    dfs(0, adj, vis, dfsorder);
    reverse(dfsorder.begin(), dfsorder.end());
    map<int, int> dfsid;
    for (int i = 0; i < N; i++) {
        dfsid[dfsorder[i]] = i + 1;
    }
    vector<pii> ranges(N);
    getdfsranges(0, adj, ranges, dfsid);
    FenwickTree FT(N, color, dfsid);
    for (int a = 0; a < Q; a++) {
        int K, X;
        cin >> K;
        if (K == 0) {
            cin >> X;
            X--;
            auto [S, E] = ranges[X];
            cout << FT.query(E, S - 1) << nl;
        } else {
            cin >> X;
            int oldcol = color[X - 1];
            int newcol = K;
            if (newcol >= 1 && newcol <= 100) {
                FT.update(dfsid[X - 1],oldcol, newcol);
                color[X - 1] = newcol;
            }
        }
    }
}
