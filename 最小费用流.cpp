#include <cstdio>
#include <iostream>
#include <queue>
#include <cstring>
using namespace std;
const int MAXN, MAXE;
int first[MAXN], next[MAXE], r[MAXE], w[MAXE], v[MAXE], edge = 1;
void link(int x, int y, int r_, int w_)
{
	next[++edge] = first[x];
	r[edge] = r_;
	w[edge] = w_;
	v[edge] = y;
	first[x] = edge;
	next[++edge] = first[y];
	r[edge] = 0;
	w[edge] = -w_;
	v[edge] = x;
	first[y] = edge;
}
queue<int> q;
int d[MAXN];
bool spfa()
{
	q.push(s);
	memset(d, 127, sizeof(d));
	d[s] = 0;
	while(!q.empty())
	{
		int u = q.front();
		q.pop();
		for(int e = first[e]; e; e = next[e])
			if(r[e] && d[v[e]] > d[u] + w[e])
			{
				pre[v] = e;
				q.push(v);
				d[v[e]] = d[u] + w[e];
			}
	}
	return d[t];
}
int augment(int delta = 2147483647)
{
	int mincost = 0;
	for(int u = t; u != s; u = pre[u])
		delta = min(delta, r[pre[u]][u]);
	for(u = t; u != s; u = v[pre[u] ^ 1])
	{
		e = pre[u];
		r[e] -= delta;
		r[e ^ 1] += delta;
		mincost += w[e] * delta;
	}
	return mincost;
}
int main()
{
	while(spfa())
		ans += augment();
	return 0;
} 
