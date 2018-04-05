#include <cstdio>
#include <iostream>
#include <cstring>
using namespace std;
const int N = 1010;
int n, a[N], b[N], c[N][N],f[N];
int main()
{
    memset(f, 127, sizeof(f));
    scanf("%d", &n);
    for(int i = 0; i < n; ++i)
    {
        scanf("%d%d", &a[i], &b[i]);
        ++c[a[i] + 1][n - b[i]];
    }
    f[0] = 0;
    for(int i = 1; i <= n; ++i)
        for(int j = 1; j < i; ++j)
            for(int k = 0; k < j; ++k)
                f[i] = min(f[i], f[k] + c[j][i]);
    return 0;
}
