///input at the bottom

#include<bits/stdc++.h>
using namespace std;
#define sz 400005
#define faster_io ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
typedef long long ll;
int segtree[sz];
int arr[sz];
int lazy[sz];

int merge(int l,int r)
{
    return l+r;
}

void relax(int node,int l,int r)
{
    segtree[node] += (r-l+1)*lazy[node];
    if(l!=r){
        lazy[2*node] = lazy[2*node+1] += lazy[node];
    }
    lazy[node] = 0;
}

void build(int node,int l,int r)
{
    if(l==r){
        segtree[node] = arr[l-1];
        return;
    }
    int mid = (l+r)/2;
    build(2*node,l,mid);
    build(2*node+1,mid+1,r);
    segtree[node] = merge(segtree[2*node],segtree[2*node+1]);
}

void update(int node,int l,int r,int i,int val)
{
    if(l==r){
        if(l==i) segtree[node]+=val;
        return;
    }
    int mid = (l+r)/2;
    if(i>=l && i<=r){
        update(2*node,l,mid,i,val);
        update(2*node+1,mid+1,r,i,val);
        segtree[node]+=val;
    }
}

void rangeUpdate(int node,int l,int r,int beg,int en,int val)
{
    if(lazy[node]) relax(node,l,r);
    int mid = (l+r)/2;
    if(l>=beg && r<=en){
        lazy[node] += val ;
        relax(node,l,r);        return ;
    }
    if(en<l || beg>r) return ;

    rangeUpdate(2*node,l,mid,beg,en,val);
    rangeUpdate(2*node+1,mid+1,r,beg,en,val);

    segtree[node] = merge(segtree[2*node],segtree[2*node+1]);
}

int query(int node,int l,int r,int beg,int en)
{
    int mid = (l+r)/2;

    if(lazy[node]) relax(node,l,r);

    if(l>=beg && r<=en){
        return segtree[node];
    }
    if(en<l || beg>r) return 0;

    int ret = query(2*node,l,mid,beg,en) + query(2*node+1,mid+1,r,beg,en);
    return ret;

}

int main()
{
    faster_io;

//    freopen("input.txt","r",stdin);
    int n,type,x,y,val;
    cin>>n;

    for(int i=0;i<n;i++){
        cin>>arr[i];
    }

    build(1,1,n);

    while(1){
        cin>>type;
        if(type==1){
            cin>>x>>y;
            cout<<query(1,1,n,x,y)<<endl;
        }
        else if(type==2){
            cin>>x>>y>>val;
            rangeUpdate(1,1,n,x,y,val);
        }
        for(int i=1;i<2*n+2;i++){
            cout<<segtree[i]<<" ";
        }
    }

    return 0;
}

///6
///3 4 2 5 1 7
///4 2
