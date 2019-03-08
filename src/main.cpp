#include <iostream>
#include "vld.h"
#include <vector>
#include <memory>

#include "linked_list/LinkedList.h"


class Foo
{
public:
	Foo(int v) : foo(v) {}
	~Foo() {}

	int getFoo() const { return foo; }
	void changeFoo(int v) { this->foo = v; }

private:
	int foo = 0;
};

int main(void) {

	
	LinkedList<Foo> fooLst;
	Foo f1 = Foo(4);
	Foo f2 = Foo(9);
	Foo f3 = Foo(7);
	fooLst.add(f1);
	fooLst.add(f3);
	fooLst.add(f2);

	for (auto it = fooLst.begin(); it.hasNext(); it++)
	{
		std::cout << it->getFoo() << std::endl;
	}

	std::cout << "Size After: " << fooLst.length() << std::endl;

	for (auto it = fooLst.begin(); it.hasNext(); it++)
	{
		std::cout << it->getFoo() << std::endl;
	}

	return 0;
}