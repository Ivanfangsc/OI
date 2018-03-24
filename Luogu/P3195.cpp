#include <cstdio>
#include <iostream>
#include <cmath>
#define SQR(x) ((x) * (x))
using namespace std;
int n, l, c[50005], ch[50005], head, tail = 1;
long long x[50005], y[50005], f[50005], s[50005];
int main()
{
	scanf("%d%d", &n, &l);
	for(int i = 1; i <= n; ++i)
	{
		scanf("%d", &c[i]);
		s[i] = s[i - 1] + c[i];
	}
	for(int i = 1; i <= n; ++i)
	{
		int k = 2 * (s[i] + i - l - 1);
		while(tail - head >= 2)
		{
			int a = ch[head], b = ch[head + 1];
			if(-k * x[a] + y[a] >= -k * x[b] + y[b])
				++head;
			else
				break;
		}
		f[i] = - k * x[ch[head]] + y[ch[head]] + SQR(s[i] + i - l - 1);
		x[i] = s[i] + i;
		y[i] = f[i] + SQR(s[i] + i);
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
	printf("%lld\n", f[n]);
	return 0;
} 
