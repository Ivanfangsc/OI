#include <cstdio>
#include <iostream>
#include <string>
#include <queue>
using namespace std;
const int N = 500010;
int n, m, fail[N], t[N][26], f[N], ans;
string s;
queue<int> q;
int main()
{
	cin >> n;
	for(int i = 0; i < n; ++i)
	{
		cin >> s;
		int p = 0;
		for(int j = 0; j < s.length(); ++j)
		{
			int c = s[j] - 'a';
			if(!t[p][c])
				t[p][c] = ++m;
			p = t[p][c];
		}
		++f[p]; 
	}
	fail[0] = 0;
	for(int c = 0; c < 26; ++c)
	{
		int u = t[0][c];
		if(u)
		{
			q.push(u);
			fail[u] = 0;
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
				q.push(v);
			}
			else
				t[u][c] = t[fail[u]][c];
		}
	}
	cin >> s;
	int p = 0;
	for(int i = 0; i < s.length(); ++i)
	{
		int c = s[i] - 'a';
		p = t[p][c];
		for(int t = p; t && f[t]; t = fail[t])
		{
			ans += f[t];
			f[t] = 0; 
		} 
	}
	cout << ans;
} 
