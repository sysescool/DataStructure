#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int ElemType;

//结点定义
typedef struct{
    struct node* next;
    ElemType data;
}Node;


//初始化单链表结点
void InitNode(Node* N, ElemType item, Node *ptr){
    N->data = item;
    N->next = ptr;
}

//插入一个单链表结点, 把p插在N后
void InsertAfter(Node* N, Node* p){
    p->next = N->next;
    N->next = p;
}

//删除一个单链表结点, 返回并删除P结点后面那个结点
Node* DeleteAfter(Node *P){
    Node* temp = P->next;
    if(temp==NULL)  return NULL;
    P->next = temp->next;
    return temp;
}

//创建一个单链表结点
//给一个空结点和值,返回一个带附加头结点的链表
//值存在附加头结点的下一个结点里
Node* GetNode(ElemType item, Node *nextptr){
    Node* newNode;
    /*申请单链表结点空间*/
    newNode=(Node *)malloc(sizeof(Node));   //附加头结点
    if(newNode==NULL){
        printf("memory allocation failed!\n");
        exit(1);
    }
    InitNode(newNode, item, nextptr);
    return newNode;
}

//释放一个单链表结点
void FreeNode(Node *ptr){
    if(!ptr){
        printf("FreeNode: invalid node pointer!\n");
    }
    free(ptr);
}

//链表的定义
typedef struct{
    Node *front, *rear;         //表头和表尾指针
    //用于访问数据,插入和删除结点
    Node *prevPtr;              //当前结点上一结点指针
    Node *currPtr;              //当前结点指针
    int size;                   //表中的结点数
    int position;               //表中当前结点位置计数
}LinkedList;

//链表初始化函数, 建立一个空链表
void InitLinkedList(LinkedList *L){
    L->front = NULL;
    L->rear  = NULL;
    L->prevPtr = NULL;
    L->currPtr = NULL;
    L->size = 0;
    L->position = -1;
}

//当前结点处插入新结点的函数
void InsertAt(LinkedList *L, ElemType item){
    Node *newNode;
    if(!L->size){
        //newNode = GetNode(item, L->front); //空表中插入
        newNode = GetNode(item, NULL);  //这种写法便于理解
        L->front = L->rear = newNode;
        L->position = 0;
        printf("前插 空表插入\n");
    }else if(!L->prevPtr){
        newNode = GetNode(item, L->front); //表头结点插入 //头插法
        L->front = newNode;
        printf("前插 表头结点插入\n");
    }else{
        newNode = GetNode(item, L->currPtr); //在链表的中间位置插入
        InsertAfter(L->prevPtr, newNode);
        printf("前插 中间位置插入\n");
    }
    L->size++;
    L->currPtr=newNode;
}

//在当前结点后插入新节点的函数
void InsertLAfter(LinkedList *L, ElemType item){
    Node* newNode;
    if(!L->size){               //空表插入
        newNode = GetNode(item, NULL);
        L->front = L->rear = newNode;
        L->position = 0;
        printf("后插 空表插入\n");
    }else if(L->currPtr == L->rear || !L->currPtr){ //在表尾结点后插入
        newNode = GetNode(item, NULL);
        InsertAfter(L->rear, newNode);
        L->prevPtr = L->rear;
        L->rear = newNode;
        L->position = L->size;
        printf("后插 表尾结点插入\n");
    }else{      //在链表的中间位置插入
        newNode = GetNode(item, (L->currPtr)->next);
        InsertAfter(L->currPtr, newNode);
        L->prevPtr = L->currPtr;
        L->position++;
        printf("后插 中间位置插入\n");
    }
    L->size++;
    L->currPtr=newNode;
}

//打印列表
void PrintList(Node *head){
    Node *currPtr = head;
    while(currPtr != NULL){
        printf("%d->",currPtr->data);
        currPtr=currPtr->next;
    }
    printf("NULL\n");
}

//基于表目按值查找单链表
int Find(Node * head, ElemType item){
    Node *currPtr = head;
    Node *prevPtr = NULL;
    while(currPtr != NULL){
        if(currPtr->data == item){
            return 1;
        }
        prevPtr = currPtr;
        currPtr = currPtr->next;
    }
    return 0;
}

//查找单链表中的一个值, 并从链表上摘除并返回这个结点
Node* FindL(Node* head, ElemType item){
    Node *currPtr = head;
    Node *prevPtr = NULL;
    while(currPtr != NULL){
        if(currPtr->data == item){
            prevPtr->next = currPtr->next;
            currPtr->next = NULL;
            return currPtr;
        }
        prevPtr = currPtr;
        currPtr = currPtr->next;
    }
    return NULL;
}

int main()
{
    LinkedList *l = (LinkedList *)malloc(sizeof(LinkedList));
    LinkedList *l2 = (LinkedList *)malloc(sizeof(LinkedList));
    LinkedList *l3 = (LinkedList *)malloc(sizeof(LinkedList));
    InitLinkedList(l);
    InitLinkedList(l2);
    InitLinkedList(l3);
    PrintList(l->front);
    InsertAt(l, 1);
    InsertAt(l, 2);
    InsertAt(l, 3);
    InsertAt(l, 4);
    InsertAt(l, 5);
    PrintList(l->front);    //5->4->3->2->1->NULL
    InsertLAfter(l2, 1);
    InsertLAfter(l2, 2);
    InsertLAfter(l2, 3);
    InsertLAfter(l2, 4);
    InsertLAfter(l2, 5);
    PrintList(l2->front);   //1->2->3->4->5->NULL
    InsertAt(l3, 1);
    InsertLAfter(l3, 2);
    InsertAt(l3, 3);
    InsertLAfter(l3, 4);
    InsertAt(l3, 5);
    InsertAt(l3, 7);
    InsertLAfter(l3, 6);
    PrintList(l3->front);  //1->3->7->6->5->4->2->NULL
    printf("find value %d\n",FindL(l3->front, 5)->data);
    PrintList(l3->front);
    return 0;
}
