# Interactive AVL Tree Implementation

## Use
The interactive.c sourcefile provides the user with an interactive interface to manage an AVL tree.  The commands available to the user are:
* `i:#` - insert some number # into the AVL tree
* `r:#` - insert # number of random integers into the AVL tree (values in range [0, 1000))
* `f:#` - searches for data in AVL tree
* `p:i` - prints the AVL tree inorder
* `p:v` - prints the AVL tree inorder (verbose: + height)
* `d:#` - deletes # from the AVL tree if it exists
* `d:@` - deletes all nodes in the AVL tree
* `q  ` - manually configurable macro 

## Build Instructions
### Compilation
1. `cd /interactive_avl/src`
2. `gcc avl.c interactive.c`

### Execution
3. `./a.out`

### Notes
The header file, avl.h, must be in the directory where the source files are being compiled.  
