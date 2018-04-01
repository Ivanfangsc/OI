#include <cstdio>
#include <iostream>
using namespace std;
const int N = 200005;
int l[N], r[N], f[N], n, m;
int q[N], head = 0, tail = 1;
int main()
{
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n + 1; ++i)
        r[i] = i - 1;
    for(int i = 0, a, b; i < m; ++i)
    {
        scanf("%d%d", &a, &b);
        l[b + 1] = max(l[b + 1], a);
        r[b] = min(r[b], a - 1);
    }
    for(int i = 2; i <= n + 1; ++i)
        l[i] = max(l[i], l[i - 1]);
    for(int i = n; i >= 1; --i)
        r[i] = min(r[i + 1], r[i]);
    for(int i = 1, j = 1; i <= n + 1; ++i)
    {
        while(j <= r[i] && j <= n)
        {
            if(f[j] == -1)
            {
                ++j;
                continue;
            }
            while(f[j] > f[q[head]] && head < tail)
                --tail;
            q[tail++] = j++;
        }
        while(q[head] < l[i] && head < tail)
            ++head;
        f[i] = head < tail ? f[q[head]] + 1: -1;
    }
    printf("%d\n", f[n + 1] != -1 ? f[n + 1] - 1 : -1);
}
