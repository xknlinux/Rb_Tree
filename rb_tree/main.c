<<<<<<< HEAD
#include"version.h"
=======
>>>>>>> cff96cf9f0384fd4127c5a43c5ecb66677ef5a59
#include<stdlib.h>
#include<stdio.h>
#include"rb_tree.h"

<<<<<<< HEAD

=======
>>>>>>> cff96cf9f0384fd4127c5a43c5ecb66677ef5a59
int main(int argc, char *argv[])
{
    int n;
    RB_TREE *Root = NULL;
    while(1)
    {
        printf("******************************\n*0: exit(0).                 *\n*1:input you wang inset data.*\n*2:delete the data:          *\n*3:print the tree.           *\n******************************\n\n\n");
        scanf("%d", &n);
        switch(n)
        {
            case 0:
                exit(0);
            case 1: 
                Rb_Insert(&Root);
				break;
            case 2:
				Rb_Delete(&Root);
				break;
            case 3:
                print(Root, 0);
                printf("\n");
				break;
            default:
                continue;
        }
    }
    return 0;
}

int print(RB_TREE *bt, int n)
{
    int i;
    if(bt == NULL)
        return 0;
    print(bt->ST_Right, n+1);
    for(i = 0; i<n; i++)
        printf("    ");
    printf("[%d %c]\n", bt->iNum, bt->iColor);
    print(bt->ST_Left, n+1);
    return 0;
}
