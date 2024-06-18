#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 20

typedef struct {
  char* directories[MAX_SIZE];
  int top;
} DirStack;

void initStack(DirStack* stack) {
  stack->top = -1;
}

int isFull(DirStack* stack) {
  return stack->top == MAX_SIZE - 1;
}

int isEmpty(DirStack* stack) {
  return stack->top == -1;
}

void push(DirStack* stack, char* dir) {
  if (isFull(stack)) {
    printf("Error: Stack overflow\n");
    return;
  }
  stack->top++;
  stack->directories[stack->top] = malloc(strlen(dir) + 1);
  strcpy(stack->directories[stack->top], dir);
}

char* pop(DirStack* stack) {
  if (isEmpty(stack)) {
    printf("Error: Stack underflow\n");
    return NULL;
  }
  char* dir = stack->directories[stack->top];
  free(dir);
  stack->top--;
  return dir;
}

int main(int argc, char* argv[]) {
  DirStack stack;
  initStack(&stack);

  if (argc == 1) {
    char* dir = pop(&stack);
    if (dir) {
      if (chdir(dir) == -1) {
        perror("chdir");
      }
      free(dir);
    }
  } else if (argc == 2) {
    char* dir = getcwd(NULL, 0);  // Allocate memory for current directory
    if (dir) {
      push(&stack, dir);
      free(dir);  // Free allocated memory after pushing
      if (chdir(argv[1]) == -1) {
        perror("chdir");
      }
    } else {
      perror("getcwd");
    }
  } else {
    printf("Usage: %s [DIR]\n", argv[0]);
  }

  for (int i = stack.top; i >= 0; i--) {
    free(stack.directories[i]);
  }

  return 0;
}
