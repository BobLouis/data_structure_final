#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// AVL structure
struct avl
{
    struct avl *left;
    struct avl *right;
    int data, height;
};
typedef struct avl *AVL;

int max(int, int);
int height(AVL);
AVL newNode(int);
AVL rightRotate(AVL);
AVL leftRotate(AVL);
int balance(AVL);
AVL insert(AVL, int);
void findKey(AVL, int);
AVL updateAVL(AVL);
void updateHeight(AVL);
AVL deleteAVL(AVL, int);
void getF(AVL, int);

// RBT structure
struct rbt
{
    struct rbt *left;
    struct rbt *right;
    struct rbt *parent;
    int color, data;
};
typedef struct rbt *RBT;
RBT root = NULL;
RBT neel;
RBT newTree(int);
void rotateRight(RBT);
void rotateLeft(RBT);
void toInsert(int);
void insertFix(RBT);
RBT search(int);
RBT successor(RBT);
RBT leftmost(RBT);
void deleteRBT(int);
void deleteFix(RBT);

int main()
{
    // neel is for safety
    clock_t start_t, end_t;
    neel = (RBT)malloc(sizeof(struct rbt));
    neel->color = 1;
    neel->left = NULL;
    neel->right = NULL;
    neel->parent = NULL;
    root = neel;
    root->parent = neel;
    char s[10];
    scanf("%s", s);
    start_t = clock();
    if (!strcmp(s, "AVL"))
    {
        AVL root = NULL;
        char cmd[10];
        while (true)
        {
            scanf("%s", cmd);
            if (!strcmp(cmd, "insert"))
            {
                int data;
                scanf("%d", &data);
                root = insert(root, data);
            }
            else if (!strcmp(cmd, "delete"))
            {
                int data;
                scanf("%d", &data);
                root = deleteAVL(root, data);
            }
            else if (!strcmp(cmd, "search"))
            {
                int data;
                scanf("%d", &data);
                getF(root, data);
            }
            else if (!strcmp(cmd, "exist"))
            {
                int data;
                scanf("%d", &data);
                findKey(root, data);
            }
            else if (!strcmp(cmd, "quit"))
                break;
        }
    }
    else if (!strcmp(s, "red_black"))
    {
        char cmd[10];
        while (true)
        {
            scanf("%s", cmd);
            if (!strcmp(cmd, "insert"))
            {
                int data;
                scanf("%d", &data);
                toInsert(data);
            }
            else if (!strcmp(cmd, "delete"))
            {
                int data;
                scanf("%d", &data);
                deleteRBT(data);
            }
            else if (!strcmp(cmd, "search"))
            {
                int data;
                scanf("%d", &data);
                RBT temp = search(data);
                if (temp != neel && temp != NULL)
                {
                    if (temp->color == 1)
                        printf("black\n");
                    else
                        printf("red\n");
                }
                else
                    printf("Not found\n");
            }
            else if (!strcmp(cmd, "exist"))
            {
                int data;
                scanf("%d", &data);
                RBT temp = search(data);
                if (temp != neel && temp != NULL)
                    printf("exist\n");
                else
                    printf("Not exist\n");
            }
            else if (!strcmp(cmd, "quit"))
                break;
        }
    }
    end_t = clock();
    return 0;
}

int max(int a, int b)
{
    return (a > b) ? a : b;
}

int height(AVL node)
{
    if (node == NULL)
        return 0;
    return node->height;
}

AVL newNode(int data)
{
    AVL node = (AVL)malloc(sizeof(struct avl));
    node->data = data;
    node->height = 1;
    node->left = NULL;
    node->right = NULL;
    return node;
}

AVL rightRotate(AVL node)
{
    AVL S = node->left;
    AVL T = S->right;
    // start rotate
    S->right = node;
    node->left = T;
    // new height
    node->height = max(height(node->left), height(node->right)) + 1;
    S->height = max(height(S->left), height(S->right)) + 1;
    // S is new root
    return S;
}

AVL leftRotate(AVL node)
{
    AVL S = node->right;
    AVL T = S->left;
    // start rotate
    S->left = node;
    node->right = T;
    // new height
    node->height = max(height(node->left), height(node->right)) + 1;
    S->height = max(height(S->left), height(S->right)) + 1;

    return S;
}

int balance(AVL node)
{
    if (node == NULL)
        return 0;
    return height(node->left) - height(node->right);
}

