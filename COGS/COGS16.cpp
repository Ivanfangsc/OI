#include <cstdio>
#include <iostream>
#include <algorithm> 
using namespace std;
const int MAXN = 100005;
int n, s, q[MAXN], t[MAXN], ch[MAXN];
double a[MAXN], b[MAXN], r[MAXN], f[MAXN], g[MAXN];
bool sortcmp(int x, int y)
{
	return b[x] * a[y] < a[x] * b[y];
}
void solve(int left, int right)
{
	if(right - left == 1)
	{
		if (left > 0 && f[left] < f[left - 1]) 
		{
	  		f[left] = f[left-1];
	  		g[left] = f[left] / (a[left]*r[left] + b[left]);
		}
		return;
	}
	int mid = (left + right) >> 1;
	for(int i = left, j = mid, k = left; k < right; ++k)
		if(q[k] < mid)
			t[i++] = q[k];
		else
			t[j++] = q[k];
	for(int i = left; i < right; ++i)
		q[i] = t[i];
	solve(left, mid);
	int head = 0, tail = 0;
	for(int i = left; i < mid; ++i)
	{
		int z = q[i];
		while(tail >= 2)
		{
			int x = ch[tail - 2], y = ch[tail - 1];
			if((g[y] * r[y] - g[x] * r[x]) * (g[z] - g[y]) <= (g[z] * r[z] - g[y] * r[y]) * (g[y] - g[x]))
				--tail;
			else
				break;
		}
		ch[tail++] = z;
	}
	for(int i = mid; i < right; ++i)
	{
		int j = ch[head];
		double max1 = g[j] * b[q[i]] + g[j] * r[j] * a[q[i]];
		while(tail - head >= 2)
		{
			int j2 = ch[head + 1];
			double max2 = g[j2] * b[q[i]] + g[j2] * r[j2] * a[q[i]];
			if(max1 <= max2)
			{
				j = j2;
				max1 = max2;
				++head;
			}
			else
				break;
		}
		if(f[q[i]] < max1)
		{
			f[q[i]] = max1;
			g[q[i]] = max1 / (a[q[i]] * r[q[i]] + b[q[i]]);
		}
	}
	solve(mid, right);
	for(int i = left, j = mid, k = left; k < right; ++k)
	{
		if(i < mid && (j == right || g[q[i]] < g[q[j]]))
			t[k] = q[i++];
		else
			t[k] = q[j++];
	}
	for(int i = left; i < right; ++i)
		q[i] = t[i];
}
int main()
{
	freopen("cash.in", "r", stdin);
	freopen("cash.out", "w", stdout);
	scanf("%d%d", &n, &s);
	for(int i = 0; i < n; ++i)
	{
		scanf("%lf%lf%lf", &a[i], &b[i], &r[i]);
		q[i] = i;
	}
	f[0] = s;
	g[0] = s / (a[0] * r[0] + b[0]);
	sort(q, q + n, sortcmp);
	solve(0, n);
	printf("%.3lf\n", f[n - 1]);
	return 0;
} 
