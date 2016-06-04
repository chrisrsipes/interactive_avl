/*
 * @author: Christopher Sipes
 * @title : avl.c
 * @date  : 06/03/2016
 * @desc  : avl tree implementation in c
 *          - source file
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <Math.h>
#include "avl.h"

#define DEBUG 1
#define ERROR 1

node *createNode(int data) {
  node *ptr = malloc(sizeof(node));

  if (ptr == NULL) {
    if (ERROR) 
      printf("error allocating memory for node with data %d\n", data);
    return NULL;
  }

  ptr->data = data;
  ptr->height = 0;
  ptr->left = ptr->right = NULL;

  return ptr;
}

node *destroyNode(node *ptr) {
  if (ptr == NULL) 
    return NULL;

  // this is not a delete tree function, so we will
  // not delete if the children are non-empty
  // (because we hate memory leaks (did that need to be said?))
  if (ptr->left != NULL || ptr->right != NULL)
    return ptr;

  free(ptr);

  return NULL;
}

node *destroyTree(node *root) {
  if (root == NULL)
    return NULL;

  if (DEBUG)
    printf("deleteing node with data = %d\n", root->data);

  if (root->left != NULL)
    root->left = destroyTree(root->left);
  
  if (root->right != NULL)
    root->right = destroyTree(root->right);

  destroyNode(root);

  return NULL;
}

int find(node *root, int query) {
  if (root == NULL)
    return 0;

  if (root->data > query)
    return find(root->left, query);
  else if (root->data < query)
    return find(root->right, query);
  else
    return 1;

}

int max(int a, int b) {
  return (a > b) ? a : b;
}

node *rHeavyRotate(node *root) {
  int childBf;
  node *newChildRight, *newLeft;

  if (DEBUG)
    printf("performing right-heavy based rotation with root->data = %d\n", root->data);

  childBf = getHeight(root->right->left) - getHeight(root->right->right);

  // double rotation time, aw yeah, 
  // we're gonna get that first rotation in
  if (childBf > 0) {
    newChildRight = root->right;
    root->right = root->right->left;
    
    // this changes the height
    newChildRight->left = root->right->right;
    newChildRight->height = 1 + max(getHeight(newChildRight->left), getHeight(newChildRight->right));

    // this changes height too
    root->right->right = newChildRight;
    root->right->height = 1 + max(getHeight(root->right->left), getHeight(root->right->right));
  }
 
  // sign match or was double rotation time a sec ago,
  // either way - single rotation time!
  if (childBf != 0) {
    // the root loses a right child, gains the new root's left child in place
    newLeft = root;
    root = root->right;

    // this changes height
    newLeft->right = root->left;
    newLeft->height = 1 + max(getHeight(newLeft->left), getHeight(newLeft->right));

    // surprise!  this does too!
    root->left = newLeft;
    root->height = 1 + max(getHeight(root->left), getHeight(root->right));
  }

  return root;
}

node *lHeavyRotate(node *root) {
  int childBf;
  node *newChildLeft, *newRight;

  if (DEBUG)
    printf("performing left-heavy based rotation with root->data = %d\n", root->data);

  childBf = getHeight(root->left->left) - getHeight(root->left->right);

  // double rotation time, aw yeah, 
  // we're gonna get that first rotation in
  if (childBf < 0) {
    newChildLeft = root->left;
    root->left = root->left->right;
    
    // this changes the height
    newChildLeft->right = root->left->left;
    newChildLeft->height = 1 + max(getHeight(newChildLeft->left), getHeight(newChildLeft->right));

    // this changes height too
    root->left->left = newChildLeft;
    root->left->height = 1 + max(getHeight(root->left->left), getHeight(root->left->right));
  }
 
  // sign match or was double rotation time a sec ago,
  // either way - single rotation time!
  if (childBf != 0) {
    // the root loses a right child, gains the new root's left child in place
    newRight = root;
    root = root->left;

    // this changes height
    newRight->left = root->right;
    newRight->height = 1 + max(getHeight(newRight->left), getHeight(newRight->right));

    // surprise!  this does too!
    root->right = newRight;
    root->height = 1 + max(getHeight(root->left), getHeight(root->right));
  }

  return root;
}

node *insert(node *root, int data) {
  int bf, lh, rh, childBf;
  node *ptr = NULL;

  // if it's an empty tree, insert as root node
  if (root == NULL) {
    ptr = createNode(data);

    printf("inserted node with data = %d\n", ptr->data);

    return ptr;
  }

  if (data < root->data)
    root->left = insert(root->left, data);
  else if (data > root->data)
    root->right = insert(root->right, data); 
  else
    ; // we politely decline to accept duplicates

  lh = getHeight(root->left);
  rh = getHeight(root->right);
  bf = lh - rh;

  root->height = (1 + max(lh, rh));

  // rotate based on balance factor
  if (bf < -1)
    root = rHeavyRotate(root);
  else if (bf > 1)
    root = lHeavyRotate(root);

  return root;
}

node *delete(node *root, int query) {
  int bf;
  node *temp;

  if (root == NULL)
    return NULL;

  // narrow down on query if query != root->data
  if (query < root->data) {
    root->left = delete(root->left, query);
  }
  else if (query > root->data) {
    root->right = delete(root->right, query);
  }
  else {

    if (root->left != NULL && root->right != NULL) {

      // find the max in the left tree
      temp = root->left;
      while (temp->right != NULL) temp = temp->right;

      // overwrite the value of the current node, and delete that node
      // note that since its the max, it'll never have two child nodes
      // and can't cause infinite recursion
      root->data = temp->data;
      root->left = delete(root->left, temp->data);
    }
    else if (root->left != NULL) {
      temp = root->left;
      destroyNode(root);
      root = temp;
    }
    else if (root->right != NULL) {
      temp = root->right;
      destroyNode(root);
      root = temp;
    }
    else {
      root = destroyNode(root);
      return NULL;
    }
  }
  
  // may need to balance out now we've made adjustments
  bf = getHeight(root->left) - getHeight(root->right);

  if (bf < -1)
    root = rHeavyRotate(root);
  else if (bf > 1)
    root = lHeavyRotate(root);

  // adjust height as we go up
  root->height = 1 + max(getHeight(root->left), getHeight(root->right));

  return root;
}

int getHeight(node *root) {
  return (root == NULL) ? -1 : root->height;
}

int calculateHeight(node *root) {
  if (root == NULL)
    return -1;

  return 1 + max(calculateHeight(root->left), calculateHeight(root->right));
}

void inorder(node *root) {

  if (root == NULL) {
    printf("(empty tree)\n");
    return;
  }

  // to be able to identify an empty tree, we needed
  // to guard against traveling to null nodes

  if (root->left != NULL)
    inorder(root->left);

  printf("%d\n", root->data);

  if (root->right != NULL)
    inorder(root->right);

  return;
}

void inorder_verbose(node *root) {

  if (root == NULL) {
    printf("(empty tree)\n");
    return;
  }

  // to be able to identify an empty tree, we needed
  // to guard against traveling to null nodes

  if (root->left != NULL)
    inorder_verbose(root->left);

  printf("%d (height = %d)\n", root->data, getHeight(root));

  if (root->right != NULL)
    inorder_verbose(root->right);

  return;

}

