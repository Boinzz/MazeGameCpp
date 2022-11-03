#include "avl_tree.h"

#include <cstdlib>

AVLTreeNode* createNode(uint key, void* value, AVLTreeNode* l, AVLTreeNode* r)
{
    AVLTreeNode* out = (AVLTreeNode*)malloc(sizeof(AVLTreeNode));
    out->key = key;
    out->value = value;
    out->left = l;
    out->right = r;
    return out;
}

AVLTree* createTree()
{
    AVLTree* out = (AVLTree*)malloc(sizeof(AVLTree));

    out->mRoot = nullptr;
    return out;
}

int height(AVLTreeNode* tree)
{
    if (tree != nullptr)
        return tree->height;

    return 0;
}

int height(AVLTree* self)
{
    return height(self->mRoot);
}

int _max(int a, int b)
{
    return a > b ? a : b;
}

AVLTreeNode* search(AVLTreeNode* x, uint key)
{
    if (x == nullptr || x->key == key)
        return x;

    if (key < x->key)
        return search(x->left, key);
    else
        return search(x->right, key);
}

AVLTreeNode* search(AVLTree* self, uint key)
{
    return search(self->mRoot, key);
}

AVLTreeNode* maximum(AVLTreeNode* tree)
{
    if (tree == nullptr)
        return nullptr;

    while (tree->right != nullptr)
        tree = tree->right;
    return tree;
}

uint maximum(AVLTree* self)
{
    AVLTreeNode* p = maximum(self->mRoot);
    if (p != nullptr)
        return p->key;

    return 0;
}

AVLTreeNode* leftLeftRotation(AVLTreeNode* k2)
{
    AVLTreeNode* k1;

    k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;

    k2->height = _max(height(k2->left), height(k2->right)) + 1;
    k1->height = _max(height(k1->left), k2->height) + 1;

    return k1;
}

AVLTreeNode* rightRightRotation(AVLTreeNode* k1)
{
    AVLTreeNode* k2;

    k2 = k1->right;
    k1->right = k2->left;
    k2->left = k1;

    k1->height = _max(height(k1->left), height(k1->right)) + 1;
    k2->height = _max(height(k2->right), k1->height) + 1;

    return k2;
}

AVLTreeNode* leftRightRotation(AVLTreeNode* k3)
{
    k3->left = rightRightRotation(k3->left);

    return leftLeftRotation(k3);
}

AVLTreeNode* rightLeftRotation(AVLTreeNode* k1)
{
    k1->right = leftLeftRotation(k1->right);

    return rightRightRotation(k1);
}

AVLTreeNode* insert(AVLTreeNode* tree, uint key, void* value)
{
    if (tree == nullptr)
    {
        tree = createNode(key, value, nullptr, nullptr);
    }
    else if (key < tree->key)
    {
        tree->left = insert(tree->left, key, value);

        if (height(tree->left) - height(tree->right) == 2)
        {
            if (key < tree->left->key)
                tree = leftLeftRotation(tree);
            else
                tree = leftRightRotation(tree);
        }
    }
    else if (key > tree->key)
    {
        tree->right = insert(tree->right, key, value);

        if (height(tree->right) - height(tree->left) == 2)
        {
            if (key > tree->right->key)
                tree = rightRightRotation(tree);
            else
                tree = rightLeftRotation(tree);
        }
    }
    else // key == tree->key)
    {
        tree->value = value;
    }

    tree->height = _max(height(tree->left), height(tree->right)) + 1;

    return tree;
}

void insert(AVLTree* self, uint key, void* value)
{
    self->mRoot = insert(self->mRoot, key, value);
}

AVLTreeNode* remove(AVLTreeNode* tree, AVLTreeNode* z)
{

    if (tree == nullptr || z == nullptr)
        return nullptr;

    if (z->key < tree->key)
    {
        tree->left = remove(tree->left, z);

        if (height(tree->right) - height(tree->left) == 2)
        {
            AVLTreeNode* r = tree->right;
            if (height(r->left) > height(r->right))
                tree = rightLeftRotation(tree);
            else
                tree = rightRightRotation(tree);
        }
    }
    else if (z->key > tree->key)
    {
        tree->right = remove(tree->right, z);
        if (height(tree->left) - height(tree->right) == 2)
        {
            AVLTreeNode* l = tree->left;
            if (height(l->right) > height(l->left))
                tree = leftRightRotation(tree);
            else
                tree = leftLeftRotation(tree);
        }
    }
    else
    {
        if ((tree->left != nullptr) && (tree->right != nullptr))
        {
            if (height(tree->left) > height(tree->right))
            {
                AVLTreeNode* _max = maximum(tree->left);
                tree->key = _max->key;
                tree->left = remove(tree->left, _max);
            }
            else
            {
                AVLTreeNode* min = maximum(tree->right);
                tree->key = min->key;
                tree->right = remove(tree->right, min);
            }
        }
        else
        {
            AVLTreeNode* tmp = tree;
            tree = (tree->left != nullptr) ? tree->left : tree->right;
            delete tmp;
        }
    }

    return tree;
}

void remove(AVLTree* self, uint key)
{
    AVLTreeNode* z;

    if ((z = search(self->mRoot, key)) != nullptr)
        self->mRoot = remove(self->mRoot, z);
}
