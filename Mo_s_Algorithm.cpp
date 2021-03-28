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

typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;
typedef tree<int, null_type, less_equal<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_multiset;

int sq, n, m;

inline int64_t hilbertOrder(int x, int y, int pow, int rotate) {
    if (pow == 0) {
        return 0;
    }
    int hpow = 1 << (pow - 1);
    int seg = (x < hpow) ? (
                  (y < hpow) ? 0 : 3
              ) : (
                  (y < hpow) ? 1 : 2
              );
    seg = (seg + rotate) & 3;
    const int rotateDelta[4] = {3, 0, 0, 1};
    int nx = x & (x ^ hpow), ny = y & (y ^ hpow);
    int nrot = (rotate + rotateDelta[seg]) & 3;
    int64_t subSquareSize = int64_t(1) << (2 * pow - 2);
    int64_t ans = seg * subSquareSize;
    int64_t add = hilbertOrder(nx, ny, pow - 1, nrot);
    ans += (seg == 1 || seg == 2) ? add : (subSquareSize - add - 1);
    return ans;
}

struct queries {
    int l;
    int r;
    int idx;
    int64_t ord;

    inline void calcOrder() {
        ord = hilbertOrder(l, r, 21, 0);
    }
} q[200005];

int a[30005];
int ans[200005];
int cnt[1000005];
set<int> st;

inline bool operator<(const queries &a, const queries &b) {
    return a.ord < b.ord;
}

struct mo_s_algorithm
{
    void add(int val)
    {
        if (cnt[val] == 0) st.insert(val);
        cnt[val]++;
    }

    void remove(int val)
    {
        cnt[val]--;
        if (cnt[val] == 0) st.erase(val);
    }

    int get_answer() { return st.size(); }

    void solve() {

        sort(q, q + m);

        int cur_l = 0;
        int cur_r = -1;

        forr(i, 0, m) {
            while (cur_l > q[i].l) {
                cur_l--;
                add(a[cur_l]);
            }
            while (cur_r < q[i].r) {
                cur_r++;
                add(a[cur_r]);
            }
            while (cur_l < q[i].l) {
                remove(a[cur_l]);
                cur_l++;
            }
            while (cur_r > q[i].r) {
                remove(a[cur_r]);
                cur_r--;
            }
            ans[q[i].idx] = get_answer();
        }
    }
};

int main()
{
    // faster_io

#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    int t = 1, x, y;

    // cin >> t;

    while (t--) {
        read(n);
        sq = sqrt(n + .0) + 1;

        forr(i, 0, n) cin >> a[i];
        read(m);

        forr(i, 0, m) {
            cin >> x >> y;
            q[i].l = --x;
            q[i].r = --y;
            q[i].idx = i;
            q[i].calcOrder();
        }

        mo_s_algorithm obj;
        obj.solve();

        forr(i, 0, m) printf("%d\n", ans[i]);;

    }

    return 0;
}
