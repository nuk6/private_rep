#include <bits/stdc++.h>
using namespace std;
int a[] = {3,4,5,1,7,5};
int n = 6;
int t[100],lt[100];

void build(int i,int l,int r){
    if(l == r) {t[i] = a[r]; return;}
    int m = (l+r)/2;
    build(2*i+1,l,m),build(2*i+2,m+1,r);
    t[i] = min(t[2*i+1],t[2*i+2]);
}

int query(int ql,int qr,int l, int r,int i){
    if((qr < l) || (ql > r)) return INT_MAX;
    if((ql <= l) && (qr >= r)) return t[i];
    int m = (l+r)>>1;
    return min(query(ql,qr,l,m,2*i+1),query(ql,qr,m+1,r,2*i+2));
}


void point_update(int idx,int v, int i,int l,int r){
    if((idx <l) || (idx > r)) return;
    if((l == r) && (r == idx)){ a[idx] = t[i] = v; return;}
    int m = (l+r)>>1;
    point_update(idx,v,2*i+1,l,m);
    point_update(idx,v,2*i+2,m+1,r);
    t[i] = min(t[2*i+1],t[2*i+2]);
}

void range_update(int ql,int qr,int l,int r,int i,int v){
    if((ql > r) || (qr < l)) return;
    if(l == r) { a[l] += v; t[i] += v; return;}
    int m = (l+r)>>1;
    range_update(ql,qr,l,m,2*i+1,v);
    range_update(ql,qr,m+1,r,2*i+2,v);
    t[i] = min(t[2*i+1],t[2*i+2]);
}

void lazy_range_update(int ql,int qr, int l,int r,int i, int x){
    if((ql > r) || (qr < l)) return;
    if((ql <=l) && (qr >= r)){
        lt[i] += x;
        t[i] += lt[i];
        if(l != r){
            lt[2*i+1] += lt[i];
            lt[2*i+2] += lt[i];
        }
        lt[i] = 0;
        return;
    }
    int m = (l+r)/2;
    t[i] += lt[i];
    if(l != r){
        lt[2*i+1] += lt[i];
        lt[2*i+2] += lt[i];
    }
    lt[i] = 0;
    lazy_range_update(ql,qr,l,m,2*i+1,x);
    lazy_range_update(ql,qr,m+1,r,2*i+2,x);
    t[i] = min(t[2*i+1],t[2*i+2]);
}

int main() {
	build(0,0,n-1);
	//for(int i = 0; i < 15; ++i) cout << t[i] << " "; cout << endl;
	cout << query(3,5,0,5,0) << endl;
	//point_update(2,10,0,0,n-1);
	lazy_range_update(0,3,0,5,0,-100);
	cout << query(1,2,0,5,0) << endl;
	return 0;
}
