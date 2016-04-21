#include <iostream>
#include <sstream>
#include <string>
#include <math.h>

using namespace std;

int main() {
	string a("11");
	string b("69");
	string c(a.begin()+1,a.begin()+a.size()-1);
	//a.pop_back();
	//stringstream stream;
	//stream << "a" << "b";
	//stream >> b;
	//cout << stream.str() << endl;
	cout << c.empty() << endl;
	//cout << b << endl;
	//cout << b.max_size()<<endl;
	//cout << pow(3,0)<<endl;
	return 0;
}