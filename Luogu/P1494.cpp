#include <cstdio>
#include <iostream> 
#include <algorithm>
#include <cstring>
#include <cmath>
using namespace std;
const int MAXN = 50005, MAXM = 50005;
void simplify(long long &a, long long &b)
{
	long long x = a, y = b, t;
	if (x < y)
		swap(x, y);
	while (true)
	{
		if (!y)
		{
			a /= x;
			b /= x;
			return;
		}
		t = y;
		y = x % y;
		x = t;
	}
}
int block_len;
struct query
{
	int l, r, id, block;
	void operator() (int l_, int r_, int id_)
	{
		l = l_;
		r = r_;
		id = id_;
		block = l / block_len;
	}
	bool operator < (query &other)
	{
		if (block == other.block)
			return r < other.r;
		return block < other.block;
	}
} queries[MAXM];
int color[MAXN], n, m;
long long ans[MAXM][2];
int main()
{
	scanf("%d%d", &n, &m);
	block_len = sqrt(m);
	for (int i = 0; i < n; ++i)
		scanf("%d", &color[i]);
	for (int i = 0; i < m; ++i)
	{
		int l, r;
		scanf("%d%d", &l, &r);
		queries[i](l - 1, r - 1, i);
	}
	sort(queries, queries + m);
	int l = 1, r = 0, t[MAXN];
	long long cur = 0;
	memset(t, 0, sizeof(t)); 
	for (int i = 0; i < m; ++i)
	{
		query &q = queries[i];
		if (q.l == q.r)
		{
			ans[q.id][0] = 0;
			ans[q.id][1] = 1;
			continue;
		}
		while (l < q.l)
			cur -= (--t[color[l++]]) * 2 + 1;
		while (q.l < l)
			cur += (t[color[--l]]++) * 2 + 1;
		while (r < q.r)
			cur += (t[color[++r]]++) * 2 + 1;
		while (q.r < r)
			cur -= (--t[color[r--]]) * 2 + 1;
		simplify(ans[q.id][0] = cur - (r - l + 1), ans[q.id][1] = (long long)(r - l + 1) * (r - l));
	} 
	for (int i = 0; i < m; ++i)
		printf("%lld/%lld\n", ans[i][0], ans[i][1]);
	return 0;
}
