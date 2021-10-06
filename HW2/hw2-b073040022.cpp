//Author: 張浩綸B073040022
//Date: Sep. 28, 2019
//Purpose: Write a class TSet that has some operators,
//such as union, intersection, difference, contain, belong to, assign, output
#include<iostream>
#include<string>
#include<iostream>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::ostream;

class TSet{
    private:
        int set[256];//records the element by its ASCII code
    public:
        TSet();
        TSet(string input);
        bool in(char element);//element belongs to A
        //operator overloading
        friend TSet operator + (const TSet& left, const TSet& right);//A + B
        friend TSet operator * (const TSet& left, const TSet& right);//A * B
        friend TSet operator - (const TSet& left, const TSet& right);//A - B
        friend bool operator >=(const TSet& left, const TSet& right);//A contains B
        friend ostream& operator << (ostream& outputStream,const TSet& output);//cout << A
        const TSet& operator = (const TSet& left);//A = B*/
};
TSet::TSet(){//set all record to 0(unused);
    for(int i = 0; i < 256; i++)
        set[i] = 0;
    //cout << "default\n";//check
}
TSet::TSet(string input):TSet(){//set record according to the input
    //TSet();//cannot call constructor here, but in initialization list
    /*for(int i = 0; i < 256; i++)//check
        set[i] = 0;*/
    /*if(input.at(0) == '{')//A = {a, b, c}//test
       for(unsigned int i = 1; i < input.length() - 1; i++)
            set[(int)input.at(i)] = 1;
    else*///A = abc
    for(unsigned int i = 0; i < input.length(); i++){
            //cout << (int)input.at(i) << endl;//check
            set[(int)input.at(i)] = 1;
    }
    /*for(int i = 0; i < 256; i++)//check
        cout << set[i];*/
}
bool TSet::in(char element){//A.in(x) is that A has an element x
    return (set[(int)element] == 1);
}
//operator overloading(class)
const TSet& TSet::operator = (const TSet& right){//change the value according to right
    for(int i = 0; i < 256; i++)
        set[i] = right.set[i];
    return *this;
}
//operator overloading(friend func.)
TSet operator + (const TSet& left, const TSet& right){//OR
    TSet returnSet;
    for(int i = 0; i < 256; i++)
        if(left.set[i] == 1 || right.set[i] == 1)
            returnSet.set[i] = 1;
    return returnSet;
}
TSet operator * (const TSet& left, const TSet& right){//AND
    TSet returnSet;
    for(int i = 0; i < 256; i++)
        if(left.set[i] == 1 && right.set[i] == 1)
            returnSet.set[i] = 1;
    return returnSet;
}
TSet operator - (const TSet& left, const TSet& right){//A - B = {a|a is in A, but not in B}
    TSet returnSet;
    for(int i = 0; i < 256; i++)
        if(left.set[i] == 1 && right.set[i] == 0)
            returnSet.set[i] = 1;
    return returnSet;
}
bool operator >=(const TSet& left, const TSet& right){//A >= B is that A has all the elements in B
    bool ans = true;
    for(int i = 0; i < 256; i++)
        if(right.set[i] == 1 && left.set[i] == 0)
            ans = false;
    return ans;
}
ostream& operator << (ostream& outputStream,const TSet& output){//output
    outputStream << "{";
    for(int i = 0; i < 256; i++){
        if(output.set[i] == 1){
            //outputStream << i;//check
            outputStream << (char)i;
        }
    }
    outputStream << "}";
    return outputStream;
}

int main(){
    int loop;
    cin >> loop;
    for(int i = 0; i < loop; i++){
        string input;
        cin >> input;
        //cout << input;//check
        TSet A(input);//A set
        cin >> input;
        //cout << input;//check
        TSet B(input);//B set
        TSet C, D;
        C = A + B;
        D = A * B;
        char element;
        cin >> element;
        cout << "Test Case " << i + 1 << ":\n";
        cout << "A: " << A << endl;
        cout << "B: " << B << endl;
        cout << "A+B: " << C << endl;
        cout << "A*B: " << D << endl;
        cout << "A-B: " << A-B << endl;
        cout << "B-A: " << B-A << endl;
        if(A >= B)
            cout << "A contains B\n";
        else
            cout << "A does not contain B\n";
        if(B >= A)
            cout << "B contains A\n";
        else
            cout << "B does not contain A\n";
        if(A.in(element))
            cout << "'" << element << "' is in A\n";
        else
            cout << "'" << element << "' is not in A\n";
        if(B.in(element))
            cout << "'" << element << "' is in B\n";
        else
            cout << "'" << element << "' is not in B\n";
        cout << endl;
    }
    return 0;
}