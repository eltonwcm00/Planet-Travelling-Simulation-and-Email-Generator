// Assignment 2 - Dataset generation

// Elton Wong Chun Meng 1181203056
// Reynard Kok Jin Yik 1181203212
// Mohammed OSama Ismail Al Hindi 1201300756

#include <iostream>
#include <chrono>
#include <math.h>
#include <fstream>
#include <string>

using namespace std;
int count = 0;

class Planet
{
public:
    string p_name;
    int x,y,z;  // coordinates
    int weight,profit;

    int distance=0;
};

void generate(string id, int a[])   // generates 10 numbers from id
{
    id += id;

    for (int i=0;i<10;i++)
    {
        char t1[4] = {id[i], id[i+1], id[i+2], '\0'};
        a[i] = atoi(t1);
    }
}

void genPlanet(string id1, string id2, string id3)
{
    if ((id1.compare(id2) ==0) || (id1.compare(id3) == 0))
    {
        // reverse id1
        for (int i=0;i<5;i++)
        {
            int tmp;
            tmp=id1[i];
            id1[i]=id1[9-i];
            id1[9-i]=tmp;
        }
    }

    if (id2.compare(id3) == 0)
    {
        // reverse id2
        for (int i=0;i<5;i++)
        {
            int tmp;
            tmp=id2[i];
            id2[i]=id2[9-i];
            id2[9-i]=tmp;
        }
    }

    static const char alphabets[] =
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    const int p_count=10;
    int x[p_count],y[p_count],z[p_count];

    generate(id1,x);
    generate(id2,y);
    generate(id3,z);

    Planet p[p_count];

    srand(time(0));

    int totalweight = 0;

    int i = 0;

    // initialise Planet A (home planet)
    p[i].p_name = "Planet_" ;
    p[i].p_name += alphabets[i];
    p[i].x = x[i];
    p[i].y = y[i];
    p[i].z = z[i];
    p[i].weight = 0;
    p[i].profit = 0;

    // initialise other planets
    for(int i=1;i<p_count;i++)
    {
        p[i].p_name = "Planet_" ;
        p[i].p_name += alphabets[i];
        p[i].x = x[i];
        p[i].y = y[i];
        p[i].z = z[i];
        p[i].weight = (rand() % 16) + 5;
        totalweight += p[i].weight;
        p[i].profit = ((rand() % 16) + 5) * 10;
    }

    ofstream myfile;
    myfile.open ("A2planetsss.txt");

    const int number = 15;

    string goTo[number] = {"Planet_A","Planet_A","Planet_B","Planet_B","Planet_C","Planet_C","Planet_D",
                           "Planet_D","Planet_E","Planet_E","Planet_F","Planet_G","Planet_G","Planet_H","Planet_J"};


    string toGo[number] = {"Planet_B","Planet_C","Planet_F","Planet_G","Planet_D","Planet_E","Planet_H",
                           "Planet_I","Planet_F","Planet_H","Planet_J","Planet_J","Planet_I","Planet_I","Planet_I"};


    cout << "\nGenerating data ..." << endl;

    myfile << "\nPlanet\t\t" << "X\t" << "Y\t" << "Z\t" << "Weight\t" << "Profit\t" << endl;

    cout << "\nNum\t" << "Planet\t\t" << "X\t" << "Y\t" << "Z\t" << "Weight\t" << "Profit\t" << endl;

    for(int i=0;i<p_count;i++)
    {
        cout << i << ":\t" << p[i].p_name << ",\t" << p[i].x << ",\t" << p[i].y << ",\t" << p[i].z
             << ",\t" << p[i].weight <<  ",\t" << p[i].profit << endl;

        myfile << p[i].p_name << "\t" << p[i].x << "\t" << p[i].y << "\t" << p[i].z
               << "\t" << p[i].weight <<  "\t\t" << p[i].profit <<endl;
    }

    cout << endl << "Total weight = " << totalweight;

    cout << "\n\n---------------Distance between planets using MAP 2---------------" << endl;

    myfile << endl;
    myfile << "\n\n---------------Distance between planets using MAP 2---------------" << endl;

    for(int i=0; i<p_count; i++)
    {
        for(int j=0; j<p_count; j++)
        {
            p[j].distance = sqrt(pow(p[j].x  - p[i].x , 2) + pow(p[j].y - p[i].y, 2) + pow(p[j].z - p[i].z, 2));

            for(int x=0; x<number;x++)
            {
                if(p[i].p_name == goTo[x])
                {
                    if(p[j].p_name == toGo[x])
                    {
                        cout << goTo[x] << " to " << toGo[x] << " = " << p[j].distance << endl;
//                        myfile << goTo[x] << " to " << toGo[x] << " = " << p[j].distance << endl;
                    }
                }
            }
        }
        cout<<endl;
        myfile<<endl;
    }
    myfile.close();
    cout << "Data generated." << endl;
}

bool isValid(string studentID)
{
    if (studentID.size() != 10)
    {
        cout << " invalid" << endl;
        return false;
    }

    for (int i=0;i<10;i++)
    {
        if (!isdigit(studentID[i]))
        {
            cout << " invalid" << endl;
            return false;
        }
    }
    return true;
}

int main()
{
    string student[3];
    int i=0;

    cout << endl << endl;

    for (int i=0;i<3;i++)
    {
        do
        {
            cout<<"Enter student ID " << i+1 << ": ";
            cin>>student[i];
        }
        while (!isValid(student[i]));
    }
    genPlanet(student[0],student[1],student[2]);
    return 0;
}