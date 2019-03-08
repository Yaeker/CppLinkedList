#pragma once

template<typename T> class LinkedList;

template<typename T>
class Iterator
{
public:
	Iterator(Node<T>* t_first, size_t& lstSize) : current(t_first), lstSize(lstSize) {}
	~Iterator() {}

	inline T& operator*() const { return *this->current->obj; }
	inline T* operator->() const { return this->current->obj; }
	inline Iterator<T>& operator++() { return this->next(); }
	inline Iterator<T> operator++(int) { return this->next(); }
	inline Iterator<T>& operator--() { return this->previous(); }
	inline Iterator<T> operator--(int) { return this->previous(); }

	inline bool operator==(const Iterator<T>& t_other) const { return this->current == t_other.current && this->itrIdx == t_other.itrIdx; }
	inline bool operator!=(const Iterator<T>& t_other) const { return this->current != t_other.current || this->itrIdx != t_other.itrIdx; }

	void remove();
	void add(T& t_obj);
	inline bool hasNext() const { return this->itrIdx < this->lstSize; }
	inline bool hasPrevious() const { return this->itrIdx > 0; }
	inline void reset(Node<T>* t_first) { this->current = t_first;  }

private:
	size_t itrIdx = 0;
	size_t& lstSize;
	LinkedList<T>* list;
	Node<T>* last = nullptr;
	Node<T>* current = nullptr;
	bool firstDeleted = false;
	Iterator<T>& next();
	Iterator<T>& previous();
};

template<typename T>
inline void Iterator<T>::remove()
{
	Node<T>* next = current->next;
	Node<T>* prev = current->prev;
	Node<T>* curr = current;

	if (next && prev) {
		itrIdx--;
		current = prev;
		prev->next = next;
		next->prev = prev;
	}
	else if(!next && prev)
	{
		current = prev;
		prev->next = nullptr;
	}
	else if(next && !prev)
	{
		current = next;
		firstDeleted = true;
		next->prev = nullptr;
	}
	--lstSize;
	delete curr;
}

template<typename T>
inline void Iterator<T>::add(T& t_obj)
{
	Node<T>* n = new Node<T>(&t_obj);
	Node<T>* next = current->next;
	Node<T>* curr = current;
	if (next) {
		next->prev = n;
		n->next = next;
	}
	
	current->next = n;
	n->prev = current;

	lstSize++;
}

template<typename T>
inline Iterator<T>& Iterator<T>::next()
{
	if (firstDeleted)
	{
		firstDeleted = !firstDeleted;
	}
	else
	{
		current = current->next;
		++itrIdx;
	}
	return *this;
}

template<typename T>
inline Iterator<T>& Iterator<T>::previous()
{
	if (firstDeleted)
	{
		firstDeleted = !firstDeleted;
	}
	else
	{
		current = current->prev;
		--itrIdx;
	}
	return *this;
}
