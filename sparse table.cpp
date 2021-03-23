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

ll table[100005][30];
ll a[100005];
ll LOG[100004 + 1];

struct sparse_table {
    ll merge_it(ll pos, ll poss, ll k) { return min(table[pos][k], table[poss][k]); }

    void build(ll n)
    {

        LOG[1] = 0;
        for (int i = 2; i <= n; i++) LOG[i] = LOG[i / 2] + 1;

        forr(i, 0, n) table[i][0] = a[i];

        forr(k, 1, 20) {
            for (int i = 0; i + (1 << k) - 1 <= n; i++) {
                table[i][k] = merge_it(i, i + (1 << k - 1), k - 1);
            }
        }
    }

    ll query(ll l, ll r) {
        ll k = LOG[r - l + 1];
        r = r - (1 << k) + 1;
        return min(table[l][k], table[r][k]);
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
    ll l, r;
    bool f, ff;

    sparse_table sparse;
    cin >> n;

    forr(i, 0, n) cin >> a[i];
    sparse.build(n);

    cin >> t;
    while (t--) {
        cin >> l >> r;
        cout << sparse.query(l, r) << endl;
    }

    return 0;
}
