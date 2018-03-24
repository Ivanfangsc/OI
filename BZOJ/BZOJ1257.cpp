#include <cstdio>
#include <iostream>
using namespace std;
long long ans, n, k;
int main()
{
	scanf("%lld%lld", &n, &k);
	ans = n * k;
	if(n > k)
		n = k;
	for(long long i = 1, x; i <= n; i = x + 1)
	{
		x = min(k / (k / i), n);
		ans -= k / x * (i + x) * (x - i + 1) / 2;
	}
	printf("%lld\n", ans);
	return 0;
} 
