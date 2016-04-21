#include <iostream>
#include <vector>

using namespace std;

/*
K caterpillars are eating their way through N leaves, each caterpillar falls from leaf to leaf in a unique sequence, 
all caterpillars start at a twig at position 0 and falls onto the leaves at position between 1 and N. 
Each caterpillar j has as associated jump number Aj. A caterpillar with jump number j eats leaves at positions that are multiple of j. 
It will proceed in the order j, 2j, 3j…. till it reaches the end of the leaves and it stops and build its cocoon. 
Given a set A of K elements K<-15, N<=10^9, we need to determine the number of uneaten leaves.

Input:

N = No of uneaten leaves
K = No. of caterpillars
A = Array of integer jump numbers
Output:

The integer nu. Of uneaten leaves
*/

//find greatest common divisor for positive numbers
int gcd(int a, int b) {
	int large = a > b? a:b;
	int small = a > b? b:a;

	if (large % small == 0) return small;
	else return gcd(small, large-small);
}

int main() {
	cout << gcd(3,1067) << endl;
}