#include <stdio.h>
#include <stdlib.h>

// ================= NODE =================
struct Node{
    int data;
    struct Node *left;
    struct Node *right;
};

// ================= CREATE =================
struct Node *createNode(int data){
    struct Node *node = (struct Node *)malloc(sizeof(struct Node));
    node->data = data;
    node->left = node->right = NULL;
    return node;
}

// ================= BST INSERT =================
struct Node *insert(struct Node *root, int data){
    if(root == NULL) return createNode(data);

    if(data < root->data)
        root->left = insert(root->left, data);
    else
        root->right = insert(root->right, data);

    return root;
}

// ================= SEARCH =================
struct Node* search(struct Node *root, int key){
    if(root == NULL || root->data == key)
        return root;

    if(key < root->data)
        return search(root->left, key);
    else
        return search(root->right, key);
}

// ================= MIN =================
struct Node* findMin(struct Node *root){
    while(root && root->left)
        root = root->left;
    return root;
}

// ================= MAX =================
struct Node* findMax(struct Node *root){
    while(root && root->right)
        root = root->right;
    return root;
}

// ================= DELETE =================
struct Node* deleteNode(struct Node *root, int key){
    if(root == NULL) return NULL;

    if(key < root->data){
        root->left = deleteNode(root->left, key);
    }
    else if(key > root->data){
        root->right = deleteNode(root->right, key);
    }
    else{
        // case 1: no child
        if(root->left == NULL && root->right == NULL){
            free(root);
            return NULL;
        }
        // case 2: one child
        else if(root->left == NULL){
            struct Node *temp = root->right;
            free(root);
            return temp;
        }
        else if(root->right == NULL){
            struct Node *temp = root->left;
            free(root);
            return temp;
        }
        // case 3: two children
        struct Node *temp = findMin(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

// ================= INORDER (STACK) =================
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
        printf("%d ", current->data);

        current = current->right;
    }
}

// ================= PREORDER (STACK) =================
void preorderStack(struct Node *root){
    if(root == NULL) return;

    struct Node* stack[100];
    int top = -1;

    stack[++top] = root;

    while(top != -1){
        struct Node *current = stack[top--];
        printf("%d ", current->data);

        if(current->right)
            stack[++top] = current->right;

        if(current->left)
            stack[++top] = current->left;
    }
}

// ================= POSTORDER (2 STACKS) =================
void postorderStack(struct Node *root){
    if(root == NULL) return;

    struct Node* stack1[100];
    struct Node* stack2[100];
    int top1 = -1, top2 = -1;

    stack1[++top1] = root;

    while(top1 != -1){
        struct Node *current = stack1[top1--];
        stack2[++top2] = current;

        if(current->left)
            stack1[++top1] = current->left;

        if(current->right)
            stack1[++top1] = current->right;
    }

    while(top2 != -1){
        printf("%d ", stack2[top2--]->data);
    }
}

// ================= LEVEL ORDER =================
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

    front = rear = -1;
    enqueue(root);

    while(!isEmpty()){
        struct Node *current = dequeue();
        printf("%d ", current->data);

        if(current->left) enqueue(current->left);
        if(current->right) enqueue(current->right);
    }
}

// ================= MAIN =================
int main(){
    int A[] = {5,3,7,2,4,6,8};
    int size = sizeof(A)/sizeof(A[0]);

    struct Node *root = NULL;

    for(int i=0; i<size; i++){
        root = insert(root, A[i]);
    }

    printf("Inorder (Stack): ");
    inorderStack(root);

    printf("\nPreorder (Stack): ");
    preorderStack(root);

    printf("\nPostorder (Stack): ");
    postorderStack(root);

    printf("\nLevel Order: ");
    levelorder(root);

    printf("\nMin: %d", findMin(root)->data);
    printf("\nMax: %d", findMax(root)->data);

    printf("\nDeleting 5...\n");
    root = deleteNode(root, 5);

    printf("Inorder after delete: ");
    inorderStack(root);

    return 0;
}
