#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

struct node {
  int value;
  struct node *next;
};

struct node* insertNode(int *len, struct node *front, struct node *list, int target) {
  if (list -> value == target) {
    return front;
  }
  if (list -> value > target) {
    struct node *n = malloc(sizeof(struct node));
    n -> value = target;
    n -> next = front;
    front = n;
    (*len)++;
    return front;
  }
  if (list -> value < target) {
    if ((list -> next && list -> next -> value > target) || !(list -> next)) {
      struct node *n = malloc(sizeof(struct node));
      n -> value = target;
      n -> next = list -> next;
      list -> next = n;
      (*len)++;
      return front;
    }
  }
  return insertNode(len, front, list -> next, target);
}

struct node* deleteNode(struct node *front, int target) {
  if (front -> value == target) {
    return front -> next;
  }
  struct node *f;
  struct node *p;
  for (f = front; f -> value != target; f = f -> next) {
    p = f;
  }
  p -> next = f -> next;

  return front;
}

int search(struct node *front, int target) {
  if (!front) {
    return 0;
  }
  struct node *p;
  for (p = front; p != NULL; p = p -> next) {
    if (p -> value == target) {
      return 1;
    }
  }
  return 0;
}

void printList(struct node *list) {
  if (list != NULL) {
    printf(" %d", list -> value);
    printList(list -> next);
  } else {
    printf("\n");
  }
}

int main(int argc, char **argv) {

  //create front of list
  struct node *front = NULL;
  int len = 0;

  //get input
  char c = '\0';
  int n = 0;
  int count = 2;

  while (count >= 2) {
    if (c == 'i') {
      if (!front) {
        front = malloc(sizeof(struct node));
        front -> value = n;
        front -> next = NULL;
        len++;
      }
      else if (!search(front, n)){
        front = insertNode(&len, front, front, n);
      }
    }
    if (c == 'd' && front && search(front, n)) {
      front = deleteNode(front, n);
      len--;
    }
    if (c == 'i' || c == 'd') {
      printf("%d :", len);
      printList(front);
    }

    c = '\0';
    count = scanf(" %c", &c);
    if (c == 'i' || c == 'd') {
      count += scanf("%d", &n);
    }
  }

  free(front);

  return EXIT_SUCCESS;
}
