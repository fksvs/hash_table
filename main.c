#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash_table.h"

#define TABLE_SIZE 5
#define KEY_SIZE 5
#define DATA_SIZE 5

int cmp(void *a, void *b)
{
	return strcmp((char *)a, (char *)b);
}

//basic usage of lib
void test()
{
	//create a table
	hash_table *table = create_table(TABLE_SIZE);

	//add data via key
	add_entry(table, TABLE_SIZE, "key1", KEY_SIZE, "data1", DATA_SIZE,
		  &cmp);
	add_entry(table, TABLE_SIZE, "key2", KEY_SIZE, "data2", DATA_SIZE,
		  &cmp);
	add_entry(table, TABLE_SIZE, "key3", KEY_SIZE, "data3", DATA_SIZE,
		  &cmp);
	add_entry(table, TABLE_SIZE, "key4", KEY_SIZE, "data4", DATA_SIZE,
		  &cmp);
	add_entry(table, TABLE_SIZE, "key5", KEY_SIZE, "data5", DATA_SIZE,
		  &cmp);

	//search entries
	hash_table *temp;
	temp = search_entry(table, TABLE_SIZE, "key1", KEY_SIZE);
	printf("key=%s\tdata=%s\n", (char *)temp->value->key,
	       (char *)temp->value->data);
	temp = search_entry(table, TABLE_SIZE, "key2", KEY_SIZE);
	printf("key=%s\tdata=%s\n", (char *)temp->value->key,
	       (char *)temp->value->data);
	temp = search_entry(table, TABLE_SIZE, "key3", KEY_SIZE);
	printf("key=%s\tdata=%s\n", (char *)temp->value->key,
	       (char *)temp->value->data);
	temp = search_entry(table, TABLE_SIZE, "key4", KEY_SIZE);
	printf("key=%s\tdata=%s\n", (char *)temp->value->key,
	       (char *)temp->value->data);
	temp = search_entry(table, TABLE_SIZE, "key5", KEY_SIZE);
	printf("key=%s\tdata=%s\n", (char *)temp->value->key,
	       (char *)temp->value->data);

	//delete entries
	del_entry(table, TABLE_SIZE, "key1", KEY_SIZE);
	del_entry(table, TABLE_SIZE, "key3", KEY_SIZE);

	//delete hash table
	delete_table(table, TABLE_SIZE);
}

int main()
{
	test();
	return 0;
}
