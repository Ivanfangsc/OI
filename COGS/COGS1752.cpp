#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;
int w, m, ans[50000];
int tree[2000001];
inline int lowbit(const int x)
{
	return x & (-x);
}
void add(int x, int k)
{
	for(; x <= w; x += lowbit(x))
		tree[x] += k;
}
int sum(int x)
{
	int s = 0;
	for(; x; x -= lowbit(x))
		s += tree[x];
	return s;
}
struct op
{
	int type, x, y, k, id;
	op(int a, int b, int c, int d, int e):type(a), x(b), y(c), k(d), id(e) {}
};
vector<op> q;
void solve(int left, int right, vector<op> &qt)
{
	if(qt.empty())
		return;
	if(right - left == 1)
	{
		for(vector<op>::const_iterator iter = qt.begin(); iter != qt.end(); ++iter)
			if(iter->type == 1)
				add(iter->y, iter->k);
			else
				ans[iter->id] += sum(iter->y);
		for(vector<op>::const_iterator iter = qt.begin(); iter != qt.end(); ++iter)
			if(iter->type == 1)
				add(iter->y, -iter->k);
		return;
	}
	vector<op> ql, qr;
	int mid = (left + right) >> 1;
	for(vector<op>::const_iterator iter = qt.begin(); iter != qt.end(); ++iter)
		if(iter->x < mid)
		{
			ql.push_back(*iter);
			if(iter->type == 1)
				add(iter->y, iter->k);
		}
		else
		{
			qr.push_back(*iter);
			if(iter->type == 2)
				ans[iter->id] += sum(iter->y);
		}
	for(vector<op>::const_iterator iter = ql.begin(); iter != ql.end(); ++iter)
		if(iter->type == 1)
			add(iter->y, -iter->k);
	solve(left, mid, ql);
	solve(mid, right, qr);
}
int main()
{
	freopen("mokia.in", "r", stdin);
	freopen("mokia.out", "w", stdout);
	scanf("%*d%d", &w);
	int cmd, a, b, c, d;
	scanf("%d", &cmd);
	while(cmd != 3)
	{
		scanf("%d%d%d", &a, &b, &c);
		if(cmd == 1)
			q.push_back(op(1, a, b, c, 0));
		else
		{
			scanf("%d", &d);
			q.push_back(op(2, a - 1, b - 1, 0, 4 * m + 1));
			q.push_back(op(2, a - 1, d, 0, 4 * m + 2));
			q.push_back(op(2, c, b - 1, 0, 4 * m + 3));
			q.push_back(op(2, c, d, 0, 4 * m + 4));
			++m;
		}
		scanf("%d", &cmd);
	}
	solve(1, w + 1, q);
	for(int i = 0; i < m; ++i)
		printf("%d\n", ans[4 * i + 4] - ans[4 * i + 3] - ans[4 * i + 2] + ans[4 * i + 1]);
	return 0;
} 
