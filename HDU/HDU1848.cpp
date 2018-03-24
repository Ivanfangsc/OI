#include <cstdio>
#include <iostream>
#include <cstring>
using namespace std;
const int MAXN = 10005;
int feb[MAXN], sg[MAXN], m, n, p;
bool mex[MAXN];
void get_feb()
{
        feb[0] = 1;
        feb[1] = 2;
        for(int i = 1; feb[i] < MAXN; ++i)
                feb[i + 1] = feb[i] + feb[i - 1];
}
void get_sg()
{
        for(int x = 0; x < MAXN; ++x)
        {
                memset(mex, 0, sizeof(mex));
                for(int i = 0; feb[i] <= x; ++i)
                        mex[sg[x - feb[i]]] = true;
                for(int i = 0; i < MAXN; ++i)
                        if(!mex[i])
                        {
                                sg[x] = i;
                                break;
                        }

        }
}
int main()
{
        get_feb();
        get_sg();
        scanf("%d%d%d", &m, &n, &p);
        while(m || n || p)
        {
                if(sg[m] ^ sg[n] ^ sg[p])
                        printf("Fibo\n");
                else
                        printf("Nacci\n");
                scanf("%d%d%d", &m, &n, &p);
        }
        return 0;
}
