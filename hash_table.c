#include <stdlib.h>
#include <string.h>
#include "hash_table.h"

hash_table *init_table(size_t table_size)
{
	hash_table *table = malloc(table_size * sizeof(hash_table));
	memset(table, 0, table_size * sizeof(hash_table));
	table->table_size = table_size;

        return table;
}

void delete_table(hash_table *table)
{
	int ind;
	for (ind = 0; ind < table->table_size; ind += 1) {
		if ((table + ind)->flag == FULL) {
			free((table + ind)->value->key);
			free((table + ind)->value->data);
			free((table + ind)->value);
		}
	}
	free(table);
}

unsigned long hash_func(hash_table *table, void *key, size_t key_size)
{
	unsigned long hash = 0;
	int ind = 0;

	hash ^= FNV_OFFSET;
	for (ind = 0; ind < key_size; ind += 1) {
		hash ^= *(char *)(key + ind);
		hash *= FNV_PRIME;
	}
	return hash % table->table_size;
}

hash_table *search_entry(hash_table *table, void *key, size_t key_size)
{
	int ind, hash_ind = hash_func(table, key, key_size);
	ind = hash_ind;

	while ((table + ind)->flag != EMPTY) {
		if ((table + ind)->flag == FULL) {
			if ((table + ind)->cmp((table + ind)->value->key, key) == 0)
				return (table + ind);
		}
		ind = (ind + 1) % table->table_size;
		if (ind == hash_ind)
			break;
	}
	return NULL;
}

void delete_entry(entry *value)
{
	free(value->key);
	free(value->data);
	free(value);
}

hash_table *del_entry(hash_table *table, void *key, size_t key_size)
{
	hash_table *temp = search_entry(table, key, key_size);
	if (temp != NULL) {
		delete_entry(temp->value);
		temp->value = NULL;
		temp->cmp = NULL;
		temp->flag = USED;
		return temp;
	}
	return NULL;
}

entry *create_entry(void *key, size_t key_size, void *data, size_t data_size)
{
	entry *value = malloc(sizeof(entry));
	value->key = malloc(key_size);
	value->data = malloc(data_size);

	memcpy(value->key, key, key_size);
	value->key_size = key_size;
	memcpy(value->data, data, data_size);
	value->data_size = data_size;

	return value;
}

hash_table *add_entry(hash_table *table, void *key, size_t key_size,
                      void *data, size_t data_size,
		      int (*cmp)(void *a, void *b))
{
	int ind, hash_ind = hash_func(table, key, key_size);
	ind = hash_ind;

	while ((table + ind)->flag == FULL) {
		if ((table + ind)->cmp((table + ind)->value->key, key) == 0) {
			delete_entry((table + ind)->value);
			break;
		}
		ind = (ind + 1) % table->table_size;
		if (ind == hash_ind)
			return NULL;
	}
	(table + ind)->value = create_entry(key, key_size, data, data_size);
	(table + ind)->cmp = cmp;
	(table + ind)->flag = FULL;
	return (table + ind);
}
