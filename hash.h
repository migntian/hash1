#pragma once
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

#define HASHMAXSIZE 1000

typedef enum{
    Empty,
    Valid,
    Removed
}stat;

typedef int keytype;
typedef int valtype;

typedef int(*HashFunc)(keytype key);
typedef struct HashElem{
    keytype key;
    valtype value;
    stat stat;
}HashElem;
typedef struct HashTable{
    HashElem data[HASHMAXSIZE];
    size_t size;
    HashFunc func;
}HashTable;
void HashInit(HashTable *ht,HashFunc hash_func);
int HashFuncDefault(keytype key);
void HashInsert(HashTable *ht,keytype key,valtype value);
int HashFind(HashTable *ht,keytype key,valtype *value);
void HashRemove(HashTable *ht,keytype key);
void Hashdestroy(HashTable *ht);
