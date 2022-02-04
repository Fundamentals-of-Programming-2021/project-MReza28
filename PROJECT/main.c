#include "Main_includes.h"
#include "Attack.h"

#ifdef main
#undef main
#endif

int main (int argc, char *argv[]) {
    struct Planet A[10];
    int s[10][10];
    Planet_alloc(10 , A);
    Planet_dis_finder_n(10 , A , s);

    for (int i = 0; i < 10; i++)
    {
        printf("%d %d\n" , A[i].x , A[i].y);
    }
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            printf("%d " , s[i][j]);
        }
        printf("\n");
    }
    
}