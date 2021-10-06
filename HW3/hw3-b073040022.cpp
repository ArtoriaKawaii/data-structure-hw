//Author: 張浩綸B073040022
//Date: Oct. 19, 2019
//Purpose: write a program to find the knight's tour
#include<iostream>
#include<iomanip>
using std::cout;
using std::endl;
using std::setw;
//Rec to store the info of step
class Rec{
    private:
        int row, col, nextDir;
        Rec* preRec;//point to the previous Rec, linked list
    public:
        Rec();
        Rec(int row, int col, int nextDir);
        int getRow() const;
        int getCol() const;
        int getNextDir() const;
        Rec* getPreRec() const;
        void setPreRec(Rec* preRec);
};
Rec::Rec(){preRec = nullptr;}
Rec::Rec(int row, int col, int nextDir){
    this->row = row;
    this->col = col;
    this->nextDir = nextDir;
    preRec = nullptr;
}
int Rec::getRow() const{
    return row;
}
int Rec::getCol() const{
    return col;
}
int Rec::getNextDir() const{
    return nextDir;
}
Rec* Rec::getPreRec() const{
    return preRec;
}
void Rec::setPreRec(Rec* preRec){
    this->preRec = preRec;
}
//Stack to record the step
class Stack{
    private:
        Rec* top;
    public:
        Stack();
        Rec* getTop() const;
        void push(Rec* step);
        void pop();
};
Stack::Stack(){top = nullptr;}
Rec* Stack::getTop() const{
    return top;
}
void Stack::push(Rec* step){
    step->setPreRec(top);
    top = step;
}
void Stack::pop(){
    Rec* temp = top;
    top = top->getPreRec();
    delete temp;
}
int main(){
    for(int mapSize = 1; mapSize <= 6; mapSize++){//map from 1*1, 2*2, ..., 6*6

        cout << "mapSize = " << mapSize << " * " << mapSize << endl;

        //create map
        int** map = new int*[mapSize];
        for(int i = 0; i < mapSize; i++)
            map[i] = new int[mapSize];

        //intializes map
        for(int i = 0; i < mapSize; i++)
            for(int j = 0; j < mapSize; j++)
                map[i][j] = 0;

        int noSolFlag = 0;//if no solution, set the flag to 1
        
        //start from map[0][0]
        int stepCount = 1;
        int row = 0;
        int col = 0;
        map[row][col] = stepCount;

        if(mapSize == 1){//map = 1*1, there's only one possibility
            for(int i = 0; i < mapSize; i++){
                cout << "\t";
                for(int j = 0; j < mapSize; j++)
                    cout << setw(3) << map[i][j];
                cout << endl;
            }
            cout << "-------------------------------\n";
            continue;
        }

        //create stack to record the step
        Stack recSteps;

        while(true){
            int pushFlag = 0;//if pushed, set flag to 1
            for(int direction = 1; direction <= 9; direction++){//try all directions
                // __ K8 __ K1 __
                // K7 __ __ __ K2
                // __ __ K  __ __
                // K6 __ __ __ K3
                // __ K5 __ K4 __
                switch(direction){
                    case 1:
                        if(row - 2 >= 0 && col + 1 < mapSize && map[row - 2][col + 1] == 0){//if direction is avalible
                            Rec* step = new Rec(row, col, direction);
                            recSteps.push(step);//add crrent step to stack
                            row = row - 2;
                            col = col + 1;
                            stepCount++;
                            map[row][col] = stepCount;//record step on the map
                            pushFlag = 1;
                        }
                        break;
                    case 2:
                        if(row - 1 >= 0 && col + 2 < mapSize && map[row - 1][col + 2] == 0){//if direction is avalible
                            Rec* step = new Rec(row, col, direction);
                            recSteps.push(step);//add crrent step to stack
                            row = row - 1;
                            col = col + 2;
                            stepCount++;
                            map[row][col] = stepCount;//record step on the map
                            pushFlag = 1;
                        }
                        break;
                    case 3:
                        if(row + 1 < mapSize && col + 2 < mapSize && map[row + 1][col + 2] == 0){//if direction is avalible
                            Rec* step = new Rec(row, col, direction);
                            recSteps.push(step);//add crrent step to stack
                            row = row + 1;
                            col = col + 2;
                            stepCount++;
                            map[row][col] = stepCount;//record step on the map
                            pushFlag = 1;
                        }
                        break;
                    case 4:
                        if(row + 2 < mapSize && col + 1 < mapSize && map[row + 2][col + 1] == 0){//if direction is avalible
                            Rec* step = new Rec(row, col, direction);
                            recSteps.push(step);//add crrent step to stack
                            row = row + 2;
                            col = col + 1;
                            stepCount++;
                            map[row][col] = stepCount;//record step on the map
                            pushFlag = 1;
                        }
                        break;
                    case 5:
                        if(row + 2 < mapSize && col - 1 >= 0 && map[row + 2][col - 1] == 0){//if direction is avalible
                            Rec* step = new Rec(row, col, direction);
                            recSteps.push(step);//add crrent step to stack
                            row = row + 2;
                            col = col - 1;
                            stepCount++;
                            map[row][col] = stepCount;//record step on the map
                            pushFlag = 1;
                        }
                        break;
                    case 6:
                        if(row + 1 < mapSize && col - 2 >= 0 && map[row + 1][col - 2] == 0){//if direction is avalible
                            Rec* step = new Rec(row, col, direction);
                            recSteps.push(step);//add crrent step to stack
                            row = row + 1;
                            col = col - 2;
                            stepCount++;
                            map[row][col] = stepCount;//record step on the map
                            pushFlag = 1;
                        }
                        break;
                    case 7:
                        if(row - 1 >= 0 && col - 2 >= 0 && map[row - 1][col - 2] == 0){//if direction is avalible
                            Rec* step = new Rec(row, col, direction);
                            recSteps.push(step);//add crrent step to stack
                            row = row - 1;
                            col = col - 2;
                            stepCount++;
                            map[row][col] = stepCount;//record step on the map
                            pushFlag = 1;
                        }
                        break;
                    case 8:
                        if(row - 2 >= 0 && col - 1 >= 0 && map[row - 2][col - 1] == 0){//if direction is avalible
                            Rec* step = new Rec(row, col, direction);
                            recSteps.push(step);//add crrent step to stack
                            row = row - 2;
                            col = col - 1;
                            stepCount++;
                            map[row][col] = stepCount;//record step on the map
                            pushFlag = 1;
                        }
                        break;
                    default://no direction is avalible(direction == 9), back to last step
                        if(stepCount == 1){//back to origin, and no direction avalible, implies no solution
                            cout << "No solution.\n";
                            cout << "-------------------------------\n";
                            noSolFlag = 1;
                            break;//end switch & loop
                        }
                        map[row][col] = 0;
                        row = recSteps.getTop()->getRow();
                        col = recSteps.getTop()->getCol();
                        direction = recSteps.getTop()->getNextDir();//next loop start from checking direction+1
                        recSteps.pop();
                        stepCount--;
                }//switch
                if(pushFlag)
                    break;//end for
            }//for
            if(noSolFlag)
                break;//end while
            else if(stepCount == mapSize * mapSize)
                break;//end while
        }//while
        if(!noSolFlag){
            for(int i = 0; i < mapSize; i++){
                cout << "\t";
                for(int j = 0; j < mapSize; j++)
                    cout << setw(3) << map[i][j];
                cout << endl;
            }
            cout << "-------------------------------\n";
        }
    }//for
}