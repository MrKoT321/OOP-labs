#include <cstddef>

// ���������
// ��������� - ��� ����������, ������� ������ ����� ������ ���������� � ������ ����������.

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
	//ptr_void_x++; // ������ �.�. void*

	//auto inadmissible_operation = another_ptr_x + ptr_x; // ������: ��������� + ���������

	Temp temp;
	Temp* ptr_temp = &temp;
	auto res = ptr_temp++;

	// T* - ��������� �� T
	// const T* - ��������� �� ����������� ���������� �� T
	// T* const - ����������� ��������� �� ���������� �� T
	// const T* const - ����������� ��������� �� ����������� ���������� �� T
}