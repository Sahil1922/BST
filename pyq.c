#include <stdio.h>
#include <stdlib.h>

// ================= ROLL LIST =================
struct RollNode {
    int roll;
    struct RollNode* next;
};

// create new roll node
struct RollNode* createRoll(int roll) {
    struct RollNode* newNode = (struct RollNode*)malloc(sizeof(struct RollNode));
    newNode->roll = roll;
    newNode->next = NULL;
    return newNode;
}

// add roll to list
struct RollNode* addRoll(struct RollNode* head, int roll) {
    struct RollNode* newNode = createRoll(roll);
    newNode->next = head;
    return newNode;
}

// remove roll from list
struct RollNode* removeRoll(struct RollNode* head, int roll) {
    struct RollNode *temp = head, *prev = NULL;

    while (temp != NULL) {
        if (temp->roll == roll) {
            if (prev == NULL)
                head = temp->next;
            else
                prev->next = temp->next;

            free(temp);
            return head;
        }
        prev = temp;
        temp = temp->next;
    }
    return head;
}

// print roll list
void printRolls(struct RollNode* head) {
    while (head != NULL) {
        printf("%d ", head->roll);
        head = head->next;
    }
}

// ================= BST NODE =================
struct Node {
    int marks;
    struct RollNode* rolls; // list of roll numbers
    struct Node *left, *right;
};

// create BST node
struct Node* createNode(int marks, int roll) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->marks = marks;
    node->rolls = createRoll(roll);
    node->left = node->right = NULL;
    return node;
}

// ================= INSERT =================
struct Node* insert(struct Node* root, int marks, int roll) {
    if (root == NULL)
        return createNode(marks, roll);

    if (marks < root->marks)
        root->left = insert(root->left, marks, roll);
    else if (marks > root->marks)
        root->right = insert(root->right, marks, roll);
    else
        // same marks → add roll to list
        root->rolls = addRoll(root->rolls, roll);

    return root;
}

// ================= SEARCH =================
struct Node* search(struct Node* root, int marks) {
    if (root == NULL || root->marks == marks)
        return root;

    if (marks < root->marks)
        return search(root->left, marks);
    else
        return search(root->right, marks);
}

// ================= FIND MIN =================
struct Node* findMin(struct Node* root) {
    while (root && root->left)
        root = root->left;
    return root;
}

// ================= DELETE =================
struct Node* deleteNode(struct Node* root, int marks, int roll) {
    if (root == NULL) return NULL;

    if (marks < root->marks) {
        root->left = deleteNode(root->left, marks, roll);
    }
    else if (marks > root->marks) {
        root->right = deleteNode(root->right, marks, roll);
    }
    else {
        // found node with marks

        // remove roll from list
        root->rolls = removeRoll(root->rolls, roll);

        // if rolls still exist → don't delete node
        if (root->rolls != NULL)
            return root;

        // otherwise delete BST node

        // case 1: no child
        if (root->left == NULL && root->right == NULL) {
            free(root);
            return NULL;
        }

        // case 2: one child
        if (root->left == NULL) {
            struct Node* temp = root->right;
            free(root);
            return temp;
        }
        if (root->right == NULL) {
            struct Node* temp = root->left;
            free(root);
            return temp;
        }

        // case 3: two children
        struct Node* temp = findMin(root->right);

        root->marks = temp->marks;
        root->rolls = temp->rolls;

        root->right = deleteNode(root->right, temp->marks, temp->rolls->roll);
    }
    return root;
}

// ================= INORDER =================
void inorder(struct Node* root) {
    if (root == NULL) return;

    inorder(root->left);

    printf("Marks: %d -> Rolls: ", root->marks);
    printRolls(root->rolls);
    printf("\n");

    inorder(root->right);
}

// ================= MAIN =================
int main() {
    struct Node* root = NULL;

    // input: (roll, marks)
    root = insert(root, 85, 1);
    root = insert(root, 90, 2);
    root = insert(root, 85, 3);
    root = insert(root, 70, 4);
    root = insert(root, 90, 5);

    printf("Inorder Traversal:\n");
    inorder(root);

    // search
    int query = 85;
    struct Node* result = search(root, query);

    if (result) {
        printf("\nStudents with %d marks: ", query);
        printRolls(result->rolls);
    } else {
        printf("\nNo students found with %d marks", query);
    }

    // delete
    printf("\n\nDeleting roll 3 with marks 85...\n");
    root = deleteNode(root, 85, 3);

    printf("\nAfter Deletion:\n");
    inorder(root);

    return 0;
}