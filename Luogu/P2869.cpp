#include<cstdio>
#include<iostream>
#include<set>
#include<algorithm>
using namespace std;
multiset<int> T;
pair<int, int> c[100000], g[100000];
int n, m;
long long ans = 0;
int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; ++i)
		scanf("%d%d", &c[i].first, &c[i].second);
	for (int i = 0; i < m; ++i)
		scanf("%d%d", &g[i].first, &g[i].second);
	sort(c, c + n);
	sort(g, g + m);
	int j = 0;
	for (int i = 0; i < m; ++i)
	{
		while (j < n && c[j].first <= g[i].first)
			T.insert(-c[j++].second);
		multiset<int>::iterator p = T.lower_bound(-g[i].second);
		if (p != T.end())
		{
			ans += g[i].first;
			T.erase(p);
		}
	}
	if (j == n && T.empty())
		printf("%lld\n", ans);
	else
		printf("-1\n");
	return 0;
}
