#include <iostream>
#include <vector>

using namespace std;

class MedianFinder {
public:
    MedianFinder() {
        size = 0;
        median = 0.0;
    }
    
    // Adds a number into the data structure.
    void addNum(int num) {
        if (size == leftHeap.size() + rightHeap.size()) {
            if (size == 0) {
                median = num * 1.00;
            } else {
                if (num > median) {
                    if (num > rightHeap[0]) {
                        median = replaceRightHeap(num) * 1.00;
                    } else
                        median = num * 1.00;
                } else {
                    if (num < leftHeap[0]) 
                        median = replaceLeftHeap(num) * 1.00;
                    else
                        median = num * 1.00;
                }
            }
        } else if (size > leftHeap.size() + rightHeap.size()) {
            int temp = median;
            if (temp > num) {
                insertLeftHeap(num);
                insertRightHeap(temp);
                median = (leftHeap[0] + rightHeap[0]) / 2.00;
            } else {
                insertLeftHeap(temp);
                insertRightHeap(num);
                median = (leftHeap[0] + rightHeap[0]) / 2.00;
            }
        }
        size ++;
    }

    // Returns the median of current data stream
    double findMedian() {
    	cout << median <<endl;
        return median;
    }

private:
    vector<int> leftHeap;//a max heap
    vector<int> rightHeap;//a min heap
    int size;
    double median;
    
    void insertLeftHeap(int num) {
        leftHeap.push_back(num);
        int n = leftHeap.size() - 1;
        n = (n-1) / 2;
        while (n >= 0) {
            int temp = n;
            if (2*n+1 < leftHeap.size()) {
                temp = leftHeap[temp] > leftHeap[2*n]? temp:2*n;
            }
            if (2*n+2 < leftHeap.size()) {
                temp = leftHeap[temp] > leftHeap[2*n+1]? temp:2*n+1;
            }
            if (temp != n) {
                int value = leftHeap[n];
                leftHeap[n] = leftHeap[temp];
                leftHeap[temp] = value;
                n = (n-1) / 2;
            } else
                break;
        }
    }
    
    void insertRightHeap(int num) {
        rightHeap.push_back(num);
        int n = rightHeap.size() - 1;
        n = (n-1) / 2;
        while (n >= 0) {
            int temp = n;
            if (2*n+1 < rightHeap.size()) {
                temp = rightHeap[temp] < rightHeap[2*n]? temp:2*n;
            }
            if (2*n+2 < rightHeap.size()) {
                temp = rightHeap[temp] < rightHeap[2*n+1]? temp:2*n+1;
            }
            if (temp != n) {
                int value = rightHeap[n];
                rightHeap[n] = rightHeap[temp];
                rightHeap[temp] = value;
                n = (n-1) / 2;
            } else
                break;
        }
    }
    
    int replaceLeftHeap(int num) {
        int temp = leftHeap[0];
        leftHeap[0] = num;
        int n = 0;
        while (n < leftHeap.size()) {
            int larger = n;
            if (2*n+1 < leftHeap.size()) {
                larger = leftHeap[larger] > leftHeap[2*n]? larger:2*n;
            }
            if (2*n+2 < leftHeap.size()) {
                larger = leftHeap[larger] > leftHeap[2*n+1]? larger:2*n+1;
            }
            if (larger != n) {
                int value = leftHeap[n];
                leftHeap[n] = leftHeap[larger];
                leftHeap[larger] = value;
                n = larger;
            } else
                break;
        }
        return temp;
    }
    
    int replaceRightHeap(int num) {
        int temp = rightHeap[0];
        rightHeap[0] = num;
        int n = 0;
        while (n < rightHeap.size()) {
            int smaller = n;
            if (2*n+1 < rightHeap.size()) {
                smaller = rightHeap[smaller] < rightHeap[2*n]? smaller:2*n;
            }
            if (2*n+2 < rightHeap.size()) {
                smaller = rightHeap[smaller] < rightHeap[2*n+1]? smaller:2*n+1;
            }
            if (smaller != n) {
                int value = rightHeap[n];
                rightHeap[n] = rightHeap[smaller];
                rightHeap[smaller] = value;
                n = smaller;
            } else
                break;
        }
        return temp;
    }

};

int main() {
	MedianFinder mf;
	mf.addNum(40);
	mf.findMedian();
	mf.addNum(12);
	mf.findMedian();
	mf.addNum(16);
	mf.findMedian();
	mf.addNum(14);
	mf.findMedian();
	mf.addNum(35);
	mf.findMedian();
	mf.addNum(19);
	mf.findMedian();
	mf.addNum(34);
	mf.findMedian();
	mf.addNum(35);
	mf.findMedian();
	mf.addNum(28);
	mf.findMedian();
	mf.addNum(35);
	mf.findMedian();
	mf.addNum(26);
	mf.findMedian();
	mf.addNum(6);
	mf.findMedian();
	mf.addNum(8);
	mf.findMedian();
	mf.addNum(2);
	mf.findMedian();
	mf.addNum(14);
	mf.findMedian();
	mf.addNum(25);
	mf.findMedian();
	mf.addNum(25);
	mf.findMedian();
	mf.addNum(4);
	mf.findMedian();
	mf.addNum(33);
	mf.findMedian();
	mf.addNum(18);
	mf.findMedian();
	mf.addNum(10);
	mf.findMedian();
	mf.addNum(14);
	mf.findMedian();
	mf.addNum(27);
	mf.findMedian();
	mf.addNum(3);
	mf.findMedian();
	mf.addNum(35);
	mf.findMedian();
	mf.addNum(13);
	mf.findMedian();
	mf.addNum(24);
	mf.findMedian();
	mf.addNum(27);
	mf.findMedian();
	mf.addNum(14);
	mf.findMedian();
	mf.addNum(5);
	mf.findMedian();
	mf.addNum(0);
	mf.findMedian();
	mf.addNum(38);
	mf.findMedian();
	mf.addNum(19);
	mf.findMedian();
	mf.addNum(25);
	mf.findMedian();
	mf.addNum(11);
	mf.findMedian();
	mf.addNum(14);
	mf.findMedian();
	mf.addNum(31);
	mf.findMedian();
	mf.addNum(30);
	mf.findMedian();
	mf.addNum(11);
	mf.findMedian();
	mf.addNum(31);
	mf.findMedian();
	mf.addNum(0);
	mf.findMedian();
}