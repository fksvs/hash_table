#ifndef HASH_TABLE
#define HASH_TABLE

#define EMPTY 0
#define FULL 1
#define USED 2

#define FNV_OFFSET 14695981039346656037UL
#define FNV_PRIME 1099511628211UL

typedef struct {
	void *key;
	size_t key_size;
	void *data;
	size_t data_size;
} entry;

typedef struct {
        size_t table_size;
	entry *value;
	int (*cmp)(void *a, void *b);
	int flag;
} hash_table;

hash_table *create_table(size_t table_size);
void delete_table(hash_table *table);

unsigned long hash_func(hash_table *table, void *key, size_t key_size);

hash_table *search_entry(hash_table *table, void *key, size_t key_size);

void delete_entry(entry *value);
hash_table *del_entry(hash_table *table, void *key, size_t key_size);

entry *create_entry(void *key, size_t key_size, void *data, size_t data_size);
hash_table *add_entry(hash_table *table, void *key, size_t key_size, 
                      void *data, size_t data_size,
		      int (*cmp)(void *a, void *b));

#endif
