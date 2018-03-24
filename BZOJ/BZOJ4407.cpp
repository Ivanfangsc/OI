#include <cstdio>
#include <iostream>
#include <cmath>
using namespace std;
typedef long long ll;
const int MAXN = 5000010, MOD = 1000000007;
bool notprime[MAXN];
int h[MAXN], sum[MAXN], ans, prime[MAXN], t, k, n, m, pnum = 0;
int power(int x, int y)
{
	int res = 1;
	while(y)
	{
		if(y & 1)
			res = (ll)res * x % MOD;
		x = (ll)x * x % MOD;
		y >>= 1;
	}
	return res;
}
int main()
{
	scanf("%d%d", &t, &k);
	h[1] = sum[1] = 1;
	for(int i = 2; i < MAXN; ++i)
	{
		if(!notprime[i])
		{
			prime[pnum++] = i;
			h[i] = power(i, k) - 1;
		}
		for(int j = 0; j < pnum && (ll)i * prime[j] < MAXN; ++j)
		{
			notprime[i * prime[j]] = true;
			if(i % prime[j] == 0)
			{
				h[i * prime[j]] = (ll)h[i] * (h[prime[j]] + 1) % MOD;
				break;
			}
			h[i * prime[j]] = (ll)h[i] * h[prime[j]] % MOD;
		}
		sum[i] = (sum[i - 1] + h[i]) % MOD;
	}
	while(t--)
	{
		ans = 0;
		scanf("%d%d", &n, &m); 
		if(n > m)
		{
			int ttt = m;
			m = n;
			n = ttt;
		}
		for(int x = 1, last; x <= n; x = last + 1)
		{
			last = min(n / (n / x), m / (m / x));
			ans = (ans + (ll)(n / x) * (m / x) % MOD * (sum[last] - sum[x - 1]) % MOD) % MOD;
		}
		printf("%d\n", (ans + MOD) % MOD);
	}
	return 0;
}
