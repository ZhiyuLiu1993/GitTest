#ifndef PFZ_OBJECT_POOL_H
#define PFZ_OBJECT_POOL_H

#include <stdlib.h>
#include <stdio.h>
#include <iostream>

//使用对象池分配对象，性能差距达到2倍以上
class DefaultMemoryAllocator
{
public:
	static inline void *Allocate(size_t size)
	{
		//分配失败不抛出异常，可以返回nullptr
		return ::operator new(size, ::std::nothrow);
	}
	static inline void Deallocate(void *pointer, size_t size)
	{
		::operator delete(pointer);
	}
};

template<typename T, class TMemoryAllocator=DefaultMemoryAllocator>
class ObjectPool
{
private:
	//内部类，类似于外部类的友元类
	//可以直接访问外部类中的static、枚举成员,不需要外部类的对象、类名
	//private的内部类，外部不可定义内部类的对象
	struct _Node
	{
		void *_memory;
		size_t _capacity;
		_Node *_nextNode;

		_Node(size_t capacity)
		{
			if (capacity < 1)
				throw std::invalid_argument("capacity must be at least 1.");

			_memory = TMemoryAllocator::Allocate(_itemSize * capacity);
			if (_memory == NULL)
				throw std::bad_alloc();

			_capacity = capacity;
			_nextNode = NULL;
		}
		~_Node()
		{
			TMemoryAllocator::Deallocate(_memory, _itemSize * _capacity);
		}
	};

	void *_nodeMemory;
	T *_firstDeleted;
	size_t _countInNode; 
	size_t _nodeCapacity;
	_Node _firstNode;
	_Node *_lastNode;
	size_t _maxBlockLength;

	static const size_t _itemSize;

	ObjectPool(const ObjectPool<T, TMemoryAllocator> &source);
	void operator = (const ObjectPool<T, TMemoryAllocator> &source);

	void _AllocateNewNode()
	{
		size_t size = _countInNode; //上一个node的节点数量,初始为32
		//此时已经达到内存池初始的最大分配,新的节点，每个节点可以有maxBlockLength个 new Object
		if (size >= _maxBlockLength)
			size = _maxBlockLength;
		else
		{
			//是否为1.5更好,多次分配后可以重复利用之前空间，VS上采用的vector分配是1.5
			size *= 2;

			if (size < _countInNode)
				throw std::overflow_error("size became too big.");

			if (size >= _maxBlockLength)
				size = _maxBlockLength;
		}

		_Node *newNode = new _Node(size);
		_lastNode->_nextNode = newNode;
		_lastNode = newNode;
		_nodeMemory = newNode->_memory;
		_countInNode = 0;
		_nodeCapacity = size;
	}

public:
	explicit ObjectPool(size_t initialCapacity=32, size_t maxBlockLength=1000000):
		_firstDeleted(NULL),
		_countInNode(0),
		_nodeCapacity(initialCapacity),
		_firstNode(initialCapacity),
		_maxBlockLength(maxBlockLength)
	{
		if (maxBlockLength < 1)
			throw std::invalid_argument("maxBlockLength must be at least 1.");

		_nodeMemory = _firstNode._memory;
		_lastNode = &_firstNode;
	}
	~ObjectPool()
	{
		_Node *node = _firstNode._nextNode;
		while(node)
		{
			_Node *nextNode = node->_nextNode;
			delete node;
			node = nextNode;
		}
		//firstNode自动析构
	}

	//调用默认构造函数
	T *New()
	{
		if (_firstDeleted)
		{
			//先判断deleted中有没有，有的话先使用这块,极大地提高使用效率
			T *result = _firstDeleted;
		//	printf("result:%p------------>%d\n", result, __LINE__);
			_firstDeleted = *((T **)_firstDeleted);
		//	printf("firstDeleted:%p------------>%d\n", _firstDeleted, __LINE__);
			new(result) T();
			return result;
		}

		//_countInNode的下标从1开始计算
		if (_countInNode >= _nodeCapacity)
			_AllocateNewNode();

		char *address = (char *)_nodeMemory;
		address += _countInNode * _itemSize;
		T *result = new(address) T();
		_countInNode++;
		return result;
	}

	// This method is useful if you want to call a non-default constructor.
	// It should be used like this:
	// new (pool.GetNextWithoutInitializing()) ObjectType(... parameters ...);
	T *GetNextWithoutInitializing()
	{
		if (_firstDeleted)
		{
			T *result = (T *)_firstDeleted;
			_firstDeleted = *((T **)_firstDeleted);
			return result;
		}

		if (_countInNode >= _nodeCapacity)
			_AllocateNewNode();

		char *address = (char *)_nodeMemory;
		address += _countInNode * _itemSize;
		_countInNode++;
		return (T *)address;
	}
	void Delete(T *content)
	{
		content->~T();
		
		//类似于链表，在前端插入，改变的是指向地址的内容
		//是否类似于STL的内存分配器，是一个union,要么指向下一块内容，要么指向实际地址
		//TODO：打印地址检测
		*((T **)content) = _firstDeleted;
		//	printf("firstDelted:%p------------>%d\n", _firstDeleted, __LINE__);
		_firstDeleted = content;
		//	printf("conten:%p------------>%d\n", content, __LINE__);
	}
	void DeleteWithoutDestroying(T *content)
	{
		*((T **)content) = _firstDeleted;
		_firstDeleted = content;
	}
};

//向上对齐取整,适应各种平台指针大小与目标对象大小
//可以改写为 ((sizeof(T) + sizeof(void *) - 1) & ~(sizeof(void *)-1))
template<typename T, class TMemoryAllocator>
const size_t ObjectPool<T, TMemoryAllocator>::_itemSize = ((sizeof(T) + sizeof(void *)-1) / sizeof(void *)) * sizeof(void *);

#endif
