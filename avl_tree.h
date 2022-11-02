#pragma once

typedef unsigned int uint;

struct AVLTreeNode
{
    uint key;
    void* value;
    int height;
    AVLTreeNode* left;
    AVLTreeNode* right;
};

struct AVLTree
{
    AVLTreeNode* mRoot;
};

AVLTreeNode* createNode(uint key, void* value, AVLTreeNode* l, AVLTreeNode* r);
AVLTree* createTree();
int height(AVLTreeNode* tree);
int height(AVLTree* self);
int _max(int a, int b);
AVLTreeNode* search(AVLTreeNode* x, uint key);
AVLTreeNode* search(AVLTree* self, uint key);
AVLTreeNode* maximum(AVLTreeNode* tree);
uint maximum(AVLTree* self);
AVLTreeNode* leftLeftRotation(AVLTreeNode* k2);
AVLTreeNode* rightRightRotation(AVLTreeNode* k1);
AVLTreeNode* leftRightRotation(AVLTreeNode* k3);
AVLTreeNode* rightLeftRotation(AVLTreeNode* k1);
AVLTreeNode* insert(AVLTreeNode* tree, uint key, void* value);
void insert(AVLTree* self, uint key, void* value);
AVLTreeNode* remove(AVLTreeNode* tree, AVLTreeNode* z);
void remove(AVLTree* self, uint key);