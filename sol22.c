#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// Creating a structure to represent a node in the heap
typedef struct Node
{
    struct Node *par; // par pointer
    struct Node *ch;  // ch pointer
    struct Node *l;   // Pointer to the node on the l
    struct Node *r;   // Pointer to the node on the r
    int key;          // key of the node
    int val;          // value of the node
    int deg;          // deg of the node
    char mark;        // Black or white mark of the node
    char c;           // Flag for assisting in the Find node function
} Node;

// Creating min pointer as "mini"
Node *mini = NULL;

// Declare an integer for number of nodes in the heap
int size = 0;

// Function to insert a node in heap
void insertion(int val, int key)
{
    Node *new = (Node *)malloc(sizeof(Node));
    new->key = key;
    new->val = val;
    new->deg = 0;
    new->mark = 'W';
    new->c = 'N';
    new->par = NULL;
    new->ch = NULL;
    new->l = new;
    new->r = new;
    if (mini != NULL)
    {
        (mini->l)->r = new;
        new->r = mini;
        new->l = mini->l;
        mini->l = new;
        if (new->key < mini->key)
            mini = new;
    }
    else
    {
        mini = new;
    }
    size++;
}
// Linking the heap nodes in par ch relationship
void Fibonnaci_link(Node *a, Node *b)
{
    (a->l)->r = a->r;
    (a->r)->l = a->l;
    if (b->r == b)
        mini = b;
    a->l = a;
    a->r = a;
    a->par = b;
    if (b->ch == NULL)
        b->ch = a;
    a->r = b->ch;
    a->l = (b->ch)->l;
    ((b->ch)->l)->r = a;
    (b->ch)->l = a;
    if (a->key < (b->ch)->key)
        b->ch = a;
    b->deg++;
}
// Consolidating the heap
void Consolidate()
{
    int temp1;
    float temp2 = (log(size)) / (log(2));
    int temp3 = temp2;
    Node *arr[temp3 + 1];
    for (int i = 0; i <= temp3; i++)
        arr[i] = NULL;
    Node *b = mini;
    Node *a;
    Node *c;
    Node *d = b;
    //do circular
    do
    {
        d = d->r;
        temp1 = b->deg;
        while (arr[temp1] != NULL)
        {
            a = arr[temp1];
            //make b smaller than a
            if (b->key > a->key)
            {
                c = b;
                b = a;
                a = c;
            }
            if (a == mini)
                mini = b;
            Fibonnaci_link(a, b);
            if (b->r == b)
                mini = b;
            arr[temp1] = NULL;
            temp1++;
        }
        arr[temp1] = b;
        b = b->r;
    } while (b != mini);
    mini = NULL;
    for (int j = 0; j <= temp3; j++)
    {
        if (arr[j] != NULL)
        {
            arr[j]->l = arr[j];
            arr[j]->r = arr[j];
            if (mini != NULL)
            {
                (mini->l)->r = arr[j];
                arr[j]->r = mini;
                arr[j]->l = mini->l;
                mini->l = arr[j];
                if (arr[j]->key < mini->key)
                    mini = arr[j];
            }
            else
            {
                mini = arr[j];
            }
            if (mini == NULL)
                mini = arr[j];
            else if (arr[j]->key < mini->key)
                mini = arr[j];
        }
    }
}

// Function to extract minimum node in the heap
void Extract_min(int *val, int *key)
{
    if (mini == NULL)
        ;
    // printf("The heap is empty");
    else
    {
        *val = mini->val;
        *key = mini->key;
        Node *temp = mini;
        Node *pntr;
        pntr = temp;
        Node *x = NULL;
        if (temp->ch != NULL)
        {

            x = temp->ch;
            do
            {
                pntr = x->r;
                (mini->l)->r = x;
                x->r = mini;
                x->l = mini->l;
                mini->l = x;
                if (x->key < mini->key)
                    mini = x;
                x->par = NULL;
                x = pntr;
            } while (pntr != temp->ch);
        }
        (temp->l)->r = temp->r;
        (temp->r)->l = temp->l;
        mini = temp->r;
        if (temp == temp->r && temp->ch == NULL)
            mini = NULL;
        else
        {
            mini = temp->r;
            Consolidate();
        }
        size--;
    }
}

