//Question 3 - Priority Queue

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <chrono>
#include "PriorityQueue.cpp"
using namespace std;

const int D_S = 100; //CHANGE THIS CONSTANT ACCORDING TO DATASET SIZE, EXAMPLE: SETA(100), SETB(1000000), SETC(5000000)

// comment out line 31, 34, 37, 50, 53 for setB.txt and setC.txt

int main () {

    PriorityQueue<int> pq;

    int* newVar = new int[D_S]; //ascii array
    ifstream infile;

    infile.open ("setA.txt"); // change according to ur file

    string* dataset = new string[D_S];

    for(int i=0; i<D_S; i++) {
        getline(infile, dataset[i]);
        newVar[i] = pq.convertToASCII(dataset[i]); //convert string to ascii int from data set
    }

    cout << "Array = ";
    printArray (newVar, D_S);

    cout << "\nEnqueue\t: PriorityQueue\n";

    auto startEnqueue = chrono::system_clock::now();

    for (int i = 0; i < D_S; i++) {
       // cout << newVar[i] << "\t: ";
        pq.enqueue (newVar[i]);
        pq.print();
    }

    auto endEnqueue = chrono::system_clock::now();
    chrono::duration<double> duration = endEnqueue - startEnqueue;
    cout.setf(ios::fixed,ios::floatfield);
    cout.precision(5);
    cout << "\nDuration taken for enqueueing the data : " << duration.count() << "s\n";

    cout << "\nDequeue\t: PriorityQueue\n";
    auto startDequeue = chrono::system_clock::now();
    for (int i = 0; i < D_S * 0.1; i++) {
        cout << pq.dequeue() << "\t: ";
        pq.print();
    }

    auto endDequeue = chrono::system_clock::now();
    chrono::duration<double> duration2 = endDequeue - startEnqueue;
    cout.setf(ios::fixed,ios::floatfield);
    cout.precision(5);
    cout << "\nDuration taken for dequeueing the data : " << duration2.count() << "s\n";
}
