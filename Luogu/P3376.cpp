#include <cstdio>
#include <iostream>
#include <queue>
#include <cstring>
using namespace std;
const int INF = 2147483647, MAXN = 10005, MAXE = 200005;
int first[MAXN], next[MAXE], r[MAXE], v[MAXE], edge = 1;
void link(int x, int y, int z)
{
	next[++edge] = first[x];
	r[edge] = z;
	v[edge] = y;
	first[x] = edge;
	next[++edge] = first[y];
	r[edge] = 0;
	v[edge] = x;
	first[y] = edge;
}
int s, t, d[MAXN], cur[MAXN];
long long ans = 0; 
queue<int> q;
bool bfs()
{
	memset(d, 0, sizeof(d));
	d[t] = 1;
	q.push(t);
	while(!q.empty())
	{
		int u = q.front();
		q.pop();
		for(int e = first[u]; e; e = next[e])
			if(!d[v[e]] && r[e ^ 1])
			{
				d[v[e]] = d[u] + 1;
				q.push(v[e]);
			}
	}
	return d[s];
}
int dfs(int u, int budget)
{
	if(u == t)
		return budget;
	int res = 0;
	for(int &e = cur[u]; e; e = next[e])
		if(d[v[e]] + 1 == d[u] && r[e])
		{
			int delta = dfs(v[e], min(budget, r[e]));
			r[e] -= delta;
			r[e ^ 1] += delta;
			budget -= delta;
			res += delta;
			if(!budget)
				break;
		}
	return res;
}
void dinic()
{
	memcpy(cur, first, sizeof(cur));
	ans += dfs(s, INF);
}
int n, m;
int main()
{
	scanf("%d%d%d%d", &n, &m, &s, &t);
	for(int i = 0; i < m; ++i)
	{
		int a, b, c;
		scanf("%d%d%d", &a, &b, &c);
		link(a, b, c);
	}
	while(bfs())
		dinic();
	printf("%lld\n", ans);
	return 0;
} 
