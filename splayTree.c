#include<stdio.h>
#include<stdlib.h>

struct node {
    int key;
    struct node *left, *right;
};

struct node* newNode(int key) {
    struct node* node = (struct node*) malloc(sizeof(struct node));
    node->key = key;
    node->left = node->right = NULL;
    return (node);
}

struct node *rightRotate(struct node *x) {
    struct node *y = x->left;
    x->left = y->right;
    y->right = x;
    return y;
}

struct node *leftRotate(struct node *x) {
    struct node *y = x->right;
    x->right = y->left;
    y->left = x;
    return y;
}

struct node *splay(struct node *root, int key) {
    if (root == NULL || root->key == key)
        return root;
    if (root->key > key) {
        if (root->left == NULL)
            return root;
        if (root->left->key > key) {
            root->left->left = splay(root->left->left, key);
            root = rightRotate(root);
        } else if (root->left->key < key)
        {
            root->left->right = splay(root->left->right, key);
            if (root->left->right != NULL)
                root->left = leftRotate(root->left);
        }
        return (root->left == NULL) ? root : rightRotate(root);
    } else
    {
        if (root->right == NULL)
            return root;
        if (root->right->key > key) {
            root->right->left = splay(root->right->left, key);
            if (root->right->left != NULL)
                root->right = rightRotate(root->right);
        } else if (root->right->key < key)
        {
            root->right->right = splay(root->right->right, key);
            root = leftRotate(root);
        }
        return (root->right == NULL) ? root : leftRotate(root);
    }
}

struct node *search(struct node *root, int key) {
    return splay(root, key);
}

void preOrder(struct node *root) {
    if (root != NULL) {
        printf("%d ", root->key);
        preOrder(root->left);
        preOrder(root->right);
    }
}

struct node *minValueNode(struct node *node)
{
    struct node *current = node;

    while (current && current->left != NULL)
        current = current->left;

    return current;
}

struct node *bstDeletion(struct node *root, int key)
{
    if (root == NULL) return root;

    if (key < root->key)
        root->left = bstDeletion(root->left, key);
    else if (key > root->key)
        root->right = bstDeletion(root->right, key);

    else
    {
        if (root->left == NULL)
        {
            struct node *temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL)
        {
            struct node *temp = root->left;
            free(root);
            return temp;
        }
        struct node *temp = minValueNode(root->right);
        root->key = temp->key;
        root->right = bstDeletion(root->right, temp->key);
    }
    return root;
}


struct node *deletion(struct node *node, int key) {
    if(key != node->key) {
        return node;
    }
    if(node->left == NULL) {
        return node->right;
    } else if(node->right == NULL){
        return node->left;
    } else {
        return bstDeletion(node, node->key);
    }
}

struct node *insert(struct node *node, int key)
{
    if (node == NULL)
        return newNode(key);
    if (key < node->key)
        node->left = insert(node->left, key);
    else if(key > node->key)
        node->right = insert(node->right, key);

    return node;
}

int main() {
    struct node *root = NULL;
    int ch, data;
    while (1)
    {
        printf("SPLAY TREE\n1.Insertion\n2. Deletion\n3. Display\n4. Exit");
        printf("\nSelect any 1...");
        scanf("%d", &ch);
        switch (ch)
        {
        case 1:
            printf("Enter the element to insert:");
            scanf("%d", &data);
            root = insert(root, data);
            root = splay(root, data);
            preOrder(root);
            break;
        case 2:
            printf("Enter the element to delete:");
            scanf("%d", &data);
            root = splay(root, data);
            root = deletion(root, data);
            preOrder(root);
            break;
        case 3:
            preOrder(root);
            break;
        case 4:
            exit(0);
        default:
            printf("Not available\n");
            break;
        }
        printf("\n");
    }
    return 0;
}
