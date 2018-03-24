#include <cstdio>
#include <iostream>
#include <queue>
#include <cstring>
using namespace std;
const int INF = 2147483647, MAXN = 1050, MAXE = 30050;
int first[MAXN], next[MAXE], v[MAXE], w[MAXE], r[MAXE], edge = 1;
void link(int a, int b, int c, int d)
{
	next[++edge] = first[a];
	first[a] = edge;
	v[edge] = b;
	r[edge] = c;
	w[edge] = d;
	next[++edge] = first[b];
	first[b] = edge;
	v[edge] = a;
	r[edge] = 0;
	w[edge] = -d;
}
int s, t, d[MAXN], pre[MAXN];
long long maxflow = 0, mincost = 0;
queue<int> q;
bool spfa()
{
	memset(d, 127, sizeof(d));
	d[s] = 0;
	q.push(s);
	while(!q.empty())
	{
		int u = q.front();
		q.pop();
		for(int e = first[u]; e; e = next[e])
			if(d[u] + w[e] < d[v[e]] && r[e])
			{
				pre[v[e]] = e;
				q.push(v[e]);
				d[v[e]] = d[u] + w[e];
			}
	}
	return d[t] != d[0];
}
void augment()
{
	int delta = INF;
	for(int u = t; u != s; u = v[pre[u] ^ 1])
		delta = min(delta, r[pre[u]]);
	for(int u = t; u != s; u = v[pre[u] ^ 1])
	{
		mincost += w[pre[u]] * delta;
		r[pre[u]] -= delta;
		r[pre[u] ^ 1] += delta;
	}
	maxflow += delta;
}
int n, m, c[MAXN];
int main()
{
	scanf("%d%d", &n, &m);
	s = n + 2;
	t = s + 1;
	for(int i = 1; i <= n; ++i)
		scanf("%d", &c[i]);
	link(1, t, c[1], 0);
	for(int i = 2; i <= n; ++i)
		if(c[i] > c[i - 1])
			link(i, t, c[i] - c[i - 1], 0);
		else
			link(s, i, c[i - 1] - c[i], 0);
	link(s, n + 1, c[n], 0);
	for(int i = 1; i <= n; ++i)
		link(i, i + 1, INF, 0);
	for(int i = 0; i < m; ++i)
	{
		int x, y, z;
		scanf("%d%d%d", &x, &y, &z);
		link(y + 1, x, INF, z);
	}
	while(spfa())
		augment();
	printf("%lld\n", mincost);
	return 0;
}
