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

