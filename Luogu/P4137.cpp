#include <cstdio>
#include <iostream>
using namespace std;
const int N = 200005;
int tree_size, root[N];
struct node
{
    int v, l, r;
} tree[N * 25];
int newnode(int l, int r, int v)
{
    ++tree_size;
    tree[tree_size].v = v;
    tree[tree_size].l = l;
    tree[tree_size].r = r;
    return tree_size;
}
int insert(int r, int pl, int pr, int x, int k)
{
    if(pl == pr)
        return newnode(0, 0, k);
    int pm = (pl + pr) / 2, t;
    if(x <= pm)
    {
        t = insert(tree[r].l, pl, pm, x, k);
        return newnode(t, tree[r].r, min(tree[t].v, tree[tree[r].r].v));
    }
    else
    {
        t = insert(tree[r].r, pm + 1, pr, x, k);
        return newnode(tree[r].l, t, min(tree[tree[r].l].v, tree[t].v));
    }
}
int find(int p, int pl, int pr, int q)
{
    if(pl == pr)
        return pl;
    int pm =  (pl + pr) / 2;
    if(tree[tree[p].l].v < q)
        return find(tree[p].l, pl, pm, q);
    else
        return find(tree[p].r, pm + 1, pr, q);
}
int n, m;
int main()
{
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; ++i)
    {
        int t;
        scanf("%d", &t);
        root[i] = insert(root[i - 1], 0, n + 1, t, i);
    }
    for(int i = 1; i <= m; ++i)
    {
        int l, r;
        scanf("%d%d", &l, &r);
        printf("%d\n", find(root[r], 0, n + 1, l));
    }
}
