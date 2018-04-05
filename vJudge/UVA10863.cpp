#include <cstdio>
#include <iostream>
#include <queue>
#include <cstring>
using namespace std;
const int N = 25, M = 20;
const int dx[4] = {1, -1, 0, 0}, dy[4] = {0, 0, 1, -1};
int n, m;
struct node
{
    int x, y, z, t;
    void operator() (int a, int b, int c, int d)
    {
        x = a;
        y = b;
        z = c;
        t = d;
    }
    bool operator < (const node &other) const
    {
        return t > other.t;
    }
};
priority_queue<node> q;
int f[N][N][M], fa[N][N][M][5];
bool vis[N][N][M];
char map[N][N];
void ans(int x, int y, int z)
{
    if(map[x][y] == 'o')
        map[x][y] = '.';
    vis[x][y][z] = true;
    for(int i = 1; i <= fa[x][y][z][0]; ++i)
    {
        int tmp = fa[x][y][z][i];
        int tx = tmp / 10000, ty = tmp % 10000 / 100, tz = tmp % 100;
        if(!vis[tx][ty][tz])
            ans(tx, ty, tz);
    }
}
void bfs()
{
    memset(f, 127, sizeof(f));
    memset(fa, 0, sizeof(fa));
    memset(vis, 0, sizeof(vis));
    while(!q.empty())
        q.pop();
    node tmp;
    for(int i = 0; i < n; ++i)
        for(int j = 0; j < m; ++j)
            if('A' <= map[i][j] && map[i][j] <= 'D')
            {
                tmp(i, j, 1 << (map[i][j] - 'A'), 0);
                q.push(tmp);
                f[i][j][tmp.z] = 0;
            }
    while(!q.empty())
    {
        node u = q.top();
        q.pop();
        int x = u.x, y = u.y, z = u.z, t = u.t;
        if(vis[x][y][z])
            continue;
        vis[x][y][z] = true;
        if(z == 15)
        {
            memset(vis, 0, sizeof(vis));
            ans(x, y, z);
            return;
        }
        for(int i = 0; i < 4; ++i)
        {
            int tx = x + dx[i], ty = y + dy[i], tz = z;
            if(tx < 0 || ty < 0 || tx >= n || ty >= m || map[tx][ty] == '#')
                continue;
            int tt = t + (map[tx][ty] == 'o' ? 1 : 0);
            if(tt < f[tx][ty][tz])
            {
                f[tx][ty][tz] = tt;
                fa[tx][ty][tz][0] = 1;
                fa[tx][ty][tz][1] = x * 10000 + y * 100 + z;
                tmp(tx, ty, tz ,tt);
                q.push(tmp);
            }
        }
        for(int i = 1; i < 15; ++i)
            if(vis[x][y][i])
            {
                int tx = x, ty = y, tz = z | i;
                int tt = t + f[x][y][i] - (map[x][y] == 'o' ? 1 : 0);
                if(tt < f[tx][ty][tz])
                {
                    f[tx][ty][tz] = tt;
                    fa[tx][ty][tz][0] = 2;
                    fa[tx][ty][tz][1] = x * 10000 + y * 100 + z;
                    fa[tx][ty][tz][2] = x * 10000 + y * 100 + i;
                    tmp(tx, ty, tz, tt);
                    q.push(tmp);
                }
            }
    }
}
int main()
{
    scanf("%d%d", &m, &n);
    while(n && m)
    {
        for(int i = 0; i < n; ++i)
            scanf("%s", map[i]);
        printf("%d %d\n", m, n);
        bfs();
        for(int i = 0; i < n; ++i)
            printf("%s\n", map[i]);
        printf("\n");
        scanf("%d%d", &m, &n);
    }
    printf("0 0\n");
    return 0;
}
