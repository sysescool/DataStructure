#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MaxSize 15
typedef int ElemType;

typedef struct{
    ElemType data[MaxSize];
    int rear;
    int front;
}CircleQueue;

CircleQueue* InitCQueue(){
    CircleQueue* CQ = (CircleQueue*)malloc(sizeof(CircleQueue));
    CQ->rear = 0;
    CQ->front = 0;
    return CQ;
}

bool EnCQueue(CircleQueue* CQ, ElemType x){
    if( (CQ->rear+1)%MaxSize == CQ->front){
        return false;
    }else{
        CQ->data[CQ->rear] = x;
        //printf("%d  %d  %d\n",CQ->front,CQ->rear,CQ->data[CQ->rear]);
        CQ->rear = (CQ->rear+1)%MaxSize;
        return true;
    }
}

bool DeCQueue(CircleQueue* CQ, ElemType* x){
    if(CQ->rear == CQ->front){
        return false;
    }else{
        *x = CQ->data[CQ->front];
        //printf("%d  %d  %d",CQ->front,CQ->rear,CQ->data[CQ->front]);
        CQ->front = (CQ->front+1)%MaxSize;
        return true;
    }
}
int main()
{
    CircleQueue* CQ = InitCQueue();
    int *x = (int*)malloc(sizeof(int));
    if(!DeCQueue(CQ, x)) printf("CQueue is empty!\n");
    for(int i=0; i<MaxSize; i++){
        if(!EnCQueue(CQ,i)) printf("CQueue is full!\n");
    }
    for(int i=0; i<MaxSize; i++){
        if(!DeCQueue(CQ, x)) printf("CQueue is empty!\n");
        else printf("%d\n",*x);
    }
    return 0;
}
