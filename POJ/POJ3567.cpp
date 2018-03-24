#include <cstdio>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
const int MAXN = 50010;
vector<int> G[MAXN];
int low[MAXN], dfn[MAXN], d[MAXN], c[MAXN << 1], p[MAXN], tick = 0, n, m, ans = 0;
int head, tail, q[MAXN << 1], v[MAXN << 1];
void task(int k)
{
	for(int i = 0; i < k; ++i)
		c[i + k] = c[i];
	head = 0;
	tail = 0;
	for(int i = k - k / 2; i <= k - 1; ++i)
	{
		v[i] = d[c[i]] - i;
		while(head < tail && v[q[tail - 1]] <= v[i])
			--tail;
		q[tail++] = i;
	}
	for(int i = k; i < 2 * k; ++i)
	{
		if(q[head] < i - k / 2)
			++head;
		ans = max(ans, d[c[i]] + i + v[q[head]]);
		v[i] = d[c[i]] - i;
		while(head < tail && v[q[tail - 1]] <= v[i])
			--tail;
		q[tail++] = i;
	}
}
void dfs(int u)
{
	dfn[u] = low[u] = ++tick;
	for(int i = 0; i < G[u].size(); ++i)
	{
		int v = G[u][i];
		if(v != p[u]) 
		{
			if(dfn[v] == 0)
			{
				p[v] = u;
				dfs(v);
				low[u] = min(low[u], low[v]);
			}
			else
				low[u] = min(low[u], dfn[v]);
		}
	}
	for(int i = 0; i < G[u].size(); ++i)
	{
		int v = G[u][i];
		if(p[v] == u && low[v] > dfn[u])
		{
			ans = max(ans, d[u] + d[v] + 1);
			d[u] = max(d[u], d[v] + 1);
		}
		if(p[v] != u && dfn[u] < dfn[v])
		{
			c[0] = u;
			int k = 1;
			for(int j = v; j != u; j = p[j])
				c[k++] = j;
			task(k);
			for(int j = 1; j < k; ++j)
				d[u] = max(d[c[j]] + min(j, k - j), d[u]);
		}
	}
}
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 0; i < m; ++i)
	{
		int k, a, b;
		scanf("%d%d", &k, &a);
		for(int j = 1; j < k; ++j)
		{
			scanf("%d", &b);
			G[a].push_back(b);
			G[b].push_back(a);
			a = b;
		}
	}
	dfs(1);
	printf("%d\n", ans);
	return 0;
} 
