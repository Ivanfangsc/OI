#include <cstdio>
#include <iostream>
#include <queue>
#include <cstring>
using namespace std;
typedef long long ll;
const int N = 2005, P = N << 1, E = 12 * N, INF = 2147483647;
int first[P], nxt[E], to[E], w[E], r[E], edge = 1;
void link(int a, int b, int c, int d)
{
    ++edge;
    nxt[edge] = first[a];
    to[edge] = b;
    r[edge] = c;
    w[edge] = d;
    first[a] = edge;
    ++edge;
    nxt[edge] = first[b];
    to[edge] = a;
    r[edge] = 0;
    w[edge] = -d;
    first[b] = edge;
}
int pre[P], s, t, dis[P];
ll mincost;
queue<int> q;
bool spfa()
{
    memset(dis, 127, sizeof(dis));
    q.push(s);
    dis[s] = 0;
    while(!q.empty())
    {
        int u = q.front();
        q.pop();
        for(int e = first[u]; e; e = nxt[e])
            if(r[e] && dis[to[e]] > dis[u] + w[e])
            {
                dis[to[e]] = dis[u] + w[e];
                pre[to[e]] = e;
                q.push(to[e]);
            }
    }
    return dis[t] != dis[0];
}
void augment()
{
    int delta = INF;
    for(int u = t; u != s; u = to[pre[u] ^ 1])
        delta = min(delta, r[pre[u]]);
    for(int u = t; u != s; u = to[pre[u] ^ 1])
    {
        int e = pre[u];
        r[e] -= delta;
        r[e ^ 1] += delta;
        mincost += w[e] * delta;
    }
}
int n, a[N], p, x, f, y, z;
int main()
{
    scanf("%d", &n);
    for(int i = 1; i <= n; ++i)
        scanf("%d", &a[i]);
    scanf("%d%d%d%d%d", &p, &x, &f, &y, &z);
    s = 2 * n + 1;
    t = 2 * n + 2;
    for(int i = 1; i <= n; ++i)
    {
        link(s, i, a[i], p);
        link(i, t, a[i], 0);
        link(s, i + n, a[i], 0);
    }
    for(int i = 1; i <= n - x; ++i)
        link(n + i, i + x, INF, f);
    for(int i = 1; i <= n - y; ++i)
        link(n + i, i + y, INF, z);
    for(int i = 1; i <= n - 1; ++i)
        link(n + i, n + i + 1, INF, 0);
    while(spfa())
        augment();
    printf("%lld\n", mincost);
    return 0;
}
