## LIMIR

LIMIR - библиотека для работы с XML репозиторием классов C++. XML-файл создается и редактируется с помощью библиотеки TinyXML2.

Для использования библиотеки, необходимо добавить в публичное поле класса:

```
	friend class LiMir;
	template<class T>
	void master(T* t_obj)
	{
		MASTER(x);
	}
```
Доступные методы:

```
void serialize(T& object, const char* name); 
void deserialize(T& object);
```

**Обязательно** соблюдать название метода и макросов. 
Список макросов:

```
MASTER(x)          - используется для целых, вещественных, вектора.
MASTER_OBJ(x)      - используется для работы с объектами. 
MASTER_OBJ_PTR(x)  - используется для работы с указателями на объекты.
MASTER_OBJ_REF(x)  - используется для работы с ссылками на объекты.
MASTER_INT_PTR(x)  - используется для работы с указателями на целые.
MASTER_BASE_OBJ(x) - используется для работы с родительскими классами.
NAME_OBJECT(x)     - используется для получения имени объекта.
```

Пример использования:

```
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
};

int main()
{

	LiMir object("output.xml");
	A a;
	object.serialize(a, NAME_OBJECT(a));
	object.deserialize(a);
}
```
