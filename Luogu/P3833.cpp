#include <cstdio>
#include <iostream>
#include <string>
using namespace std;
typedef long long ll;
const int N = 1000100;
int first[N], nxt[N << 1], to[N << 1], edge;
void link(int a, int b)
{
    ++edge;
    nxt[edge] = first[a];
    to[edge] = b;
    first[a] = edge;
}
int depth[N], size[N], son[N], top[N], fa[N], pos[N], tic;
void dfs1(int u, int f)
{
    size[u] = 1;
    fa[u] = f;
    depth[u] = depth[f] + 1;
    for(int e = first[u]; e; e = nxt[e])
        if(to[e] != f)
        {
            dfs1(to[e], u);
            size[u] += size[to[e]];
            if(!son[u] || size[son[u]] < size[to[e]])
                son[u] = to[e];
        }
}
void dfs2(int u, int f)
{
    pos[u] = ++tic;
    top[u] = f;
    if(!son[u])
        return;
    dfs2(son[u], f);
    for(int e = first[u]; e; e = nxt[e])
        if(to[e] != son[u] && to[e] != fa[u])
            dfs2(to[e], to[e]);
}
ll tree[N << 1], lazy[N << 1];
void down(int p, int pl, int pr)
{
    if(lazy[p])
    {
        int m = (pl + pr) >> 1, lc = p << 1, rc = (p << 1) + 1;
        tree[lc] += lazy[p] * (m - pl + 1);
        tree[rc] += lazy[p] * (pr - m);
        lazy[lc] += lazy[p];
        lazy[rc] += lazy[p];
        lazy[p] = 0;
    }
}
void _add(int p, int pl, int pr, int l, int r, int k)
{
    if(pr < l || r < pl)
        return;
    if(l <= pl && pr <= r)
    {
        tree[p] += k * (pr - pl + 1);
        lazy[p] += k;
        return;
    }
    down(p, pl, pr);
    int m = (pl + pr) >> 1, lc = p << 1, rc = (p << 1) + 1;
    _add(lc, pl, m, l, r, k);
    _add(rc, m + 1, pr, l, r, k);
    tree[p] = tree[lc] + tree[rc];
}
void add(int l, int r, int k)
{
    _add(1, 1, tic, l, r, k);
}
ll _ask(int p, int pl, int pr, int l, int r)
{
    if(pr < l || r < pl)
        return 0;
    if(l <= pl && pr <= r)
        return tree[p];
    down(p, pl, pr);
    int m = (pl + pr) >> 1, lc = p << 1, rc = (p << 1) + 1;
    return _ask(lc, pl, m, l, r) + _ask(rc, m + 1, pr, l, r);
}
ll ask(int l, int r)
{
    return _ask(1, 1, tic, l, r);
}
int n, q;
int main()
{
    scanf("%d", &n);
    for(int i = 0; i < n - 1; ++i)
    {
        int a, b;
        scanf("%d%d", &a, &b);
        link(a + 1, b + 1);
    }
    dfs1(1, 0);
    dfs2(1, 1);
    scanf("%d", &q);
    while(q--)
    {
        string s;
        int a, b, c;
        cin >> s >> a;
        ++a;
        if(s[0] == 'A')
        {
            scanf("%d%d", &b, &c);
            ++b;
            int f1 = top[a], f2 = top[b];
            while(f1 != f2)
            {
                if(depth[f1] > depth[f2])
                {
                    add(pos[f1], pos[a], c);
                    a = fa[f1];
                }
                else
                {
                    add(pos[f2], pos[b], c);
                    b = fa[f2];
                }
                f1 = top[a];
                f2 = top[b];
            }
            if(pos[a] > pos[b])
                add(pos[b], pos[a], c);
            else
                add(pos[a], pos[b], c);
        }
        else
            printf("%lld\n", ask(pos[a], pos[a] + size[a] - 1));
    }
    return 0;
}
