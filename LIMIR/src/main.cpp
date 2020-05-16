#include <iostream>
#include "limir.h"

class A {
 public:
  template<class T>
  void Master(T* obj) {
     MASTER(x_);
  }

  virtual void ClearFields() {
	x_ = 0;
  }

  virtual void Print() {
	std::cout << "x: " << x_ << std::endl;
  }

private:
  friend class LiMir;
  int x_ = 10;
};

class B : public virtual A {
 public:
  template<class T>
  void Master(T* obj) {
	MASTER_BASE_OBJ(A);
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

class C : public virtual A {
 public:
  template<class T>
  void Master(T* obj) {
	MASTER_BASE_OBJ(A);
	MASTER_OBJ(b_);
	MASTER_OBJ_REF(bref_);
	MASTER_OBJ_PTR(cptr_);
  }

 private:
  friend class LiMir;
  B b_;
  B& bref_ = b_;
  C* cptr_ = this;
};

class D : public B, public C {
 public:
  template<class T>
  void Master(T* obj) {
	MASTER_BASE_OBJ(B);
	MASTER_BASE_OBJ(C);
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
  LiMir object("test1.xml");
  A a;
  object.Serialize(a, NAME_OBJECT(a));
  a.ClearFields();
  object.Deserialize(a);
  a.Print();
  printf("========= ===== =========\n\n");
}

void test2() {
  printf("========= TEST2 =========\n");
  LiMir object("test2.xml");
  B b;
  object.Serialize(b, NAME_OBJECT(b));
  b.ClearFields();
  object.Deserialize(b);
  b.Print();
  printf("========= ===== =========\n\n");
}

void test3() {
  printf("========= TEST3 =========\n");
  LiMir object("test3.xml");
  D d;
  object.Serialize(d, NAME_OBJECT(d));
  d.ClearFields();
  object.Deserialize(d);
  d.Print();
  printf("========= ===== =========\n\n");
}

int main() {
  test1();
  test2();
  test3();
  system("pause");
}