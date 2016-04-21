#include <iostream>

class parent1 {
public:
	int a;
	int b;
	void setA(int num) {
		a = num;
		std::cout << "from parent 1: "<<a<<std::endl;
	}
};

class parent2 {
public:
	int a;
	int c;
	void setA(int num) {
		a = num;
		std::cout << "from parent 2: "<<a<<std::endl;
	}
};

class child : public parent1, public parent2 {
public:
	int d;
};

int main() {
	child testMult;
	testMult.setA(1);
	return 0;
}