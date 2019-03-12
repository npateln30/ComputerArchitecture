#include <stdio.h>
#include <stdlib.h>

struct node {
  int value;
  struct node *left;
  struct node *right;
};

struct node* createNode(int target) {
  struct node *n = malloc(sizeof(struct node));
  n -> value = target;
  n -> left = NULL;
  n -> right = NULL;
  return n;
}

void insert(struct node *root, int target) {
  if (root -> value > target) {
    if (!(root -> left)) {
      root -> left = createNode(target);
      return;
    }
    insert(root -> left, target);
  }
  if (root -> value < target) {
    if (!(root -> right)) {
      root -> right = createNode(target);
      return;
    }
    insert(root -> right, target);
  }
}

void delete(struct node *parent, struct node *current, int target) {
  if (current -> value == target) {
    //if leaf node, can just delete the node
    if (!(current -> left) && !(current -> right)) {
      if (current -> value < parent -> value) {
        free(parent -> left);
        parent -> left = NULL;
        return;
      }
      free(parent -> right);
      parent -> right = NULL;
      return;
    }
    //if node has a left, traverse to get next greatest value
    //replace current with next greatest value
    //delete node with next greatest value
    if (current -> left) {
      struct node *f;
      struct node *p = NULL;
      for (f = current -> left; f -> right != NULL; f = f -> right) {
        p = f;
      }
      if (p) {
        current -> value = p -> right -> value;
        delete(p, p -> right, p -> right -> value);
      }
      else {
        int value = current -> left -> value;
        delete(current, current -> left, current -> left -> value);
        current -> value = value;
      }
      return;
    }
    //if no left but there's a right, replace current with the right node
    if (current -> right) {
      struct node *n = current -> right;
      current -> value = current -> right -> value;
      current -> left = current -> right -> left;
      current -> right = current -> right -> right;
      free(n);
      return;
    }
  }
  if (current -> value > target) {
    delete(current, current -> left, target);
    return;
  }
  delete(current, current -> right, target);
  return;
}

int search(struct node *root, int target) {
  if (root == NULL) {
    return 0;
  }
  if (root -> value == target) {
    return 1;
  }
  if (root -> value > target) {
    return search(root -> left, target);
  }
  return search(root -> right, target);
}

void printTree(struct node *root) {
  if (root == NULL) {
    return;
  }
  printf("(");
  printTree(root -> left);
  printf("%d", root -> value);
  printTree(root -> right);
  printf(")");
}

int main() {
  struct node *root = NULL;

  char type = '\0';
  int n = 0;
  int sc = 1;

  while (sc >= 0) {
    if (type == 's') {
      if(search(root, n)) {
        printf("present\n");
      }
      else {
        printf("absent\n");
      }
    }

    if (type == 'i') {
      if (!search(root, n)) {
        if (root == NULL) {
          root = createNode(n);
        }
        else {
          insert(root, n);
        }
        printf("inserted\n");
      }
      else {
        printf("duplicate\n");
      }
    }

    if (type == 'd') {
      if (search(root, n)) {
        if (root -> value == n && !(root -> left) && !(root -> right)) {
          root = NULL;
        }
        else {
          delete(NULL, root, n);
        }
        printf("deleted\n");
      }
      else {
        printf("absent\n");
      }
    }

    type = '\0';
    sc = scanf(" %c", &type);
    if (type == 'p') {
      printTree(root);
      printf("\n");
    }
    if (type == 'i' || type == 's' || type == 'd') {
      sc += scanf("%d", &n);
    }
  }

  free(root);

  return EXIT_SUCCESS;
}
