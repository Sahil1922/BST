#include <stdio.h>
#include <stdlib.h>

// ================= NODE =================
struct Node{
    int data;
    struct Node *left, *right;
};

// ================= CREATE =================
struct Node* createNode(int data){
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = data;
    node->left = node->right = NULL;
    return node;
}

// ================= SEARCH =================
int search(int arr[], int start, int end, int value){
    for(int i = start; i <= end; i++){
        if(arr[i] == value)
            return i;
    }
    return -1;
}

// ======================================================
// 🔹 BUILD FROM INORDER + PREORDER
// ======================================================
struct Node* buildPreIn(int inorder[], int preorder[], int start, int end, int *preIndex){

    if(start > end) return NULL;

    int curr = preorder[*preIndex];
    (*preIndex)++;

    struct Node* node = createNode(curr);

    if(start == end) return node;

    int inIndex = search(inorder, start, end, curr);

    node->left  = buildPreIn(inorder, preorder, start, inIndex-1, preIndex);
    node->right = buildPreIn(inorder, preorder, inIndex+1, end, preIndex);

    return node;
}

// ======================================================
// 🔹 BUILD FROM INORDER + POSTORDER
// ======================================================
struct Node* buildPostIn(int inorder[], int postorder[], int start, int end, int *postIndex){

    if(start > end) return NULL;

    int curr = postorder[*postIndex];
    (*postIndex)--;

    struct Node* node = createNode(curr);

    if(start == end) return node;

    int inIndex = search(inorder, start, end, curr);

    // IMPORTANT: build right first
    node->right = buildPostIn(inorder, postorder, inIndex+1, end, postIndex);
    node->left  = buildPostIn(inorder, postorder, start, inIndex-1, postIndex);

    return node;
}

// ================= INORDER PRINT =================
void inorderPrint(struct Node* root){
    if(root == NULL) return;

    inorderPrint(root->left);
    printf("%d ", root->data);
    inorderPrint(root->right);
}

// ================= MAIN =================
int main(){

    int inorder[]   = {4,2,5,1,6,3};
    int preorder[]  = {1,2,4,5,3,6};
    int postorder[] = {4,5,2,6,3,1};

    int n = 6;

    // -------- PREORDER + INORDER --------
    int preIndex = 0;
    struct Node* root1 = buildPreIn(inorder, preorder, 0, n-1, &preIndex);

    printf("Tree from Preorder + Inorder (Inorder Output): ");
    inorderPrint(root1);

    printf("\n");

    // -------- POSTORDER + INORDER --------
    int postIndex = n - 1;
    struct Node* root2 = buildPostIn(inorder, postorder, 0, n-1, &postIndex);

    printf("Tree from Postorder + Inorder (Inorder Output): ");
    inorderPrint(root2);

    printf("\n");

    return 0;
}
