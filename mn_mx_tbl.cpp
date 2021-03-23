#include<bits/stdc++.h>
using namespace std;
#define faster_io ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define read(x) scanf("%d",&x)
#define llread(x) scanf("%lld",&x)
#define forr(i,x,n) for(int i = x;i<n;i++)
#define fort(i,x,n) for(int i = x;i>=n;i--)
#define ll long long
#define F first
#define S second
#define pb push_back
#define inf 10000000

vector<int> path;
vector<pair<int, int> > v[100005];
int parent[100005];
int par_tbl[100005][30];
int mn_tbl[100005][30];
int mx_tbl[100005][30];
int dep[100005];

struct LCA
{
    void init(int n)
    {
        forr(i, 1, n + 1) {
            v[i].clear();
            parent[i] = 0;
            dep[i] = 0;
        }

        forr(i, 0, 25) {
            forr(j, 1, n + 1) {
                par_tbl[j][i] = 0;
                mn_tbl[j][i] = inf;
                mx_tbl[j][i] = -1;
            }
        }
    }

    void dfs(int s, int par, int dis)
    {
        dep[s] = dis;
        parent[s] = par;
        int n = v[s].size();

        forr(i, 0, n) {
            int nxt = v[s][i].F;
            int w = v[s][i].S;
            if (nxt != par) {
                mn_tbl[nxt][0] = mx_tbl[nxt][0] = w;
                dfs(nxt, s, dis + 1);
            }
        }
    }

    void build_parent_tbl(int n)
    {
        forr(i, 1, n + 1) par_tbl[i][0] = parent[i];

        for (int k = 1; k <= 20; k++) {
            forr(i, 1, n + 1) {
                if (par_tbl[i][k - 1] == -1) {
                    par_tbl[i][k] = -1;
                    // mn_tbl[i][k] = inf;
                    // mx_tbl[i][k] = -1;
                }
                else {
                    par_tbl[i][k] = par_tbl[par_tbl[i][k - 1]][k - 1];
                    mx_tbl[i][k] = max(mx_tbl[par_tbl[i][k - 1]][k - 1], mx_tbl[i][k - 1]);
                    mn_tbl[i][k] = min(mn_tbl[par_tbl[i][k - 1]][k - 1], mn_tbl[i][k - 1]);
                }
            }
        }
    }

    int find_kth_parent(int node, int k)
    {
        // if (!k) node = parent[node];    //for 0th parent
        forr(i, 0, 25) {
            if (k & (1 << i)) {
                node = par_tbl[node][i];
            }
        }

        return node;
    }

    int mx_till_kth(int node, int k)
    {
        int mx = -1;
        forr(i, 0, 25) {
            if (k & (1 << i)) {
                mx = max(mx, mx_tbl[node][i]);
                node = par_tbl[node][i];
            }
        }

        return mx;
    }

    int mn_till_kth(int node, int k)
    {
        int mn = inf;
        forr(i, 0, 25) {
            if (k & (1 << i)) {
                mn = min(mn, mn_tbl[node][i]);
                node = par_tbl[node][i];
            }
        }

        return mn;
    }

    pair<int, int> find_LCA(int root, int u, int v, int n)
    {
        // dfs(root, -1, 0);
        // build_parent_tbl(n);

        if (dep[u] < dep[v]) swap(u, v);
        int uu = u;
        int diff = dep[u] - dep[v];

        if (u != v) u = find_kth_parent(u, diff);

        if (u == v) return {mn_till_kth(uu, diff), mx_till_kth(uu, diff)};

        int l = 0, r = dep[u], mid;
        int parent1, parent2, node_th;

        while (l <= r) {
            mid = (l + r) / 2;
            parent1 = find_kth_parent(u, mid);
            parent2 = find_kth_parent(v, mid);
            if (parent1 == parent2) {
                node_th = mid;
                r = mid - 1;
            }
            else l = mid + 1;
        }

        int x = mx_till_kth(uu, diff + node_th);
        int xx = mx_till_kth(v, node_th);

        int y = mn_till_kth(uu, diff + node_th);
        int yy = mn_till_kth(v, node_th);

        pair<int, int> ans;

        ans.F = min(y, yy);
        ans.S = max(x, xx);

        return ans;
    }
};

int main()
{
    // faster_io

#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    int t = 1, n, xx, x = 0, y = 0, cc, m, k, c, q, w, tc = 0;
    bool f, ff;

    // cin >> t;
    // llread(t);

    while (t--) {
        // cin >> n;
        llread(n);
        forr(i, 1, n) {
            // cin >> x >> y >> w;
            llread(x);
            llread(y);
            llread(w);
            v[x].pb({y, w});
            v[y].pb({x, w});
        }

        LCA obj;

        obj.dfs(1, -1, 0);
        obj.build_parent_tbl(n);

        cin >> q;
        // cout << "Case " << ++tc << ":\n";
        // printf("Case %d:\n", ++tc);

        while (q--) {
            cin >> x >> y;
            pair<int, int> ans = obj.find_LCA(1, x, y, n);
            // cout << ans.F << " " << ans.S << endl;
            printf("%d %d\n", ans.F, ans.S);
        }

        obj.init(n);

    }

    return 0;
}
