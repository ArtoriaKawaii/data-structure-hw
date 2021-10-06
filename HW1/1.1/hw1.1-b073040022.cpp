//Author:張浩綸B073040022
//Date:Sep. 9, 2019
//Purpose:Create a n^2 magic square which n = 1, 3, 5, 7, 9
#include<iostream>
#include<iomanip>
using namespace std;

int main(){
    for(int n = 1; n <= 9; n += 2){//let n = 1, 3, 5, 7, 9
        int **magicSquare = new int*[n];//make an n*n 2D-dynamic array
        for(int i = 0; i < n; i++)
            magicSquare[i] = new int[n];
        for(int i = 0; i < n; i++)//initializes every elements(numbers) to 0
            for(int j = 0; j < n; j++)
                magicSquare[i][j] = 0;
        int row, col;//create two variables records the number of column and row
        row = 0;
        col = n / 2;
        magicSquare[row][col] = 1;//step 1: let the middle number in the first row be 1
        for(int num = 2; num <= n*n; num++){
            int originalRow = row, originalCol = col;//record the original row/column number before calculate
            row -= 1;//step 2: assume the number sat at magicSquare[row-1][col-1]
            if(row < 0)
                row += n;
            col -= 1;
            if(col < 0)
                col += n;
            if(magicSquare[row][col] == 0)//if magicSquare[row-1][col-1] is reasonable and equals 0, let it equal num
                magicSquare[row][col] = num;
            else{//step 3: if magicSquare[row-1][col-1] is reasonable but doesn't equal 0, let magicSquare[row+1][col] equal num
                row = originalRow + 1;
                col = originalCol;
                magicSquare[row][col] = num;
            }
            //step 4: num++(in for-loop)
        }
        for(int i = 0; i < n; i++){//print result
            for(int j = 0; j < n; j++)
                cout << setw(2) << magicSquare[i][j] << " ";//setw() set number format
            cout << endl;
        }
        cout << endl;
        //delete dynamic array
        for(int i = 0; i < n; i++)
            delete [] magicSquare[i];
        delete [] magicSquare;
    }
    return 0;
}