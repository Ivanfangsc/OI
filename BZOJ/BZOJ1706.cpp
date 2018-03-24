#include <cstdio>
#include <iostream>
#include <cstring>
using namespace std;
void mul(long long a[210][210], long long b[210][210])
{
	long long c[210][210];
	for(int i = 0; i < 210; ++i)
		for(int j = 0; j < 210; ++j)
			c[i][j] = 1000000005;
	for(int i = 0; i < 202; ++i)
		for(int j = 0; j < 202; ++j)
			for(int k = 0; k < 202; ++k)
				c[i][j] = min(c[i][j], a[i][k] + b[k][j]);
	memcpy(a, c, sizeof(c));
}
int k, m, s, e, ind[1005], tot;
long long f[210][210], x[210][210];
int main()
{
	scanf("%d%d%d%d", &k, &m, &s, &e);
	for(int i = 0; i < 210; ++i)
		for(int j = 0; j < 210; ++j)
			f[i][j] = 1000000005;
	for(int i = 0; i < m; ++i)
	{
		int d, u, v;
		scanf("%d%d%d", &d, &u, &v);
		if(!ind[u])
			ind[u] = ++tot;
		if(!ind[v])
			ind[v] = ++tot;
		f[ind[u]][ind[v]] = f[ind[v]][ind[u]] = d;
	}
	memcpy(x, f, sizeof(f));
	--k;
	while(k)
	{
		if(k & 1)
			mul(x, f);
		mul(f, f);
		k >>= 1;
	}
	printf("%lld\n", x[ind[s]][ind[e]]);
	return 0;
} 
