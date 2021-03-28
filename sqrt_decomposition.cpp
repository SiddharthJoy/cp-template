/// sqrt_decomposition (range sum query) implementation
/// 0 based indexed input array + 0 based indexed query
/// can be converted for min/max/gcd


#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <functional>
using namespace  __gnu_pbds;
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

typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;
typedef tree<int, null_type, less_equal<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_multiset;


int n, block_size;
int blocks[2002];
int a[20000 + 5];

struct sqrt_decomposition
{

    void init()
    {
        forr(i, 0, block_size + 2) blocks[i] = 0;
    }

    void build(int a[])
    {
        forr(i, 0, n) {
            blocks[i / block_size] += a[i];
        }
    }

    void update(int idx, int val)
    {
        blocks[idx / block_size] += (val - a[idx]);
        a[idx] = val;
    }

    int query(int l, int r)
    {
        int sum = 0;
        int c_l = l / block_size,   c_r = r / block_size;
        if (c_l == c_r)
            for (int i = l; i <= r; ++i) sum += a[i];       ///if the range is in the same block

        else {
            for (int i = l, end = (c_l + 1) * block_size - 1; i <= end; ++i) sum += a[i];

            for (int i = c_l + 1; i <= c_r - 1; ++i) sum += blocks[i];

            for (int i = c_r * block_size; i <= r; ++i) sum += a[i];
        }

        return sum;
    }

} obj;

int main()
{
    faster_io

    int  t = 1, m, l, r;
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    // cin >> t;

    while (t--) {
        cin >> n;

        forr(i, 0, n) cin >> a[i];

        block_size = sqrt(n + .0);

        obj.init();
        obj.build(a);

        cin >> m;

        while (m--) {
            cin >> l >> r;
            cout << obj.query(--l, --r) << endl;
        }
    }

    return 0;
}
