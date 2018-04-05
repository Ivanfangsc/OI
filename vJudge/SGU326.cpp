#include <cstdio>
#include <iostream>
#include <queue>
#include <cstring>
using namespace std;
const int N = 30, P = N * N + N, E = 6 * N * N + 2 * N;
int first[P], nxt[E], to[E], r[E], edge = 1;
void link(int a, int b, int c)
{
    ++edge;
    nxt[edge] = first[a];
    to[edge] = b;
    r[edge] = c;
    first[a] = edge;
    ++edge;
    nxt[edge] = first[b];
    to[edge] = a;
    r[edge] = 0;
    first[b] = edge;
}
int s, t, d[P], cur[P];
queue<int> q;
bool bfs()
{
    memset(d, 0, sizeof(d));
    q.push(t);
    d[t] = 1;
    while(!q.empty())
    {
        int u = q.front();
        q.pop();
        for(int e = first[u]; e; e = nxt[e])
            if(!d[to[e]] && r[e ^ 1])
            {
                d[to[e]] = d[u] + 1;
                q.push(to[e]);
            }
    }
    return d[s];
}
int dfs(int u, int budget)
{
    if(u == t)
        return budget;
    int res = 0;
    for(int &e = cur[u]; e; e = nxt[e])
        if(d[to[e]] + 1 == d[u] && r[e])
        {
            int delta = dfs(to[e], min(budget, r[e]));
            r[e] -= delta;
            r[e ^ 1] += delta;
            budget -= delta;
            res += delta;
            if(!budget)
                break;
        }
    return res;
}
int dinic()
{
    int res = 0;
    while(bfs())
    {
        memcpy(cur, first, sizeof(cur));
        res += dfs(s, 214748364);
    }
    return res;
}
int w[N], l[N], a[N][N], n, sum = 0;
int main()
{
    scanf("%d", &n);
    for(int i = 1; i <= n; ++i)
        scanf("%d", &w[i]);
    for(int i = 1; i <= n; ++i)
        scanf("%d", &l[i]);
    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= n; ++j)
            scanf("%d", &a[i][j]);
    int max_score = w[1] + l[1];
    for(int i = 2; i <= n; ++i)
        if(w[i] > max_score)
        {
            printf("NO\n");
            return 0;
        }
    s = 1;
    t = n * n + 1;
    for(int i = 2; i <= n; ++i)
        link(s, i, max_score - w[i]);
    for(int i = 2; i <= n; ++i)
        for(int j = i + 1; j <= n; ++j)
        {
            sum += a[i][j];
            int node = (i - 1) * n + j;
            link(node, t, a[i][j]);
            link(i, node, a[i][j]);
            link(j, node, a[i][j]);
        }
    if(dinic() == sum)
        printf("YES\n");
    else
        printf("NO\n");
    return 0;
}
