//Author: 張浩綸B073040022
//Date: Oct. 19, 2019
//Purpose: write a program to find the knight's tour, using recursion instead of stack

#include<iostream>
#include<iomanip>
using std::cout;
using std::endl;
using std::setw;

//recursion
void recSteps(int** map,const int mapSize, int& stepCount, int row, int col);

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

        recSteps(map, mapSize, stepCount, row, col);//recursion

        if(stepCount != -1){//if there's a solution
            for(int i = 0; i < mapSize; i++){//print map
                cout << "\t";
                for(int j = 0; j < mapSize; j++)
                    cout << setw(3) << map[i][j];
                cout << endl;
            }
            cout << "-------------------------------\n";
        }
    }//for
}

void recSteps(int** map,const int mapSize, int& stepCount, int row, int col){
    if(stepCount == mapSize * mapSize)//end
        return;
    for(int direction = 1; direction <= 9; direction++){//try all directions
        // __ K8 __ K1 __
        // K7 __ __ __ K2
        // __ __ K  __ __
        // K6 __ __ __ K3
        // __ K5 __ K4 __
        switch(direction){
            case 1:
                if(row - 2 >= 0 && col + 1 < mapSize && map[row - 2][col + 1] == 0){//if direction is avalible
                    stepCount++;
                    map[row - 2][col + 1] = stepCount;//record step on the map
                    recSteps(map, mapSize, stepCount, row - 2, col + 1);
                    if(stepCount == mapSize * mapSize)//end
                        return;
                }
                break;
            case 2:
                if(row - 1 >= 0 && col + 2 < mapSize && map[row - 1][col + 2] == 0){//if direction is avalible
                    stepCount++;
                    map[row - 1][col + 2] = stepCount;//record step on the map
                    recSteps(map, mapSize, stepCount, row - 1, col + 2);
                    if(stepCount == mapSize * mapSize)//end
                        return;
                }
                break;
            case 3:
                if(row + 1 < mapSize && col + 2 < mapSize && map[row + 1][col + 2] == 0){//if direction is avalible
                    stepCount++;
                    map[row + 1][col + 2] = stepCount;//record step on the map
                    recSteps(map, mapSize, stepCount, row + 1, col + 2);
                    if(stepCount == mapSize * mapSize)//end
                        return;
                }
                break;
            case 4:
                if(row + 2 < mapSize && col + 1 < mapSize && map[row + 2][col + 1] == 0){//if direction is avalible
                    stepCount++;
                    map[row + 2][col + 1] = stepCount;//record step on the map
                    recSteps(map, mapSize, stepCount, row + 2, col + 1);
                    if(stepCount == mapSize * mapSize)//end
                        return;
                }
                break;
            case 5:
                if(row + 2 < mapSize && col - 1 >= 0 && map[row + 2][col - 1] == 0){//if direction is avalible
                    stepCount++;
                    map[row + 2][col - 1] = stepCount;//record step on the map
                    recSteps(map, mapSize, stepCount, row + 2, col - 1);
                    if(stepCount == mapSize * mapSize)//end
                        return;
                }
                break;
            case 6:
                if(row + 1 < mapSize && col - 2 >= 0 && map[row + 1][col - 2] == 0){//if direction is avalible
                    stepCount++;
                    map[row + 1][col - 2] = stepCount;//record step on the map
                    recSteps(map, mapSize, stepCount, row + 1, col - 2);
                    if(stepCount == mapSize * mapSize)//end
                        return;
                }
                break;
            case 7:
                if(row - 1 >= 0 && col - 2 >= 0 && map[row - 1][col - 2] == 0){//if direction is avalible
                    stepCount++;
                    map[row - 1][col - 2] = stepCount;//record step on the map
                    recSteps(map, mapSize, stepCount, row - 1, col - 2);
                    if(stepCount == mapSize * mapSize)//end
                        return;
                }
                break;
            case 8:
                if(row - 2 >= 0 && col - 1 >= 0 && map[row - 2][col - 1] == 0){//if direction is avalible
                    stepCount++;
                    map[row - 2][col - 1] = stepCount;//record step on the map
                    recSteps(map, mapSize, stepCount, row - 2, col - 1);
                    if(stepCount == mapSize * mapSize)//end
                        return;
                }
                break;
            default://no direction is avalible(direction == 9),continue last step
                if(stepCount == 1){//back to origin, and no direction avalible, implies no solution
                    cout << "No solution.\n";
                    cout << "-------------------------------\n";
                    stepCount = -1;//no solution flag
                    return;
                }
                map[row][col] = 0;
                stepCount--;
                return;
        }//switch
    }//for
}