// Cutting a node in the heap to be placed in the root list
void Cut(Node *found, Node *temp)
{
    if (found == found->r)
        temp->ch = NULL;

    (found->l)->r = found->r;
    (found->r)->l = found->l;
    if (found == temp->ch)
        temp->ch = found->r;

    temp->deg = temp->deg - 1;
    found->r = found;
    found->l = found;
    (mini->l)->r = found;
    found->r = mini;
    found->l = mini->l;
    mini->l = found;
    found->par = NULL;
    found->mark = 'B';
}

// Recursive cascade cutting function
void Cascase_cut(Node *temp)
{
    Node *ptr5 = temp->par;
    if (ptr5 != NULL)
    {
        if (temp->mark == 'W')
        {
            temp->mark = 'B';
        }
        else
        {
            Cut(temp, ptr5);
            Cascase_cut(ptr5);
        }
    }
}

// Function to decrease the value of a node in the heap
void Decrease_key(Node *found, int val)
{
    // if (mini == NULL)
    //     printf("The Heap is Empty");

    if (found == NULL)
        printf("Node not found in the Heap");

    found->key = val;

    Node *temp = found->par;
    if (temp != NULL && found->key < temp->key)
    {
        Cut(found, temp);
        Cascase_cut(temp);
    }
    if (found->key < mini->key)
        mini = found;
}

// Function to find the given node
void Find(Node *mini, int old_key, int key, int val)
{
    Node *found = NULL;
    Node *temp5 = mini;
    temp5->c = 'Y';
    Node *found_ptr = NULL;
    if (temp5->key == old_key && temp5->val == val)
    {
        found_ptr = temp5;
        temp5->c = 'N';
        found = found_ptr;
        Decrease_key(found, key);
    }
    if (found_ptr == NULL)
    {
        if (temp5->ch != NULL)
            Find(temp5->ch, old_key, key, val);
        if ((temp5->r)->c != 'Y')
            Find(temp5->r, old_key, key, val);
    }
    temp5->c = 'N';
    found = found_ptr;
}

// Deleting a node from the heap
void Deletion(int val, int key)
{
    if (mini == NULL)
        ;
    // printf("The heap is empty");
    else
    {
        int old_key = key;
        // Decreasing the value of the node to 0
        Node *del = NULL;
        for (Node *ptr = mini->r; ptr != mini; ptr = ptr->r)
        {
            if (ptr->key == key && ptr->val == val && ptr->ch == NULL)
                del = ptr;
        }

        if (del)
        {
            del->l->r = del->r;
            del->r->l = del->l;
        }
        else
        {
            Find(mini, key, -99999, val);
            // Calling Extract_min function to
            // delete minimum value node, which is 0
            int key, val;
            Extract_min(&val, &key);
        }
        // printf("Key Deleted%d %d\n", old_key, val);
    }
}

void print(Node *node)
{
    printf("key: %d val: %d\n", node->key, node->val);
    if (node->ch != NULL)
    {
        print(node->ch);
    }

    for (Node *ptr = node->r; ptr != node; ptr = ptr->r)
        printf("key: %d val: %d\n", ptr->key, ptr->val);
}

// Driver code
int main()
{
    // We will create a heap and insert 3 nodes into it
    char str[15];
    int dcr;
    int key;
    int val;
    while (*str != 'q')
    {
        scanf("%s", str);
        if (*str == 'i')
        {
            scanf("%d%d", &key, &val);
            insertion(val, key);
        }
        else if (*str == 'd')
        {
            if (*(str + 2) == 'l')
            {
                scanf("%d%d", &key, &val);
                Deletion(val, key);
            }
            else
            {
                scanf("%d%d%d", &key, &val, &dcr);
                Find(mini, key, key - dcr, val);
            }
        }
        else if (*str == 'e')
        {
            if (mini)
            {
                Extract_min(&val, &key);
                printf("(%d)%d\n", key, val);
            }
        }
    }
    return 0;
}