#include <cstdio> 
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;
class SegTree
{
  private:
    int tree[100000 * 4 + 5];
    int n;
    void _build(int n, int b, int e, int a[])
    {
        if (b == e)
        {
            tree[n] = a[b];
            return;
        }
        int m = (b + e) >> 1, lc = n << 1, rc = (n << 1) + 1;
        _build(lc, b, m, a);
        _build(rc, m + 1, e, a);
        tree[n] = max(tree[lc], tree[rc]);
    }
    int _query(int n, int b, int e, int l, int r)
    {
        if (e < l || r < b)
            return 0;
        if (l <= b && e <= r)
            return tree[n];
        int m = (b + e) >> 1, lc = n << 1, rc = (n << 1) + 1;
        return max(_query(lc, b, m, l, r), _query(rc, m + 1, e, l, r));
    }
    void _modify(int n, int b, int e, int index, int v)
    {
        if (e < index || index < b)
            return;
        if (b == e)
        {
            tree[n] = v;
            return;
        }
        int m = (b + e) >> 1, lc = n << 1, rc = (n << 1) + 1;
        if(index <= m)
        	_modify(lc, b, m, index, v);
        else
        	_modify(rc, m + 1, e, index, v);
        tree[n] = max(tree[lc], tree[rc]);
    }
  public:
    void build(int n, int a[])
    {
        this->n = n;
        _build(1, 1, n, a);
    }
    int query(int l, int r)
    {
        return _query(1, 1, n, l, r);
    }
    void modify(int index, int v)
    {
        _modify(1, 1, n, index, v);
    }
} segTree;
void read(int &x)
{
	x = 0;
	char ch = getchar();
	while(ch < '0' || '9' < ch)
		ch = getchar();
	while('0' <= ch && ch <= '9')
	{
		x = (x << 3) + (x << 1) + ch - '0';
		ch = getchar();
	}
}
struct treenode
{
	int next, map, top, size, depth, son, parent, val;
} tree[100005];
struct node
{
	int v, id, next, w;
} adjlist[200005];
int n, adjlen, list[100005], len, vertex[100005];
void dfs1(int n, int p, int d)
{
    tree[n].depth = d;
    tree[n].parent = p;
    tree[n].size = 1;
    for (int i = tree[n].next; i; i = adjlist[i].next)
    {
        int v = adjlist[i].v;
        if (v == p)
            continue;
        tree[v].val = adjlist[i].w;
        vertex[adjlist[i].id] = v;
        dfs1(v, n, d + 1);
        tree[n].size += tree[v].size;
        if (!tree[n].son || tree[tree[n].son].size < tree[v].size)
            tree[n].son = v;
    }
}
void dfs2(int n, int f)
{
    tree[n].top = f;
    list[tree[n].map = ++len] = tree[n].val;
    if (!tree[n].son)
        return;
    dfs2(tree[n].son, f);
    int p = tree[n].parent;
    for (int i = tree[n].next; i; i = adjlist[i].next)
    {
        int v = adjlist[i].v;
        if (v == p || v == tree[n].son)
            continue;
        dfs2(v, v);
    }
}
int main()
{
	//freopen("qtree.in", "r", stdin);
	//freopen("qtree.out", "w", stdout);
	read(n);
	for(int i = 1; i < n; ++i)
	{
		static int x, y, z;
		read(x);
		read(y);
		read(z); 
		adjlist[++adjlen].v = x;
		adjlist[adjlen].next = tree[y].next;
		adjlist[adjlen].id = i;
		adjlist[adjlen].w = z;
		tree[y].next = adjlen;
		adjlist[++adjlen].v = y;
		adjlist[adjlen].next = tree[x].next;
		adjlist[adjlen].id = i;
		adjlist[adjlen].w = z;
		tree[x].next = adjlen;
	}
	dfs1(1, 0, 1);
	dfs2(1, 1);
	segTree.build(n, list);
	string cmd;
	while(1)
	{
		cin >> cmd;
		static int x, y; 
		if(cmd == "QUERY")
		{
			read(x);
			read(y);
			if(x == y)
			{
				printf("0\n");
				continue;
			} 
			int f1 = tree[x].top, f2 = tree[y].top, ans = 0;
			while(f1 != f2)
			{
				if(tree[f1].depth < tree[f2].depth)
				{
					ans = max(ans, segTree.query(tree[f2].map, tree[y].map));
					y = tree[f2].parent;
				}
				else
				{
					ans = max(ans, segTree.query(tree[f1].map, tree[x].map));
					x = tree[f1].parent;
				}
				f1 = tree[x].top;
				f2 = tree[y].top;
			}
			if(tree[x].map > tree[y].map)
				ans = max(ans, segTree.query(tree[tree[y].son].map, tree[x].map));
			else
				ans = max(ans, segTree.query(tree[tree[x].son].map, tree[y].map));
			printf("%d\n", ans);
		}	
		if(cmd == "CHANGE")
		{
			read(x);
			read(y);
			segTree.modify(tree[vertex[x]].map, y); 
		}
		if(cmd == "DONE")
			break;
	}
	return 0;
}
