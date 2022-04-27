#include <bits/stdc++.h>
using namespace std;

/* RMQ */

int a[]{3, 1, -1, 3, -4, 6};

int seg_tree[10000];

void build(int l, int r, int i) {
	if(l==r) {
		seg_tree[i] = a[l];
		return;
	}
	int m = (l+r)/2;
	build(l,m, 2*i+1);
	build(m+1,r, 2*i+2);
	seg_tree[i] = min(seg_tree[2*i+1], seg_tree[2*i+2]);
}

int query(int x, int y, int l, int r, int i) {
	if(x <= l && y >= r) return seg_tree[i];
	if(x > r || y < l) return INT_MAX;
	int m = (l + r)/2;
	return min(query(x, y, l, m, 2*i+1), query(x, y, m+1, r, 2*i+2));
}

int main()
{
	int n = sizeof(a)/sizeof(a[0]);
	//cout << "size = " << n << endl;
	build(0,n-1,0);
	// querying 0 based
	cout << query(1,3, 0, n-1, 0) << endl;
	return 0;
};
