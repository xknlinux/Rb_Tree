#ifndef RB_TREE_
#define RB_TREE_

typedef struct tree
{
    int iNum;
    char iColor;
    struct tree *ST_Parent;
    struct tree *ST_Right;
    struct tree *ST_Left;
}RB_TREE;

int Right_Rotate(RB_TREE **Root, RB_TREE *x);
int Left_Rotate(RB_TREE **Root, RB_TREE *x);
int Rb_Insert(RB_TREE **Root);
int Rb_Insert_Data(RB_TREE **Root, RB_TREE *New);
int Rb_Insert_Fixup(RB_TREE **Root, RB_TREE *x);
int Rb_Transplant(RB_TREE **Root, RB_TREE *v, RB_TREE *u); //v�滻u
RB_TREE *Rb_Minimum(RB_TREE *t);  //����ڵ�ĺ��Ԫ��
RB_TREE *Rb_FindBrother(RB_TREE *B); //����ֵܽڵ�
int Rb_Delete(RB_TREE **Root);
int Rb_Delete_Data(RB_TREE **Root, RB_TREE *Z);
int Rb_Delete_Data_Fixup(RB_TREE **Root, RB_TREE *New);
int print(RB_TREE *bt, int n);


#endif //RB_TREE_
