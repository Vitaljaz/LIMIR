#include <iostream>
#include "limir.h"

class B
{
public:
	int oo = 10;

	friend class LiMir;
	template<class T>
	void master(T* t_obj)
	{
		MASTER(oo);
	}
};

class A: public B {
public: 
	int zero = 10;
	int b = 3;
	std::vector<int> vectors = { 1,2,3,4,4,4 };

public:
	friend class LiMir;
	template<class T>
	void master(T* t_obj)
	{
		MASTER_BASE_OBJ(B);
		MASTER(zero);
		MASTER(vectors);
		MASTER(b);
	}
};


class Example : public A
{
private:
	int x = 1;

public:
	friend class LiMir;
	template<class T>
	void master(T* t_obj)
	{
		MASTER_BASE_OBJ(A);
		MASTER(x);
	}

	void resetAll()
	{
		x = 0;
		A::zero = 0;
		A::b = 0;
	}

	void printAll()
	{
		std::cout << "x: " << x << " zero: " << zero << " b: " << b << std::endl;
	}
};

int main()
{
	Example e;
	LiMir object("output.xml");
	object.serialize(e, NAME_OBJECT(e));
	e.resetAll();
	e.printAll();

	object.deserialize(e);
	e.printAll();

	std::cin.get();
}