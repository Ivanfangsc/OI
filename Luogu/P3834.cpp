#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
struct node
{
	int l, r, s;
	void operator() (int a, int b, int c)
	{
		l = a;
		r = b;
		s = c;
	}
} tree[200005 << 5];
int treesize, n, m, a[200005], b[200005], root[200005];
int newnode(int l, int r, int s)
{
	tree[++treesize](l, r, s);
	return treesize;
}
int inc(int p, int pl, int pr, int loc)
{
	if(pl == pr)
		return newnode(0, 0, tree[p].s + 1);
	int pm = (pl + pr) >> 1;
	if(loc <= pm)
		return newnode(inc(tree[p].l, pl, pm, loc), tree[p].r, tree[p].s + 1);
	else
		return newnode(tree[p].l, inc(tree[p].r, pm + 1, pr, loc), tree[p].s + 1);
}
int find(int p, int q, int pl, int pr, int k)
{
	if(pl == pr)
		return pl;
	int ls = tree[tree[q].l].s - tree[tree[p].l].s, pm = (pl + pr) >> 1;
	if(ls >= k)
		return find(tree[p].l, tree[q].l, pl, pm, k);
	else
		return find(tree[p].r, tree[q].r, pm + 1, pr, k - ls);
} 
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 0; i < n; ++i)
		scanf("%d", &a[i]);
	memcpy(b, a, sizeof(b));
	sort(b, b + n);
	int bl = unique(b, b + n) - b;
	for(int i = 1; i <= n; ++i)
		root[i] = inc(root[i - 1], 1, bl, lower_bound(b, b + bl, a[i - 1]) - b + 1);
	for(int i = 0; i < m; ++i)
	{
		static int l, r, k;
		scanf("%d%d%d", &l, &r, &k);
		printf("%d\n", b[find(root[l - 1], root[r], 1, bl, k) - 1]);
	}
	return 0;
} 

