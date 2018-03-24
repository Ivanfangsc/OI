#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>
using namespace std;
const int MAXM = 10005, MAXN = 10005;
int block_len, q_num, m_num;
struct query
{
	int l, r, t, id, block;
	void operator() (int l_, int r_, int t_, int id_)
	{
		l = l_;
		r = r_;
		t = t_;
		id = id_;
		block = l / block_len;
	}
	bool operator< (query &other)
	{
		if (block != other.block)
			return block < other.block;
		if (r != other.r)
			return r < other.r;
		return t > other.t;
	}
} queries[MAXM];
struct mod
{
	int v, pos;
	void operator() (int v_, int pos_)
	{
		v = v_;
		pos = pos_;
	} 
} mods[MAXM];
int color[MAXN], n, m, ans[MAXM], s[1000005];
int main()
{
	scanf("%d%d", &n, &m); 
	block_len = sqrt(n);
	for (int i = 1; i <= n; ++i)
		scanf("%d", &color[i]);
	for (int i = 0; i < m; ++i) 
	{
		char cmd[10];
		int a, b;
		scanf("%s%d%d", cmd, &a, &b);
		if (cmd[0] == 'Q')
			queries[q_num](a, b, m_num, q_num), ++q_num;
		else
			mods[++m_num](b, a);
	}
	sort(queries, queries + q_num);
	int l = 1, r = 0, t = 0, cur = 0;
	for (int i = 0; i < q_num; ++i)
	{
		query &q = queries[i];
		while (r < q.r)
			if (!s[color[++r]]++)
				++cur;
		while (q.l < l)
			if (!s[color[--l]]++)
				++cur;
		while (q.r < r)
			if (!--s[color[r--]])
				--cur;
		while (l < q.l)
			if (!--s[color[l++]])
				--cur;
		while (t != q.t)
		{
			if(t < q.t)
				++t;
			if (l <= mods[t].pos && mods[t].pos <= r)
			{
				if (!s[mods[t].v]++)
					++cur;
				if (!--s[color[mods[t].pos]])
					--cur;
			}
			swap(mods[t].v, color[mods[t].pos]);
			if(q.t < t)
				--t;
		}
		ans[q.id] = cur;
	}
	for (int i = 0; i < q_num; ++i)
		printf("%d\n", ans[i]);
	return 0;
} 
