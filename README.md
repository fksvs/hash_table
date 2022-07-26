Hash Table
---

**you can find a example usage in main.c**

### creating and deleting a hash table

     hash_table *create_table(size_t table_size);

     void delete_table(hash_table *table,size_t table_size);

### add data with a key 

>key and data is (void *), so you can use any type for key and data

     hash_table *add_entry(hash_table *table,size_t table_size,\
             void *key,size_t key_size,void *data,size_t data_size,\
             int (*cmp)(void *a,void *b));

### delete data with a key

     hash_table *del_entry(hash_table *table,size_t table_size,\
             void *key,size_t key_size);

### search entry with a key

     hash_table *search_entry(hash_table *table,size_t table_size,\
             void *key,size_t key_size);

### data structures

  #### entry

     typedef struct{
         void *key;
         size_t key_size;
         void *data;
         size_t data_size;
     } entry;

  #### hash table

     typedef struct{
         entry *value;
         int (*cmp)(void *a,void *b);
         int flag;
     } hash_table;

