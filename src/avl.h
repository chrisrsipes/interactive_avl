/*
 * @author: Christopher Sipes
 * @title : avl.h
 * @date  : 06/03/2016
 * @desc  : avl tree header file in c
 *          - header file
 */


#ifndef __AVL_H
#define __AVL_H

typedef struct node {
  int data;
  int height;
  struct node *left, *right;
} node;

node *createNode(int data);
node *destroyNode(node *ptr);
node *destroyTree(node *root);
node *insert(node *root, int data);
node *delete(node *root, int query);
int find(node *root, int query);
int max(int a, int b);
int getHeight(node *root);
int calculateHeight(node *root);
void inorder(node *root);
void inorder_verbose(node *root);



#endif
