#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;
typedef long long ll;
const int MOD = 20101009, MAXN = 10000010;
int mu[MAXN], prime[MAXN], sum[MAXN];
bool notprime[MAXN];
void get_mu(int max)
{
	int pnum = 0;
	mu[1] = 1;
	for(int i = 2; i <= max; ++i)
	{
		if(!notprime[i])
		{
			prime[pnum++] = i;
			mu[i] = -1;
		}
		for(int j = 0; j < pnum && i * prime[j] <= max; ++j)
		{
			notprime[i * prime[j]] = true;
			if(i % prime[j] == 0)
			{
				mu[i * prime[j]] = 0;
				break;
			}
			mu[i * prime[j]] = -mu[i];
		}
	}
	for(int i = 1; i <= max; ++i)
		sum[i] = (sum[i - 1] + (ll)i * i % MOD * mu[i]) % MOD;
}
int s(int x, int y)
{
	return (((ll)x * (x + 1) / 2 % MOD) * ((ll)y * (y + 1) / 2 % MOD)) % MOD;
}
int solve(int n, int m)
{
	int res = 0;
	for(int x = 1, xt; x <= n; x = xt + 1)
	{
		xt = min(n / (n / x), m / (m / x));
		res = (res + (sum[xt] - sum[x - 1] + MOD) % MOD * (ll)s(n / x, m / x) % MOD) % MOD;
	}
	return res;
}
int n, m, ans = 0;
int main()
{
	scanf("%d%d", &n, &m);
	if(n > m)
	{
		int ttt = m;
		m = n;
		n = ttt;
	}
	get_mu(n);
	for(int x = 1, last; x <= n; x = last + 1)
	{
		last = min(n / (n / x), m / (m / x));
		ans = (ans + (ll)(x + last) * (last - x + 1) / 2 % MOD * solve(n / x, m / x) % MOD) % MOD;
	}
	printf("%d\n", ans);
	return 0;
}
