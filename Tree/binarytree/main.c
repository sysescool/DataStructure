#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int ElemType;
typedef struct BiTNode{
    ElemType data;
    struct BiTNode *lchild, *rchild;
}BiTNode, *BiTree;

typedef struct QNode{
    BiTNode* data;
    struct QNode* next;
}QNode, *pQNode;
typedef struct Queue{
    pQNode front;
    pQNode rear;
}Queue;
bool InitQueue(Queue* Q){
    Q->front=(pQNode)malloc(sizeof(QNode));
    if(Q->front==NULL)   return false;
    Q->rear=Q->front;
    Q->front->next = NULL;
    return true;
}
bool EnQueue(Queue* Q, BiTree T){
    pQNode q = (pQNode)malloc(sizeof(QNode));
    if(q==NULL) return false;
    q->data = T;
    q->next=NULL;
    Q->rear->next = q;
    Q->rear = q;
    return true;
}
bool DeQueue(Queue *Q, BiTree T){
    if(Q->rear==Q->front){return false;}
    QNode* q = Q->front->next;
    T->data = q->data->data;
    T->lchild = q->data->lchild;
    T->rchild = q->data->rchild;
    Q->front->next = q->next;
    if(Q->rear == q){
        Q->rear = Q->front;
    }
    free(q);
    return true;
}

bool QIsEmpty(Queue* Q){
    if(Q->front == Q->rear) return true;
    else return false;
}
//访问结点
void visit(BiTNode* T){
    if(T==NULL) printf("N");
    else printf("%d ", T->data);
}
//一, 深度优先遍历:
//1.1先序遍历-递归算法
void PreOrder(BiTree T){
    if(T!=NULL){
        visit(T);
        //printf("T->lchild: %d\n", T->lchild);
        PreOrder(T->lchild);
        PreOrder(T->rchild);
    }else printf("# ");
}
//1.2中序遍历-递归算法
void InOrder(BiTree T){
    if(T!=NULL){
        InOrder(T->lchild);
        visit(T);
        InOrder(T->rchild);
    }else printf("# ");
}
//1.3后序遍历-递归算法
void PostOrder(BiTree T){
    if(T!=NULL){
        PostOrder(T->lchild);
        PostOrder(T->rchild);
        visit(T);
    }else printf("# ");
}
//1.4中序遍历-非递归算法--用到了栈
void BiTreeInOrder2(BiTree T){

}
//根据完全先序序列构造二叉树(一种标准的错误写法)
void CreateBTbyPreOrder(BiTree BT){
    int a;                    //如果想要改对, 应该在外面传入指针时就申请好第一个空间
    scanf("%d",&a);           //用操作空间内容的方式 *(指针) 进行后续操作, 才不需要返回指针
    if(a==-1) {               //否则这样malloc出来的结点, 都没有被连上, 最后也没有返回指针
        BT=NULL;              //等于new出了很多单独的结点.
    }
    else{
        BT = (BiTNode*)malloc(sizeof(BiTNode));
        BT->data = a;
        BT->lchild = NULL;
        BT->rchild = NULL;
        CreateBTbyPreOrder(BT->lchild);
        CreateBTbyPreOrder(BT->rchild);
    }
    return;
}

//2.1根据完全先序序列构造二叉树
BiTree CreateBT(){
    int a;
    BiTree BT;
    scanf("%d", &a);
    if(a==-1) {
        BT=NULL;
    }
    else{
        BT=(BiTree)malloc(sizeof(BiTNode));
        BT->data = a;
        BT->lchild = CreateBT();
        BT->rchild = CreateBT();
    }
    return BT;
}

