#include<bits/stdc++.h>
using namespace std;

struct dsu {
    int par[100000];
    int sz[100000];

    void init(int n) {
        for (int i = 0; i <= n; i++) {
            sz[i] = 1;
            par[i] = i;
        }
    }

    int findpar(int node) {
        if (node == par[node]) return node;
        return par[node] = findpar(par[node]);
    }

    bool unite(int u, int v) {
        u = findpar(u);
        v = findpar(v);

        if (u == v) return false;
        if (sz[u] < sz[v]) swap(u, v);
        sz[u] += sz[v];
        par[v] = u;
        return true;
    }
};

int main() {
    int n, x, y, w, cost = 0;
    cin >> n;
    pair<int, pair<int, int>> edges[n + 2];

    for (int i = 0; i < n; i++) {
        cin >> x >> y >> w;
        edges[i] = {w, {x, y}};
    }

    sort(edges, edges + n);

    dsu dsu;
    dsu.init(100);

    for (int i = 0; i < n; i++) {
        x = edges[i].second.first;
        y = edges[i].second.second;
        w = edges[i].first;

        if (dsu.unite(x, y)) {
            cost += w;
//            cout << char('A' + (x-1)) <<" and "<< char('A' + (y-1)) <<" added to the tree.\n";
            cout << x << " and " << y << " added to the tree." << endl;
        }
    }

    cout << cost << endl;

    return 0;
}
