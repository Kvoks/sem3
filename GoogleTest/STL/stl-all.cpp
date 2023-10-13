#include "../STL/Libs.h"

int add(int a, int b) {
	return a + b;
}

float division(int a, int b) {
	if (b == 0) { // ����
		throw std::logic_error("Error.Division on zero in function \"div\"!");
	}
	else if (a == 0 && b < 0) { // ����
		return 0;
	}
	else { // ����
		return a*1.0/b;
	}
}