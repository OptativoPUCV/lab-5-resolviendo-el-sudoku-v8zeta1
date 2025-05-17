#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct{
   int sudo[9][9];
}Node;

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n){
    Node* new=(Node*) malloc(sizeof(Node));
    *new = *n;
    return new;
}

Node* read_file (char* file_name){
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          if(!fscanf (file, "%d", &n->sudo[i][j]))
            printf("failed to read data!");
       }
  }

  fclose (file);
  return n;
}

void print_node(Node* n){
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++)
          printf("%d ", n->sudo[i][j]);
       printf("\n");
    }
    printf("\n");
}

int is_valid(Node* n){
  for(int i = 0 ; i < 9 ; i++) {
    int array[10] = {0};
    for(int j = 0 ; j < 9 ; j++) {
      int num = n->sudo[i][j];
      if(num != 0) {
        if(array[num]) return 0;
        array[num] = 1;
      }
    }
  }
  for(int j = 0 ; j < 9 ; j++) {
    int array[10] = {0};
    for(int i = 0 ; i < 9 ; i++) {
      int num = n->sudo[i][j];
      if(num != 0) {
        if(array[num]) return 0;
        array[num] = 1;
      }
    }
  }
  for(int k = 0 ; k < 9 ; k++) {
    int array[10] = {0};
    for(int p = 0 ; p < 9 ; p++) {
      int i = 3 * (k/3) + (p/3);
      int j = 3 * (k%3) + (p%3);
      int num = n->sudo[i][j];
      if(num != 0) {
        if(array[num]) return 0;
        array[num] = 1;
      }
    }
  }
  return 1;
}

List* get_adj_nodes(Node* n) {
  List* list = createList();
  int encontrado = 0;
  for(int i = 0 ; i < 9 && !encontrado ; i++) {
    for(int k = 0 ; k < 9 && !encontrado ; k++) {
      if(n->sudo[i][k] == 0) {
        encontrado = 1;
        for(int num = 1 ; num <= 9 ; num++) {
          Node* new_node = copy(n);
          new_node->sudo[i][k] = num;
          if(is_valid(new_node)) {
            pushBack(list, new_node);
          }
          else {
            free(new_node);
          }
        }
      }
    }
  }
  return list;
}

int is_final(Node* n){
  for(int i = 0 ; i < 9 ; i++) {
    for(int j = 0 ; j < 9 ; j++) {
      if(n->sudo[i][j] == 0) return 0;
    }
  }
  return 1;
}

Node* DFS(Node* initial, int* cont){
  Stack* stack = createStack();
  push(stack, initial);
  *cont = 0;
  while(!is_empty(stack)) {
    (*cont)++;
    Node* top_node = top(stack);
    pop(stack);
    if(is_final(top_node)) {
      while(!is_empty(stack)) {
        Node* temp = top(stack);
        pop(stack);
        free(temp);
      }
      return top_node;
    }
    List* adj_nodes = get_adj_nodes(top_node);
    Node* adj_node = first(adj_nodes);
    while(adj_node != NULL) {
      push(stack, adj_node);
      adj_node = next(adj_nodes);
    }
    free(top_node);
    free(adj_nodes);
  }
  return NULL;
}

/*int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/