//二, 广度优先遍历:
//1.层次遍历  非递归的        --作为模板要熟背
void LevelOrder(BiTree T){
    Queue* Q=(Queue*)malloc(sizeof(Queue));
    InitQueue(Q);
    BiTNode *p = (BiTNode*)malloc(sizeof(BiTNode));
    EnQueue(Q, T);
    while(!QIsEmpty(Q)){
        DeQueue(Q,p);
        visit(p);
        if(p->lchild!=NULL) EnQueue(Q,p->lchild);
        if(p->rchild!=NULL) EnQueue(Q,p->rchild);
    }
}
//创建二叉排序树       递归的
BiTree CreateBST(){
    BiTree BT = (BiTNode*)malloc(sizeof(BiTNode));          //创建指针A->申请空间B
    if(BT == NULL) return;
    BT->lchild = NULL;
    BT->rchild = NULL;
    int x;
    scanf("%d",&x);
    if(x!=-1){
        BT->data = x;   //创建根节点
    }else{
        free(BT);
        return NULL;    //不插入任何值, 直接返回一个NULL
    }
    while(x!=-1){
        scanf("%d", &x);
        if(x!=-1){
            InsertBST(BT, x);
        }
    }
    return BT;                                              //返回了指针A的值->空间B
}
//向二叉排序树中插入一个结点     递归的
void InsertBST(BiTNode* BT, int x){
    if(x<=BT->data){
        if( BT->lchild!=NULL ){
            InsertBST(BT->lchild, x);
        }else{
            //printf("%d", BT);
            (*BT).lchild = (BiTNode*)malloc(sizeof(BiTNode));
            (*BT).lchild->data = x;
            (*BT).lchild->lchild = NULL;
            (*BT).lchild->rchild = NULL;
        }
    }else{
        if( BT->rchild!=NULL ){
            InsertBST(BT->rchild, x);
        }else{
            (*BT).rchild = (BiTNode*)malloc(sizeof(BiTNode));
            (*BT).rchild->data = x;
            (*BT).rchild->lchild = NULL;
            (*BT).rchild->rchild = NULL;
        }
    }
}
//搜索二叉排序树中的结点   递归的
BiTNode* SearchBST(BiTree BST, int x){
    if(BST == NULL){return NULL;}
    if(x == BST->data){return BST;}
    else if(x<=BST->data){
        SearchBST(BST->lchild, x);
    }else{
        SearchBST(BST->rchild, x);
    }
}
//找父节点 任何树皆可用
BiTNode* SearchParent(BiTree BT, BiTNode* BTN){
    if(BT==NULL){return NULL;}
    else if(BT->lchild == BTN || BT->rchild == BTN){ return BT;}
    BiTNode* p;
    if(p=SearchParent(BT->lchild, BTN)!=NULL) return p;
    if(p=SearchParent(BT->rchild, BTN)!=NULL) return p;
}
//在二叉排序树中删除一个值为x的结点
BiTNode* DeleteBSTNode(BiTree BST, int x){
    if(BST==NULL){
        return NULL;
    }
    if(BST->data > x){
        BST->lchild = DeleteBSTNode(BST->lchild, x);
    }else if(BST->data < x){
        BST->rchild = DeleteBSTNode(BST->rchild, x);
    }else{
        if(BST->lchild == NULL){       //待删除结点的左孩是NULL, 那么只需要让右孩替换该待删除结点
            BiTNode* BT = BST;
            BST = BST->rchild;
            free(BT);
        }else if(BST->rchild == NULL){ //待删除结点的右孩是NULL, 那么只需要让左孩替换该该删除结点
            BiTNode* BT = BST;
            BST = BST->lchild;
            free(BT);
        }
        else{   //左右子树都不是空, 用左子树的最大数据或右子树的最小数据来替换该删除结点
                //(也就是该结点的中序序列的前驱或后继)
            BiTNode* BT = BST->rchild;      //BT = 待删结点的右子树
            if(BT!=NULL){
                while(BT->lchild != NULL)   //遍历找待删结点的右子树去找最左子树(最小值)
                    BT = BT->lchild;
            }
            BST->data = BT->data;           //待删结点的值等于 那个最小值
            BT = DeleteBSTNode(BST->rchild, BT->data);    //从待删结点的右结点开始遍历, 删掉那个最小值(此时有两个最小值)
                                                          //删除的值一定是一个叶子结点, 它要返回给BT一个NULL,
                                                          //上面左孩是NULL的情况, 会return一个为NULL的BST
        }
    }
    return BST;
}

