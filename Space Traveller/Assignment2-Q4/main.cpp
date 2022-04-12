#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <iomanip>
#include <string>

using namespace std;


class Planet
{
    public:
    string p_name;
    int x,y,z;
    int weight,profit;
    float value;
};

void readPlanets(Planet p[], int n) {
    ifstream inFile;
    inFile.open("A2planets.txt");

    int i = 0;
    string p_name;
    int x, y, z, weight, profit;

    string spam;
        for (int i=0; i<6; i++) 
        inFile >> spam;

    cout << "\nExtracting Planets From Dataset File: \n" << endl;

    while((inFile >> p_name >> x >> y >> z >> weight >> profit) && i < n) {
        cout << "Planet Name: " << p_name << endl;
        p[i].p_name = p_name;
        p[i].x = x;
        p[i].y = y;
        p[i].z = z;
        p[i].weight = weight;
        p[i].profit = profit;
        if (i > 0)
            p[i].value = profit/weight;
        else
            p[i].value = 0;
        i++;
    }

    inFile.close();
}

void displayPlanets(Planet p[], int n) {
    cout << "\n\n\t\t\tList of Planets & Details: \n" << endl;
    for (int i = 0; i < n; i++) {
        cout << "Planet " << i << ": ("
            << setw(3) << p[i].x << ","
            << setw(3) << p[i].y << ","
            << setw(3) << p[i].z << ")"
            << " \tWeight = " << setw(3) << p[i].weight
            << " \tProfit = " << setw(3) << p[i].profit
            << " \tValue = " << setw(3) << p[i].value << endl;
    }
    cout << endl;
}

void knapsack(Planet p[], int shipsize, int n) {
        int table[n+1][shipsize+1];

    for (int i=0; i<n+1; i++) {
      for (int j=0; j<shipsize+1; j++) {
        if (i == 0 || j == 0)
          table[i][j] = 0;
        else if (p[i-1].weight > j) {
          table[i][j] = table[i-1][j];
        }
         else {
          table[i][j] = max(table[i-1][j], table[i-1][j - p[i-1].weight] + p[i-1].profit);
        }
      }
    }

    for (int i=0; i<n+1; i++) {
        cout << "Line " << i << ": ";
        for (int j=0; j<shipsize+1; j++) {
            cout << table[i][j] << " ";
        }
        cout << endl;
    }

    int result = table[n][shipsize];
    int totalWeight = 0;
    int totalProfit = 0;

    for (int i=n; i>0 && result>0; i--) {
       if (result == table[i-1][shipsize])
          continue;
       else {
          cout << "\nPlanet " << i << " Selected: Weight = " << p[i-1].weight << ",\t Profit = " << p[i-1].profit << endl;
          totalWeight = totalWeight + p[i-1].weight;
          totalProfit = totalProfit + p[i-1].profit;
          result = result - p[i-1].profit;
          shipsize = shipsize - p[i-1].weight;
       }
    }

    cout << "\nTotal Weight = " << totalWeight << endl;
    cout << "Total Profit = " << totalProfit << endl;
}

int main() {
    const int n = 10;
    Planet p[n];
    int shipsize = 80;
    readPlanets(p,n);
    displayPlanets(p,n);
    knapsack(p,shipsize,n);
}