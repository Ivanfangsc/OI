#include <cstdio>
#include <iostream>
#include <queue>
#include <cstring>
#define INF 9223372036854775807ll
using namespace std;
const int MAXE = 485000, MAXN = 20005;
struct adjlist
{
	int first[MAXN], next[MAXE], v[MAXE], len;
	long long w[MAXE];
	adjlist()
	{
		memset(first, 0, sizeof(first));
		memset(next, 0, sizeof(next));
		len = 1;
	}
	void link(int x, int y, long long z)
	{
		next[++len] = first[x];
		w[len] = z;
		v[len] = y;
		first[x] = len;
		next[++len] = first[y];
		w[len] = z;
		v[len] = x;
		first[y] = len;
	}
} r;
int m, n;
long long ans = 0;
int d[MAXN], cur[MAXN], s, t;
queue<int> q;
bool bfs()
{
	memset(d, 0, sizeof(d));
	d[t] = 1;
	q.push(t);
	while(!q.empty())
	{
		int v = q.front();
		q.pop();
		for(int e = r.first[v]; e; e = r.next[e])
		{
			int u = r.v[e];
			if(!d[u] && r.w[e ^ 1])
			{
				d[u] = d[v] + 1;
				q.push(u);
			}
		}
	}
	return d[s];
}
long long dfs(int u, long long budget)
{
	if(u == t)
		return budget;
	int res = 0;
	for(int &e = cur[u]; e; e = r.next[e]) 
		if(d[r.v[e]] + 1 == d[u] && r.w[e])
		{
			long long delta = dfs(r.v[e], min(budget, r.w[e]));
			res += delta;
			budget -= delta;
			r.w[e] -= delta; 
			r.w[e ^ 1] += delta;
			if(!budget)
				break;
		}
	return res;
}
int main()
{
	cin >> n >> m;
	s = n + 1;
	t = s + 1;
	for(int i = 1; i <= n; ++i)
	{
		long long a, b;
		cin >> a >> b;
		r.link(s, i, a);
		r.link(i, t, b); 
	}
	for(int i = 1; i <= m; ++i)
	{
		int a, b;
		long long w;
		cin >> a >> b >> w;
		r.link(a, b, w);
	}
	while(bfs())
	{
		memcpy(cur, r.first, sizeof(cur));
		ans += dfs(s, INF);
	}
	cout << ans;
	return 0;
}
