#pragma once
#include <iostream>

using namespace std;


/**
*	@brief	Exception class thrown by Enqueue when queue is full.
*/
class FullQueue
{
public:

	/**
	*	@brief	Display a message for full queue on screen.
	*/
	void print()
	{
		cout << "FullQueue exception thrown." << endl;
	}
};


/**
*	@brief	Exception class thrown by Dequeue when queue is empty.
*/
class EmptyQueue
{
public:
	/**
	*	@brief	Display a message for empty queue on screen.
	*/
	void print()
	{
		cout << "EmtpyQueue exception thrown." << endl;
	}
};

/**
*	@brief	Queue class.
*	@details	This class processes as First In, First Out (FIFO), 템플릿을 적용해 다양한 변수 타입을 저장할 수 있다.
*/

template <typename T>
class CircularQueueType
{
public:
	/**
	*	@brief	Allocate dynamic array whose size is maxQueue.
	*	@pre	The maxQueue is defined 
	*	@post	Member of items points the allocated array.
	*/
	CircularQueueType();

	/**
	*	@brief	Allocate dynamic array whose size is max.
	*	@pre	none.
	*	@post	Member of items points the allocated array.
	*/
	CircularQueueType(int max);

	/**
	*	@brief	Destruct the object. Free the array dynamically allocated.
	*	@pre	Release memory for queue pointer.
	*	@post	none.
	*/
	~CircularQueueType();


	/**
	*	@brief	Determines whether the queue is full.
	*	@pre	Queue has been initialized.
	*	@post	Function value = (queue is full)
	*/
	bool IsFull();

	/**
	*	@brief	Determines whether the queue is empty.
	*	@pre	Queue has been initialized.
	*	@post	Function value = (queue is empty)
	*/
	bool IsEmpty();

	/**
	*	@brief	Makes the queue empty.
	*	@pre	Queue has been initialized.
	*	@post	miFront와 miRear is set same value as Constructer.
	*/
	void MakeEmpty();

	/**
	*	@brief	Adds newItem to the last of the queue.
	*	@pre	Queue has been initialized.
	*	@post	If (queue is full), FullQueue exception is thrown; otherwise, newItem is at the last.
	*/
	void EnQueue(T item);

	/**
	*	@brief	Removes first item from the queue.
	*	@pre	Queue has been initialized.
	*	@post	If (queue is empty), EmptyQueue exception is thrown; otherwise, first element has been removed from queue. item gets value of removed item.
	*/
	void DeQueue(T& item);

	/**
	*	@brief	Get front item in Q
	*	@pre	Queue has been initialized.
	*/

	T GetFront();

	/**
	*	@brief	Print all the items in the queue on screen
	*	@pre	Queue has been initialized.
	*	@post	None.
	*/
	void Print();

	/**
	* @brief Return length of current Q
	*/
	int GetLength();

private:
	int miFront;	//index of one infront of the first element.
	int miRear;	//index of the last element.
	int mMaxQueue;	//max size of the queue.
	T* mPtrItems;	//pointer for dynamic allocation
	int maxQueue; //defining Q size
	int mQLength; //Length of Q
};


template<typename T>
CircularQueueType<T>::CircularQueueType()
{
	maxQueue = 10;
	mMaxQueue = maxQueue + 1;
	miFront = mMaxQueue - 1;
	miRear = mMaxQueue - 1;
	mQLength = 0;
	mPtrItems = new T[mMaxQueue];
}


template<typename T>
CircularQueueType<T>::CircularQueueType(int max)
{
	mMaxQueue = max + 1;
	miFront = mMaxQueue - 1;
	miRear = mMaxQueue - 1;
	mQLength = 0;
	mPtrItems = new T[mMaxQueue];
}

template<typename T>
CircularQueueType<T>::~CircularQueueType()
{
	delete[] mPtrItems;
}

template<typename T>
bool CircularQueueType<T>::IsFull()
{
	return ((miRear + 1) % mMaxQueue == miFront);
}

template<typename T>
bool CircularQueueType<T>::IsEmpty()
{
	return(miFront == miRear);
}

template<typename T>
void CircularQueueType<T>::MakeEmpty()
{
	miFront = mMaxQueue - 1;
	miRear = mMaxQueue - 1;

}

template<typename T>
void CircularQueueType<T>::EnQueue(T item)
{
	if (IsFull())
	{
		throw FullQueue();
	}
	else
	{
		miRear = (miRear + 1) % mMaxQueue; //하나 더 큰 걸로 나눠줘야 깔끔하게 넘어감
		mPtrItems[miRear] = item;
		mQLength++;
	}
}

template<typename T>
void CircularQueueType<T>::DeQueue(T& item)
{
	if (IsEmpty())
	{
		throw EmptyQueue();
	}
	else
	{
		miFront = (miFront + 1) % mMaxQueue;
		item = mPtrItems[miFront];
		mQLength--;
	}
}


template<typename T>
void CircularQueueType<T>::Print()
{
	if (IsEmpty() == 1)
	{
		cout << "Empty Q";
		return;
	}
	else
	{
		int i = miFront;
		while(1)
		{
			i++;
			i %= mMaxQueue; //maxsize일때는 유지하고, maxsize+1일때 0으로
			cout << mPtrItems[i] << "-";

			if (i == miRear)
			{
				cout << endl;
				return;
			}
		}
	}
}

template<typename T>
T CircularQueueType<T>::GetFront()
{
	return mPtrItems[miFront];
}

template<typename T>
int CircularQueueType<T>::GetLength()
{
	return mQLength;
}

template<typename T>
inline T CircularQueueType<T>::getFront()
{
	if (IsEmpty())
	{
		throw EmptyQueue();
	}

	return m_pItems[m_iFront];
}