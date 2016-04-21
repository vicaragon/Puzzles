#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

int primeMultiplier(int number, int prime) {
	int count = 0;
	int mult = prime;
	while (number % mult == 0) {
		count ++;
		mult *= prime;
	}
	return count;
}

int countDevisors(std::vector<int>& primes, int number) {
	int count = 1;
	for (int i = 0; i < primes.size(); i++) {
		count *= (primeMultiplier(number,primes[i])+1);
	}
	return count;
}

int maxSubArrayLen(vector<int>& nums, int k) {
    if (nums.empty()) return 0;
    unordered_map<int,int> leftSub;//<subArray, index>

    int tempSum = 0;
    for(int i = 0; i < nums.size(); i++) {
        tempSum += nums[i];
        if (leftSub.find(tempSum) == leftSub.end())
            leftSub[tempSum] = i;
        else
            leftSub[tempSum] = leftSub[tempSum] > i? leftSub[tempSum]:i;
        cout << "pair<" << tempSum << " " <<leftSub[tempSum]<<endl;
    }
    
    tempSum = 0;
    int max = 0;
    for (int i = -1; nums.size() - i > 0; i++) {
        tempSum += i<0?0:nums[i];
        if (leftSub.find(tempSum+k) != leftSub.end()) {
            max = leftSub[tempSum+k]-i > max?leftSub[tempSum+k]-i:max;
        }
        cout << "max: "<<max<<endl;
    }
    
    return max;
}

int findModulo (int base, int pow, int devisor) {
	cout << "base:" << base << " pow: "<< pow<<" devisor: "<<devisor<<endl;
	if (pow == 0) return 1;
	cout << "not 0"<< endl;
	if (pow == 1) return base % devisor;
	cout << "not 1" << endl;
	int temp = findModulo(base,pow/2,devisor);
	cout << "temp: "<<temp<<endl;
	if (pow%2 == 0)
		return (temp*temp) % devisor;
	else
		return (temp*temp*base) % devisor;
}

int main() {
	int number = 100;
	const int p[] = {2, 5};
	std::vector<int> primes(p,p+sizeof(p)/sizeof(p[0]));

	int num[] = {1,-1,5,-2,3};
	vector<int> nums(num,num+sizeof(num)/sizeof(num[0]));

	//cout << ((3/2) == 1) << endl;
	cout << findModulo(3,533,1067)<<endl;
	//cout << (129*750*699) % 1067<<endl;
	//cout << maxSubArrayLen(nums,3) <<endl;
	//std::cout << countDevisors(primes,number)<<std::endl;
	return 0;
}