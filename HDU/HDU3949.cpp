#include <iostream>
using namespace std;
const int MAXN = 10005; 
int T, n, q;
int main()
{
	cin >> T;
	for (int t = 1; t <= T;  ++t)
	{
		cin >> n;
		long long a[MAXN];
		for (int i = 0; i < n; ++i)
			cin >> a[i];
		int d = 0;
		for (int k = 63; k >= 0; --k)
		{
			bool flag = false;
			for (int i = d; i < n; ++i)
				if ((a[i] >> k) & 1)
				{
					long long swap = a[i];
					a[i] = a[d];
					a[d] = swap;
					flag = true;
					break;
				}
			if (flag)
			{
				for (int i = d + 1; i < n; ++i)
					if((a[i] >> k) & 1)
						a[i] ^= a[d];
				++d;
			}
		}
		cin >> q;
		printf("Case #%d:\n", t);
		while (q--)
		{
			long long k;
			cin >> k;
			if (d == n) 
				k++; 
			long long res = 0, num = 1LL << d;
			for (int i = 0; i < d; ++i)
			{
				num >>= 1;
				if (k > num) 
				{
					res = max(res, res ^ a[i]);
					k -= num;
				} 
				else 
					res = min(res, res ^ a[i]);
			}
			if (k == 1)
				cout << res << endl;
			else
				cout << -1 << endl;
		}
	}
} 
