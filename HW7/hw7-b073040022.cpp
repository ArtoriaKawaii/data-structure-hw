//Author: 張浩綸B073040022
//Date: Dec. 8, 2019
//Purpose: use 5 ways of sort and test their efficiency
/***************************************************/
//while size = 500000, selection sort go TLE********/
//so you may want to comment it to test other sorts*/
/***************************************************/
//#include<bits/stdc++.h>//include all standard libaray
#include<iostream>
#include<cstdlib>
#include<algorithm>
#include<fstream>
#include<ctime>
using std::cout;
using std::endl;
using std::ifstream;
using std::qsort;
using std::sort;
using std::ofstream;
using std::ios;
// using std::time;
void swap(int& a, int& b){
    int temp = a;
    a = b;
    b = temp;
}
//sort arr[0:N-1]
void seletionSort(int *arr, int size){
   for(int i = 0; i < size; i++){
        int j = i;//min j = i
        for(int k = i+1; k < size; k++)
            if(arr[k] < arr[j])
                j = k;
        swap(arr[i], arr[j]);
   } 
}
//
//sort arr[1:N]
void maxHeap(int *arr, const int root, const int length){
    int left = 2*root;      //get left child
    int right = 2*root + 1; //get right child
    int largest = root;
    if(left <= length && arr[left] > arr[root])
        largest = left;
    if(right <= length && arr[right] > arr[largest])
        largest = right;
    if(largest != root){
        swap(arr[largest], arr[root]);
        maxHeap(arr, largest, length); //adjust subtree
    }
}
void heapSort(int* arr, const int length){
    for (int i = length/2; i >= 1; i--) 
        maxHeap(arr, i, length);

    for (int i = length-1; i >= 1; i--){
        swap(arr[1], arr[i+1]);
        maxHeap(arr, 1, i);
    }
}
//
//sort a[1:N]
void quickSort(int* arr, const int left, const int right){
    if(left < right){
        int i = left, j = right + 1;//pivot = arr[left]
        do{
            do i++; while(arr[i] < arr[left]);
            do j--; while(arr[j] > arr[left]);
            if(i < j) swap(arr[i], arr[j]);
        }while(i < j);
        swap(arr[left], arr[j]);
        quickSort(arr, left, j-1);
        quickSort(arr, j+1, right);
    }
}
//
//qsort()
int compare (const void* a, const void* b){
    return ( *(int*)a - *(int*)b );
}
//
int main(){
    // input.txt format:
    // N
    // .
    // .
    // .
    // (data*N first set)
    // N
    // .
    // .
    // .
    // (data*N second set)
    // .
    // .
    // .
    // N
    // .
    // .
    // .
    // (data*N tenth set)
    // 
    // ofstream ofs("input.txt");
    // srand(time(NULL));
    // int i = 100;
    // for(int j = 0; j < 10; j++){
    //     ofs << i << endl;
    //     for(int k = 0; k < i; k++)
    //         ofs << rand() << endl;
    // }
    // i = 500;
    // for(int j = 0; j < 10; j++){
    //     ofs << i << endl;
    //     for(int k = 0; k < i; k++)
    //         ofs << rand() << endl;
    // }
    // i = 1000;
    // for(int j = 0; j < 10; j++){
    //     ofs << i << endl;
    //     for(int k = 0; k < i; k++)
    //         ofs << rand() << endl;
    // }
    // i = 5000;
    // for(int j = 0; j < 10; j++){
    //     ofs << i << endl;
    //     for(int k = 0; k < i; k++)
    //         ofs << rand() << endl;
    // }
    // i = 10000;
    // for(int j = 0; j < 10; j++){
    //     ofs << i << endl;
    //     for(int k = 0; k < i; k++)
    //         ofs << rand() << endl;
    // }
    // i = 50000;
    // for(int j = 0; j < 10; j++){
    //     ofs << i << endl;
    //     for(int k = 0; k < i; k++)
    //         ofs << rand() << endl;
    // }
    // i = 100000;
    // for(int j = 0; j < 10; j++){
    //     ofs << i << endl;
    //     for(int k = 0; k < i; k++)
    //         ofs << rand() << endl;
    // }
    // i = 500000;
    // for(int j = 0; j < 10; j++){
    //     ofs << i << endl;
    //     for(int k = 0; k < i; k++)
    //         ofs << rand() << endl;
    // }
    // ofs.close();
    ifstream ifs("input.txt");
    ofstream ofs;
    int size;
    double start, end;
    double runTime[5][10];  //A, B, C, D, E
    double avgTime[5];      //A, B, C, D, E
    //size == 100
    for(int i = 0; i < 10; i++){
        ifs >> size;//size == 100
        int* arr = new int[size];//10 sets of 100 datas
        for(int j = 0; j < size; j++)
            ifs >> arr[j];
        //A
        int* arrA = new int[size];//a[0:99]
        for(int j = 0; j < size; j++)
            arrA[j] = arr[j];
        start = clock();
        seletionSort(arrA, size);
        end = clock();
        runTime[0][i] = end - start;//ms
        ofs.open("outputA.txt", ios::app);
        ofs << "Selection Sort of " << size << " numbers, use " << runTime[0][i] << " ms\n";
        for(int j = 0; j < size; j++)
            ofs << arrA[j] << endl;
        ofs << "=============================================\n";
        ofs.close();
        delete [] arrA;
        //B
        int* arrB = new int[size+1];//a[1:100]
        arrB[0] = 0;
        for(int j = 1; j <= size; j++)
            arrB[j] = arr[j-1];
        start = clock();
        heapSort(arrB, size);
        end = clock();
        runTime[1][i] = end - start;//ms
        ofs.open("outputB.txt", ios::app);
        ofs << "Heap Sort of " << size << " numbers, use " << runTime[1][i] << "ms\n";
        for(int j = 1; j <= size; j++)
            ofs << arrB[j] << endl;
        ofs << "=============================================\n";
        ofs.close();
        delete [] arrB;
        //C
        int* arrC = new int[size+1];//a[1:100]
        arrC[0] = 0;
        for(int j = 1; j <= size; j++)
            arrC[j] = arr[j-1];
        start = clock();
        quickSort(arrC, 1, size);//a[1:100]
        end = clock();
        runTime[2][i] = end - start;//ms
        ofs.open("outputC.txt", ios::app);
        ofs << "Quick Sort of " << size << " numbers, use " << runTime[2][i] << "ms\n";
        for(int j = 1; j <= size; j++)
            ofs << arrC[j] << endl;
        ofs << "=============================================\n";
        ofs.close();
        delete [] arrC;
        //D
        int* arrD = new int[size];//a[0:99]
        for(int j = 0; j < size; j++)
            arrD[j] = arr[j];
        start = clock();
        qsort(arrD, size, sizeof(int), compare);
        end = clock();
        runTime[3][i] = end - start;//ms
        ofs.open("outputD.txt", ios::app);
        ofs << "Qsort(C) of " << size << " numbers, use " << runTime[3][i] << "ms\n";
        for(int j = 0; j < size; j++)
            ofs << arrD[j] << endl;
        ofs << "=============================================\n";
        ofs.close();
        delete [] arrD;
        //E
        int* arrE = new int[size];//a[0:99]
        for(int j = 0; j < size; j++)
            arrE[j] = arr[j];
        start = clock();
        sort(arrE, arrE+size);
        end = clock();
        runTime[4][i] = end - start;//ms
        ofs.open("outputE.txt", ios::app);
        ofs << "Sort(C++) of " << size << " numbers, use " << runTime[4][i] << "ms\n";
        for(int j = 0; j < size; j++)
            ofs << arrE[j] << endl;
        ofs << "=============================================\n";
        ofs.close();
        delete [] arrE;
        delete [] arr;
    }
    for(int i = 0; i < 5; i++){
        double sum = 0;
        for(int j = 0; j < 10; j++)
            sum += runTime[i][j];
        avgTime[i] = sum / 10;
    }
    ofs.open("outputA.txt", ios::app);
    ofs << "Average time : " << avgTime[0] << "ms\n";
    ofs.close();
    ofs.open("outputB.txt", ios::app);
    ofs << "Average time : " << avgTime[1] << "ms\n";
    ofs.close();
    ofs.open("outputC.txt", ios::app);
    ofs << "Average time : " << avgTime[2] << "ms\n";
    ofs.close();
    ofs.open("outputD.txt", ios::app);
    ofs << "Average time : " << avgTime[3] << "ms\n";
    ofs.close();
    ofs.open("outputE.txt", ios::app);
    ofs << "Average time : " << avgTime[4] << "ms\n";
    ofs.close();
    //size == 500
    for(int i = 0; i < 10; i++){
        ifs >> size;//size == 500
        int* arr = new int[size];//10 sets of 500 datas
        for(int j = 0; j < size; j++)
            ifs >> arr[j];
        //A
        int* arrA = new int[size];//a[0:499]
        for(int j = 0; j < size; j++)
            arrA[j] = arr[j];
        start = clock();
        seletionSort(arrA, size);
        end = clock();
        runTime[0][i] = end - start;//ms
        ofs.open("outputA.txt", ios::app);
        ofs << "Selection Sort of " << size << " numbers, use " << runTime[0][i] << " ms\n";
        for(int j = 0; j < size; j++)
            ofs << arrA[j] << endl;
        ofs << "=============================================\n";
        ofs.close();
        delete [] arrA;
        //B
        int* arrB = new int[size+1];//a[1:500]
        arrB[0] = 0;
        for(int j = 1; j <= size; j++)
            arrB[j] = arr[j-1];
        start = clock();
        heapSort(arrB, size);
        end = clock();
        runTime[1][i] = end - start;//ms
        ofs.open("outputB.txt", ios::app);
        ofs << "Heap Sort of " << size << " numbers, use " << runTime[1][i] << "ms\n";
        for(int j = 1; j <= size; j++)
            ofs << arrB[j] << endl;
        ofs << "=============================================\n";
        ofs.close();
        delete [] arrB;
        //C
        int* arrC = new int[size+1];//a[1:500]
        arrC[0] = 0;
        for(int j = 1; j <= size; j++)
            arrC[j] = arr[j-1];
        start = clock();
        quickSort(arrC, 1, size);//a[1:500]
        end = clock();
        runTime[2][i] = end - start;//ms
        ofs.open("outputC.txt", ios::app);
        ofs << "Quick Sort of " << size << " numbers, use " << runTime[2][i] << "ms\n";
        for(int j = 1; j <= size; j++)
            ofs << arrC[j] << endl;
        ofs << "=============================================\n";
        ofs.close();
        delete [] arrC;
        //D
        int* arrD = new int[size];//a[0:499]
        for(int j = 0; j < size; j++)
            arrD[j] = arr[j];
        start = clock();
        qsort(arrD, size, sizeof(int), compare);
        end = clock();
        runTime[3][i] = end - start;//ms
        ofs.open("outputD.txt", ios::app);
        ofs << "Qsort(C) of " << size << " numbers, use " << runTime[3][i] << "ms\n";
        for(int j = 0; j < size; j++)
            ofs << arrD[j] << endl;
        ofs << "=============================================\n";
        ofs.close();
        delete [] arrD;
        //E
        int* arrE = new int[size];//a[0:499]
        for(int j = 0; j < size; j++)
            arrE[j] = arr[j];
        start = clock();
        sort(arrE, arrE+size);
        end = clock();
        runTime[4][i] = end - start;//ms
        ofs.open("outputE.txt", ios::app);
        ofs << "Sort(C++) of " << size << " numbers, use " << runTime[4][i] << "ms\n";
        for(int j = 0; j < size; j++)
            ofs << arrE[j] << endl;
        ofs << "=============================================\n";
        ofs.close();
        delete [] arrE;
        delete [] arr;
    }
    for(int i = 0; i < 5; i++){
        double sum = 0;
        for(int j = 0; j < 10; j++)
            sum += runTime[i][j];
        avgTime[i] = sum / 10;
    }
    ofs.open("outputA.txt", ios::app);
    ofs << "Average time : " << avgTime[0] << "ms\n";
    ofs.close();
    ofs.open("outputB.txt", ios::app);
    ofs << "Average time : " << avgTime[1] << "ms\n";
    ofs.close();
    ofs.open("outputC.txt", ios::app);
    ofs << "Average time : " << avgTime[2] << "ms\n";
    ofs.close();
    ofs.open("outputD.txt", ios::app);
    ofs << "Average time : " << avgTime[3] << "ms\n";
    ofs.close();
    ofs.open("outputE.txt", ios::app);
    ofs << "Average time : " << avgTime[4] << "ms\n";
    ofs.close();
    //size == 1000
    for(int i = 0; i < 10; i++){
        ifs >> size;//size == 1000
        int* arr = new int[size];//10 sets of 1000 datas
        for(int j = 0; j < size; j++)
            ifs >> arr[j];
        //A
        int* arrA = new int[size];//a[0:999]
        for(int j = 0; j < size; j++)
            arrA[j] = arr[j];
        start = clock();
        seletionSort(arrA, size);
        end = clock();
        runTime[0][i] = end - start;//ms
        ofs.open("outputA.txt", ios::app);
        ofs << "Selection Sort of " << size << " numbers, use " << runTime[0][i] << " ms\n";
        for(int j = 0; j < size; j++)
            ofs << arrA[j] << endl;
        ofs << "=============================================\n";
        ofs.close();
        delete [] arrA;
        //B
        int* arrB = new int[size+1];//a[1:1000]
        arrB[0] = 0;
        for(int j = 1; j <= size; j++)
            arrB[j] = arr[j-1];
        start = clock();
        heapSort(arrB, size);
        end = clock();
        runTime[1][i] = end - start;//ms
        ofs.open("outputB.txt", ios::app);
        ofs << "Heap Sort of " << size << " numbers, use " << runTime[1][i] << "ms\n";
        for(int j = 1; j <= size; j++)
            ofs << arrB[j] << endl;
        ofs << "=============================================\n";
        ofs.close();
        delete [] arrB;
        //C
        int* arrC = new int[size+1];//a[1:1000]
        arrC[0] = 0;
        for(int j = 1; j <= size; j++)
            arrC[j] = arr[j-1];
        start = clock();
        quickSort(arrC, 1, size);//a[1:1000]
        end = clock();
        runTime[2][i] = end - start;//ms
        ofs.open("outputC.txt", ios::app);
        ofs << "Quick Sort of " << size << " numbers, use " << runTime[2][i] << "ms\n";
        for(int j = 1; j <= size; j++)
            ofs << arrC[j] << endl;
        ofs << "=============================================\n";
        ofs.close();
        delete [] arrC;
        //D
        int* arrD = new int[size];//a[0:999]
        for(int j = 0; j < size; j++)
            arrD[j] = arr[j];
        start = clock();
        qsort(arrD, size, sizeof(int), compare);
        end = clock();
        runTime[3][i] = end - start;//ms
        ofs.open("outputD.txt", ios::app);
        ofs << "Qsort(C) of " << size << " numbers, use " << runTime[3][i] << "ms\n";
        for(int j = 0; j < size; j++)
            ofs << arrD[j] << endl;
        ofs << "=============================================\n";
        ofs.close();
        delete [] arrD;
        //E
        int* arrE = new int[size];//a[0:999]
        for(int j = 0; j < size; j++)
            arrE[j] = arr[j];
        start = clock();
        sort(arrE, arrE+size);
        end = clock();
        runTime[4][i] = end - start;//ms
        ofs.open("outputE.txt", ios::app);
        ofs << "Sort(C++) of " << size << " numbers, use " << runTime[4][i] << "ms\n";
        for(int j = 0; j < size; j++)
            ofs << arrE[j] << endl;
        ofs << "=============================================\n";
        ofs.close();
        delete [] arrE;
        delete [] arr;
    }
    for(int i = 0; i < 5; i++){
        double sum = 0;
        for(int j = 0; j < 10; j++)
            sum += runTime[i][j];
        avgTime[i] = sum / 10;
    }
    ofs.open("outputA.txt", ios::app);
    ofs << "Average time : " << avgTime[0] << "ms\n";
    ofs.close();
    ofs.open("outputB.txt", ios::app);
    ofs << "Average time : " << avgTime[1] << "ms\n";
    ofs.close();
    ofs.open("outputC.txt", ios::app);
    ofs << "Average time : " << avgTime[2] << "ms\n";
    ofs.close();
    ofs.open("outputD.txt", ios::app);
    ofs << "Average time : " << avgTime[3] << "ms\n";
    ofs.close();
    ofs.open("outputE.txt", ios::app);
    ofs << "Average time : " << avgTime[4] << "ms\n";
    ofs.close();
    //size == 5000
    for(int i = 0; i < 10; i++){
        ifs >> size;//size == 5000
        int* arr = new int[size];//10 sets of 5000 datas
        for(int j = 0; j < size; j++)
            ifs >> arr[j];
        //A
        int* arrA = new int[size];//a[0:4999]
        for(int j = 0; j < size; j++)
            arrA[j] = arr[j];
        start = clock();
        seletionSort(arrA, size);
        end = clock();
        runTime[0][i] = end - start;//ms
        ofs.open("outputA.txt", ios::app);
        ofs << "Selection Sort of " << size << " numbers, use " << runTime[0][i] << " ms\n";
        for(int j = 0; j < size; j++)
            ofs << arrA[j] << endl;
        ofs << "=============================================\n";
        ofs.close();
        delete [] arrA;
        //B
        int* arrB = new int[size+1];//a[1:5000]
        arrB[0] = 0;
        for(int j = 1; j <= size; j++)
            arrB[j] = arr[j-1];
        start = clock();
        heapSort(arrB, size);
        end = clock();
        runTime[1][i] = end - start;//ms
        ofs.open("outputB.txt", ios::app);
        ofs << "Heap Sort of " << size << " numbers, use " << runTime[1][i] << "ms\n";
        for(int j = 1; j <= size; j++)
            ofs << arrB[j] << endl;
        ofs << "=============================================\n";
        ofs.close();
        delete [] arrB;
        //C
        int* arrC = new int[size+1];//a[1:5000]
        arrC[0] = 0;
        for(int j = 1; j <= size; j++)
            arrC[j] = arr[j-1];
        start = clock();
        quickSort(arrC, 1, size);//a[1:5000]
        end = clock();
        runTime[2][i] = end - start;//ms
        ofs.open("outputC.txt", ios::app);
        ofs << "Quick Sort of " << size << " numbers, use " << runTime[2][i] << "ms\n";
        for(int j = 1; j <= size; j++)
            ofs << arrC[j] << endl;
        ofs << "=============================================\n";
        ofs.close();
        delete [] arrC;
        //D
        int* arrD = new int[size];//a[0:4999]
        for(int j = 0; j < size; j++)
            arrD[j] = arr[j];
        start = clock();
        qsort(arrD, size, sizeof(int), compare);
        end = clock();
        runTime[3][i] = end - start;//ms
        ofs.open("outputD.txt", ios::app);
        ofs << "Qsort(C) of " << size << " numbers, use " << runTime[3][i] << "ms\n";
        for(int j = 0; j < size; j++)
            ofs << arrD[j] << endl;
        ofs << "=============================================\n";
        ofs.close();
        delete [] arrD;
        //E
        int* arrE = new int[size];//a[0:4999]
        for(int j = 0; j < size; j++)
            arrE[j] = arr[j];
        start = clock();
        sort(arrE, arrE+size);
        end = clock();
        runTime[4][i] = end - start;//ms
        ofs.open("outputE.txt", ios::app);
        ofs << "Sort(C++) of " << size << " numbers, use " << runTime[4][i] << "ms\n";
        for(int j = 0; j < size; j++)
            ofs << arrE[j] << endl;
        ofs << "=============================================\n";
        ofs.close();
        delete [] arrE;
        delete [] arr;
    }
    for(int i = 0; i < 5; i++){
        double sum = 0;
        for(int j = 0; j < 10; j++)
            sum += runTime[i][j];
        avgTime[i] = sum / 10;
    }
    ofs.open("outputA.txt", ios::app);
    ofs << "Average time : " << avgTime[0] << "ms\n";
    ofs.close();
    ofs.open("outputB.txt", ios::app);
    ofs << "Average time : " << avgTime[1] << "ms\n";
    ofs.close();
    ofs.open("outputC.txt", ios::app);
    ofs << "Average time : " << avgTime[2] << "ms\n";
    ofs.close();
    ofs.open("outputD.txt", ios::app);
    ofs << "Average time : " << avgTime[3] << "ms\n";
    ofs.close();
    ofs.open("outputE.txt", ios::app);
    ofs << "Average time : " << avgTime[4] << "ms\n";
    ofs.close();
    //size == 10000
    for(int i = 0; i < 10; i++){
        ifs >> size;//size == 10000
        int* arr = new int[size];//10 sets of 10000 datas
        for(int j = 0; j < size; j++)
            ifs >> arr[j];
        //A
        int* arrA = new int[size];//a[0:9999]
        for(int j = 0; j < size; j++)
            arrA[j] = arr[j];
        start = clock();
        seletionSort(arrA, size);
        end = clock();
        runTime[0][i] = end - start;//ms
        ofs.open("outputA.txt", ios::app);
        ofs << "Selection Sort of " << size << " numbers, use " << runTime[0][i] << " ms\n";
        for(int j = 0; j < size; j++)
            ofs << arrA[j] << endl;
        ofs << "=============================================\n";
        ofs.close();
        delete [] arrA;
        //B
        int* arrB = new int[size+1];//a[1:10000]
        arrB[0] = 0;
        for(int j = 1; j <= size; j++)
            arrB[j] = arr[j-1];
        start = clock();
        heapSort(arrB, size);
        end = clock();
        runTime[1][i] = end - start;//ms
        ofs.open("outputB.txt", ios::app);
        ofs << "Heap Sort of " << size << " numbers, use " << runTime[1][i] << "ms\n";
        for(int j = 1; j <= size; j++)
            ofs << arrB[j] << endl;
        ofs << "=============================================\n";
        ofs.close();
        delete [] arrB;
        //C
        int* arrC = new int[size+1];//a[1:10000]
        arrC[0] = 0;
        for(int j = 1; j <= size; j++)
            arrC[j] = arr[j-1];
        start = clock();
        quickSort(arrC, 1, size);//a[1:10000]
        end = clock();
        runTime[2][i] = end - start;//ms
        ofs.open("outputC.txt", ios::app);
        ofs << "Quick Sort of " << size << " numbers, use " << runTime[2][i] << "ms\n";
        for(int j = 1; j <= size; j++)
            ofs << arrC[j] << endl;
        ofs << "=============================================\n";
        ofs.close();
        delete [] arrC;
        //D
        int* arrD = new int[size];//a[0:9999]
        for(int j = 0; j < size; j++)
            arrD[j] = arr[j];
        start = clock();
        qsort(arrD, size, sizeof(int), compare);
        end = clock();
        runTime[3][i] = end - start;//ms
        ofs.open("outputD.txt", ios::app);
        ofs << "Qsort(C) of " << size << " numbers, use " << runTime[3][i] << "ms\n";
        for(int j = 0; j < size; j++)
            ofs << arrD[j] << endl;
        ofs << "=============================================\n";
        ofs.close();
        delete [] arrD;
        //E
        int* arrE = new int[size];//a[0:9999]
        for(int j = 0; j < size; j++)
            arrE[j] = arr[j];
        start = clock();
        sort(arrE, arrE+size);
        end = clock();
        runTime[4][i] = end - start;//ms
        ofs.open("outputE.txt", ios::app);
        ofs << "Sort(C++) of " << size << " numbers, use " << runTime[4][i] << "ms\n";
        for(int j = 0; j < size; j++)
            ofs << arrE[j] << endl;
        ofs << "=============================================\n";
        ofs.close();
        delete [] arrE;
        delete [] arr;
    }
    for(int i = 0; i < 5; i++){
        double sum = 0;
        for(int j = 0; j < 10; j++)
            sum += runTime[i][j];
        avgTime[i] = sum / 10;
    }
    ofs.open("outputA.txt", ios::app);
    ofs << "Average time : " << avgTime[0] << "ms\n";
    ofs.close();
    ofs.open("outputB.txt", ios::app);
    ofs << "Average time : " << avgTime[1] << "ms\n";
    ofs.close();
    ofs.open("outputC.txt", ios::app);
    ofs << "Average time : " << avgTime[2] << "ms\n";
    ofs.close();
    ofs.open("outputD.txt", ios::app);
    ofs << "Average time : " << avgTime[3] << "ms\n";
    ofs.close();
    ofs.open("outputE.txt", ios::app);
    ofs << "Average time : " << avgTime[4] << "ms\n";
    ofs.close();
    //size == 50000
    for(int i = 0; i < 10; i++){
        ifs >> size;//size == 50000
        int* arr = new int[size];//10 sets of 50000 datas
        for(int j = 0; j < size; j++)
            ifs >> arr[j];
        //A
        int* arrA = new int[size];//a[0:49999]
        for(int j = 0; j < size; j++)
            arrA[j] = arr[j];
        start = clock();
        seletionSort(arrA, size);
        end = clock();
        runTime[0][i] = end - start;//ms
        ofs.open("outputA.txt", ios::app);
        ofs << "Selection Sort of " << size << " numbers, use " << runTime[0][i] << " ms\n";
        for(int j = 0; j < size; j++)
            ofs << arrA[j] << endl;
        ofs << "=============================================\n";
        ofs.close();
        delete [] arrA;
        //B
        int* arrB = new int[size+1];//a[1:50000]
        arrB[0] = 0;
        for(int j = 1; j <= size; j++)
            arrB[j] = arr[j-1];
        start = clock();
        heapSort(arrB, size);
        end = clock();
        runTime[1][i] = end - start;//ms
        ofs.open("outputB.txt", ios::app);
        ofs << "Heap Sort of " << size << " numbers, use " << runTime[1][i] << "ms\n";
        for(int j = 1; j <= size; j++)
            ofs << arrB[j] << endl;
        ofs << "=============================================\n";
        ofs.close();
        delete [] arrB;
        //C
        int* arrC = new int[size+1];//a[1:50000]
        arrC[0] = 0;
        for(int j = 1; j <= size; j++)
            arrC[j] = arr[j-1];
        start = clock();
        quickSort(arrC, 1, size);//a[1:50000]
        end = clock();
        runTime[2][i] = end - start;//ms
        ofs.open("outputC.txt", ios::app);
        ofs << "Quick Sort of " << size << " numbers, use " << runTime[2][i] << "ms\n";
        for(int j = 1; j <= size; j++)
            ofs << arrC[j] << endl;
        ofs << "=============================================\n";
        ofs.close();
        delete [] arrC;
        //D
        int* arrD = new int[size];//a[0:49999]
        for(int j = 0; j < size; j++)
            arrD[j] = arr[j];
        start = clock();
        qsort(arrD, size, sizeof(int), compare);
        end = clock();
        runTime[3][i] = end - start;//ms
        ofs.open("outputD.txt", ios::app);
        ofs << "Qsort(C) of " << size << " numbers, use " << runTime[3][i] << "ms\n";
        for(int j = 0; j < size; j++)
            ofs << arrD[j] << endl;
        ofs << "=============================================\n";
        ofs.close();
        delete [] arrD;
        //E
        int* arrE = new int[size];//a[0:49999]
        for(int j = 0; j < size; j++)
            arrE[j] = arr[j];
        start = clock();
        sort(arrE, arrE+size);
        end = clock();
        runTime[4][i] = end - start;//ms
        ofs.open("outputE.txt", ios::app);
        ofs << "Sort(C++) of " << size << " numbers, use " << runTime[4][i] << "ms\n";
        for(int j = 0; j < size; j++)
            ofs << arrE[j] << endl;
        ofs << "=============================================\n";
        ofs.close();
        delete [] arrE;
        delete [] arr;
    }
    for(int i = 0; i < 5; i++){
        double sum = 0;
        for(int j = 0; j < 10; j++)
            sum += runTime[i][j];
        avgTime[i] = sum / 10;
    }
    ofs.open("outputA.txt", ios::app);
    ofs << "Average time : " << avgTime[0] << "ms\n";
    ofs.close();
    ofs.open("outputB.txt", ios::app);
    ofs << "Average time : " << avgTime[1] << "ms\n";
    ofs.close();
    ofs.open("outputC.txt", ios::app);
    ofs << "Average time : " << avgTime[2] << "ms\n";
    ofs.close();
    ofs.open("outputD.txt", ios::app);
    ofs << "Average time : " << avgTime[3] << "ms\n";
    ofs.close();
    ofs.open("outputE.txt", ios::app);
    ofs << "Average time : " << avgTime[4] << "ms\n";
    ofs.close();
    //size == 100000
    for(int i = 0; i < 10; i++){
        ifs >> size;//size == 100000
        int* arr = new int[size];//10 sets of 100000 datas
        for(int j = 0; j < size; j++)
            ifs >> arr[j];
        //A
        int* arrA = new int[size];//a[0:99999]
        for(int j = 0; j < size; j++)
            arrA[j] = arr[j];
        start = clock();
        seletionSort(arrA, size);
        end = clock();
        runTime[0][i] = end - start;//ms
        ofs.open("outputA.txt", ios::app);
        ofs << "Selection Sort of " << size << " numbers, use " << runTime[0][i] << " ms\n";
        for(int j = 0; j < size; j++)
            ofs << arrA[j] << endl;
        ofs << "=============================================\n";
        ofs.close();
        delete [] arrA;
        //B
        int* arrB = new int[size+1];//a[1:100000]
        arrB[0] = 0;
        for(int j = 1; j <= size; j++)
            arrB[j] = arr[j-1];
        start = clock();
        heapSort(arrB, size);
        end = clock();
        runTime[1][i] = end - start;//ms
        ofs.open("outputB.txt", ios::app);
        ofs << "Heap Sort of " << size << " numbers, use " << runTime[1][i] << "ms\n";
        for(int j = 1; j <= size; j++)
            ofs << arrB[j] << endl;
        ofs << "=============================================\n";
        ofs.close();
        delete [] arrB;
        //C
        int* arrC = new int[size+1];//a[1:100000]
        arrC[0] = 0;
        for(int j = 1; j <= size; j++)
            arrC[j] = arr[j-1];
        start = clock();
        quickSort(arrC, 1, size);//a[1:100000]
        end = clock();
        runTime[2][i] = end - start;//ms
        ofs.open("outputC.txt", ios::app);
        ofs << "Quick Sort of " << size << " numbers, use " << runTime[2][i] << "ms\n";
        for(int j = 1; j <= size; j++)
            ofs << arrC[j] << endl;
        ofs << "=============================================\n";
        ofs.close();
        delete [] arrC;
        //D
        int* arrD = new int[size];//a[0:99999]
        for(int j = 0; j < size; j++)
            arrD[j] = arr[j];
        start = clock();
        qsort(arrD, size, sizeof(int), compare);
        end = clock();
        runTime[3][i] = end - start;//ms
        ofs.open("outputD.txt", ios::app);
        ofs << "Qsort(C) of " << size << " numbers, use " << runTime[3][i] << "ms\n";
        for(int j = 0; j < size; j++)
            ofs << arrD[j] << endl;
        ofs << "=============================================\n";
        ofs.close();
        delete [] arrD;
        //E
        int* arrE = new int[size];//a[0:99999]
        for(int j = 0; j < size; j++)
            arrE[j] = arr[j];
        start = clock();
        sort(arrE, arrE+size);
        end = clock();
        runTime[4][i] = end - start;//ms
        ofs.open("outputE.txt", ios::app);
        ofs << "Sort(C++) of " << size << " numbers, use " << runTime[4][i] << "ms\n";
        for(int j = 0; j < size; j++)
            ofs << arrE[j] << endl;
        ofs << "=============================================\n";
        ofs.close();
        delete [] arrE;
        delete [] arr;
    }
    for(int i = 0; i < 5; i++){
        double sum = 0;
        for(int j = 0; j < 10; j++)
            sum += runTime[i][j];
        avgTime[i] = sum / 10;
    }
    ofs.open("outputA.txt", ios::app);
    ofs << "Average time : " << avgTime[0] << "ms\n";
    ofs.close();
    ofs.open("outputB.txt", ios::app);
    ofs << "Average time : " << avgTime[1] << "ms\n";
    ofs.close();
    ofs.open("outputC.txt", ios::app);
    ofs << "Average time : " << avgTime[2] << "ms\n";
    ofs.close();
    ofs.open("outputD.txt", ios::app);
    ofs << "Average time : " << avgTime[3] << "ms\n";
    ofs.close();
    ofs.open("outputE.txt", ios::app);
    ofs << "Average time : " << avgTime[4] << "ms\n";
    ofs.close();
    //size == 500000
    for(int i = 0; i < 10; i++){
        ifs >> size;//size == 500000
        int* arr = new int[size];//10 sets of 500000 datas
        for(int j = 0; j < size; j++)
            ifs >> arr[j];
        //A
        int* arrA = new int[size];//a[0:499999]
        for(int j = 0; j < size; j++)
            arrA[j] = arr[j];
        start = clock();
        seletionSort(arrA, size);
        end = clock();
        runTime[0][i] = end - start;//ms
        ofs.open("outputA.txt", ios::app);
        ofs << "Selection Sort of " << size << " numbers, use " << runTime[0][i] << " ms\n";
        for(int j = 0; j < size; j++)
            ofs << arrA[j] << endl;
        ofs << "=============================================\n";
        ofs.close();
        delete [] arrA;
        //B
        int* arrB = new int[size+1];//a[1:500000]
        arrB[0] = 0;
        for(int j = 1; j <= size; j++)
            arrB[j] = arr[j-1];
        start = clock();
        heapSort(arrB, size);
        end = clock();
        runTime[1][i] = end - start;//ms
        ofs.open("outputB.txt", ios::app);
        ofs << "Heap Sort of " << size << " numbers, use " << runTime[1][i] << "ms\n";
        for(int j = 1; j <= size; j++)
            ofs << arrB[j] << endl;
        ofs << "=============================================\n";
        ofs.close();
        delete [] arrB;
        //C
        int* arrC = new int[size+1];//a[1:500000]
        arrC[0] = 0;
        for(int j = 1; j <= size; j++)
            arrC[j] = arr[j-1];
        start = clock();
        quickSort(arrC, 1, size);//a[1:500000]
        end = clock();
        runTime[2][i] = end - start;//ms
        ofs.open("outputC.txt", ios::app);
        ofs << "Quick Sort of " << size << " numbers, use " << runTime[2][i] << "ms\n";
        for(int j = 1; j <= size; j++)
            ofs << arrC[j] << endl;
        ofs << "=============================================\n";
        ofs.close();
        delete [] arrC;
        //D
        int* arrD = new int[size];//a[0:499999]
        for(int j = 0; j < size; j++)
            arrD[j] = arr[j];
        start = clock();
        qsort(arrD, size, sizeof(int), compare);
        end = clock();
        runTime[3][i] = end - start;//ms
        ofs.open("outputD.txt", ios::app);
        ofs << "Qsort(C) of " << size << " numbers, use " << runTime[3][i] << "ms\n";
        for(int j = 0; j < size; j++)
            ofs << arrD[j] << endl;
        ofs << "=============================================\n";
        ofs.close();
        delete [] arrD;
        //E
        int* arrE = new int[size];//a[0:499999]
        for(int j = 0; j < size; j++)
            arrE[j] = arr[j];
        start = clock();
        sort(arrE, arrE+size);
        end = clock();
        runTime[4][i] = end - start;//ms
        ofs.open("outputE.txt", ios::app);
        ofs << "Sort(C++) of " << size << " numbers, use " << runTime[4][i] << "ms\n";
        for(int j = 0; j < size; j++)
            ofs << arrE[j] << endl;
        ofs << "=============================================\n";
        ofs.close();
        delete [] arrE;
        delete [] arr;
    }
    for(int i = 0; i < 5; i++){
        double sum = 0;
        for(int j = 0; j < 10; j++)
            sum += runTime[i][j];
        avgTime[i] = sum / 10;
    }
    ofs.open("outputA.txt", ios::app);
    ofs << "Average time : " << avgTime[0] << "ms\n";
    ofs.close();
    ofs.open("outputB.txt", ios::app);
    ofs << "Average time : " << avgTime[1] << "ms\n";
    ofs.close();
    ofs.open("outputC.txt", ios::app);
    ofs << "Average time : " << avgTime[2] << "ms\n";
    ofs.close();
    ofs.open("outputD.txt", ios::app);
    ofs << "Average time : " << avgTime[3] << "ms\n";
    ofs.close();
    ofs.open("outputE.txt", ios::app);
    ofs << "Average time : " << avgTime[4] << "ms\n";
    ofs.close();
    ifs.close();
    return 0;
}