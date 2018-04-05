#include <cstdio>
#include <iostream>
#include <cstring>
#include <queue>
using namespace std;
const int N = 15, M = 30, P = N + M + 5, E = (N * M) << 1;
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
int T, n, m, a[N][M], ans;
int main()
{
    scanf("%d", &T);
    for(int haha = 1; haha <= T; ++haha)
    {
        memset(a, 0, sizeof(a));
        memset(first, 0, sizeof(first));
        memset(nxt, 0, sizeof(nxt));
        edge = 1;
        ans = 0;
        scanf("%d%d", &n, &m);
        for(int i = 1; i <= n; ++i)
        {
            int k, t;
            scanf("%d", &k);
            for(int j = 0; j < k; ++j)
            {
                scanf("%d", &t);
                ++a[i][t];
            }
        }
        s = 1;
        t = m + n + 1;
        for(int i = 1; i <= m; ++i)
        {
            link(i + 1, t, 1);
            if(a[1][i])
                link(s, i + 1, a[1][i]);
        }
        for(int i = 2; i <= n; ++i)
            for(int j = 1; j <= m; ++j)
                if(!a[i][j])
                    link(j + 1, m + i, 1);
                else
                    if(a[i][j] > 1)
                        link(m + i, j + 1, a[i][j] - 1);
        while(bfs())
        {
            memcpy(cur, first, sizeof(cur));
            ans += dfs(s, 214748364);
        }
        printf("Case #%d: %d\n", haha, ans);
    }
    return 0;
}
