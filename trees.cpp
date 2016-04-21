#include <iostream>
#include <math.h>
#include <stack>
#include <vector>

using namespace std;

struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 };

int countHelper(TreeNode* root, bool leftValid, int leftH, bool rightValid, int rightH) {
    if (root == NULL) return 0;
    if (!leftValid) {
        leftH = 0;
        TreeNode* temp = root;
        while (temp->left != NULL) {
            temp = temp->left;
            leftH ++;
        }
    }
    cout << "leftH: "<<leftH;
    if (!rightValid) {
        rightH = 0;
        TreeNode* temp = root;
        while (temp->right != NULL) {
            temp = temp->right;
            rightH ++;
        }
    }
    cout << " rightH: "<<rightH<<endl;
    
    if (leftH == rightH) return pow(2,leftH+1)-1;
    else return 1+countHelper(root->left,true,leftH-1,false,0)+countHelper(root->right,false,0,true,rightH-1);
}

int countNodes(TreeNode* root) {
        return countHelper(root,false,0,false,0);
}

void fillSmall(stack<TreeNode*>& tempSmall, TreeNode* smallRoot) {
    if (smallRoot == NULL) return;
    fillSmall(tempSmall, smallRoot->left);
    tempSmall.push(smallRoot);
    fillSmall(tempSmall, smallRoot->right);
}

void fillLarge(stack<TreeNode*>& tempLarge, TreeNode* largeRoot) {
    if (largeRoot == NULL) return;
    fillLarge(tempLarge,largeRoot->right);
    tempLarge.push(largeRoot);
    fillLarge(tempLarge,largeRoot->left);
}

vector<int> closestKValues(TreeNode* root, double target, int k) {
    vector<int> result;
    if (k==0) return result;
    TreeNode* tempRoot = root;
    stack<TreeNode*> smallStack;
    stack<TreeNode*> largeStack;
    double tempVal;
    while (tempRoot != NULL) {
        tempVal = tempRoot->val;
        if (tempVal < target) {
            smallStack.push(tempRoot);
            tempRoot = tempRoot->right;
        } else if (tempVal > target) {
            largeStack.push(tempRoot);
            tempRoot = tempRoot->left;
        } else {
            TreeNode* temp;
            temp = tempRoot->left;
            while (temp!=NULL) {
                smallStack.push(temp);
                temp = temp->right;
            }
            temp = tempRoot->right;
            while (temp!=NULL) {
                largeStack.push(temp);
                temp = temp->left;
            }
            result.push_back(tempVal);
            break;
        }
    }
    
    TreeNode* smallNode = NULL;
    TreeNode* largeNode = NULL;
    TreeNode* previous = NULL;
    stack<TreeNode*> tempSmall;
    stack<TreeNode*> tempLarge;
   
    while (result.size() < k) {
        if (!smallStack.empty() && tempSmall.empty()) {
            smallNode = smallStack.top();
            smallStack.pop();
            fillSmall(tempSmall, smallNode->left);
            tempSmall.push(smallNode);
        } else if (smallStack.empty() && tempSmall.empty())
            smallNode = NULL;

        if (smallNode != previous && !tempSmall.empty()) {
            smallNode = tempSmall.top();
            tempSmall.pop();
        }
        if (!largeStack.empty() && tempLarge.empty()) {
            largeNode = largeStack.top();
            largeStack.pop();
            fillLarge(tempLarge, largeNode->right);
            tempLarge.push(largeNode);
        } else if (largeStack.empty() && tempLarge.empty())
            largeNode = NULL;

        if (largeNode != previous && !tempLarge.empty()) {
            largeNode = tempLarge.top();
            tempLarge.pop();
        }
        
        if (smallNode==NULL) {
            result.push_back(largeNode->val);
            previous = smallNode;
            continue;
        }
        if (largeNode==NULL) {
            result.push_back(smallNode->val);
            previous = largeNode;
            continue;
        }
        if (target-smallNode->val < largeNode->val-target) {
            result.push_back(smallNode->val);
            previous = largeNode;
        } else {
            result.push_back(largeNode->val);
            previous = smallNode;
        }
    }
    return result;
}

int main() {
    TreeNode* root = new TreeNode(4);
    root->left = new TreeNode(2);
    root->right = new TreeNode(5);
    root->left->left = new TreeNode(1);
    root->left->right = new TreeNode(3);
    //root->right = new TreeNode(3);

    //cout << "#nodes: "<<endl<<countNodes(root)<<endl;
    vector<int> result = closestKValues(root, 4.5, 3);
    for (int i = 0; i < result.size(); i++) {
        cout << result[i] << " ";
    }
    cout << endl;
    //delete root->right;
    delete root->left->left;
    delete root->left->right;
    delete root->left;
    delete root->right;
    delete root;
}

/*
Given two arrays of size N, containing bytes, 
how do you write a function hasSum(unsigned N) that returns True if there exists an A[i] + B[j] = N (i and j can be any array index value) 
and False otherwise?
We went through the problem and found in total 3 ways of doing it, O(n^2), O(n*log(n)), and finally O(n).
*/

