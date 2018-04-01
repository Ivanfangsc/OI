#include <cstdio>
#include <iostream>
#include <queue>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
const int N = 15, M = 500010;
int a[N], n;
ll dis[M], bl, br, ans;
queue<int> q;
int main()
{
    scanf("%d%lld%lld", &n, &bl, &br);
    for(int i = 0; i < n; ++i)
    {
        scanf("%d", &a[i]);
        if(a[i] == 0)
        {
            --i;
            --n;
        }
    }
    sort(a, a + n);
    memset(dis, 127, sizeof(dis));
    q.push(0);
    dis[0] = 0;
    while(!q.empty())
    {
        int u = q.front();
        q.pop();
        for(int i = 1; i < n; ++i)
            if(dis[(u + a[i]) % a[0]] > dis[u] + a[i])
            {
                dis[(u + a[i]) % a[0]] = dis[u] + a[i];
                q.push((u + a[i]) % a[0]);
            }
    }
    for(int i = 0; i < a[0]; ++i)
    {
        if(dis[i] <=  br)
            ans += (br - dis[i]) / a[0] + 1;
        if(dis[i] <= bl - 1)
            ans -= (bl - 1 - dis[i]) / a[0] + 1;
    }
    printf("%lld\n", ans);
}