// Solution of CF-1569C

#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <functional>
using namespace  __gnu_pbds;
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
#define mod 998244353
#define mxn 200005

ll fact[200010];
ll inv[200010];

ll modInverse(ll a, ll m)
{
    ll m0 = m;
    ll y = 0, x = 1;

    if (m == 1)
        return 0;

    while (a > 1) {
        ll q = a / m;
        ll t = m;

        m = a % m, a = t;
        t = y;

        y = x - q * y;
        x = t;
    }

    if (x < 0) x += m0;

    return x;
}

ll precalc()
{
    fact[1] = fact[0] = 1;
    inv[1] = 1;

    forr(i, 2, 200005) {
        fact[i] = (fact[i - 1] * i) % mod;
        inv[i] = modInverse(fact[i], mod) % mod;
    }

}

ll ncr(ll n, ll r)
{
    if (r == 0 || n == r) return 1ll;

    return (((fact[n] * inv[r]) % mod) * inv[n - r]) % mod;
}


int main()
{
    faster_io

#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    ll t = 1, m, xx, n, x = 0, y = 0, k, z, q, tc = 0, yy, ans;
    fact[1] = 1;

    cin >> t;

    precalc();


    while (t--) {
        cin >> n;
        map<ll, ll> mp;
        ll xval, yval, all;

        ll a[n + 5];

        forr(i, 0, n) {
            cin >> a[i];
            mp[a[i]]++;
        }

        auto it = mp.end();

        it--;
        xval = it->F;
        x = it->S;

        it--;
        yval = it->F;
        y = it->S;

        if (xval - yval > 1 && x == 1) cout << 0 << endl;
        else if (x >= 2) {
            all = fact[n];
            cout << all << endl;
        }
        else {
            all = fact[n];
            ll cnt, XX, YY, cancel = 0;

            fort(i, n, y + 1) {
                cnt = n - i;
                XX = (x * fact[n - cnt - 1]) % mod;
                k = n - x - y;
                YY = (ncr(k, cnt) * fact[cnt]) % mod;
                XX = (XX * YY) % mod;
                all -= XX;
                if (all < 0) all += mod;
            }

            cout << all << endl;
        }

    }

    return 0;
}
