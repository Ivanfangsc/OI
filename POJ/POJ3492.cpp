#include <cstdio>
#include <iostream>
#include <queue>
#include <cstring>
using namespace std;
const int N = 505, M = 5005;
int adjmat[M][M], a[N], n, dis[M], ans;
void work()
{
    memset(adjmat, 127, sizeof(adjmat));
    int t = 5005;
    for(int i = 0; i < n; ++i)
    {
        scanf("%d", &a[i]);
        if(a[i] < t)
            t = a[i];
    }
    for(int i = 0; i < n; ++i)
        if(a[i] > t)
        {
            int k = a[i] % t, x = 0, y = k;
            for(int j = 0; j < t; ++j)
            {
                adjmat[x][y] = min(adjmat[x][y], a[i]);
                x = (x + k) % t;
                y = (y + k) % t;
            }
        }
    queue<int> q;
    q.push(0);
    memset(dis, 127, sizeof(dis));
    dis[0] = 0;
    while(!q.empty())
    {
        int u = q.front();
        q.pop();
        for(int i = 0; i < t; ++i)
            if(i != u && dis[u] + adjmat[u][i] < dis[i])
            {
                dis[i] = dis[u] + adjmat[u][i];
                q.push(i);
            }
    }
    for(int i = 0; i < t; ++i)
        if(dis[i] > ans)
            ans = dis[i];
    if(ans > 214748364)
        printf("INF\n");
    else
        printf("%d\n", ans - t);
}
int main()
{
    while(scanf("%d", &n) == 1)
        work();
    return 0;
}
