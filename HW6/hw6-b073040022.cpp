//Author: 張浩綸B073040022
//Date: Nov. 13, 2019
//Purpose: use binary search tree to find the number which appears odd times

//#include<bits/stdc++.h>//include all standard libaray
#include<iostream>
#include<vector>
#include<iomanip>
#include<fstream>
using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::setw;
using std::ifstream;
class Node{//node structure
    private:
        int data;
        Node* left;
        Node* right;
    public:
        Node(){}
        Node(int data):data(data), left(nullptr), right(nullptr){}
        friend class BSTree;
};
class NodeDataSet{//use to store data set
    private:
        int data;
        int left;
        int right;
    public:
        NodeDataSet(){}
        NodeDataSet(int data, int left, int right):data(data), left(left), right(right){}
        inline int getData(){return data;}
        inline int getLeft(){return left;}
        inline int getRight(){return right;}
        friend class BSTree;
};
class BSTree{//binary search tree
    private:
        Node* root;
        void deleteTwoSonsNonLeafNode(Node* cur);//helping func.
    public:
        BSTree(){root = nullptr;}
        inline Node* getRoot(){return root;}
        bool findDataPreNode(Node* &pre, Node* cur, int data);
        //if find, delete the node
        void deleteNode(Node* pre, int data);
        //if not find, insert data
        void insertNode(Node* pre, int data);
        void currentTree(vector<NodeDataSet> &dataSet, Node* cur);
        void makeEmpty(Node* pre, Node* cur);
        ~BSTree();
};
void BSTree::deleteTwoSonsNonLeafNode(Node* cur){
    //find the inorder successor sub and its parent preSub
    Node* sub = cur->right;
    Node* preSub = cur;
    while(sub->left != nullptr){
        preSub = sub;
        sub = sub->left;
    }
    if(sub->right != nullptr){//non leaf node which has one son which must be on the right
        cur->data = sub->data;
        if(sub == preSub->left)//sub is on the left of preSub
            preSub->left = sub->right;
        else//sub is on the right of preSub
            preSub->right = sub->right;
        delete sub;
    }
    else{//leaf node
        cur->data = sub->data;
        if(sub == preSub->left)//sub is on the left of preSub
            preSub->left = nullptr;
        else//sub is on the right of preSub
            preSub->right = nullptr;
        delete sub;
    }
}
bool BSTree::findDataPreNode(Node* &pre, Node* cur, int data){//recursive
    if(cur == nullptr)
        return false;
    else if(cur->data == data)
        return true;
    else if(data < cur->data){//find left
        pre = cur;
        return findDataPreNode(pre, cur->left, data);
    }
    else{//else if(data > cur->data) find right
        pre = cur;
        return findDataPreNode(pre, cur->right, data);
    }
}
void BSTree::deleteNode(Node* pre, int data){//if find
    Node* cur;
    if(root != nullptr && root->left == nullptr && root->right == nullptr){//one node tree
        delete root;
        root = nullptr;
    }
    else if(pre == nullptr){//delete root
        if(root->left != nullptr && root->right != nullptr)//non leaf node which has two sons
            deleteTwoSonsNonLeafNode(root);
        else{//non leaf which has one son 
            if(root->left != nullptr){//the son is on the left
                cur = root;
                root = root->left;
                delete cur;
            }
            else{//the son is on the right
                cur = root;
                root = root->right;
                delete cur;
            }
        }
    }
    else{//pre pointer is functional
        if(data < pre->data){//cur is the left node of pre
            cur = pre->left;
            if(cur->left == nullptr && cur->right == nullptr){//leaf node, delete directly
                pre->left = nullptr;
                delete cur;
            }
            else if(cur->left != nullptr && cur->right != nullptr)//non leaf node which has two sons
                deleteTwoSonsNonLeafNode(cur);
            else{//non leaf node which has one son 
                if(cur->left != nullptr){//the son is on the left
                    pre->left = cur->left;
                    delete cur;
                }
                else{//the son is on the right
                    pre->left = cur->right;
                    delete cur;
                }
            }
        }
        else{//cur is the right node of pre
            cur = pre->right;
            if(cur->left == nullptr && cur->right == nullptr){//leaf node, delete directly
                pre->right = nullptr;
                delete cur;
            }
            else if(cur->left != nullptr && cur->right != nullptr)//non leaf node which has to sons
                deleteTwoSonsNonLeafNode(cur);
            else{//non leaf node which has one son 
                if(cur->left != nullptr){//the son is on the left
                    pre->right = cur->left;
                    delete cur;
                }
                else{//the son is on the right
                    pre->right = cur->right;
                    delete cur;
                }
            }
        }
    }
}
void BSTree::insertNode(Node* pre, int data){//if not find
    Node* newNode = new Node(data);
    if(root == nullptr)//empty tree
        root = newNode;
    else{//non-empty tree
        if(data < pre->data)//insert left
            pre->left = newNode;
        else//data > pre->data insert right
            pre->right = newNode;
    }
}
void BSTree::currentTree(vector<NodeDataSet> &dataSet, Node* cur){//add tree nodes to vector
    if(cur == nullptr)//empty tree
        return;
    else{//non-empty tree
        int leftData, rightData;
        if(cur->left == nullptr)
            leftData = 0;
        else
            leftData = cur->left->data;
        if(cur->right == nullptr)
            rightData = 0;
        else
            rightData = cur->right->data;
        dataSet.push_back(NodeDataSet(cur->data, leftData, rightData));
        currentTree(dataSet, cur->left);
        currentTree(dataSet, cur->right);
    }
}
void BSTree::makeEmpty(Node* pre, Node* cur){
    if(cur == nullptr && pre == nullptr)//empty tree
        return;
    else{
        if(cur->left == nullptr && cur->right == nullptr);//cur == leaf node
        else{
            if(cur->left != nullptr)
                makeEmpty(cur, cur->left);
            if(cur->right != nullptr)
                makeEmpty(cur, cur->right);
        }
        if(cur == root);//one node(cur) tree
        else if(cur == pre->left)//cur == pre left son
            pre->left = nullptr;
        else//cur == pre right son
            pre->right = nullptr;
        delete cur;
        return;
    }
}
BSTree::~BSTree(){
    makeEmpty(nullptr, root);
    root = nullptr;
}
void ascendSort(vector<NodeDataSet> &dataSet){//sort dataset using ascending selection sort
    for(int i = 0; i < dataSet.size(); i++){
        int min = i;
        for(int j = i + 1; j < dataSet.size(); j++)
            if(dataSet.at(j).getData() <  dataSet.at(min).getData())
                min = j;
        //swap
        NodeDataSet temp = dataSet.at(i);
        dataSet.at(i) = dataSet.at(min);
        dataSet.at(min) = temp;
    }
}
int main(){
    ifstream fcin;
    fcin.open("input.txt");

    while(true){
        int input;
        BSTree tree;
        while(true){
            if(!(fcin >> input))
                return 0;
            if(input == -1)
                break;
            Node* pre = nullptr;
            bool find = tree.findDataPreNode(pre, tree.getRoot(), input);
            if(find)
                tree.deleteNode(pre, input);
            else
                tree.insertNode(pre, input);
        }
        //sort & print results
        vector<NodeDataSet> dataSet;
        tree.currentTree(dataSet, tree.getRoot());
        ascendSort(dataSet);
        cout << "Node :\t";
        for(int i = 0; i < dataSet.size(); i++)
            cout << setw(3) << dataSet.at(i).getData() << " ";
        cout << endl;
        cout << "Left :\t";
        for(int i = 0; i < dataSet.size(); i++)
            cout << setw(3) << dataSet.at(i).getLeft() << " ";
        cout << endl;
        cout << "Right :\t";
        for(int i = 0; i < dataSet.size(); i++)
            cout << setw(3) << dataSet.at(i).getRight() << " ";
        cout << endl;
        if(fcin.eof())//file end
            return 0;
        else
            cout << endl;
    }
    fcin.close();
    return 0;
}