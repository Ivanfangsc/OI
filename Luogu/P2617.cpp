#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;
const int MAXN = 10005;
int n, m, a[MAXN], tree[MAXN], ans[MAXN];

inline int lowbit(const int x)
{
	return x&(-x);
}

void add(int x, int k)
{
	for(;x <= n; x += lowbit(x))
		tree[x] += k;
}

int sum(int x)
{
	int sum = 0;
	for(; x > 0; x -= lowbit(x))
		sum += tree[x];
	return sum;
}

struct op
{
	int type;
	int i, j, k;
	int id; 
	op(int x, int y, int z, int w, int v):type(x), i(y), j(z), k(w), id(v) {}
};

void solve(int lb, int ub, vector<op> &qt)
{
	if(qt.empty())
		return;
	if(ub - lb == 1)
	{
		for(vector<op>::const_iterator i = qt.begin(); i != qt.end(); ++i)
			if(i->type == 1)
				ans[i->id] = lb;
		return;
	}
	
	int mb = (lb + ub) >> 1;
	vector<op> ql, qr;
	
	for(vector<op>::iterator i = qt.begin(); i != qt.end(); ++i)
	{
		if(i->type == 0)
		{
			if(i->k < mb)
				{
					add(i->i, i->j);
					ql.push_back(*i);
				}
			else
				qr.push_back(*i);
		}
		else
		{
			int kth = sum(i -> j) - sum(i -> i - 1);
			if(i->k <= kth)
				ql.push_back(*i);
			else
			{
				i->k -= kth;
				qr.push_back(*i);
			}
		}
	}
	for(vector<op>::const_iterator i = ql.begin(); i != ql.end(); ++i)
		if(i -> type == 0)
			add(i -> i, - (i -> j)) ;
	solve(lb, mb, ql);
	solve(mb, ub, qr);
} 

int main()
{
	vector<op> q;

	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; ++i)
	{
		scanf("%d", &a[i]);
		q.push_back(op(0, i, 1, a[i], 0));
	}
	for(int i = 1; i <= m; ++i)
	{
		char cmd;
		scanf("\n%c", &cmd);
		if(cmd == 'C')
		{
			int index, k;
			scanf("%d%d", &index, &k);
			q.push_back(op(0, index, -1, a[index], 0));
			q.push_back(op(0, index, 1, k, 0));
			a[index] = k;
			ans[i] = -1;
		}
		else
		{
			int x, y, k;
			scanf("%d%d%d", &x, &y, &k);
			q.push_back(op(1, x, y, k, i));
		}
	}
	solve(0, 1000000000+1, q);
	for(int i = 1; i <= m; ++i)
		if(ans[i] >= 0)
			printf("%d\n", ans[i]);
}
