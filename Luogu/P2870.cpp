#include <cstdio>
#include <iostream>
#include <string>
#include <cstring>
using namespace std;
const int N = 300010, M = 27;
int n, c[M], sa[N], x[N], y[N], s[N];
int main()
{
	cin >> n;
	for (int i = 0; i < n; ++i)
	{
		char ch;
		cin >> ch;
		s[i] = (int)(ch - 'A');
	}
	s[n] = 0;
	for (int i = 0; i < n; ++i)
		s[i + n + 1] = s[n - 1 - i];
	n = 2 * n + 1;
	memset(c, 0, sizeof(c));
	for (int i = 0; i < n; ++i)
		++c[x[i] = s[i]];
	for (int i = 1; i < M; ++i)
		c[i] += c[i - 1];
	for (int i = n - 1; i >= 0; --i)
		sa[--c[x[i]]] = i;
	for (int k = 1; k <= n; k <<= 1)
	{
		int index = 0;
		for (int i = n - k; i < n; ++i)
			y[index++] = i;
		for (int i = 0; i < n; ++i)
			if (sa[i] >= k)
				y[index++] = sa[i] - k;
		memset(c, 0, sizeof(c));
		for (int i = 0; i < n; ++i)
			++c[x[y[i]]];
		for (int i = 1; i < M; ++i)
			c[i] += c[i - 1];
		for (int i = n - 1; i >= 0; --i)
			sa[--c[x[y[i]]]] = y[i];
		memcpy(y, x, sizeof(y));
		int num = 0;
		x[sa[0]] = 0;
		for (int i = 1; i < n; ++i)
			if (y[sa[i]] == y[sa[i - 1]] && y[sa[i] + k] == y[sa[i - 1] + k])
				x[sa[i]] = num;
			else
				x[sa[i]] = ++num;
		if (num + 1 >= n)
			break;
	}
	n /= 2;
	int l = 0, r = n - 1;
	for (int i = 0; i < n; ++i)
	{
		if(x[l] > x[2 * n - r])
			putchar(s[r--] + 'A');
		else
			putchar(s[l++] + 'A');
		if((i + 1) % 80 == 0)
			putchar('\n');
	}
}
