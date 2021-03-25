#include <stdlib.h>
#include <stdio.h>

#include "huct.h"

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
                        /*puts("FREED SINGLE NODE");*/
                        continue;
                  }
                  struct h_node* prev = hs->ind_opts[i].node;
                  for(struct h_node* hn = prev->next; hn != hs->ind_opts[i].end; hn = hn->next){
                        free(prev);
                        /*puts("FREED PREV NODE");*/
                        prev = hn;
                  }
                  free(prev);
                  free(hs->ind_opts[i].end);
                  /*puts("FREED FINAL TWO NODES");*/
            }
      }
      free(hs->ind_opts);
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

float hash_spread(struct h_struct* hs){
      float n_unique = 0, n_entries = 0;
      for(int i = 0; i < hs->n_buckets; ++i){
            /*num larger with more variety*/
            /*nunique/nbuckets*/
            /*for(struct h_node* hn = hs->ind_opts[i].)*/
            n_unique += (_Bool)hs->ind_opts[i].n_occupants;
            n_entries += hs->ind_opts[i].n_occupants;
      }
      return n_unique/n_entries;
}
