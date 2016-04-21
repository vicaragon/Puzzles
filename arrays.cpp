#include <vector>
#include <unordered_map>
#include <algorithm>
#include <iostream>

using namespace std;

int minSubArrayLen_1(int s, vector<int>& nums) {
    unordered_map<int,vector<int> > leftSub;
    int length = 0;
    if (nums.empty()) return length;
    int sum = 0;
    for (int i = 0; i < nums.size(); i++) {
        sum += nums[i];
        if (leftSub.find(sum) == leftSub.end()) {
            vector<int> temp;
            temp.push_back(i);
            leftSub[sum] = temp;
        } else {
            leftSub[sum].push_back(i);
        }
    }
    
    for (unordered_map<int,vector<int> >::iterator it = leftSub.begin(); it != leftSub.end(); it++) {
    	cout << "sum: "<<it->first<<" "<<it->second[0]<<endl;

        sort(it->second.begin(), it->second.end());
    }
    
    int total = sum;
    cout << "total: "<<total<<endl;
    sum = 0;
    for (int i = -1; nums.size()-i > 0; i++) {
        sum += i < 0?0:nums[i];
        cout <<"inner sum: "<<sum<<endl;
        for (int j = sum+s; j <= total; j++) {
            int count = 0;
            cout << "i: "<<i<<" j:"<<j<<endl;
            if (leftSub.find(j) != leftSub.end()) {
                vector<int> temp = leftSub[j];
                for (int id = 0; id < temp.size(); id++) {
                    if (temp[id] - i <= 0) continue;
                    if (temp[id] - i < length || length == 0) {
                        length = temp[id]-i;
                        cout << "i:" << i <<" j:"<<j<<" length"<<length<<endl;
                        count ++;
                        break;
                    }
                }
            }
            if (count != 0) break;
        }
    }
    return length;
}

int largerBinarySearch(vector<int>& leftSum, int searchKey, int start, int end) {//[start, end)
	if (start >= end) return -1;
    int pIdx = (start + end) / 2;
    //cout << "pIdx: "<<pIdx << endl;
    if (leftSum[pIdx] > searchKey) {
    	int close = largerBinarySearch(leftSum, searchKey, start, pIdx);
    	if (close == -1) return pIdx;
    } else if (leftSum[pIdx] < searchKey) {
        return largerBinarySearch(leftSum, searchKey, pIdx+1, end);
    } else return pIdx;
}

int binarySearch(vector<int>& leftSum, int searchKey, int start) {
    int end = leftSum.size()-1;
    int middle;
    while (start <= end) {
        middle = (start+end)/2;
        cout << "middle: "<<middle<<endl;
        if (searchKey == leftSum[middle]) return middle;
        else if (searchKey < leftSum[middle]) {
            if (start == end) return middle+1;
            start = middle+1;
            continue;
        } else {
            if (start == end) return middle;
            end = middle-1;
            continue;
        }
    }
    return -1;
}

int maxSubHelper(vector<int>& subProduct) {//non zero integers
    int size = subProduct.size();
    if (size == 0) return 0;
    if (size == 1) return subProduct[0];
    if (size == 2) {
        return subProduct[0] > subProduct[1]? subProduct[0]:subProduct[1];
    }
    int headSum, secondSum;
    headSum = subProduct[0] * subProduct[1] * subProduct[2];
    int max = subProduct[0] > subProduct[1]? subProduct[0]:subProduct[1];
    if (subProduct[0] > 0) {
        secondSum = subProduct[2];
    } else {
        secondSum = subProduct[1] * subProduct[2];
    }
    max = subProduct[2] > max? subProduct[2]:max;
    for (int i =3; i < size; i++) {
        max = subProduct[i] > max? subProduct[i]:max;
        if (subProduct[i] < 0 && i >= size - 2) {
            if (i == size-2) {
                if (headSum < 0)
                    headSum *= subProduct[i]*subProduct[i+1];
                if (secondSum < 0)
                    secondSum *= subProduct[i]*subProduct[i+1];
                max = subProduct[i+1] > max? subProduct[i+1]:max;
            } else {
                if (headSum < 0)
                    headSum *= subProduct[i];
                if (secondSum < 0)
                    secondSum *= subProduct[i];
            }
            break;
        } else {
            headSum *= subProduct[i];
            secondSum *= subProduct[i];
        }
    }
    max = headSum > max? headSum:max;
    max = secondSum > max? secondSum:max;
    return max;
}

