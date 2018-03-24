#include <cstdio>
#include <iostream>
#include <cstring>
using namespace std;
const int MAXW = 205, MAXH = 205;
int sg[MAXW][MAXH], w, h;
bool mex[MAXW * MAXH];
int get_sg(int x, int y)
{
        if(sg[x][y] >= 0)
                return sg[x][y];
        memset(mex, 0, sizeof(mex));
        for(int i = 2; i <= x - i; ++i)
                mex[get_sg(x - i, y) ^ get_sg(i,y)] = true;
        for(int i = 2; i <= y - i; ++i)
                mex[get_sg(x, y - i) ^ get_sg(x, i)] = true;
        for(int i = 0; i < MAXW * MAXH; ++i)
                if(!mex[i])
                        return sg[x][y] = i;
        return 0;
}
int main()
{
        memset(sg, -1, sizeof(sg));
        while(scanf("%d%d\n", &w, &h) != EOF)
                if(get_sg(w, h))
                        printf("WIN\n");
                else
                        printf("LOSE\n");
        return 0;
}
