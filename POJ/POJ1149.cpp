#include <cstdio>
#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;
const int MAXE = 20005, MAXN = 1005;
int first[MAXN], next[MAXE], v[MAXE], w[MAXE], edge = 1;
void link(int x, int y, int z)
{
	next[++edge] = first[x];
	w[edge] = z;
	v[edge] = y;
	first[x] = edge;
	next[++edge] = first[y];
	w[edge] = 0;
	v[edge] = x;
	first[y] = edge;
}
int m, n, ans = 0, pig[MAXN], l[MAXN];
vector<int> k[105]; 
int d[MAXN], cur[MAXN], s, t;
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
		int u = q.front();
		q.pop();
		for(int e = first[u]; e; e = next[e])
		{
			if(!d[v[e]] && w[e ^ 1])
			{
				d[v[e]] = d[u] + 1;
				q.push(v[e]);
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
	for(int &e = cur[u]; e; e = next[e]) 
		if(d[v[e]] + 1 == d[u] && w[e])
		{
			int delta = dfs(v[e], min(budget, w[e]));
			res += delta;
			budget -= delta;
			w[e] -= delta; 
			w[e ^ 1] += delta;
			if(!budget)
				break;
		}
	return res;
}
int main()
{
	m = read();
	n = read();
	s = n + 1;
	t = n + 2;
	for(int i = 1; i <= m; ++i)
		pig[i] = read();
	for(int i = 1; i <= n; ++i)
	{
		int a = read();
		while(a--)
			k[i].push_back(read());
		link(i, t, read());
	}
	for(int i = 1; i <= n; ++i)
		for(vector<int>::const_iterator iter = k[i].begin(); iter != k[i].end(); ++iter)
			if(!l[*iter])
			{
				l[*iter] = i;
				link(s, i, pig[*iter]);
			}
			else
			{
				link(l[*iter], i, INT_MAX);
				l[*iter] = i;
			}
	while(bfs())
	{
		memcpy(cur, first, sizeof(cur));
		ans += dfs(s, INT_MAX);
	}
	printf("%d\n", ans);
	return 0;
}
