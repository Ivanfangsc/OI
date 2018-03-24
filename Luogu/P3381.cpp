#include <cstdio>
#include <iostream>
#include <queue>
#include <cstring>
using namespace std;
const int INF = 2147483647, MAXN = 5005, MAXE = 100005;
int first[MAXN], next[MAXE], r[MAXE], w[MAXE], v[MAXE], edge = 1;
void link(int x, int y, int z, int f)
{
	next[++edge] = first[x];
	r[edge] = z;
	w[edge] = f;
	v[edge] = y;
	first[x] = edge;
	next[++edge] = first[y];
	r[edge] = 0;
	w[edge] = -f;
	v[edge] = x;
	first[y] = edge;
} 
int d[MAXN], s, t, pre[MAXN];
long long maxflow = 0, mincost = 0; 
queue<int> q;
bool spfa()
{
	memset(d, 127, sizeof(d));
	q.push(s);
	d[s] = 0;
	while(!q.empty())
	{
		int u = q.front();
		q.pop();
		for(int e = first[u]; e; e = next[e])
			if(r[e] && d[v[e]] > d[u] + w[e])
			{
				d[v[e]] = d[u] + w[e];
				pre[v[e]] = e;
				q.push(v[e]); 
			}
	} 
	return d[t] != d[0];
}
void augment(int delta = INF)
{
	for(int u = t; u != s; u = v[pre[u] ^ 1])
		delta = min(delta, r[pre[u]]);
	for(int u = t; u != s; u = v[pre[u] ^ 1])
	{
		r[pre[u]] -= delta;
		r[pre[u] ^ 1] += delta;
		mincost += delta * w[pre[u]];
	}
	maxflow += delta;
}
int n, m;
int main()
{
	scanf("%d%d%d%d", &n, &m, &s, &t);
	for(int i = 0; i < m; ++i)
	{
		int a, b, c, f;
		scanf("%d%d%d%d", &a, &b, &c, &f);
		link(a, b, c, f);
	}
	while(spfa())
		augment();
	printf("%lld %lld\n", maxflow, mincost);
	return 0;
}
