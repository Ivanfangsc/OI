#include <cstdio>
#include <iostream>
#include <cstring>
using namespace std;
typedef long long ll;
const int K = 55;
ll n, p, r, k;
struct mat
{
    ll val[K][K];
    mat operator *(mat b)
    {
        mat c;
        memset(&c, 0, sizeof(mat));
        for(int i = 0; i < k; ++i)
            for(int j = 0; j < k; ++j)
                for(int l = 0; l < k; ++l)
                    c.val[i][j] = (c.val[i][j] + val[i][l] * b.val[l][j]) % p;
        return c;
    }
} matrix;
void pow(mat &a, ll n)
{
    mat b;
    memcpy(&b, &a, sizeof(mat));
    --n;
    while(n)
    {
        if(n & 1)
            a = a * b;
        b = b * b;
        n >>= 1;
    }
}
int main()
{
    scanf("%lld%lld%lld%lld", &n, &p, &k, &r);
    for(int i = 0; i < k; ++i)
    {
        ++matrix.val[i][i];
        ++matrix.val[(i + 1) % k][i];
    }
    pow(matrix, n * k);
    printf("%lld\n", matrix.val[r][0]);
    return 0;
}
