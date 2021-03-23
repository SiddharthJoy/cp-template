#include<bits/stdc++.h>
using namespace std;
#define faster_io ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define read(x) scanf("%d",&x)
#define llread(x) scanf("%lld",&x)
#define forr(i,x,n) for(ll i = x;i<n;i++)
#define fort(i,x,n) for(ll i = x;i>=n;i--)
#define ll long long
#define F first
#define S second
#define pb push_back

std::vector<ll> v[100005];
ll parent[100005];
ll par_tbl[100005][30];
ll dep[100005];

struct LCA
{
    void init(ll n)
    {
        forr(i, 1, n + 1) {
            v[i].clear();
            parent[i] = 0;
            dep[i] = 0;
        }

        forr(i, 0, 25) {
            forr(j, 1, n + 1) {
                par_tbl[j][i] = 0;
            }
        }
    }

    void dfs(ll s, ll par, ll dis)
    {
        dep[s] = dis;
        parent[s] = par;
        ll n = v[s].size();

        forr(i, 0, n) {
            ll nxt = v[s][i];
            if (nxt != par) dfs(nxt, s, dis + 1);
        }
    }

    void build_parent_tbl(ll n)
    {
        forr(i, 1, n + 1) par_tbl[i][0] = parent[i];

        for (ll k = 1; k <= 20; k++) {
            forr(i, 1, n + 1) {
                if (par_tbl[i][k - 1] == -1) par_tbl[i][k] = -1;
                else par_tbl[i][k] = par_tbl[par_tbl[i][k - 1]][k - 1];
            }
        }
    }

    ll find_kth_parent(ll node, ll k)
    {
        // if (!k) node = parent[node];    //for 0th parent
        forr(i, 0, 25) {
            if (k & (1 << i)) {
                node = par_tbl[node][i];
            }
        }

        return node;
    }

    ll find_LCA(ll root, ll u, ll v, ll n)
    {
        dfs(root, -1, 0);
        build_parent_tbl(n);

        if (dep[u] < dep[v]) swap(u, v);
        ll diff = dep[u] - dep[v];

        if (u != v) u = find_kth_parent(u, diff);

        if (u == v) return u;

        ll l = 0, r = dep[u], mid;
        ll parent1, parent2, node;

        while (l <= r) {
            mid = (l + r) / 2;
            parent1 = find_kth_parent(u, mid);
            parent2 = find_kth_parent(v, mid);
            if (parent1 == parent2) {
                node = parent1;
                r = mid - 1;
            }
            else l = mid + 1;
        }

        return node;
    }
};

int main()
{
    faster_io

#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    ll t = 1, n, xx, x = 0, y = 0, cc, m, k, c, q, yy;
    bool f, ff;

    // cin >> t;

    while (t--) {
        cin >> n;
        forr(i, 1, n) {
            cin >> x >> y;
            v[x].pb(y);
            v[y].pb(x);
        }

        LCA obj;

        cin >> q;

        while (q--) {
            cin >> x >> y;
            cout << obj.find_LCA(1, x, y, n) << endl;
        }

        obj.init(n);

    }

    return 0;
}
