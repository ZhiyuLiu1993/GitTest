//
// Created by root on 1/22/18.
//

#ifndef CLIONRANTEST_MYHASH_H
#define CLIONRANTEST_MYHASH_H

#include <stdio.h>
#include <malloc.h>

#define DEFAULT_LOAD_FACTOR         0.75
#define DEFAULT_INITIAL_CAPACITY    16

typedef struct myNode
{
    void * data;
    struct myNode *next;
} MyNode;

typedef struct myList
{
    MyNode * first;
    MyNode * last;
    int count;
    int (*equal)(void * a, void * b);
} MyList;

typedef struct myListIterator
{
    MyNode * p;
    int count;
    int allSize;
} MyListIterator;

//创建链表
MyList * createMyList()
{
    MyList * re = (MyList *) malloc(sizeof(MyList));
    re->count = 0;
    re->first = NULL;
    re->last = NULL;
    re->equal = NULL;
    return re;
}

//释放链表
void freeMyList(MyList * list)
{
    MyNode * p;
    while (list->first)
    {
        p = list->first->next;
        free(list->first);
        list->first = p;
    }
    free(list);
}

//插入在尾部
void myListInsertDataAtLast(MyList * const list, void* const data)
{
    MyNode * node = (MyNode *) malloc(sizeof(MyNode));
    node->data = data;
    node->next = NULL;
    if (list->count)
    {
        list->last->next = node;
        list->last = node;
    }
    else
    {
        list->first = node;
        list->last = node;
    }
    (list->count)++;
}

//插入在首部
void myListInsertDataAtFirst(MyList * const list, void* const data)
{
    MyNode * node = (MyNode *) malloc(sizeof(MyNode));
    node->data = data;
    node->next = NULL;

    if (list->count)
    {
        node->next = list->first;
        list->first = node;
    }
    else
    {
        list->first = node;
        list->last = node;
    }
    (list->count)++;
}

//长度
int myListGetSize(const MyList * const list)
{
    return list->count;
}

//打印
void myListOutput(const MyList * const list, void(*pt)(const void * const))
{
    MyNode * p = list->first;
    while (p)
    {
        (*pt)(p->data);
        p = p->next;
    }
}

//删除在首部
void* myListRemoveDataAtFirst(MyList * const list)
{
    MyNode *p = list->first;
    list->first = p->next;
    void * re = p->data;
    free(p);
    (list->count)--;
    if (list->count == 0)
    {
        list->last = NULL;
    }
    return re;
}

//删除在尾部
void* myListRemoveDataAtLast(MyList* const list)
{
    if (list->count == 1)
    {
        return myListRemoveDataAtFirst(list);
    }
    MyNode * p = list->first;
    while (p->next != list->last)
    {
        p = p->next;
    }
    void *re = list->last->data;
    free(list->last);
    p->next = NULL;
    list->last = p;
    (list->count)--;
    return re;
}

//插入
void myListInsertDataAt(MyList * const list, void* const data, int index)
{
    if (index == 0)
    {
        myListInsertDataAtFirst(list, data);
        return;
    }
    if (index == list->count)
    {
        myListInsertDataAtLast(list, data);
        return;
    }
    MyNode * node = (MyNode *) malloc(sizeof(MyNode));
    node->data = data;
    node->next = NULL;

    MyNode * p = list->first;
    for (int i = 0; i < index - 1; i++)
    {
        p = p->next;
    }
    node->next = p->next;
    p->next = node;

    (list->count)++;
}

//删除
void* myListRemoveDataAt(MyList* const list, int index)
{
    if (index == 0)
    {
        return myListRemoveDataAtFirst(list);
    }
    if (index == list->count - 1)
    {
        return myListRemoveDataAtLast(list);
    }

    MyNode * p = list->first;
    for (int i = 0; i < index - 1; i++)
    {
        p = p->next;
    }
    MyNode *tp = p->next;
    p->next = p->next->next;
    void * re = tp->data;
    free(tp);
    (list->count)--;
    return re;
}

//取得第一个数据
void* myListGetDataAtFirst(const MyList * const list)
{
    return list->first->data;
}

//取得最后一个数据
void* myListGetDataAtLast(const MyList * const list)
{
    return list->last->data;
}

