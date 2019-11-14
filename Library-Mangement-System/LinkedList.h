#ifndef _LINKED_LIST_H
#define _LINKED_LIST_H


/**
*	Structure for NodeType to use in Linked structure.
*/
template <typename T>
struct NodeType
{
	T data;	///< A data for each node.
	NodeType* next;	///< A node pointer to point succeed node.
};


/**
*	Simple unsorted list class for managing items.
*/
template <typename T>
class LinkedList
{
public:
	/**
	*	default constructor.
	*/
	LinkedList();

	/**
	*	destructor.
	*/
	~LinkedList();

	/**
	*	@brief	Initialize list to empty state.
	*	@pre	None
	*	@post	List is empty.
	*/
	void MakeEmpty();

	/**
	*	@brief	Get number of elements in the list.
	*	@pre	None.
	*	@post	Function value = number of elements in list.
	*	@return	Number of elements in this list.
	*/
	int GetLength() const;

	/**
	*	@brief	Add item into this list.
	*	@pre	List is not full. item is not in list.
	*	@post	Item is inserted in this list.
	*	@return	1 if this function works well, otherwise 0.
	*/
	int Add(T item);

	/**
	*	@brief	Retrieve list element whose key matches item's key (if present).
	*	@pre	Key member of item is initialized.
	*	@post	If there is an element whose key matches with item's key then the element's record is copied to the item.
	*	@return	1 if any element's primary key matches with item's, otherwise 0.
	*/
	int Get(T& item);

	/**
	*	@brief	Initialize current pointer for an iteration through the list.
	*	@pre	None.
	*	@post	current pointer is prior to list. current pointer has been initialized.
	*/
	void ResetList();

	/**
	*	@brief	Ű ���� ���� ��Ҹ� �����ϴ� ���
	*	@pre	����Ʈ�� �ʱ�ȭ�� ���� ��
	*	@post	Ű ���� �´� ��Ұ� ������
	*	@return 1�̸� �ùٸ��� ����, 0�̸� �ش� ��Ҹ� ã�� ����
	*/
	int Delete(T);

	/**
	*	@brief	Get the next element in list.
	*	@pre	current pointer is defined. Element at current pointer is not last in list.
	*	@post	current pointer is updated to next position. item is a copy of element at current pointer.
	*	@return 1�̸� �ùٸ��� ��ȯ, -1�̸� ����Ʈ�� ��
	*/
	int GetNextItem(T& item);

	T& operator[](int);
private:
	NodeType<T>* m_pList;	///< Pointer for pointing a first node.
	NodeType<T>* m_pCurPointer;	///< Node pointer for pointing current node to use iteration.
	int m_nLength;	///< Number of node in the list.
};


// Class constructor
template <typename T>
LinkedList<T>::LinkedList()
{
	m_nLength = 0;
	m_pList = nullptr;
	m_pCurPointer = nullptr;
}


// Class destructor
template <typename T>
LinkedList<T>::~LinkedList()
{
	//����Ʈ���� ��� node ����
	MakeEmpty();
}


// Initialize list to empty state.
template <typename T>
void LinkedList<T>::MakeEmpty()
// Post: List is empty; all items have been deallocated.
{
	// ����Ʈ���� ��� ��� ���� �ϰ� ����Ʈ�� length�� �ʱ�ȭ
	NodeType<T>* tempPtr;

	while (m_pList != nullptr)
	{
		tempPtr = m_pList;
		m_pList = m_pList->next;
		delete tempPtr;
	}

	m_nLength = 0;
}


// Get number of elements in the list.
template <typename T>
int LinkedList<T>::GetLength() const
{
	return m_nLength;
}


// Add item into this list.
template <typename T>
int LinkedList<T>::Add(T item)
{
	// ����Ʈ �ʱ�ȭ
	ResetList();

	// ����Ʈ�� �߰��� ���ο� node ��ü�� ���� ��带 ����ų ������ ����
	NodeType<T>* node = new NodeType<T>;
	NodeType<T>* pre;
	T dummy;
	bool bFound = false;

	// node ��ü�� �Է¹��� ������ ���� �� �ʱ�ȭ
	node->data = item;
	node->next = nullptr;

	// list �� node �� �������� �ʴ� ���
	if (!m_nLength)
	{
		m_pList = node;
	}
	// list �� node �� �ϳ� �̻� �����ϴ� ���
	else
	{
		// ���� ������ node �� �̵� �� ����
		while (1)
		{
			// ���� ��带 ����Ű�� ������ ����
			pre = m_pCurPointer;

			// iteration �� �̿��� node ������ ����.
			GetNextItem(dummy);

			// node �����Ͱ� ������ node �� ����Ű�� �� �ڿ� ���ο� node ����.
			if (m_pCurPointer->next == nullptr)
			{
				// ������ node �� ���ο� node ����
				m_pCurPointer->next = node;
				break;
			}
		}
	}

	m_nLength++;

	return 1;
}


// Retrieve list element whose key matches item's key (if present).
template <typename T>
int LinkedList<T>::Get(T& item)
{
	bool moreToSearch, found;
	NodeType<T>* location;

	location = m_pList;
	found = false;
	moreToSearch = (location != nullptr);

	while (moreToSearch && !found)
	{
		if (item == location->data)
		{
			found = true;
			item = location->data;
		}
		else
		{
			location = location->next;
			moreToSearch = (location != nullptr);
		}
	}

	if (found)
		return 1;
	else
		return 0;
}


// Initializes current pointer for an iteration through the list.
template <typename T>
void LinkedList<T>::ResetList()
{
	// current pointer �ʱ�ȭ
	m_pCurPointer = nullptr;
}


// Gets the next element in list.
template <typename T>
int LinkedList<T>::GetNextItem(T & item)
{
	// current pointer �� nullptr�̶�� ó�� node�� ����Ŵ.
	if (m_pCurPointer == nullptr)
	{
		m_pCurPointer = m_pList;
	}
	else
		//current position �� ���� ���� �̵�
		m_pCurPointer = m_pCurPointer->next;

	if (m_pCurPointer == nullptr)
	{
		return -1;
	}
	else
	{
		//item �� current position �� info �� ����
		item = m_pCurPointer->data;
		return 1;
	}
}


template <typename T>
int LinkedList<T>::Delete(T item)
{
	// ����Ʈ �ʱ�ȭ
	ResetList();

	NodeType<T>* pre;
	T dummy;
	bool bFound = false;

	// list �� node �� �������� �ʴ� ���
	if (m_nLength)
	{
		// ���� ������ node �� �̵� �� ����
		while (1)
		{
			// ���� ��带 ����Ű�� ������ ����
			pre = m_pCurPointer;

			// iteration �� �̿��� node ������ ����.
			GetNextItem(dummy);

			if (dummy == item)
			{
				if (pre == nullptr)
				{
					m_pList = m_pCurPointer->next;
					delete m_pCurPointer;
				}
				else
				{
					pre->next = m_pCurPointer->next;
					delete m_pCurPointer;
				}

				m_nLength--;
				return 1;
			}

			if (m_pCurPointer->next == nullptr)
			{
				return 0;
			}
		}
	}

}

template <typename T>
T& LinkedList<T>::operator[](int idx)
{
	if (idx >= m_nLength || idx < 0)
	{
		throw std::out_of_range("�߸��� �ε����Դϴ�.");
	}

	ResetList();
	T t;

	for (int i = 0; i <= idx; i++)
	{
		GetNextItem(t);
	}

	return m_pCurPointer->data;
}

#endif	// LINKED_LIST