#include <bits/stdc++.h>
using namespace std;
struct adjlist
{
	int first[50000], next[50000], v[50000], w[50000], len;
	adjlist()
	{
		memset(first, 0, sizeof(first));
		memset(next, 0, sizeof(next));
		len = 1;
	}
	void link(int x, int y)
	{
		next[++len] = first[x];
		w[len] = 1;
		v[len] = y;
		first[x] = len;
		next[++len] = first[y];
		w[len] = 0;
		v[len] = x;
		first[y] = len;
	}
} r;
int n, food, drink, ans = 0;
int d[405], cur[405], s, t;
int read()
{
	int x = 0;
	char ch = getchar();
	while(ch < '0' || '9' < ch)
		ch = getchar();
	while('0' <= ch && ch <= '9')
	{
		x = (x << 3) + (x << 1) + ch - '0';
		ch = getchar();
	}
	return x;
}
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
int dfs(int u, int budget)
{
	if(u == t)
		return budget;
	int res = 0;
	for(int &e = cur[u]; e; e = r.next[e]) 
		if(d[r.v[e]] + 1 == d[u] && r.w[e])
		{
			int delta = dfs(r.v[e], min(budget, r.w[e]));
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
	n = read();
	food = read();
	drink = read();
	s = food + 2 * n + drink + 1;
	t = s + 1;
	for(int i = 1; i <= n; ++i)
	{
		int x, y;
		scanf("%d%d", &x, &y);
		while(x--)
			r.link(read(), food + i);
		while(y--)
			r.link(food + n + i, read() + food + 2 * n);
		r.link(food + i, food + n + i);
	}
	for(int i = 1; i <= food; ++i)
		r.link(s, i);
	for(int i = 1; i <= drink; ++i)
		r.link(food + 2 * n + i, t);
	while(bfs())
	{
		memcpy(cur, r.first, sizeof(cur));
		ans += dfs(s, INT_MAX);
	}
	printf("%d\n", ans);
	return 0;
}
