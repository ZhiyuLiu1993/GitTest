
/*************************
*** File myhash.c
**************************/
#include "myhash.h"

//int类型hashCode
int myHashCodeInt(void * a)
{
    int * aa = (int *) a;
    return *aa;
}

//int类型相等的方法
int myEqualInt(void * a, void *b)
{
    int *aa = (int*) a;
    int *bb = (int *) b;
    return *aa == *bb;
}

//创建HashSet
MyHashSet *createMyHashSet(int(*hashCode)(void *data), int(*equal)(void *data1, void *data2))
{
    MyHashSet *re = (MyHashSet *)malloc(sizeof(MyHashSet));
    re->size = 0;
    re->loadFactor = DEFAULT_LOAD_FACTOR;
    re->initialCapacity = DEFAULT_INITIAL_CAPACITY;
    re->dataList = (MyList **) malloc(sizeof(MyList*) * re->initialCapacity);
    re->hashCode = hashCode;
    re->equal = equal;
    for (int i = 0; i < re->initialCapacity; i++)
    {
        re->dataList[i] = createMySearchList(equal);
    }
    return re;
}

//使用全部参数创建HashSet
MyHashSet *createMyHashSetForAll(int initialCapacity, float loadFactor, int(*hashCode)(void *data), int(*equal)(void *data1, void *data2))
{
    MyHashSet *re = createMyHashSet(hashCode, equal);
    re->initialCapacity = initialCapacity;
    re->loadFactor = loadFactor;
    return re;
}

//释放HashSet
void freeMyHashSet(MyHashSet * set)
{
    for (int i = 0; i < set->initialCapacity; i++)
    {
        freeMyList(set->dataList[i]);
    }
    free(set->dataList);
    free(set);
}

//是否包含某个data
int myHashSetContains(MyHashSet * const set, void * const data)
{
    int hasCode = (*(set->hashCode))(data);
    hasCode %= set->initialCapacity;
    if (hasCode<0)
        hasCode+=set->initialCapacity;
    int re = myListFindDataIndex(set->dataList[hasCode], data);
    return re > -1;
}

void rebuildMyHashSet(MyHashSet * set)
{
    int newSize = set->initialCapacity * 2;
    MyList **newdataList = (MyList **) malloc(sizeof(MyList*) * newSize);
    for (int i = 0; i < newSize; i++)
    {
        newdataList[i] = createMyList();
    }
    MyHashSetIterator* it = createMyHashSetIterator(set);
    while (myHashSetIteratorHasNext(it))
    {
        void * data = myHashSetIteratorNext(it);
        int hasCode = (*(set->hashCode))(data);
        hasCode %= newSize;
        myListInsertDataAtLast(newdataList[hasCode], data);
    }
    freeMyHashSetIterator(it);
    for (int i = 0; i < set->initialCapacity; i++)
    {
        freeMyList(set->dataList[i]);
    }
    free(set->dataList);
    set->dataList = newdataList;
    set->initialCapacity = newSize;
}

//增加一条数据,返回是否添加成功
int myHashSetAddData(MyHashSet * const set, void * const data)
{
    int hasCode = (*(set->hashCode))(data);
    hasCode %= set->initialCapacity;
    if (hasCode<0)
        hasCode+=set->initialCapacity;
    int re = myListFindDataIndex(set->dataList[hasCode], data);
    if (re == -1)
    {
        myListInsertDataAtLast(set->dataList[hasCode], data);
        (set->size)++;
        if (set->size > set->initialCapacity * set->loadFactor)
        {
            rebuildMyHashSet(set);
        }
        return 1;
    }
    return 0;
}

//数据的容量
int myHashSetGetSize(const MyHashSet * const set)
{
    return set->size;
}

//创建迭代器
MyHashSetIterator* createMyHashSetIterator(MyHashSet * const set)
{
    MyHashSetIterator* re = (MyHashSetIterator*) malloc(
            sizeof(MyHashSetIterator));
    re->count = 0;
    re->index = 0;
    re->set = set;
    re->current = set->dataList[0]->first;
    return re;
}

//释放迭代器
void freeMyHashSetIterator(MyHashSetIterator* iterator)
{
    free(iterator);
}

//迭代器是否有下一个
int myHashSetIteratorHasNext(MyHashSetIterator* iterator)
{
    return iterator->count < iterator->set->size;
}

//遍历下一个元素
void* myHashSetIteratorNext(MyHashSetIterator* iterator)
{
    (iterator->count)++;
    while (!(iterator->current))
    {
        (iterator->index)++;
        iterator->current = iterator->set->dataList[iterator->index]->first;
    }
    void * re = iterator->current->data;
    iterator->current = iterator->current->next;
    return re;
}

//删除一条数据，返回是否删除成功
int myHashSetRemoveData(MyHashSet * const set, void * const data)
{
    int hasCode = (*(set->hashCode))(data);
    hasCode %= set->initialCapacity;
    if (hasCode<0)
        hasCode+=set->initialCapacity;
    int re = myListRemoveDataObject(set->dataList[hasCode], data);
    if (re)
    {
        (set->size)--;
    }
    return re;
}

//将第二个Set的全部对象加入到第一个，返回增加的个数
int myHashSetAddAllSet(MyHashSet * set,MyHashSet *other)
{
    int ssize=set->size;
    MyHashSetIterator * it=createMyHashSetIterator(other);
    while (myHashSetIteratorHasNext(it))
    {
        myHashSetAddData(set,myHashSetIteratorNext(it));
    }
    freeMyHashSetIterator(it);
    int re=set->size-ssize;
    return re;
}

//复制HashSet
MyHashSet* myHashSetCopy(MyHashSet * set)
{
    MyHashSet* re=createMyHashSetForAll(set->initialCapacity,set->loadFactor,set->hashCode,set->equal);
    myHashSetAddAllSet(re,set);
    return re;
}

//遍历
void myHashSetOutput(MyHashSet *set, void(*pt)(void*))
{
    MyHashSetIterator * it=createMyHashSetIterator(set);
    while (myHashSetIteratorHasNext(it))
    {
        pt(myHashSetIteratorNext(it));
    }
    freeMyHashSetIterator(it);
}