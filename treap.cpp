#include <cstdio>
#include <iostream>
using namespace std;
class treap
{
	private:
		const int size = 100005;
		int root, l[size], r[size], val[size], dup[size], h[size], s = 0;
		int _find(const int root, const int k)
		{
			int c = 0, x = root;
			while(x != 0)
				if(val[x] <= k)
				{
					c = x;
					x = r[x];
				}
				else
					x = l[x];
			return c;
		}
		int lrot(const int x)
		{
			int y = r[x];
			r[x] = l[y];
			l[y] = x;
			return y; 
		} 
		int rrot(const int y)
		{
			int x = l[y];
			l[y] = r[x]; 
			r[x] = y; 
			return 0;
		}
		int _insert(const int root, const int k)
		{
			if(root == 0)
			{
				k[++s] = k;
				h[s] = rand();
				return s;
			}
			if(val[root] < k)
			{
				r[root] = _insert(r[root], k);
				if(h[r[root]] > h[root])
					return lrot(root);
			}
			else if(k < val[root])
			{
				l[x] = _insert(l[root], k);
				if(h[l[root]]) > h[root]
					return rror(root);
			}
			else
				++dup[root];
			return root;
		}
		int pop(const int root)
		{
			if(l[x] == 0)
				return r[x];
			if(r[x] == 0)
				return l[x];
			if(h[l[x]] > h[r[x]])
			{
				int y = rrot(root);
				r[y] = pop(root);
				return y;
			}
			else
			{
				int y = lrot(root);
				l[y] = pop(root);
				return y;
			}
		}
		int _del(const int root, const int k)
		{
			if(root == 0)
				return 0;
			if(k < val[root])
				l[root] = _del(l[root], k);
			else if(val[root] < k)
				r[root] = _del(r[root], k);
			else if(dup[root] > 0)
				--dup[root];
			else return pop(root);
			return root;
		}
	public:
		int find(int k)
		{
			return _find(root, k);
		}
		void insert(int k)
		{
			root = _insert(root, k);
		}
		void del(int k)
		{
			root = _del(root, k);
		}
} 
