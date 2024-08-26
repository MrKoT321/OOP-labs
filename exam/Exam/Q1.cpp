#include <cstddef>

// Указатели
// Указатель - это переменная, которая хранит адрес другой переменной в памяти компьютера.

struct Temp
{
	int t1;
	int t2;
};

int sum(int a, int b) { return a + b; };

void foo()
{
	auto (*operation)(int, int) { sum };

	int x = 10;
	int* ptr_x = &x;
	int* another_ptr_x = &x;
	*ptr_x = 20;

	auto q7_1 = ptr_x == nullptr;

	void* ptr_void_x = &x;
	int* tt = static_cast<int*>(ptr_void_x);
	//ptr_void_x++; // нельзя т.к. void*

	//auto inadmissible_operation = another_ptr_x + ptr_x; // нельзя: указатель + указатель

	Temp temp;
	Temp* ptr_temp = &temp;
	auto res = ptr_temp++;

	// T* - указатель на T
	// const T* - указатель на константную переменную на T
	// T* const - константный указатель на переменную на T
	// const T* const - константный указатель на константную переменную на T
}