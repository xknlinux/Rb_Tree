#include<stdio.h>
#include<malloc.h>
#include"rb_tree.h"

int Rb_Delete(RB_TREE **Root)
{
	int iData;
	RB_TREE *f = *Root;
	
	printf("input you want delete data....\n");
	scanf("%d", &iData);
	while(f != NULL)
	{
		if(f->iNum == iData)
			break;
		else if(f->iNum > iData)
			f = f->ST_Left;
		else
			f = f->ST_Right;
	}
	if(f == NULL)
	{
		printf("no find you wang data\n");
		return -1;
	}
	else
		Rb_Delete_Data(Root, f);
}

int Rb_Delete_Data(RB_TREE **Root, RB_TREE *Z)
{

}

int Rb_Insert(RB_TREE **Root)
{
    RB_TREE *New = (RB_TREE *)malloc(sizeof(RB_TREE));
    printf("please input you want insert data...\n-->: ");
    scanf("%d", &(New->iNum));
    New->ST_Right = NULL;
    New->ST_Parent = NULL;
    New->ST_Left = NULL;
    New->iColor = 'R';
    Rb_Insert_Data(Root, New);
    return 0;
}

int Rb_Insert_Data(RB_TREE **Root, RB_TREE *New)
{
    RB_TREE *P = NULL;
    RB_TREE *x = *Root;
    while(x != NULL)
    {
        P = x;
        if(x->iNum > New->iNum)
            x = x->ST_Left;
        else 
            x = x->ST_Right;
    }
    New->ST_Parent = P;
    if(P == NULL)
    {
        *Root = New;
        New->iColor = 'B';
        return 0;
    }
    else if(P->iNum > New->iNum)
        P->ST_Left = New;
    else
        P->ST_Right = New;
    Rb_Insert_Fixup(Root, New);
    return 0;
}

int Rb_Insert_Fixup(RB_TREE **Root, RB_TREE *New)
{
    RB_TREE *y;
    while(New != *Root && New->ST_Parent->iColor == 'R')
    {
        if(New->ST_Parent == New->ST_Parent->ST_Parent->ST_Left)              //New的父结点是New的祖父结点的左孩子
        {
            y = New->ST_Parent->ST_Parent->ST_Right;
            if(y == NULL || y->iColor == 'R')        //情况1：New的叔叔结点y是红色的
            {
                if(y != NULL)
                    y->iColor = 'B';
                New->ST_Parent->iColor = 'B';
                New->ST_Parent->ST_Parent->iColor = 'R';
                New = New->ST_Parent->ST_Parent;
                continue;
            }
            else if(New == New->ST_Parent->ST_Right) //情况2：New的叔叔结点y是黑色的且是一个右孩子
            {
                New = New -> ST_Parent;
                Left_Rotate(Root, New);
            }
            //情况3：New的叔叔结点是黑色的且是一个左孩子
            New->ST_Parent->iColor = 'B';
            New->ST_Parent->ST_Parent->iColor = 'R';
            Right_Rotate(Root, New->ST_Parent->ST_Parent);
        }
        
        else    //New的父结点是New的祖父结点的右孩子
        {
            y = New->ST_Parent->ST_Parent->ST_Left;//情况1
            if(y == NULL || y->iColor == 'R')
            {
                if(y != NULL)
                    y->iColor = 'B';
                New->ST_Parent->iColor = 'B';
                New->ST_Parent->ST_Parent->iColor = 'R';
                New = New -> ST_Parent -> ST_Parent;
                continue;
            }
            else if(New == New->ST_Parent->ST_Left)//情况
            {
                New = New->ST_Parent;
                Right_Rotate(Root, New);
            }

            //情况3：New的叔叔结点是黑色的且是一个左孩子
            New->ST_Parent->iColor = 'B';
            New->ST_Parent->ST_Parent->iColor = 'R';
            Left_Rotate(Root, New->ST_Parent->ST_Parent);
        }
    }
    (*Root)->iColor = 'B'; //最后一步将根结点设置为黑色
    return 0;
}

int Left_Rotate(RB_TREE **Root, RB_TREE *x)
{
    RB_TREE *y = x->ST_Right;
    x->ST_Right = y->ST_Left;
    if(y->ST_Left != NULL)
        y->ST_Left->ST_Parent = x;
    y->ST_Parent = x->ST_Parent;
    if(x->ST_Parent == NULL)
        *Root = y;
    else if(x == x->ST_Parent->ST_Right)
        x->ST_Parent->ST_Right = y;
    else 
        x->ST_Parent->ST_Left = y;
    y->ST_Left = x;
    x->ST_Parent = y;
    return 0;
}

int Right_Rotate(RB_TREE **Root, RB_TREE *x)
{
    RB_TREE *y = x->ST_Left;
    x->ST_Left = y ->ST_Right;
    if(y->ST_Right != NULL)
        y->ST_Right->ST_Parent = x;
    y->ST_Parent = x->ST_Parent;
    if(x->ST_Parent == NULL)
        *Root = y;
    else if(x == x->ST_Parent->ST_Right)
        x->ST_Parent->ST_Right = y;
    else
        x->ST_Parent->ST_Left = y;
    y->ST_Right = x;
    x->ST_Parent = y;
    return 0;
}
