////BST + stack+queue

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Node{
  int data;
  struct Node *left;
  struct Node *right;
};

///////////LEVEL ORDER////////////////////////////
#define MAX 100
struct Node *queue[MAX];
int front = -1, rear = -1;

void enqueue(struct Node* node){
    if(rear == MAX-1){ //overflow
        return; 
    }
    if(front == -1){
        front = 0;
    }
    queue[++rear] = node;
}

struct Node *dequeue(){
    if(front == -1 || front>rear){ //empty
        return NULL;
    } 
    return queue[front++];
}

int isEmpty(){
    return (front == -1 || front>rear);
}

void levelorder(struct Node *root){
    if(root == NULL){
        return;
    }
    enqueue(root); //BFS start from root
    
    while(!isEmpty()){
        struct Node *current = dequeue();
        printf("%d ", current->data);
        
        if(current->left !=NULL){
            enqueue(current->left);
        }
        if(current->right !=NULL){
            enqueue(current->right);
        }
    }
}
////////////////////////////////////////////////////////


struct Node *createNode(int data){
    struct Node *node = (struct Node *)malloc(sizeof(struct Node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

struct Node *insert(struct Node *root, int data){
    if(root == NULL){
        return createNode(data);
    }
    if(rand()%2 == 0){
        root->left = insert(root->left, data);
    }else{
        root->right = insert(root->right, data);
    }
    return root;
}

void inorder(struct Node *root){
    if(root == NULL){
        return;
    }
    inorder(root->left); 
    printf("%d ", root->data);
    inorder(root->right);
}

void inorderStack(struct Node *root){
    struct Node* stack[100];
    int top = -1;

    struct Node *current = root;

    while(current != NULL || top != -1){
        
        // Step 1: Go to leftmost node
        while(current != NULL){
            stack[++top] = current;
            current = current->left;
        }

        // Step 2: Pop from stack
        current = stack[top--];
        printf("%d ", current->data);

        // Step 3: Move to right subtree
        current = current->right;
    }
}

void preorderStack(struct Node *root){
    if(root == NULL) return;

    struct Node* stack[100];
    int top = -1;

    // push root
    stack[++top] = root;

    while(top != -1){
        // pop
        struct Node *current = stack[top--];

        // visit node
        printf("%d ", current->data);

        // push right first
        if(current->right != NULL){
            stack[++top] = current->right;
        }

        // push left after
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

    // push root
    stack1[++top1] = root;

    while(top1 != -1){
        struct Node *current = stack1[top1--];

        // push into stack2
        stack2[++top2] = current;

        // push left
        if(current->left != NULL){
            stack1[++top1] = current->left;
        }

        // push right
        if(current->right != NULL){
            stack1[++top1] = current->right;
        }
    }

    // print stack2
    while(top2 != -1){
        printf("%d ", stack2[top2--]->data);
    }
}

int main(){
    srand(time(NULL));
    int A[] = {2,3,1,4,5,6};
    int size =sizeof(A)/sizeof(A[0]);
    struct Node *root = NULL;
    for(int i=0; i<size; i++){
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
    printf("Stack pre-order: ");
    preorderStack(root);
    printf("\n");
    
    return 0;
}