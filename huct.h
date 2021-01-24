struct h_node{
      /* points to some data */
      void* data;
      struct h_node* next;
};

struct h_node_entry{
      struct h_node* node, * end;
      int n_occupants;
};

struct h_struct{
      int n_buckets;
      struct h_node_entry* ind_opts;
};

void init_h_struct(struct h_struct* hs, int n_buckets);
void free_h_struct(struct h_struct* hs);
void insert_h_data(struct h_struct* hs, void* data, int hasher(void*));
struct h_node* find_h_node(struct h_struct* hs, void* data, int hasher(void*), _Bool dcomp(void*, void*));
float hash_spread(struct h_struct* hs);
