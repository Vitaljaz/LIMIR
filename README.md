## LIMIR

LiMir - библиотека для работы с XML репозиторием классов C++. 
XML-файл создается и редактируется с помощью библиотеки TinyXML2.
Ссылка на TinyXML2: http://www.grinninglizard.com/tinyxml2/ 

Как использовать:

```
	Для использования библиотеки, необходимо добавить в публичное поле класса:
	friend class LiMir;
	template<class T>
	void master(T* obj) {
	  MASTER(x);
	}
```
Как происходит сериализация:

```
Используются встроенные макросы из библиотеки LiMir (например, MASTER(x), где в качестве x передается поле из класса). 
В библиотеке обрабатываются значение переменной и её имя. Затем создается уникальный тег:
<variable_name> value </variable_name>
Пример использования:
... 
int x_ = 10;
...
MASTER(x_); - после сериализации получаем:
<x_> 10 </x_>
```

Структура XML файла:

```
<?xml version="1.0" encoding="UTF-8"?>
<LiMir>
    <object>
        <field>value</field>
    </object>
</LiMir>
```

Пояснения

```
<?xml version="1.0" encoding="UTF-8"?> - описание формата документа (declaration).
<LiMir> </LiMir> - авторские теги.
<object> </object> - сериализуемый объект. 
<field> </field> - поле объекта, которое было передано для сериализации.
value - значение поля объекта, которое было передано для сериализации.
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
class A {
 public:
  int x_ = 10;
	
  friend class LiMir;
  template<class T>
  void master(T* obj) {
    MASTER(x);
  }
};

int main() {
  LiMir object("output.xml");
  A a;
  object.Serialize(a, NAME_OBJECT(a));
  object.Deserialize(a);
}
```
