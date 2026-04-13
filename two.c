/////////Frequency ////////////////

#include <stdio.h>
#include <stdlib.h>

struct Node{
  int data;
  int freq;   // 🔥 frequency of duplicates
  struct Node *left;
  struct Node *right;
};

///////////LEVEL ORDER////////////////////////////
#define MAX 100
struct Node *queue[MAX];
int front = -1, rear = -1;

void enqueue(struct Node* node){
    if(rear == MAX-1) return;
    if(front == -1) front = 0;
    queue[++rear] = node;
}

struct Node *dequeue(){
    if(front == -1 || front > rear) return NULL;
    return queue[front++];
}

int isEmpty(){
    return (front == -1 || front > rear);
}

void levelorder(struct Node *root){
    if(root == NULL) return;

    enqueue(root);

    while(!isEmpty()){
        struct Node *current = dequeue();

        // print according to frequency
        for(int i = 0; i < current->freq; i++){
            printf("%d ", current->data);
        }

        if(current->left != NULL){
            enqueue(current->left);
        }
        if(current->right != NULL){
            enqueue(current->right);
        }
    }
}
////////////////////////////////////////////////////////

struct Node *createNode(int data){
    struct Node *node = (struct Node *)malloc(sizeof(struct Node));
    node->data = data;
    node->freq = 1;   // 🔥 initialize freq
    node->left = NULL;
    node->right = NULL;
    return node;
}

// 🔥 BST insert with frequency
struct Node *insert(struct Node *root, int data){
    if(root == NULL){
        return createNode(data);
    }

    if(data == root->data){
        root->freq++;   // duplicate found
    }
    else if(data < root->data){
        root->left = insert(root->left, data);
    }
    else{
        root->right = insert(root->right, data);
    }

    return root;
}

void inorder(struct Node *root){
    if(root == NULL) return;

    inorder(root->left);

    for(int i = 0; i < root->freq; i++){
        printf("%d ", root->data);
    }

    inorder(root->right);
}

void inorderStack(struct Node *root){
    struct Node* stack[100];
    int top = -1;

    struct Node *current = root;

    while(current != NULL || top != -1){
        while(current != NULL){
            stack[++top] = current;
            current = current->left;
        }

        current = stack[top--];

        for(int i = 0; i < current->freq; i++){
            printf("%d ", current->data);
        }

        current = current->right;
    }
}

void preorderStack(struct Node *root){
    if(root == NULL) return;

    struct Node* stack[100];
    int top = -1;

    stack[++top] = root;

    while(top != -1){
        struct Node *current = stack[top--];

        for(int i = 0; i < current->freq; i++){
            printf("%d ", current->data);
        }

        if(current->right != NULL){
            stack[++top] = current->right;
        }

        if(current->left != NULL){
            stack[++top] = current->left;
        }
    }
}

void postorderStack(struct Node *root){
    if(root == NULL) return;

    struct Node* stack1[100];
    struct Node* stack2[100];
    int top1 = -1, top2 = -1;

    stack1[++top1] = root;

    while(top1 != -1){
        struct Node *current = stack1[top1--];
        stack2[++top2] = current;

        if(current->left != NULL){
            stack1[++top1] = current->left;
        }

        if(current->right != NULL){
            stack1[++top1] = current->right;
        }
    }

    while(top2 != -1){
        struct Node *node = stack2[top2--];

        for(int i = 0; i < node->freq; i++){
            printf("%d ", node->data);
        }
    }
}

int main(){
    int A[] = {2,3,1,4,5,6,3,5,5};                
    int size = sizeof(A)/sizeof(A[0]);

    struct Node *root = NULL;

    for(int i = 0; i < size; i++){
        root = insert(root, A[i]);
    }

    printf("In-order: ");
    inorder(root);
    printf("\n");

    printf("Level-order: ");
    levelorder(root);
    printf("\n");

    printf("Stack In-order: ");
    inorderStack(root);
    printf("\n");

    printf("Stack Pre-order: ");
    preorderStack(root);
    printf("\n");

    printf("Stack Post-order: ");
    postorderStack(root);
    printf("\n");

    return 0;
}