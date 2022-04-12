#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "Sort.cpp";
using namespace std;

int vertArr[10][10];

string* distanceDataset = new string[100];
string* weightDataset = new string[100];

int* profit = new int[100];
int* dist = new int [100];

char alphabet[] = {'A','B','C','D','E','F','G','H','I', 'J'};

Sort obj = Sort();

int main() {

    fstream indataDistance, indataProfit;
    stringstream ss;

    int lineno;
    bool readDist = false;
    bool readProfit = false;
    indataDistance.open("A2planets.txt");
    indataProfit.open("A2planets.txt");

    cout << "Edges" << "\t\t\t" << "Distance" << endl;
    cout << "=====================" << "\t" << "========" << endl;

    for (lineno = 0; getline(indataDistance, distanceDataset[lineno]) && lineno < 50; lineno++) //starts counter from 1 in increment
    {
        string toGo, goTo;
        string whitespace = " ";
        istringstream sb(distanceDataset[lineno]);

        if(lineno >= 16) {

            sb >> toGo >> whitespace >> goTo >> whitespace >> dist[lineno];
            //cout << dist[lineno] << " ";
            cout << distanceDataset[lineno] << endl;
        }

        readDist = true;
    }

    if(readDist) {
        // planet a to planet b; planet a to planet c
        vertArr[0][1] = dist[16]; // 109
        vertArr[1][0] = dist[16]; // 109
        vertArr[0][2] = dist[17]; // 1202
        vertArr[2][0] = dist[17]; // 1202
        // planet b to f; planet b to g
        vertArr[5][1] = dist[18];  //258
        vertArr[1][5] = dist[18];  //258
        vertArr[6][1] = dist[19];  //239
        vertArr[1][6] = dist[19];  //239
        // planet c to d; planet c to e
        vertArr[2][3] = dist[20];  //1198
        vertArr[3][2] = dist[20];  //1198
        vertArr[2][4] = dist[21];  //1054
        vertArr[4][2] = dist[21];  //1054
        // planet d to h; planet d to i
        vertArr[3][7] = dist[22];  //224
        vertArr[7][3] = dist[22];  //224
        vertArr[3][8] = dist[23];  //441
        vertArr[8][3] = dist[23];  //441
        // planet e to f; planet e to h
        vertArr[4][5] = dist[24];  //296
        vertArr[5][4] = dist[24];  //296
        vertArr[4][7] = dist[25];  //184
        vertArr[7][4] = dist[25];  //184
        // planet f to j
        vertArr[5][9] = dist[26];  //715
        vertArr[9][5] = dist[26];  //715
        // planet g to i; planet g to j
        vertArr[6][8] = dist[27];  //376
        vertArr[8][6] = dist[27];  //376
        vertArr[6][9] = dist[28];  //334
        vertArr[9][6] = dist[28];  //334
        // planet h to i
        vertArr[7][8] = dist[29];  //541
        vertArr[8][7] = dist[29];  //541
        // planet j to i
        vertArr[9][8] = dist[30];  //288
        vertArr[8][9] = dist[30];  //288

        int v = 10;
        int i, j;

        cout <<"\n\n";
        cout << "Adjacency Matrix" << endl;
        cout << "================" << endl;
        cout << "\t__A__\t__B__\t__C__\t__D__\t__E__\t__F__\t__G__\t__H__\t__I__\t__J__" << endl;

        for(i = 0; i < v; i++) {

            cout << alphabet[i] << "\t|";

            for(j = 0; j < v; j++) {
                cout << vertArr[i][j] << "\t|";
            }
            cout << endl;
        }

        cout << endl;

        cout << "Adjacency List" << endl;
        cout << "==============" << endl;

        for(i = 0; i < v; i++) {
            cout << alphabet[i] << "| ----> ";
            for(j = 0; j < v; j++) {
                if(vertArr[i][j] != 0) {
                    cout << vertArr[i][j] << " ";
                }
            }
            cout << endl;
        }
    }


    cout << endl;

    ///////////////////////////////////////DISTANCE///////////////////////////////////////
    cout << "\n----------------------------------------------DISTANCE OF EDGES-----------------------------------------------\n";



    cout << "Original order of Distance  : ";
    for (lineno = 0;  lineno < 29; lineno++) //starts counter from 1 in increment
    {
        if(lineno > 15 )
        {
            cout << dist[lineno] << " ";
        }
    }

    obj.quickSort(dist, 0, lineno - 1);
    cout << endl ;

    cout << "Ascending order of Distance : ";
    for (lineno = 0; lineno < 27; lineno++){
        if(lineno > 13 ){
            cout << dist[lineno] << " ";
        }
    }

    cout << endl ;

    cout << "Descending order of Distance: ";
    for (lineno = 26; lineno > 13; --lineno) {
        cout << dist[lineno] << " ";
    }

    cout << endl << endl;

    ///////////////////////////////////////PROFIT///////////////////////////////////////

    cout << "\n----------------------------------------------PROFITS OF PLANETS----------------------------------------------\n";
    cout << "Original order of Profits   : " ;

    for (lineno = 0; getline(indataProfit,weightDataset[lineno]) && lineno < 13; lineno++) //starts counter from 1 in increment
    {
        string p_name;
        int x,r,z;
        int weight;
        istringstream ss(weightDataset[lineno]);

        if(ss >> p_name >> x >> r >> z >> weight >> profit[lineno]){
           // readProfit = true;
            cout << profit[lineno] << " ";
        }
    }

    obj.quickSort(profit, 0, lineno - 1);

    cout << endl;

    cout << "Ascending order of Profits  : ";

    for (lineno = 2; lineno < 12; lineno++) {
        cout << profit[lineno] << " ";
    }

    cout << endl;

    cout << "Descending order of Profits : ";

    for (lineno = 11; lineno > 1; --lineno) {
        cout << profit[lineno] << " ";
    }

    cout << endl;

    indataProfit.close();
    indataDistance.close();

    return 0;
}