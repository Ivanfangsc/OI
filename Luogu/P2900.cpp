#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
struct land
{
	int l, w;
	bool operator < (const land &other) const
	{
		if(w == other.w)
			return l > other.l;
		else
			return w > other.w;
	}
} lands[50005];
int n, nt, ch[50005], head, tail = 1;
long long x[50005], y[50005];
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i)
		scanf("%d%d", &lands[i].l, &lands[i].w);
	sort(lands + 1, lands + n + 1);
	for(int i = 1; i <= n; ++i)
	{
		lands[++nt] = lands[i];
		while(i < n && lands[nt].l >= lands[i + 1].l)
			++i;
	}
	x[0] = -lands[1].w;
	for(int i = 1; i <= nt; ++i)
	{
		int k = lands[i].l;
		while(tail - head >= 2)
		{
			int a = ch[head], b = ch[head + 1];
			if(-k * x[a] + y[a] >= -k * x[b] + y[b])
				++head;
			else
				break;
		}
		y[i] = -k * x[ch[head]] + y[ch[head]];
		x[i] = -lands[i + 1].w;
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
	printf("%lld\n", y[nt]);
	return 0;
}
