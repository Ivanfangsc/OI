#include <cstdio>
#include <iostream>
using namespace std;
int n, s, t[5005], f[5005], ts[5005], fs[5005], ch[5005], head, tail = 1;
long long x[5005], y[5005], dp[5005];
int main()
{
	freopen("batch.in", "r", stdin);
	freopen("batch.out", "w", stdout);
	scanf("%d%d", &n, &s);
	for(int i = 1; i <= n; ++i)
		scanf("%d%d", &t[i], &f[i]);
	for(int i = n; i >= 1; --i)
	{
		ts[i] = ts[i + 1] + t[i];
		fs[i] = fs[i + 1] + f[i];
	}
	for(int i = n; i >= 1; --i)
	{
		int k = fs[i];
		while(tail - head >= 2)
		{
			int a = ch[head], b = ch[head + 1];
			if(-k * x[a] + y[a] >= -k * x[b] + y[b])
				++head;
			else
				break;
		}
		y[i] = -k * x[ch[head]] + y[ch[head]] + fs[i] * (ts[i] + s);
		x[i] = ts[i];
		while(tail - head >= 2)
		{
			int a = ch[tail - 2], b = ch[tail - 1];
			if((y[b] - y[a]) * (x[i] - x[b]) >= (y[i] - y[b]) * (x[b] - x[a]))
				--tail;
			else
				break;
		}
		ch[tail++] = i;
	}
	printf("%lld\n", y[1]);
	fclose(stdin);
	fclose(stdout);
	return 0;
} 
