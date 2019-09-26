#include <iostream>
#include "limir.h"

class Example
{
private:
	int x = 10;
	double d = 14.43;
	float f = 15.22f;
	int* p = &x;

	std::vector<int> vec = { 1, 2, 3, 4, 5 };

public:
	friend class LiMir;

	template<class T>
	void save(T* t_obj)
	{
		SAVE(x);
		SAVE(d);
		SAVE(f);
		SAVE(vec);
		SAVE_PTR(p);
	}

	template <class T>
	void load(T* t_obj)
	{
		LOAD(x);
		LOAD(d);
		LOAD(f);
		LOAD(vec);
		LOAD_PTR(p);
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