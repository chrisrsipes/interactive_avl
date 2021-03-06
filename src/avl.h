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

node *destroyTree(node *root);
node *insert(node *root, int data);
node *delete(node *root, int query);
int find(node *root, int query);
int findMin(node *root);
int findMax(node *root);

void inorder(node *root);
void inorder_verbose(node *root);



#endif
