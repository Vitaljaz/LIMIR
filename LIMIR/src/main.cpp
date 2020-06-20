#include <iostream>
#include "limir.h"
#include "test.h"

// Base class
// Serialization fields: int
class Base {
 public:
  template<class T>
  void Master(T* obj) {
     MASTER(x_);
  }

  virtual void ClearFields() {
    x_ = 0;
  }

  virtual void Print() {
    printf("x: %d \n", x_);
  }

private:
  friend class LiMir;
  int x_ = 10;
};

// Child1 class with virtual inheritance
// Serialization fields: vector, int, pointer to int
class Child1 : public virtual Base {
 public:
  template<class T>
  void Master(T* obj) {
    MASTER_BASE_OBJ(Base);
    MASTER(vec_);
    MASTER(a_);
    MASTER_INT_PTR(aptr_);
  }

  void ClearFields() override {
    a_ = 0;
    vec_.clear();
  }

  void Print() override {
    printf("a: %d \n", a_);
    printf("*aptr: %d \n", *aptr_);
    printf("vector: \n");

    for (const auto& i : vec_)
      printf("%d, ", i);

    printf("\n");
  }

 private:
  friend class LiMir;

  std::vector<int> vec_ = { 1, 2, 3, 4, 5 };
  int a_ = 5;
  int* aptr_ = &a_;
};

// Child2 class with virtual inheritance
// Serialization fields: Child1 object, Child1 object reference, pointer to Child2 object
class Child2 : public virtual Base {
 public:
  template<class T>
  void Master(T* obj) {
    MASTER_BASE_OBJ(Base);
    MASTER_OBJ(b_);
    MASTER_OBJ_REF(bref_);
    MASTER_OBJ_PTR(cptr_);
  }

 private:
  friend class LiMir;
  Child1 b_;
  Child1& bref_ = b_;
  Child2* cptr_ = this;
};

// Child3 class with multiple inheritance
// Serialization fields: int, double
class Child3 : public Child1, public Child2 {
 public:
  template<class T>
  void Master(T* obj) {
    MASTER_BASE_OBJ(Child1);
    MASTER_BASE_OBJ(Child2);
    MASTER(y_);
    MASTER(pi_);
  }

  void ClearFields() override {
    y_ = 0;
    pi_ = 0;
  }

  void Print() override {
    printf("y: %d \n", y_);
    printf("pi: %lf \n", pi_);
  }

 private:
  friend class LiMir;
  int y_ = 3;
  double pi_ = 3.14;
};

void test1() {
  printf("========= TEST1 =========\n");
	Test test("test1.xml");
	Base base;
	test.Run(base, NAME_OBJECT(base));
	base.Print();
  printf("========= ===== =========\n\n");
}

void test2() {
  printf("========= TEST2 =========\n");
	Test test("test2.xml");
	Child1 child1;
	test.Run(child1, NAME_OBJECT(child1));
	child1.Print();
  printf("========= ===== =========\n\n");
}

void test3() {
  printf("========= TEST3 =========\n");
	Test test("test3.xml");
	Child3 child3;
	test.Run(child3, NAME_OBJECT(child3));
	child3.Print();
  printf("========= ===== =========\n\n");
}

int main() {
  test1();
  test2();
  test3();
  system("pause");
}