//取得数据
void* myListGetDataAt(const MyList * const list, int index)
{
    if (index == list->count - 1)
    {
        return myListGetDataAtLast(list);
    }
    MyNode * p = list->first;
    for (int i = 0; i < index; i++)
    {
        p = p->next;
    }
    return p->data;
}

//查找某个数据的位置,如果equal方法为空，比较地址，否则调用equal方法
//如果不存在返回-1，如果存在，返回出现的第一个位置
int myListFindDataIndex(const MyList * const list, void * data)
{
    MyNode * p = list->first;
    int re = 0;
    if (list->equal)
    {
        while (p)
        {
            if (p->data == data || (*(list->equal))(p->data, data))
            {
                return re;
            }
            re++;
            p = p->next;
        }

    }
    else
    {
        while (p)
        {
            if (p->data == data)
            {
                return re;
            }
            re++;
            p = p->next;
        }
    }
    return -1;
}

//创建链表，带有相等参数，用于查找
MyList * createMySearchList(int(*equal)(void * a, void * b))
{
    MyList * re = createMyList();
    re->equal = equal;
    return re;
}

//创建遍历器
MyListIterator* createMyListIterator(const MyList * const list)
{
    MyListIterator * re = (MyListIterator *) malloc(sizeof(MyListIterator));
    re->p = list->first;
    re->allSize = list->count;
    re->count = 0;
    return re;
}

//释放遍历器
void freeMyListIterator(MyListIterator* iterator)
{
    free(iterator);
}

//遍历器是否有下一个元素
int myListIteratorHasNext(const MyListIterator* const iterator)
{
    return iterator->count < iterator->allSize;
}

//返回遍历器的下一个元素
void * myListIteratorNext(MyListIterator* const iterator)
{
    void * re = iterator->p->data;
    iterator->p = iterator->p->next;
    (iterator->count)++;
    return re;
}

//删除对象,返回是否删除成功
int myListRemoveDataObject(MyList* const list, void * data)
{
    MyListIterator * it = createMyListIterator(list);
    int a = 0;
    while (myListIteratorHasNext(it))
    {
        void * ld = myListIteratorNext(it);
        if (data == ld || (list->equal != NULL && (*(list->equal))(ld, data)))
        {
            a = 1;
            break;
        }
    }
    if (a)
    {
        myListRemoveDataAt(list, it->count - 1);
    }
    return a;
}

typedef struct myHashSet
{
    int size; //大小
    int initialCapacity; //初始容量
    float loadFactor; //加载因子
    int (*hashCode)(void *data);
    int (*equal)(void *data1, void *data2);
    MyList ** dataList;
} MyHashSet;

typedef struct myHashSetIterator
{
    int index; //第几个链表
    MyHashSet *set;
    MyNode *current;
    int count; //第几个数据
} MyHashSetIterator;

//int类型hashCode
int myHashCodeInt(void * a);

//int类型相等的方法
int myEqualInt(void * a, void *b);

//创建HashSet
MyHashSet *createMyHashSet(int (*hashCode)(void *data),int (*equal)(void *data1,void *data2));

//使用全部参数创建HashSet
MyHashSet *createMyHashSetForAll(int initialCapacity,float loadFactor,int (*hashCode)(void *data),int (*equal)(void *data1,void *data2));

//释放HashSet
void freeMyHashSet(MyHashSet * set);

//是否包含某个data
int myHashSetContains(MyHashSet * const set, void * const data);

//增加一条数据,返回是否添加成功
int myHashSetAddData(MyHashSet * const set, void * const data);

//数据的容量
int myHashSetGetSize(const MyHashSet * const set);

//创建迭代器
MyHashSetIterator* createMyHashSetIterator(MyHashSet * const set);

//释放迭代器
void freeMyHashSetIterator(MyHashSetIterator* iterator);

//迭代器是否有下一个
int myHashSetIteratorHasNext(MyHashSetIterator* iterator);

//遍历下一个元素
void* myHashSetIteratorNext(MyHashSetIterator* iterator);

//删除一条数据，返回是否删除成功
int myHashSetRemoveData(MyHashSet * const set, void * const data);

//将第二个Set的全部对象加入到第一个，返回增加的个数
int myHashSetAddAllSet(MyHashSet * set,MyHashSet *other);

//复制HashSet
MyHashSet* myHashSetCopy(MyHashSet * set);

//遍历
void myHashSetOutput(MyHashSet *set, void(*pt)(void*));

#endif //CLIONRANTEST_MYHASH_H
