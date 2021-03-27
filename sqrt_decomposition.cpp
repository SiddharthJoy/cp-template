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

        forr(i, 0, block_size) {
            cout << blocks[i] << " ";
        }
    }

    int query(int l, int r)
    {
        int nxt_block_idx = ((l / block_size) + 1) * block_size;
        int scnd_block = nxt_block_idx / block_size;
        int lst_block = r / block_size;
        int lst_block_idx = lst_block * block_size;

        int sum = 0;

        forr(i, l, min(r + 1, nxt_block_idx)) sum += a[i];

        if (scnd_block  > lst_block) return sum;    ///l and r in same block

        forr(i, scnd_block, lst_block) sum += blocks[i];

        forr(i, lst_block_idx, r + 1) sum += a[i];

        return sum;
    }
} obj;

int main()
{
    faster_io

    int  t = 1;
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
        cout << obj.query(0, n - 1) << endl;
    }

    return 0;
}
