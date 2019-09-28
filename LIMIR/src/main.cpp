#include <iostream>
#include "limir.h"

class Beta
{
public:
	int a;
	Beta() = default;
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

	object.deserialize(e);
	e.printFields();
	e.testPointer();


	std::cin.get();
}