#include <cstdio>
#include <iostream>
#include <queue>
#include <vector>
#include <string>
using namespace std;
const int N = 1e5 + 5;
int n, m, id, t[N][26], tree[N], begin[N], end[N], tick, ans[N], pos[N], fa[N], fail[N];
string s;
queue<int> q;
vector<int> g[N], query[N], index[N];
inline int lowbit(int x)
{
	return x & -x;
}
void add(int x, int v)
{
	for(; x < N; x += lowbit(x))
		tree[x] += v; 
}
int ask(int x)
{
	int res = 0;
	for(; x; x -= lowbit(x))
		res += tree[x];
	return res;
}
void dfs(int u)
{
	begin[u] = ++tick;
	for(int i = 0; i < g[u].size(); ++i)
		dfs(g[u][i]);
	end[u] = tick;
}
int main()
{
	cin >> s;
	int p = 0;
	for(int i = 0; i < s.length(); ++i)
	{
		int c = s[i] - 'a';
		if(s[i] == 'P')
			pos[++id] = p;
		else if(s[i] == 'B')
			p = fa[p];
		else
		{
			if(!t[p][c])
			{
				t[p][c] = ++m;
				fa[m] = p;
			}
			p = t[p][c];
		}
	}
	fail[0] = 0;
	for(int c = 0; c < 26; ++c)
	{
		int u = t[0][c];
		if(u)
		{
			q.push(u);
			fail[u] = 0;
			g[0].push_back(u);
		}
	}
	while(!q.empty())
	{
		int u = q.front(), v;
		q.pop();
		for(int c = 0; c < 26; ++c)
		{
			v = t[u][c];
			if(v)
			{
				fail[v] = t[fail[u]][c];
				g[t[fail[u]][c]].push_back(v);
				q.push(v);
			}
			else
				t[u][c] = t[fail[u]][c];
		}
	}
	dfs(0);
	cin >> m;
	for(int i = 0; i < m; ++i)
	{
		int x, y;
		scanf("%d%d", &x, &y);
		query[y].push_back(pos[x]);
		index[y].push_back(i);
	}
	int y = 0;
	p = 0;
	for(int i = 0; i < s.length(); ++i)
	{
		if(s[i] == 'P')
		{
			++y;
			for(int i = 0; i < query[y].size(); ++i)
				ans[index[y][i]] = ask(end[query[y][i]]) - ask(begin[query[y][i]] - 1);
		} 
		else if (s[i] == 'B')
		{
			add(begin[p], -1);
			p = fa[p];
		}
		else
		{
			p = t[p][s[i] - 'a'];
			add(begin[p], 1);
		}
	}
	for(int i = 0; i < m; ++i)
		printf("%d\n", ans[i]);
}
