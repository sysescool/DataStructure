#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MaxSize 50
typedef int ElemType;

typedef struct{   //顺序栈
    ElemType data[MaxSize];      //栈中元素
    int top;            //栈顶指针
}SqStack;

SqStack* InitStack(){
    SqStack* S = (SqStack*)malloc(sizeof(SqStack));
    S->top = -1;
    return S;
}

bool IsStackEmpty(SqStack* S){
    if(S->top==-1){return true;}
    else {return false;}
}

bool Push(SqStack *S, ElemType x){
    if(S->top==MaxSize-1){return false;}
    S->data[++S->top] = x;
    return true;
}

bool Pop(SqStack *S, ElemType *x){

    if(S->top==-1) {return false;}
    *x = S->data[S->top--];
    return true;
}

bool GetTop(SqStack *S, ElemType *x){
    if(S->top==-1)  {return false;}
    *x = S->data[S->top];
    return true;
}

//链式栈
typedef struct{
    struct LSNode* next;
    ElemType data;
}LSNode;

typedef struct{
    LSNode* top;
    LSNode* bottom;
}*LinkStack;

LinkStack InitLStack(){
    LinkStack LS = (LinkStack)malloc(sizeof(LinkStack));
    LS->top = (LSNode*)malloc(sizeof(LSNode));
    LS->bottom = (LSNode*)malloc(sizeof(LSNode));
    LS->bottom->next = NULL;
    LS->top->next = LS->bottom;
    return LS;
}

bool LSPush(LinkStack LS, ElemType x){
    LSNode *s = (LSNode*)malloc(sizeof(LSNode));
    if(s==NULL){printf("Memory allocation failure!\n"); return false;}
    s->data = x;
    s->next = LS->top->next;
    LS->top->next = s;
    return true;
}

bool LSPop(LinkStack LS, ElemType *x){
    if(LS->bottom == LS->top->next ) return false;
    else{
        LSNode *temp =  LS->top->next;
        *x = temp->data;
        LS->top->next = temp->next;
        free(temp);
        return true;
    }
}

bool LSGetTop(LinkStack LS, ElemType* x){
    if(LS->top->next == LS->bottom){ return false;}
    else{
        LSNode* temp = LS->top->next;
        *x = temp->data;
        return true;
    }
}

int main()
{
    SqStack* S = InitStack();
    Push(S, 1);
    Push(S, 2);
    Push(S, 3);
    ElemType *x = malloc(sizeof(int));
    Pop(S, x);
    printf("%d\n", *x);
    GetTop(S, x);
    printf("%d\n", *x);
    printf("sizeof(LSNode):%d\n", sizeof(LSNode));
    printf("sizeof(LinkStack):%d\n", sizeof(LinkStack));

    LinkStack LS = InitLStack();
    LSPush(LS, 10);
    LSPop(LS, x);
    printf("%d\n",*x);
    if(!LSPop(LS, x))
        printf("stack is empty\n");
    if(!LSGetTop(LS, x))
        printf("stack is empty\n");
    LSPush(LS, 150);
    LSPush(LS, 151);
    if(!LSGetTop(LS, x)) printf("failue!\n");
    printf("%d\n",*x);
    return 0;

}
