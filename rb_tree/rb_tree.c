#include"version.h"
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
	return 0;
}

int Rb_Delete_Data(RB_TREE **Root, RB_TREE *Z)
{
	RB_TREE *y;//指向即将被移除的节点或替代删除节点的节点
	RB_TREE *x;//指向y的孩子（唯一）节点
	char y_color; //记录即将被移除节点的颜色

	y = Z;
	y_color = y->iColor;
	if (y->ST_Left == NULL)
	{
		x = y->ST_Right;
		Rb_Transplant(Root, Z->ST_Right, Z);
	}
	else if (y->ST_Right == NULL)
	{
		x = y->ST_Left;
		Rb_Transplant(Root, Z->ST_Left, Z);
	}
	else
	{
		y = Rb_Minimum(Z->ST_Right);
		y_color = y->iColor;
		x = y->ST_Right;
		if (y->ST_Parent != Z)
		{
			Rb_Transplant(Root, y->ST_Right, y);
			y->ST_Right = Z->ST_Right;
			y->ST_Right->ST_Parent = y;
		}
		Rb_Transplant(Root, y, Z);
		y->ST_Left = Z->ST_Left;
		y->ST_Left->ST_Parent = y;
		y->iColor = Z->iColor;
	}
	if (y_color == 'B')
		Rb_Delete_Data_Fixup(Root, x);
	return 0;
}

RB_TREE *Rb_FindBrother(RB_TREE *B)
{
	if (B = B->ST_Parent->ST_Left)
		return B->ST_Parent->ST_Right;
	else
		return B->ST_Parent->ST_Left;
}

int Rb_Delete_Data_Fixup(RB_TREE **Root, RB_TREE *x)
{
	RB_TREE *w;//指向x的兄弟节点
	while (x != *Root && x->iColor == 'B')
	{
		if (x == x->ST_Parent->ST_Left)	//当x是左孩子
		{
			w = Rb_FindBrother(x);
			if (w->iColor = 'R')
			{
				w->ST_Parent->iColor = 'R';
				w->iColor = 'B';
				Left_Rotate(Root, x->ST_Parent);
				w = x->ST_Parent->ST_Right;
			}
			if (w->ST_Left->iColor == 'B' && w->ST_Right->iColor == 'B')
			{
				w->iColor = 'R';
				x = x->ST_Parent;
			}
			else if (w->ST_Right->iColor == 'B')
			{
				w->iColor = 'R';
				w->ST_Left->iColor = 'B';
				Right_Rotate(Root, w);
				w = Rb_FindBrother(x);
				
				w->iColor = x->ST_Parent->iColor;
				x->ST_Parent->iColor = 'B';
				w->ST_Right->iColor = 'B';
				Left_Rotate(Root, x->ST_Parent);
				x = *Root;
			}
		}
		else			//当x是右孩子
		{
			w = Rb_FindBrother(x);
			if (w->iColor == 'R')
			{
				w->ST_Parent->iColor = 'R';
				w->iColor = 'B';
				Right_Rotate(Root, x->ST_Parent);
			}
			if (w->ST_Left->iColor == 'B' && w->ST_Right->iColor == 'B')
			{
				w->iColor = 'R';
				x = x->ST_Parent;
			}
			else if (w->ST_Left->iColor == 'B')
			{
				w->iColor = 'R';
				w->ST_Right->iColor = 'B';
				Left_Rotate(Root, w);
				w = Rb_FindBrother(x);

				w->iColor = x->ST_Parent->iColor;
				x->ST_Parent->iColor = 'B';
				w->ST_Left->iColor = 'B';
				Right_Rotate(Root, x->ST_Parent);
				x = *Root;
			}
		}
	}
	x->iColor = 'R';
	return 0;
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

int Rb_Transplant(RB_TREE **Root, RB_TREE *v, RB_TREE *u)
{
	if (u->ST_Parent == NULL)
		*Root = v;
	else if (u->ST_Parent == u->ST_Parent->ST_Left)
		u->ST_Parent->ST_Left = v;
	else
		u->ST_Parent->ST_Right = v;
	if (v != NULL)
	v->ST_Parent = u->ST_Parent;
}

RB_TREE *Rb_Minimum(RB_TREE *t)
{
	while (t != NULL)
	{
		t = t->ST_Left;
	}
	return t;
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
