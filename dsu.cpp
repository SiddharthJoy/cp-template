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

// struct DSU {
//     vector<ll> e;
//     void init(ll N) { e = vector<ll> (N, -1); }
//     // get representive component, uses path compression
//     ll get(ll x) { return e[x] < 0 ? x : e[x] = get(e[x]); }
//     bool sameSet(ll a, ll b) { return get(a) == get(b); }
//     ll size(ll x) { return -e[get(x)]; }
//     bool unite(ll x, ll y) { // union by size
//         x = get(x), y = get(y); if (x == y) return 0;
//         if (e[x] > e[y]) swap(x, y);
//         e[x] += e[y]; e[y] = x; return 1;
//     }
// };


struct DSU {
    ll root[200005], sz[200005];
    void init(ll n) {
        forr(i, 1, n + 1) root[i] = i, sz[i] = 1;
    }
    ll get(ll x) {
        if (root[x] == x) return x;
        else return get(root[x]);
    }

    bool sameSet(ll x, ll y) { return get(x) == get(y); }

    ll comp_size(ll x) { return sz[get(x)]; }
    void unite(ll x, ll y) {
        x = get(x);
        y = get(y);
        if (x == y) return;
        if (sz[x] >= sz[y]) swap(x, y);
        sz[y] += sz[x];
        root[x] = y;
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

    cin >> t;

    DSU dsu;

    while (t--) {

        cin >> q;
        dsu.init(10);
        while (q--) {
            ll type;
            cin >> type;
            if (!type) {
                cin >> x >> y;
                // cout << dsu.get(x) << " " << dsu.get(y) << endl;
                dsu.unite(x, y);
                // cout << dsu.get(x) << " " << dsu.get(y) << endl;
                // cout << "ok" << endl;
            }
            else {
                cin >> x;
                // cout << dsu.get(x) << endl;
                cout << dsu.comp_size(x) << endl;
            }
        }
    }

    return 0;
}
