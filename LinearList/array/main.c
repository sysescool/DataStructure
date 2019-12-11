#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//线性表定义
//MaxSize代表有几个数据从1到n的,
//Last是从1到n的,与实际位置差一个;
typedef int ElemType;
typedef struct {
    ElemType *data;
    int MaxSize;
    int Last;
}LinearList;

//线性表初始化
void InitList(LinearList *L, int sz){
    if(sz>0){
        L->MaxSize = sz;
        L->Last = 0;
        L->data = (ElemType *)malloc(sizeof(ElemType)*L->MaxSize);
    }
}

//线性表的释放
void FreeList(LinearList *L){
    free(L->data);
}

//线性表的插入
bool ListInsert(LinearList *L, int i, ElemType x){  //i从1开始数
    if(i<1 || i>L->Last+1 || L->Last==L->MaxSize )  //判断i范围有效
        return false;
    else{
        for(int j=L->Last; j>=i-1; j--){  //Last-1是最后一个元素位置
            L->data[j+1] = L->data[j];    //后移, 直到让出了第i个位置
        }
        L->data[i-1] = x;
        L->Last++;
        return true;
    }
}

//线性表的删除
bool ListDelete(LinearList *L, int i){      //i代表第几个, n个数据是从1~n的
    if(i<0 || i>=L->Last || L->Last==0){
        return false;
    }else{
        for(int j=i-1; j<L->Last-1; j++)
            L->data[j] = L->data[j+1];
        L->Last--;
        return true;
    }
}

//线性表的查找
int LocateElem(LinearList *L, int x){
    for(int i=0; i<=L->Last; i++){
        if(L->data[i]==x) return i;
    }
    return -1;
}

//线性表的输出
int PrintList(LinearList *L){
    for(int i=0; i<L->Last; i++){
        printf("%d ",L->data[i]);
    }
    printf("\n");
}

//返回线性表的第i个条目
ElemType GetElem(LinearList *L, int i){
    if(i<1 || i>L->Last) return -1;
    else return L->data[i];
}

int main()
{
    LinearList *l1 = (LinearList *)malloc(sizeof(LinearList));
    InitList(l1,5);
    printf("insert:\n");
    ListInsert(l1,1,5);
    ListInsert(l1,2,4);
    ListInsert(l1,3,3);
    ListInsert(l1,4,2);
    ListInsert(l1,1,1);
    if(!ListInsert(l1,6,1)) printf("insert failed!\n");
    PrintList(l1);
    ListDelete(l1, 2);
    PrintList(l1);
    printf("return value: %d\n", GetElem(l1, 4));
    return 0;
}
