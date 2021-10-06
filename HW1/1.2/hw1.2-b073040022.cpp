//Author: 張浩綸B073040022
//Date: Sep. 12, 2019
//Purpose: Print all factorial number between 1 to N, after enter 0, the program will end
#include<iostream>
#include<vector>
using std::cin;
using std::cout;
using std::endl;
using std::vector;

int main(){
    int n;//the number N
    while(true){
        cin >> n;
        if(n == 0)
            break;
        vector<int> value;//create an vector(array) to store and calcuate the factorial number
        for(int i = 1; i <= n; i++){//i is the new number needs to mutiply the value, the loop runs 1! to n!
            if(i == 1)//1!
                value.push_back(1);//1! is sure to equal 1
            else{//2! to n!
                int digit = 0;//records the digit which is modifying
                int carry = 0;//records the number needs to add to the next digit
                while(true){
                    int temp = value.at(digit) * i + carry;//calculate the result of the digit mutiply i and adds carry
                    carry = 0;
                    value.at(digit) = temp % 10;//update the digit
                    if(temp < 10 && value.size() == digit + 1)//if encounter the top digit and don't need to carry over numbers
                        break;
                    else{
                        if(value.size() > digit + 1){//encounters digits except the top one
                            carry = temp / 10;
                            digit++;
                        }
                        else{//encounter the top digit
                            if(temp / 10 < 10){//if the carry is lower then 10, then just make it the the top digit
                                carry = temp / 10;
                                value.push_back(carry);
                                break;
                            }
                            else{//if then carry is higher or equal to 10
                                int more = temp / 10;//more is the carry needs to be place to the proper position
                                while(true){
                                    value.push_back(more % 10);//mod more to get the reminder of more / 10, set it to be the top digit
                                    more /= 10;//update more
                                    if(more == 0)//if more equals 0, then the number we push before is the real top digit
                                        break;
                                }
                                break;
                            }
                        } 
                    }
                }
            }
            //print the result
            cout << i << "!=";
            for(int i = value.size() - 1; i >= 0; i--)
                cout << value.at(i);
            cout << endl;
        }
        cout << endl;       
    }
    return 0;
}
