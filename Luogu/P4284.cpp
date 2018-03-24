#include <cstdio>
#include <iostream>
using namespace std;
const int N = 500005;
int n, first[N], next[N << 1], v[N << 1], adjlen = 1;
double q[N], w[N << 1], ans;
void link(int a, int b, double c)
{
    v[adjlen] = b;
    w[adjlen] = c;
    next[adjlen] = first[a];
    first[a] = adjlen++;
    v[adjlen] = a;
    w[adjlen] = c;
    next[adjlen] = first[b];
    first[b] = adjlen++;
}
double f_[N];
void dfs1(int u, int fa)
{
    f_[u] = 1 - q[u];
    for(int i = first[u]; i; i = next[i])
    {
        if(v[i] == fa)
            continue;
        dfs1(v[i], u);
        f_[u] *= 1 - w[i] * (1 - f_[v[i]]);
    }
}
void dfs2(int u, int fa)
{
    for(int i = first[u]; i; i = next[i])
    {
        if(v[i] == fa)
            continue;
        double tmp = 1 - w[i] * (1 - f_[v[i]]);
        if (tmp > 0.0000001)
            f_[v[i]] *= 1 - w[i] * (1 - f_[u] / tmp);
        dfs2(v[i], u);
    }
}
int main()
{
    scanf("%d", &n);
    for(int i = 0; i < n - 1; ++i)
    {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        link(a, b, (double)c / 100);
    }
    for(int i = 1; i <= n; ++i)
    {
        int a;
        scanf("%d", &a);
        q[i] = (double)a / 100;
    }
    dfs1(1, 0);
    dfs2(1, 0);
    ans = n;
    for(int i = 1; i <= n; ++i)
        ans -= f_[i];
    printf("%.6f\n", ans);
    return 0;
}
