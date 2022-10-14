#include<bits/stdc++.h>
using namespace std;

void build(int *arr, int *segtree, int s, int e, int tidx){
    // base case
    if(s==e){
        segtree[tidx]=arr[s];
        return;
    }
    int mid=(s+e)/2;
    build(arr,segtree,s,mid,2*tidx);
    build(arr,segtree,mid+1,e,2*tidx+1);

    // self work
    segtree[tidx]=segtree[2*tidx]+segtree[2*tidx+1];
}

void updateSegmentTreeLazy(int *tree, int *lazy, int s, int e, int left, int right, int currPos, int inc){
    if(s>e){
        return;
    }

    if(lazy[currPos]!=0){
       /* Note that this node represents sum of elements in arr[s..e] and all these elements must be increased by lazy[currPos] */
        tree[currPos] += lazy[currPos]*(e-s+1); 
        if(s!=e){
            lazy[2*currPos] += lazy[currPos];
            lazy[2*currPos+1] += lazy[currPos];
        }
        lazy[currPos]=0;
    }

    // no overlap
    if(s>right || e<left){    
        return;
    }

    // complete overlap
    if(s>=left && e<=right){
        tree[currPos] += inc;

        // child ke lazy prop me update
        if(s!=e){
            lazy[2*currPos] += inc;
            lazy[2*currPos+1] += inc; 
        }
        return;
    }

    // partial overlap
    int mid=(s+e)/2;
    updateSegmentTreeLazy(tree,lazy,s,mid,left,right,2*currPos,inc);
    updateSegmentTreeLazy(tree,lazy,mid+1,e,left,right,2*currPos+1,inc);

    tree[currPos] = tree[2*currPos]+tree[2*currPos+1];
}

int querySegmentTreeLazy(int *lazy, int*tree, int s, int e, int currPos, int left, int right){
    if(s>e) return 0;;

    if(lazy[currPos]!=0){
        tree[currPos] += lazy[currPos]*(e-s+1); 

        if(s!=e){
            lazy[2*currPos] += lazy[currPos];
            lazy[2*currPos+1] += lazy[currPos];
        }
        lazy[currPos]=0;
    }

    if(s>right  || e<left){
        // complete outside
        return 0;
    }
    if(s>=left && e<=right){
        // complete inside
        return tree[currPos];
    }

    int mid=(s+e)/2;
    int a1=querySegmentTreeLazy(lazy,tree,s,mid,currPos,left,right);
    int a2=querySegmentTreeLazy(lazy,tree,mid+1,e,currPos,left,right);
    return a1+a2;
}
void update(int *arr, int* tree, int s, int e,int tidx, int idx, int val){
    // updating on leaf node
    if(s==e){
        arr[idx]=val;
        tree[tidx]=val;
        return;
    }
    int mid=(s+e)/2;
    if(idx>mid){
        update(arr,tree,mid+1,e,2*tidx+1,idx,val);
    }else{
        update(arr,tree,s,mid,2*tidx,idx,val);
    }
    tree[tidx]=tree[2*tidx]+tree[2*tidx+1];
}

int query(int *tree, int s, int e, int tidx, int left, int right){
    // s & e denote node kya range ki values store krti h
    if(s>right || e<left){
        // complete outside
        return 0;
    }
    if(s>=left && e<=right){
        // completely inside
        return tree[tidx];
    }
    int mid=(s+e)/2;
    int a1=query(tree,s,mid,2*tidx,left,right);
    int a2=query(tree,mid+1,e,2*tidx+1,left,right);
    return a1+a2;
}

int main(){
    int n; cin>>n; 
    int *arr = new int[n];
    for(int i=0;i<n;i++){
        cin>>arr[i];
    }
    // making segment tree
    int *segtree = new int[4*n];
    build(arr,segtree,0,n-1,1);
    // lazy tree
    int *lazy = new int[4*n]();
    int q; cin>>q;
    while(q--){
        int type; cin>>type;
        if(type==1){
            int l,r; cin>>l>>r;
            cout<<query(segtree,0,n-1,1,l,r);
        }else{
            int i,v; cin>>i>>v;
            update(arr,segtree,0,n-1,1,i,v);
        }
    }

}
