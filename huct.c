#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct h_node{
      /* points to some data */
      void* data;
      /*char* str[100];*/
      struct h_node* next;
};

struct h_node_entry{
      struct h_node* node, * end;
      int n_occupants;
      /*struct h_node* end;*/
};

struct h_struct{
      int n_buckets;
      /*struct h_node* ind_opts;*/
      struct h_node_entry* ind_opts;
};

/*
 * this creates n_buckets linked lists in an array
 * we index into this outer array using insert_h_data,
 * a user provided function
 */
void init_h_struct(struct h_struct* hs, int n_buckets){
      hs->n_buckets = n_buckets;
      hs->ind_opts = calloc(sizeof(struct h_node_entry), hs->n_buckets);
}

void free_h_struct(struct h_struct* hs){
      for(int i = 0; i < hs->n_buckets; ++i){
            if(hs->ind_opts[i].n_occupants){
                  if(hs->ind_opts[i].n_occupants == 1){
                        free(hs->ind_opts[i].node);
                        puts("FREED SINGLE NODE");
                        continue;
                  }
                  struct h_node* prev = hs->ind_opts[i].node;
                  for(struct h_node* hn = prev->next; hn != hs->ind_opts[i].end; hn = hn->next){
                        free(prev);
                        puts("FREED PREV NODE");
                        prev = hn;
                  }
                  free(prev);
                  free(hs->ind_opts[i].end);
                  puts("FREED FINAL TWO NODES");
            }
      }
}

void insert_h_data(struct h_struct* hs, void* data, int hasher(void*)){
      int ind = hasher(data)%hs->n_buckets;
      if(!hs->ind_opts[ind].n_occupants){
            hs->ind_opts[ind].node = hs->ind_opts[ind].end = malloc(sizeof(struct h_node));
            hs->ind_opts[ind].node->next = NULL;
            /* we insert here as a separate case so that we can use end->next in all others */
            hs->ind_opts[ind].node->data = data;
            hs->ind_opts[ind].n_occupants = 1;
            return;
      }
      hs->ind_opts[ind].end->next = malloc(sizeof(struct h_node));
      hs->ind_opts[ind].end->next->data = data;
      hs->ind_opts[ind].end->next->next = NULL;
      hs->ind_opts[ind].end = hs->ind_opts[ind].end->next;
      ++hs->ind_opts[ind].n_occupants;
}

struct h_node* find_h_node(struct h_struct* hs, void* data, int hasher(void*), _Bool dcomp(void*, void*)){
      int ind = hasher(data)%hs->n_buckets;
      if(!hs->ind_opts[ind].n_occupants)return NULL;
      for(struct h_node* hn = hs->ind_opts[ind].node; hn; hn = hn->next){
            if(dcomp(data, hn->data))return hn;
      }
      return NULL;
}

/* user provided functions */
int hasher(void* data){
      char* str = data;
      return (int)*str;
      /*return 4;*/
}

_Bool dcomp(void* str0, void* str1){
      char* s0 = str0, * s1 = str1;
      return !strcmp(s0, s1);
}
/* end user provided functions */

int main(int a, char** b){
      if(a < 2)return 0;
      int n_buckets = atoi(b[1]);

      struct h_struct hs;
      init_h_struct(&hs, n_buckets);
      char str[] = "asher";

      insert_h_data(&hs, (void*)"iota", hasher);
      insert_h_data(&hs, (void*)"iuck", hasher);
      insert_h_data(&hs, (void*)str, hasher);
      insert_h_data(&hs, (void*)str, hasher);
      insert_h_data(&hs, (void*)str, hasher);

      for(int i = 0; i < n_buckets; ++i){
            printf("hs[%2i]: %i occupants\n", i, hs.ind_opts[i].n_occupants);
      }
      puts("");

      struct h_node* found = find_h_node(&hs, (void*)str, hasher, dcomp);
      printf("%sABLE to find entry\n", (found) ? "" : "UN");
      if(found)printf("found entry is %sidentical to input\n", (found->data == str) ? "" : "not ");
      puts("");

      free_h_struct(&hs);

      return 0;
}
