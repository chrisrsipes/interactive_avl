/*
 * @author: Christopher Sipes
 * @title : interactive.c
 * @date  : 06/03/2016
 * @desc  : interactive prompt to interface
 *          with an AVL tree implementation
 *          - main implementation
 *
 */



#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "avl.h"

#define BUFFER_SIZE 10
#define DEBUG 1

void printMenu() {
  printf("\n\n");
  printf("=====================================\n");
  printf("               Menu                  \n");
  printf("=====================================\n");
  printf("i:#  insert #\n");
  printf("r:#  random insert # times\n");
  printf("f:#  find #\n");
  printf("p:i  print out the tree (inorder)\n");
  printf("p:v  print out the tree (inorder)(verbose)\n");
  printf("d:#  delete #\n");
  printf("d:@  delete tree\n");
  printf("q    (macro 1 - autofill)\n");
  printf("\n\n");
  
  return;
}

int isValidInput(char input) {
  return (input == 'i' || input == 'f' || input == 'p' || input == 'r' || input == 'd' || input == 'q');
}

node *captureInsertion(node *root, char *command) {
  return insert(root, atoi(&command[2]));
}

node *captureDelete(node *root, char *command) {
  char dAll = (command[2] == '@');
  return dAll ? destroyTree(root) : delete(root, atoi(&command[2]));
}


node *captureRepeating(node *root, char *command) {
  int i, n = atoi(&command[2]);

  for (i = 0; i < n; i++)
    root = insert(root, rand() % 1000);

  return root;
}

void captureFind(node *root, char *command) {
  int data = atoi(&command[2]);

  printf("searching for %d\n", data);

  if (find(root, data))
    printf("Found %d\n", data);
  else
    printf("Did not find %d\n", data);
  
}

void capturePrint(node *root, char *command) {
  char type, throwaway;

  switch(command[2]) {
    case 'i':
      inorder(root);
      break;
    case 'v':
      inorder_verbose(root);
      break;
    default:
      printf("entered: %s\n", command);
  }

  return;
}

node *insertDefaults(node *root) {
  root = insert(root, 10);
  root = insert(root, 15);
  root = insert(root, 3);
  root = insert(root, 2);

  return root;
}

int main (void) {
  char *command = NULL;
  node *root = NULL;

  command = malloc(sizeof(char) * BUFFER_SIZE);

  srand(time(NULL));

  do {
    printMenu();
    scanf("%s", command);

    // 'z' will skip the rest of the loop,
    // and fail the continuing condition (hopefully)
    if (!isValidInput(command[0])) {
      if (DEBUG) printf("command not recognized. (%c)\n", command[0]);
      continue;
    }

    switch(command[0]) {
      case 'i':
        root = captureInsertion(root, command);
        break;
      case 'r':
        root = captureRepeating(root, command);
        break;
      case 'p':
        capturePrint(root, command);
        break;
      case 'f':
        captureFind(root, command);
        break;
      case 'd':
        root = captureDelete(root, command);
        break;
      case 'q':
        root = insertDefaults(root);
        break;
    }
    
  } while (command[0] != 'z');

  return 0;
}
