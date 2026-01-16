#include <iostream>
using namespace std;

template<typename T , int length>
class Array {
public:
	T array[length];

	void fill(T value) {
		for (int i = 0; i < length; ++i) array[i] = value;
	}

	T& at(int index) { return array[index]; }
};

int main() {
	Array<int , 10> intArr;

	intArr.fill(1);

	intArr.at(4);

	return 0;
}