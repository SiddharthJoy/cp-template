std::vector<ll> g[200005];
int used[100005];

int dfs(int v) {
    used[v] = 1;
    for (int to : g[v]) {
        if (used[to] == 1) {
            return 1;
        }
        if (!used[to] && dfs(to)) return 1;
    }
    used[v] = 2;
    return 0;
}

// returns 1 if the connected component has any cycle
// used in cf-1411C