int main()
{
/*    //简单建立二叉树
    BiTNode BT[6];int FLAG = (int)'.';
    for(int i=0; i<6; i++){
        BT[i].data = i+1;
        BT[i].lchild=NULL;
        BT[i].rchild=NULL;
    }
    BT[0].lchild = &BT[3];
    BT[0].rchild = &BT[2];
    BT[3].lchild = &BT[1];
    BT[3].rchild = &BT[4];
    BT[2].rchild = &BT[5];

    PreOrder(&BT[0]);
    printf("\n");
    InOrder(&BT[0]);
    printf("\n");
    PostOrder(&BT[0]);
    printf("\n");
    LevelOrder(&BT[0]);
    printf("\n");
*/
/*    //完全先序序列建立二叉树   //测试案例:1 4 2 -1 -1 5 -1 -1 3 -1 6 -1 -1 //会得到跟上面一样的结果
    printf("\n");
    BiTree BT4 = CreateBT();
    PreOrder(BT4);printf("\n");
    InOrder(BT4);printf("\n");
    PostOrder(BT4);printf("\n");
    LevelOrder(BT4);printf("\n");
*/
/*    //测试创建一个二叉排序树, 插入结点, 搜索结点, 求父节点; //测试案例:5 3 7 4 6 1 2 -1
    printf("\n");
    BiTree BST = CreateBST();
    LevelOrder(BST); printf("\n");
    InsertBST(BST, -2);
    InOrder(BST);
    LevelOrder(BST); printf("\n");
    BiTNode* BTN1 = SearchBST(BST, 3); //确保前面输入了3, 并且3结点下有左孩和右孩;
    printf("%d, %d, %d\n", BTN1->data, BTN1->lchild->data, BTN1->rchild->data); // 3 1 4
    for(int i=1; i<8; i++){
        BiTNode* BTN2 = SearchBST(BST,i);
        printf("%d的父节点:",BTN2->data);
        if( SearchParent(BST, BTN2) ){
            printf("%d", BTN2->data);   //5是根节点, 没有父结点
        }
        printf("\n");
    }
*/
/*    //测试删除二叉排序树中的结点
    //测试用例: 50 25 100 75 150 60 80 125 175 55 90 110 135 160 190 -1
    printf("\n");
    BiTree BST2 = CreateBST();
    printf("创建二叉排序树:  "); LevelOrder(BST2); printf("\n");
    DeleteBSTNode(BST2, 25);    //左右子树皆为空
    printf("删除二叉排序25:  "); LevelOrder(BST2); printf("\n");
    DeleteBSTNode(BST2, 60);    //右子树为空
    printf("删除二叉排序60:  "); LevelOrder(BST2); printf("\n");
    DeleteBSTNode(BST2, 80);    //左子树为空
    printf("删除二叉排序80:  "); LevelOrder(BST2); printf("\n");
    DeleteBSTNode(BST2, 100);   //左右子树皆不为空
    printf("删除二叉排序100: "); LevelOrder(BST2); printf("\n");
*/

    /**这是错误的写法!!! 没有返回, 函数里的指针和外面的指针不是一个指针!
    很典型的错误, 保留了下来, 避免下次再犯
    BiTree BT2 ;//= (BiTree)malloc(sizeof(BiTNode));
    CreateBTbyPreOrder(BT2);  //1 4 2 -1 -1 5 -1 -1 3 -1 6 -1 -1
    PreOrder(BT2);printf("\n");
    InOrder(BT2);printf("\n");
    PostOrder(BT2);printf("\n");
    LevelOrder(BT2);printf("\n");
    */
    return 0;
}