int maxProduct_0(vector<int>& nums) {
    int size = nums.size();
    if (size == 1) return nums[0];
    vector<int> subProduct;
    subProduct.push_back(nums[0]);
    int max = nums[0];
    for (int i = 1; i < size; i++) {
        if (nums[i] == 0) {
            int temp = maxSubHelper(subProduct);
            subProduct.clear();
            cout << "subProduct size: "<<subProduct.size()<<endl;
            max = temp > max? temp:max;
            max = max > 0? max:0;
            continue;
        } else if (nums[i] > 0) {
            if (subProduct.back() > 0)
                subProduct.back() *= nums[i];
            else {
                subProduct.push_back(nums[i]);
            }
            continue;
        } else if (nums[i] < 0) {
            if (subProduct.back() >= 0)
                subProduct.push_back(nums[i]);
            else {
                subProduct.back() *= nums[i];
                if (subProduct.size() > 1 && subProduct[subProduct.size()-2] > 0) {
                    int temp = subProduct.back();
                    subProduct.pop_back();
                    subProduct.back() *= temp;
                }
            }
        }
    }
    int temp = maxSubHelper(subProduct);
    cout << "subProduct size: "<<subProduct.size()<<endl;
    max = temp > max? temp:max;
    return max;
}

int maxProduct(vector<int>& nums) {
    int size = nums.size();
    if (size == 1) return nums[0];
    int start = 0;
    int end = 0;
    int negNum = 0;
    vector<int> results;
    for (;end < size; end ++) {
        if (nums[end] == 0) {
            int temp = maxHelper(nums,start,end,negNum);
            temp = temp > 0? temp:0;
            result.push_back(temp);
            start = end+1;
            negNum = 0;
        } else if (nums[i] < 0)
            negNum ++;
    }
    int temp = maxHelper(nums,start,end);
    for (int i = 0; i < result.size(); i++) {
        temp = result[i] > temp? result[i]:temp;
    }
    return temp;
}

int maxHelper(vector<int>& nums, int start, int end, int negNum) {
    if (start >= end) return 0;
    if (start+1 == end) return nums[start];
    int headProd = nums[start];
    int secondProd = 0;
    int idx = start+1;
    while (idx < end) {
        headProd *= nums[idx];
        if (nums[idx-1] < 0) {
            secondProd = nums[idx];
            negNum --;
            idx ++;
            break;
        }
        idx ++;
    }
    while (idx < end) {
        if (nums[idx] < 0) {
            if (negNum == 1)
                break;
            negNum --;
        }
        headProd *= nums[idx];
        secondProd *= nums[idx];
        idx ++;
    }
    if (negNum > 0 && idx < end) {
        if (headProd < 0) {
            while (idx < end) {
                headProd *= nums[idx];
                idx++;
            }
        }
        if (secondProd < 0) {
            while (idx < end) {
                secondProd *= nums[idx];
                idx ++;
            }
        }
    }
    return headProd > secondProd? headProd:secondProd;
}



int main() {
	int input[] = {-2,0,-1};
	int s = 4;
	vector<int> nums(input,input+sizeof(input)/sizeof(input[0]));

	//cout <<minSubArrayLen(s,nums) << endl;
	//cout << binarySearch(nums,11,0)<<endl;
	cout << maxProduct(nums)<<endl;

}