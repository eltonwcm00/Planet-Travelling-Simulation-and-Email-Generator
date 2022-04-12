// Question 1b - Linear Probing Hashing)
#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <vector>

const int D_S = 100; //data size
const int T_S = 150; //table size

using namespace std;

int convertToASCII(string letter) {

    int newVar ;

    for (int i = 0; i < letter.length(); i++) {
        char x = letter.at(i);
        newVar = newVar + x;
    }
    return newVar;
}

int searchData() {

    string choice;
    int newVarUser;

    cout << "\nEnter the email that you would like to search : ";
    getline(cin, choice);
    cout << "\n";

    newVarUser = convertToASCII(choice);

    return newVarUser;
}

int main() {

    int* hash = new int[D_S];
    int* newVar = new int[D_S];
    int newVarUser;
    string* array = new string[T_S], * dataset = new string[D_S];
    string choice;
    int i;
    bool check;

    ifstream infile;

    infile.open ("setA.txt"); //setA.txt, setB.txt, setC.txt

    if(infile.is_open()) {

        auto startInsert = chrono::system_clock::now();

        cout << "Key Index\tASCII \tEmail Address" << endl;
        cout << "---------\t----- \t----------------------" << endl;

        for(i = 0; i < D_S; ++i) {

            getline(infile,dataset[i]); //infile >> dataset[i];
            newVar[i] = convertToASCII(dataset[i]); //convert string to ascii int from data set

            hash[i] = newVar[i] % T_S;

            while(!array[hash[i]].empty()) {
                hash[i] = hash[i] + 1;
            }

            array[hash[i]] = dataset[i];

            cout<<hash[i]<< "\t\t" << newVar[i] << "\t" << dataset[i] << endl; //print out the table data
        }

        auto endInsert = chrono::system_clock::now();
        chrono::duration<double> duration = endInsert - startInsert;
        cout.setf(ios::fixed,ios::floatfield);
        cout.precision(5);
        cout << "Duration taken for inserting : " << duration.count() << "s\n";
    }

    for(int x=0; x<10; x++) { // ask for user to key in 10 times

        newVarUser = searchData();

        auto startSearch = chrono::system_clock::now();

        for (i = 0; i < D_S; ++i) {
            if (newVarUser == newVar[i]) {
                check = true;
                break;
            } else {
                check = false;
            }
        }

        if (check) {
            cout << "Target is found" << endl;
        } else {
            cout << "Target is not found" << endl;
        }

        auto endSearch = chrono::system_clock::now();
        chrono::duration<double> duration = endSearch - startSearch;
        cout.setf(ios::fixed,ios::floatfield);
        cout.precision(5);
        cout << "Duration taken for searching : " << duration.count() << "s\n";

    }

    infile.close();
}