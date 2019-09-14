#include <iostream>
#include "limir.h"

class Example
{
private:
	int x, y;
	double z;
	char d;
	float s;
	std::vector <int> vec = { 1,2,3,4,5 };

public:
	Example() : x(10), y(11), z(0.2), d('f'), s(0.5f) {}

	friend class LiMir;
	template<class T>
	void save(T *t_obj)
	{
		SAVE(x);
		SAVE(y);
		SAVE(d);
		SAVE(s);
		SAVE(z);
		SAVE(vec);
	}
};

int main()
{
	Example e;
	LiMir object("output.xml");
	object.serialize(e);
	std::cin.get();
}