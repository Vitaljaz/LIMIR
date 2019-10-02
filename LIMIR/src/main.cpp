#include <iostream>
#include "limir.h"

class A
{
public:
	int x = 10;
	
	friend class LiMir;
	template<class T>
	void master(T* t_obj)
	{
		MASTER(x);
	}

	virtual void clearFields()
	{
		x = 0;
	}

	virtual void print()
	{
		std::cout << "x: " << x << std::endl;
	}
};

class B : public virtual A
{
public:
	std::vector<int> vec = { 1, 2, 3, 4, 5 };
	int a = 5;
	int* aptr = &a;

	friend class LiMir;
	template<class T>
	void master(T* t_obj)
	{
		MASTER_BASE_OBJ(A);
		MASTER(vec);
		MASTER(a);
		MASTER_INT_PTR(aptr);
	}

	void clearFields() override
	{
		a = 0;
		vec.clear();
	}

	void print() override
	{
		std::cout << "a: " << a << std::endl;
		std::cout << "*aptr: " << *aptr << std::endl;
		std::cout << "vector: ";
		for (auto i : vec)
			std::cout << i << " ";
		std::cout << std::endl;
	}
};

class C : public virtual A
{
public:
	B b;
	B& bref = b;
	C* cptr = this;

	friend class LiMir;
	template<class T>
	void master(T* t_obj)
	{
		MASTER_BASE_OBJ(A);
		MASTER_OBJ(b);
		MASTER_OBJ_REF(bref);
		MASTER_OBJ_PTR(cptr);
	}
};

class D : public B, public C
{
public:
	int y = 3;
	double pi = 3.14;

	friend class LiMir;
	template<class T>
	void master(T* t_obj)
	{
		MASTER_BASE_OBJ(B);
		MASTER_BASE_OBJ(C);
		MASTER(y);
		MASTER(pi);
	}

	void clearFields() override
	{
		y = 0;
		pi = 0;
	}

	void print() override
	{
		std::cout << "y: " << y << std::endl;
		std::cout << "pi: " << pi << std::endl;
	}
};

void test1()
{
	std::cout << "========= TEST1 =========\n";
	LiMir object("test1.xml");
	A a;
	object.serialize(a, NAME_OBJECT(a));
	a.clearFields();
	object.deserialize(a);
	a.print();
	std::cout << "========= ===== =========\n\n";
}

void test2()
{
	std::cout << "========= TEST2 =========\n";
	LiMir object("test2.xml");
	B b;
	object.serialize(b, NAME_OBJECT(b));
	b.clearFields();
	object.deserialize(b);
	b.print();
	std::cout << "========= ===== =========\n\n";
}

void test3()
{
	std::cout << "========= TEST3 =========\n";
	LiMir object("test3.xml");
	D d;
	object.serialize(d, NAME_OBJECT(d));
	d.clearFields();
	object.deserialize(d);
	d.print();
	std::cout << "========= ===== =========\n\n";
}

int main()
{
	test1();
	test2();
	test3();
	std::cin.get();
}