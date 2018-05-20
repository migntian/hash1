#include "hash.h"
void HashInit(HashTable *ht,HashFunc hash_func)
{
    if(ht == NULL)
    {
        return;
    }
    ht->size = 0;
    ht->func = hash_func;
    size_t i = 0;
    for(;i < HASHMAXSIZE;i++)
    {
        ht->data[i].stat = Empty;
    }
    return;
}
int HashFuncDefault(keytype key)
{
    return (key % HASHMAXSIZE);
}
void HashInsert(HashTable *ht,keytype key,valtype value)
{
    if(ht == NULL)
    {
        return;
    }
    //判断哈希表是否可以插入
    
    if((ht->size) >= (0.8 * HASHMAXSIZE))
    {
        return;//满了
    }
    size_t offset = HashFuncDefault(key);
    while(1)
    {
        if(ht->data[offset].stat != Valid)
        {
            ht->data[offset].stat = Valid;
            ht->data[offset].key = key;
            ht->data[offset].value = value;
            ++ht->size;
            return;
        }
        else if(ht->data[offset].stat == Valid && ht->data[offset].key == key)
        {
            return;
        }
        else
        {
            ++offset;
            if(offset >= HASHMAXSIZE)
            {
                offset = 0;
            }
        }
    }
}
int HashFind(HashTable *ht,keytype key,valtype *value)
{
    if(ht == NULL)
    {
        return 0;
    }
    int offset = HashFuncDefault(key);
    while(1)
    {
        if(ht->data[offset].stat == Valid && ht->data[offset].key == key)
        {
            *value = ht->data[offset].value;
            return 1;
        }
        else if(ht->data[offset].stat == Empty)
        {
            return 0;
        }
        else
        {
            ++offset;
            if(offset >= HASHMAXSIZE)
            {
                offset = 0;
            }

        }
    }
}
void HashRemove(HashTable *ht,keytype key)
{
    if(ht == NULL)
    {
        return;
    }
    valtype value;
    int offset = HashFuncDefault(key);
    int ret = HashFind(ht,key,&value);
    if(ret == 0)
    {
        return;
    }
    else if(ret == 1)
    {
        ht->data[offset].stat = Removed;
        --ht->size;
    }
    //else
    //{
    //    ++offset;
    //    if(offset >= HASHMAXSIZE)
    //    {
    //        offset = 0;
    //    }
    //}
}
void Hashdestroy(HashTable *ht)
{
    if(ht == NULL)
    {
        return;
    }
    ht->size = 0;
    size_t i = 0;
    for(;i < HASHMAXSIZE;i++)
    {
        ht->data[offset].stat = Empty;
    }
}

/////////
//test
/////////
#define HEADER printf("\n==========%s==========\n",__FUNCTION__);
void Hashprint(HashTable *ht)
{
    if(ht == 0)
    {
        return;
    }
    size_t i = 0;
    for(;i < HASHMAXSIZE;i++)
    {
        if(ht->data[i].stat != Valid)
        {
            continue;
        }
        printf("%d:%d\n",ht->data[i].key,ht->data[i].value);
    }
    printf("\n");
}
void testinsert()
{
    HEADER;
    HashTable hash;
    HashInit(&hash,HashFuncDefault);
    HashInsert(&hash,1,1);
    HashInsert(&hash,2,2);
    HashInsert(&hash,2,10);
    HashInsert(&hash,11,11);
    HashInsert(&hash,12,12);
    Hashprint(&hash);
}
void testfind()
{
    HEADER;
    HashTable hash;
    HashInit(&hash,HashFuncDefault);
    HashInsert(&hash,1,1);
    HashInsert(&hash,2,2);
    HashInsert(&hash,2,10);
    HashInsert(&hash,11,11);
    HashInsert(&hash,12,12);
    Hashprint(&hash);
    valtype value;
    int ret = HashFind(&hash,2,&value);
    printf("查找key为2的元素\n");
    printf("excpted ret is 1,actul is %d\n",ret);
    printf("excpted value is 2,actul is %d\n",value);

}
void testremove()
{
    HEADER;
    HashTable hash;
    HashInit(&hash,HashFuncDefault);
    HashInsert(&hash,1,1);
    HashInsert(&hash,2,2);
    HashInsert(&hash,2,10);
    HashInsert(&hash,11,11);
    HashInsert(&hash,12,12);
    HashInsert(&hash,1002,1002);
    Hashprint(&hash);
    valtype value;
    printf("删除key为2的元素\n");
    HashRemove(&hash,2);
    int ret = HashFind(&hash,1002,&value);
    printf("查找key为1002的元素\n");
    printf("excpted ret is 1,actul is %d\n",ret);
    printf("excpted value is 1002,actul is %d\n",value);
}
int main()
{
    testinsert();
    testfind();
    testremove();
    return 0;
}
