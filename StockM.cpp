#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
using namespace std;

int bestStrategy(int n, vector<int>& prices){
    if (n <= 1) return 0;
    
    vector<int> peakIdx;
    vector<int> gains;
    vector<int> leftIdx;
    peakIdx.push_back(-1);
    gains.push_back(0);
    leftIdx.push_back(-1);
    
    int lowIdx = 0;
    int curGain = 0;
    
    for (int i = 1; i < n; i ++) {
        if (prices[i] > prices[i-1]) {
            curGain += (prices[i]-prices[i-1]) * (i-lowIdx);
            while (lowIdx > (peakIdx.back()+1) && prices[i] > prices[lowIdx-1]) {
                curGain += (prices[i] - prices[lowIdx-1]);
                lowIdx --;
            }
        } else if (prices[i] < prices[i-1]) {
            if (i-1 > 0) {
                //treat duplicates
                int edge = i - 2;
                while (prices[edge+1] == prices[edge] && edge > 0) edge --;
                if (prices[i-1] > prices[edge]) {
                    peakIdx.push_back(i-1);
                    gains.push_back(curGain);
                    leftIdx.push_back(lowIdx);
                    lowIdx = i-1;
                    curGain = 0;
                }
            }  
            lowIdx ++;
        } else {
            lowIdx ++;
        }
    }
    
    int peak = prices[n-1];
    //cout << "peakIdx: \n";
    for (int i = peakIdx.size()-1; i > 0; i--) {
        if (peak > prices[peakIdx[i]]) {
            int count = peakIdx[i] - leftIdx[i];
            gains[i] += count * (peak - prices[peakIdx[i]]);
            int left = leftIdx[i];
            while (left > peakIdx[i-1]+1 && peak > prices[left-1]) {
                gains[i] += (peak - prices[left-1]);
                left --;
            }
        } else {
            peak = prices[peakIdx[i]];
        }
        //cout << peakIdx[i] << endl;
    }
    
    //cout << "gains:\n";
    for (int i = 0; i < gains.size(); i++) {
        curGain += gains[i];
        //cout << gains[i] << endl;
    }
    
    return curGain;
}

long simpleStrategy(vector<long>& prices) {
    int n = prices.size();
    if (n <= 1) return 0;

    long largest = prices.back();
    long result = 0;

    for (int i = n-2; i >= 0; i--) {
        if (prices[i] < largest) result += largest - prices[i];
        else largest = prices[i];
    }

    return result;

}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int count;
    //cout << "please provide input:\n";
    string testString;
    stringstream stream;
    getline(cin, testString);
    stream.str(testString);
    stream >> count;

    int n;
    vector<long> prices;
    vector<long> result;
    long temp;
    while (count > 0) {
        stream.str("");
        stream.clear();
        getline(cin, testString);
        stream.str(testString);
        stream >> n;
        stream.str("");
        stream.clear();
        getline(cin, testString);
        stream.str(testString);
        for (int i = 0; i < n; i++) {
            stream >> temp;
            prices.push_back(temp);
        }
        //cout << "Test Case n: " << n << endl;
        //for (int i = 0; i < n; i++) {
        //    cout << prices[i] <<" ";
        //}
        //cout << endl;
        //result.push_back(bestStrategy(n, prices));
        result.push_back(simpleStrategy(prices));
        count --;
        prices.clear();
    }

    //cout << "result: ";
    for (int i = 0; i < result.size(); i++) {
        cout << result[i] << endl;
    }

    return 0;
}
