#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int P = 2333;
int c[P + 50][P + 50], sum[P + 50][P + 50];
int t;
int lucas(ll n, ll m)
{
    if(m)
        return lucas(n / P, m / P) * c[n % P][m % P] % P;
    else
        return 1;
}
int s(ll n, ll k)
{
    if(n && k)
    {
        int res = s(n / P, k / P);
        return (sum[n % P][k % P] * res % P + (sum[n % P][P - 1] - sum[n % P][k % P] + P) % P * (res - lucas(n / P, k / P) + P) % P) % P;
    }
    else
        return 1;
}
int main()
{
    sum[0][0] = c[0][0] = 1;
    for(int i = 1; i < P + 5; ++i)
    {
        sum[i][0] = c[i][0] = 1;
        for(int j = 1; j <= i; ++j)
            c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % P;
    }
    for(int i = 0; i < P + 5; ++i)
        for(int j = 1; j < P + 5; ++j)
            sum[i][j] = (sum[i][j - 1] + c[i][j]) % P;
    scanf("%d", &t);
    ll n, k;
    while(t--)
    {
        scanf("%lld%lld", &n, &k);
        printf("%d\n", s(n, k));
    }
}
