#include <cstdio>
#include <iostream>
using namespace std;
typedef long long ll;
const int P = 100005;
ll n, m, p;
ll f[P];
ll pow(ll a, ll b)
{
    ll res = 1;
    while(b)
    {
        if(b & 1)
            res = res * a % p;
        b >>= 1;
        a = a * a % p;
    }
    return res;
}
ll c(int n, int m)
{
    return f[n] * pow(f[m] * f[n - m] % p, p - 2) % p;
}
ll lucas(int n, int m)
{
    ll res = 1;
    while(n && m)
    {
        if(n % p < m % p)
            return 0;
        res = res * c(n % p, m % p) % p;
        n /= p;
        m /= p;
    }
    return res;
}
int T;
int main()
{
    scanf("%d", &T);
    while(T--)
    {
        scanf("%lld%lld%lld", &n, &m, &p);
        f[0] = 1;
        for(ll i = 1; i <= p; ++i)
            f[i] = f[i - 1] * i % p;
        printf("%lld\n", lucas(n + m, m));
    }
}
