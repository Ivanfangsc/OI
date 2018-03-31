#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
const int N = 75;
struct book
{
    int h, t;
    bool operator < (book other)
    {
        return h > other.h;
    }
} books[N];
int n, sum = 0, dp[2][2105][2105], k;
long long ans = 214748364;
int main()
{
    scanf("%d", &n);
    for(int i = 1; i <= n; ++i)
        scanf("%d%d", &books[i].h, &books[i].t);
    sort(books + 1, books + n + 1);
    memset(dp, 127, sizeof(dp));
    dp[0][0][0] = 0;
    for(int i = 1; i <= n; ++i)
    {
        memset(dp[1 - k], 127, sizeof(dp[1 - k]));
        for(int x = sum; x >= 0; --x)
            for(int y = sum - x; y >= 0; --y)
            if(dp[k][x][y] < 1000)
            {
                if(x)
                    dp[1 - k][x + books[i].t][y] = min(dp[1 - k][x + books[i].t][y], dp[k][x][y]);
                else
                    dp[1 - k][books[i].t][y] = min(dp[1 - k][books[i].t][y], dp[k][x][y] + books[i].h);
                if(y)
                    dp[1 - k][x][y + books[i].t] = min(dp[1 - k][x][y + books[i].t], dp[k][x][y]);
                else
                    dp[1 - k][x][books[i].t] = min(dp[1 - k][x][books[i].t], dp[k][x][y] + books[i].h);
                if(sum - x - y)
                    dp[1 - k][x][y] = min(dp[1 - k][x][y], dp[k][x][y]);
                else
                    dp[1 - k][x][y] = min(dp[1 - k][x][y], dp[k][x][y] + books[i].h);
            }
        sum += books[i].t;
        k = 1 - k;
    }
    for(int x = 1; x < sum; ++x)
        for(int y = 1; x + y < sum; ++y)
            ans = min(ans, max(sum - x - y, max(x, y)) * (long long)dp[k][x][y]);
    printf("%lld\n", ans);
    return 0;
}
