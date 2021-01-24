#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "huct.h"

/* user provided functions */
int hasher(void* data){
      char* str = data;
      return (int)*str;
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
