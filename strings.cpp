#include <iostream>
#include <string>
#include <vector>

using namespace std;

int noBound(vector<char>& digits, int length, int fullLength) {
    if (length == 0) return 0;
    int half = length/2;
    int mode2 = length%2;

    int count = 1;
    if (mode2 == 1) count *= (digits.size() - 2);
    
    if (half > 0) {
        if (length == fullLength)
            count *= (digits.size()-1);
        else count *= digits.size();
    }
    for (int i = 1; i < half; i++) {
        count *= digits.size();
    }
    
    return count;
}

int lowerBound(vector<char>& digits, string low, int fullLength) {
    int length = low.size();
    if (length == 0) return 0; 
    int count = 0;
    if (length == 1) {
        char forOdd[] = {'0','1','8'};
        for (int i = 2; i >= 0; i--) {
            if (forOdd[i] < low.front()) return count;
            count ++;
        }
    } else {
        int smaller = 0;
        int i = digits.size()-1;
        int end = length == fullLength?0:-1;
        for (; i > end; i--) {
            if (digits[i] <= low.front()) break;//no violation
            smaller ++;
        }
        
        count += length > 2? smaller*noBound(digits,length-2,fullLength):smaller;
        
        char equal = digits[i];
        if (low.front() == equal) {//possible violation
        	if (equal == '6') equal = '9';
        	else if (equal == '9') equal = '6';
            if (low.back() > equal) {//violation of lower bound
                string smallerS(low.begin()+1,low.begin()+low.size()-1);
                if (!smallerS.empty()) {
                    smallerS.back() = smallerS.back() - 1;
                    count += lowerBound(digits,smallerS,fullLength);
                }
            } else {
                string same(low.begin()+1, low.begin()+low.size()-1);
                if (!same.empty())count += lowerBound(digits,same,fullLength);
                else count += 1;
            }
        }
    }
    return count;
}

int upperBound(vector<char>& digits, string high, int fullLength) {
    int length = high.size();
    if (length == 0) return 0;
    int count = 0;
    if (length == 1) {
        char forOdd[] = {'0','1','8'};
        for (int i = 0; i < 3; i++) {
            if (forOdd[i] > high.front()) return count;//violation
            count ++;
        }
    } else {
        int higher = 0;
        int i = length == fullLength?1:0;
        for (; i < digits.size(); i++) {
            if (digits[i] >= high.front()) break;//no violation
            higher ++;
        }
        
        count += length > 2?higher*noBound(digits,length-2,fullLength):higher;
        
        char equal = digits[i];
        if (high[0] == equal) {//possible violation
        	if (equal == '6') equal = '9';
        	else if (equal == '9') equal = '6';
            if (high.back() < equal) {//violation of lower bound
                string higherS(high.begin()+1,high.begin()+high.size()-1);
                if (!higherS.empty()) {
                    higherS.back() = higherS.back() - 1;
                    count += upperBound(digits,higherS,fullLength);
                }
            } else {
                string same(high.begin()+1, high.begin()+high.size()-1);
                if (!same.empty()) count += upperBound(digits,same,fullLength);
                else count += 1;
            }
        }
    }
    return count;
}

int strobogrammaticInRange(string low, string high) {
    int maxLength = high.size();
    int minLength = low.size();
    if (minLength > maxLength) return 0;
    if (minLength == maxLength && low > high) return 0;

    const char dig[] = {'0','1','6','8','9'};
    vector<char> digits(dig, dig+sizeof(dig)/sizeof(dig[0]));
    int result = 0;
    result += lowerBound(digits,low,minLength);
    cout << "lowerBound added: "<<result<<endl;
    result += upperBound(digits,high,maxLength);
    cout << "upperBound added: "<<result<<endl;
    
    if (maxLength == minLength)
        result -= noBound(digits,maxLength,maxLength);
    else {
        for (int i = minLength+1; i < maxLength; i++) {
            result += noBound(digits,i,i);
        }
    }
    return result;
}

int main() {
	string low = "11";
	string high = "69";

	cout << "total valid nums in the range: " << strobogrammaticInRange(low,high) << endl;
}