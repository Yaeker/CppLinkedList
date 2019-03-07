#pragma once

template<typename T> class LinkedList;

template<typename T>
class Iterator
{
public:
	Iterator(Node<T>* t_first) : current(t_first) {}
	~Iterator() {}

	T& operator*() const { return *this->current->obj; }
	Iterator<T>& operator++() { return this->next(); }
	Iterator<T> operator++(int) { return this->next(); }
	Iterator<T>& operator--() { return this->previous(); }
	Iterator<T> operator--(int) { return this->previous(); }
	bool operator==(const Iterator<T>& t_other) const { return this->current == t_other.current; }
	bool operator!=(const Iterator<T>& t_other) const { return this->current != t_other.current; }

private:
	Node<T>* current = nullptr;
	Iterator<T>& next() { current = current->next; return *this; }
	Iterator<T>& previous() { current = current->prev; return *this; }
};
