#include <iostream>
#include "limir.h"

class Beta
{
public:
	int a;
	Beta() = default;
};

class A {
};


class Example
{
private:
	int x = 10;
	double d = 14.43;
	float f = 15.22f;
	int* p = &x;
	Beta b;
	Beta *bp;
	A a;
	A& z = a;

	std::vector<int> vec = { 1, 2, 3, 4, 5 };

public:
	friend class LiMir;

	template<class T>
	void master(T* t_obj)
	{
		MASTER(x);
		MASTER(d);
		MASTER(f);
		MASTER(vec);
		MASTER_INT_PTR(p);
		MASTER_OBJ(b);
		MASTER_OBJ(a);
		MASTER_OBJ_PTR(bp);
		MASTER_OBJ_REF(z);
	}

	void clearFields()
	{
		x = 0;
		d = 0;
		f = 0;
		vec.clear();
	}

	void printFields()
	{
		std::cout << "x: " << x << std::endl;
		std::cout << "d: " << d << std::endl;
		std::cout << "f: " << f << std::endl;
		std::cout << "*P: " << *p << std::endl;
		
		std::cout << "Vector: ";
		for (auto& i : vec)
		{
			std::cout << i << " ";
		}
		
		std::cout << "\n";
	}

	void testPointer()
	{
		x = 11;
		std::cout << "x: " << x << " *p: " << *p << std::endl;
	}
};

int main()
{
	Example e;
	LiMir object("output.xml");
	object.serialize(e);
	e.clearFields();
	e.printFields();

	std::cin.get();
}