AVL insert(AVL node, int data)
{
    if (node == NULL)
        return newNode(data);
    if (data < node->data)
        node->left = insert(node->left, data);
    else if (data > node->data)
        node->right = insert(node->right, data);
    else // no same data
        return node;
    node->height = max(height(node->left), height(node->right)) + 1;
    int BT = balance(node);
    // LL
    if (BT > 1 && data < node->left->data)
        return rightRotate(node);
    // RR
    if (BT < -1 && data > node->right->data)
        return leftRotate(node);
    // LR
    if (BT > 1 && data > node->left->data)
    {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    // RL
    if (BT < -1 && data < node->right->data)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    return node;
}

void findKey(AVL node, int key)
{
    AVL temp = node;
    while (temp != NULL && temp->data != key)
    {
        if (temp->data > key)
            temp = temp->left;
        else if (temp->data < key)
            temp = temp->right;
    }
    if (temp == NULL)
        printf("Not exist\n");
    else
    {
        printf("exist\n");
        return;
    }
}

AVL updateAVL(AVL node)
{
    int BT = balance(node);
    if (BT > 1)
    {
        // LL
        if (node->left && node->left->left)
            return rightRotate(node);
        // LR
        else
        {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
    }
    else if (BT < -1)
    {
        // RR
        if (node->right && node->right->right)
            return leftRotate(node);
        // RL
        else
        {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
    }
    // safe
    return node;
}

void updateHeight(AVL node)
{
    if (node == NULL)
        return;
    node->height = max(height(node->left), height(node->right)) + 1;
}

AVL deleteAVL(AVL node, int key)
{
    // nothing
    if (node == NULL)
        return node;
    if (key < node->data)
        node->left = deleteAVL(node->left, key);
    else if (key > node->data)
        node->right = deleteAVL(node->right, key);
    else if (key == node->data)
    {
        // one child or no child case
        if (node->left == NULL)
        {
            AVL temp = node->right;
            free(node);
            return temp;
        }
        else if (node->right == NULL)
        {
            AVL temp = node->left;
            free(node);
            return temp;
        }
        else
        {
            // two children case
            AVL temp = node;
            while (temp && temp->left)
                temp = temp->left;
            node->data = temp->data;
            node->right = deleteAVL(node->right, temp->data);
        }
    }
    else
        return node;
    updateHeight(node);
    node = updateAVL(node);
    return node;
}

void getF(AVL node, int key)
{
    AVL temp = node;
    while (temp != NULL)
    {
        if (temp->data == key)
            break;
        else if (temp->data > key)
            temp = temp->left;
        else if (temp->data < key)
            temp = temp->right;
    }
    if (temp == NULL)
        printf("Not found\n");
    else
        printf("%d\n", balance(temp));
}

RBT newTree(int data)
{
    RBT node = (RBT)malloc(sizeof(struct rbt));
    node->data = data;
    node->color = 0; // means red
    node->left = NULL;
    node->right = NULL;
    node->parent = NULL;
    return node;
}

void rotateRight(RBT node)
{
    RBT left = node->left;
    node->left = left->right;
    if (left->right != neel)
        left->right->parent = node;
    left->parent = node->parent;
    if (node->parent == neel)
        root = left;
    else if (node == node->parent->left)
        node->parent->left = left;
    else
        node->parent->right = left;
    left->right = node;
    node->parent = left;
}

void rotateLeft(RBT node)
{
    RBT right = node->right;
    node->right = right->left;
    if (right->left != neel)
        right->left->parent = node;
    right->parent = node->parent;
    if (node->parent == neel)
        root = right;
    else if (node == node->parent->left)
        node->parent->left = right;
    else
        node->parent->right = right;
    right->left = node;
    node->parent = right;
}

void toInsert(int data)
{
    RBT x = root;
    RBT y = neel;
    RBT node = newTree(data);
    while (x != neel)
    {
        y = x;
        if (node->data < x->data)
            x = x->left;
        else if (node->data > x->data)
            x = x->right;
        else
            return;
    }
    node->parent = y;
    if (y == neel)
        root = node;
    else if (node->data < y->data)
        y->left = node;
    else
        y->right = node;
    node->left = neel;
    node->right = neel;
    insertFix(node);
    neel->parent = root;
}

void insertFix(RBT currentNode)
{

    while (currentNode->parent->color == 0)
    {
        // parent is grand->left
        if (currentNode->parent == currentNode->parent->parent->left)
        {
            RBT uncle = currentNode->parent->parent->right;
            // case1 : uncle is red
            if (uncle->color == 0)
            {
                currentNode->parent->color = 1;
                uncle->color = 1;
                currentNode->parent->parent->color = 0;
                currentNode = currentNode->parent->parent;
            }
            // case2 & 3 : uncle is black
            else
            {
                if (currentNode == currentNode->parent->right)
                {
                    currentNode = currentNode->parent;
                    rotateLeft(currentNode);
                }
                currentNode->parent->color = 1;
                currentNode->parent->parent->color = 0;
                rotateRight(currentNode->parent->parent);
            }
        }
        // parent is grand->right
        else
        {
            RBT uncle = currentNode->parent->parent->left;
            // case 1 : uncle is red
            if (uncle->color == 0)
            {
                currentNode->parent->color = 1;
                uncle->color = 1;
                currentNode->parent->parent->color = 0;
                currentNode = currentNode->parent->parent;
            }
            // case 2 & 3 : same as above
            else
            {
                if (currentNode == currentNode->parent->left)
                {
                    currentNode = currentNode->parent;
                    rotateRight(currentNode);
                }
                currentNode->parent->color = 1;
                currentNode->parent->parent->color = 0;
                rotateLeft(currentNode->parent->parent);
            }
        }
    }
    root->color = 1; // make sure root is black
}

RBT search(int key)
{
    RBT current = root;
    while (current != neel && current->data != key)
    {
        if (current->data > key)
            current = current->left;
        else
            current = current->right;
    }
    if (current == neel)
        return NULL;
    else
        return current;
}

RBT leftmost(RBT current)
{
    while (current->left != neel)
        current = current->left;
    return current;
}

RBT successor(RBT current)
{
    if (current->right != neel)
        return leftmost(current->right);
    RBT current_pt = current->parent;
    while (current_pt != neel && current == current_pt->right)
    {
        current = current_pt;
        current_pt = current_pt->parent;
    }
    return current_pt;
}

void deleteRBT(int key)
{
    RBT toDelete = search(key);
    if (toDelete == NULL)
        return;
    RBT x, y;
    if (toDelete->left == neel || toDelete->right == neel)
        y = toDelete;
    else
        y = successor(toDelete);
    if (y->left != neel)
        x = y->left;
    else
        x = y->right;

    x->parent = y->parent;

    if (y->parent == neel)
        root = x;
    else if (y == y->parent->left)
        y->parent->left = x;
    else
        y->parent->right = x;

    if (y != toDelete)
        toDelete->data = y->data;

    if (y->color == 1)
        deleteFix(x);
    neel->parent = root;
}

void deleteFix(RBT current)
{
    while (current != root && current->color == 1)
    {
        if (current == current->parent->left)
        {
            RBT sibling = current->parent->right;
            if (sibling->color == 0)
            {
                sibling->color = 1;
                current->parent->color = 0;
                rotateLeft(current->parent);
                sibling = current->parent->right;
            }
            if (sibling->left->color == 1 && sibling->right->color == 1)
            {
                sibling->color = 0;
                current = current->parent;
            }
            else
            {
                if (sibling->right->color == 1)
                {
                    sibling->left->color = 1;
                    sibling->color = 0;
                    rotateRight(sibling);
                    sibling = current->parent->right;
                }
                sibling->color = current->parent->color;
                current->parent->color = 1;
                sibling->right->color = 1;
                rotateLeft(current->parent);
                current = root;
            }
        }
        else
        {
            RBT sibling = current->parent->left;
            if (sibling->color == 0)
            {
                sibling->color = 1;
                current->parent->color = 0;
                rotateRight(current->parent);
                sibling = current->parent->left;
            }
            if (sibling->left->color == 1 && sibling->right->color == 1)
            {
                sibling->color = 0;
                current = current->parent;
            }
            else
            {
                if (sibling->left->color == 1)
                {
                    sibling->right->color = 1;
                    sibling->color = 0;
                    rotateLeft(sibling);
                    sibling = current->parent->left;
                }
                sibling->color = current->parent->color;
                current->parent->color = 1;
                sibling->left->color = 1;
                rotateRight(current->parent);
                current = root;
            }
        }
    }
    current->color = 1;
}
