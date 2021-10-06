//Author: 張浩綸B073040022
//Date: Nov. 3, 2019
//Purpose: use linked list to store polynomial, and overload add and mutiply operator

//#include<bits/stdc++.h>//include all standard libaray
#include<iostream>
using std::cin;
using std::ostream;
using std::cout;
using std::endl;
class Node{
    private:
        double coefficient, exponent;
        Node* next;
    public:
        inline Node(){next = nullptr;}
        inline Node(double coefficient, double exponent):coefficient(coefficient), exponent(exponent){
            next = nullptr;
        }
        inline double getCoefficient(){return coefficient;}
        inline double getExponent(){return exponent;}
        inline Node* getNext(){return next;}
        inline void setCoefficient(double coefficient){this->coefficient = coefficient;}
        inline void setExponent(double exponent){this->exponent = exponent;}
        inline void setNext(Node* next){this->next = next;}
        friend class Polynomial;
};
class Polynomial{
    private:
        //a Node ptr point to the highest exponent
        Node* high;
    public:
        inline Polynomial(){high = nullptr;}
        Polynomial(const Polynomial& toCopy);//copy constructor
        ~Polynomial();//automatically called when ending a scope
        //find the applicable position(in descending order)
        void insert(double coefficient, double exponent);
        friend Polynomial operator+(const Polynomial& A, const Polynomial& B);
        friend Polynomial operator*(const Polynomial& A, const Polynomial& B);
        friend ostream& operator<<(ostream& os, const Polynomial& A);
        Polynomial& operator=(const Polynomial& A);
};
Polynomial::Polynomial(const Polynomial& toCopy){
    if(toCopy.high == nullptr){//no element
        high = nullptr;
    }
    else if(toCopy.high->next == nullptr){//one element
        high = new Node(toCopy.high->coefficient, toCopy.high->exponent);
    }
    else{//two or more elements
        high = new Node(toCopy.high->coefficient, toCopy.high->exponent);
        Node* temp = high;
        Node* copyTemp = toCopy.high;
        while(copyTemp->next != nullptr){
            temp->next = new Node(copyTemp->next->coefficient, copyTemp->next->exponent);
            temp = temp->next;
            copyTemp = copyTemp->next;
        }
    }
}
Polynomial::~Polynomial(){
    while(high != nullptr){//delete content first
        Node* temp = high;
        high = high->getNext();
        delete temp;
    }
}
void Polynomial::insert(double coefficient, double exponent){
    if(coefficient != 0){
        Node* newNode = new Node(coefficient, exponent);
        if(high == nullptr){//if there is no element
            high = newNode;
        }
        else if(high->next == nullptr){//only one element
            if(high->exponent > exponent){
                high->next = newNode;
            }
            else if(high->exponent < exponent){
                newNode->next = high;
                high = newNode;
            }
            else{//high->exponent == exponent
                high->coefficient += coefficient;
                //check if need to delete a node(coefficient == 0)
                if(high->coefficient == 0){
                    delete high;
                    high = nullptr;
                }
            }
        }
        else{//two or more elements
            if(high->exponent < exponent){//insert from the hightest
                newNode->next = high;
                high = newNode;
            }
            else if(high->exponent == exponent){//add to the hightest
                high->coefficient += coefficient;
                //check if need to delete a node(coefficient == 0)
                if(high->coefficient == 0){
                    Node* temp = high->next;
                    delete high;
                    high = temp;
                }
            }
            else{//find position
                //use big & small ptr to find the position
                Node* big = high, *small = high->next;
                while(small != nullptr){
                    if(big->exponent > exponent && small->exponent < exponent){
                        big->next = newNode;
                        newNode->next = small;
                        return;
                    }
                    else if(small->exponent == exponent){
                        small->coefficient += coefficient;
                        //check if need to delete a node(coefficient == 0)
                        if(small->coefficient == 0){
                            delete small;
                            big->next = nullptr;
                        }
                        return;
                    }
                    big = small;
                    small = small->next;
                }
                big->next = newNode;//insert at the last
            }
        }
    }
}
ostream& operator<<(ostream& os, const Polynomial& A){
    if(A.high == nullptr){
        os << "0 0";
    }
    else{
        Node* temp = A.high;
        while(temp != nullptr){//at least one element
            os << temp->getCoefficient() << " " << temp->getExponent();
            if(temp->getNext() != nullptr)
                os << endl;
            temp = temp->getNext();
        }
    }
    return os;
}
Polynomial operator+(const Polynomial& A, const Polynomial& B){
    Polynomial temp(A);//copy A
    Node* tempNode = B.high;
    while(tempNode != nullptr){//at least one element in B
        //insert all B's element into temp
        temp.insert(tempNode->getCoefficient(), tempNode->getExponent());
        tempNode = tempNode->getNext();
    }
    return temp;
}
Polynomial& Polynomial::operator=(const Polynomial& A){
    //delete content first(if any)
    while(high != nullptr){
        Node* temp = high;
        high = high->getNext();
        delete temp;
    }
    //(*this) = Polynomial(A);connot use because it uses '='
    //so we copy the code from copy constructor
    if(A.high == nullptr){//no element
        high = nullptr;
    }
    else if(A.high->next == nullptr){//one element
        high = new Node(A.high->coefficient, A.high->exponent);
    }
    else{//two or more elements
        high = new Node(A.high->coefficient, A.high->exponent);
        Node* temp = high;
        Node* copyTemp = A.high;
        while(copyTemp->next != nullptr){
            temp->next = new Node(copyTemp->next->coefficient, copyTemp->next->exponent);
            temp = temp->next;
            copyTemp = copyTemp->next;
        }
    }
    return *this;
}
Polynomial operator*(const Polynomial& A, const Polynomial& B){
    Polynomial result;
    if(A.high == nullptr || B.high == nullptr);//has no element
    else{
        //after multiplication respectively, sum it up
        //traversal B
        Node* outter = B.high;
        while(outter != nullptr){
            double coefB = outter->getCoefficient();
            double expB = outter->getExponent();
            //mutiply elements respectively
            //traversal A
            Polynomial temp;
            Node* inner = A.high;
            while(inner != nullptr){
                double coef = inner->getCoefficient();
                double exp = inner->getExponent();
                temp.insert(coefB * coef, expB + exp);
                inner = inner->getNext();
            }
            outter = outter->getNext();
            result = result + temp;//sum
        }
    }
    return result;
}
int main(){
    int cases = 1;
    while(true){
        //inputs
        int firstPloyTerms, secondPloyTerms;
        cin >> firstPloyTerms;//input the # of terms in first polynomial
        Polynomial A;
        for(int i = 0; i < firstPloyTerms; i++){//input first polynomial
            double coefficient, exponent;
            cin >> coefficient >> exponent;
            A.insert(coefficient, exponent);
        }
        cin >> secondPloyTerms;//input the # of terms in second polynomial
        Polynomial B;
        for(int i = 0; i < secondPloyTerms; i++){//input second polynomial
            double coefficient, exponent;
            cin >> coefficient >> exponent;
            B.insert(coefficient, exponent);
        }
        if(firstPloyTerms == 0 && secondPloyTerms == 0)//end program
            return 0;
        Polynomial C, D;
        C = A + B;
        D = A * B;
        cout << "Case " << cases << ":\n";
        cout << "ADD\n" << C << endl;
        cout << "MULTIPLY\n" << D << endl;
        cases++;
    }
}