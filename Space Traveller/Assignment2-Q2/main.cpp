// A C++ program for Dijkstra's single source shortest path algorithm.
// The program is for adjacency matrix representation of the graph
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <climits>
using namespace std;

// Number of vertices in the graph
#define V 10

int vertArr[V][V];

string* distanceDataset = new string[100];
string* coordinateDataset = new string[100];

char alphabet[] = {'A','B','C','D','E','F','G','H','I', 'J'};

// A utility function to find the vertex with minimum distance value, from
// the set of vertices not yet included in shortest path tree
int minDistance(int dist[], bool sptSet[])
{
    // Initialize min value
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++)
        if (sptSet[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;

    return min_index;
}

// Function to print shortest
// path from source to j
// using parent array
void printPath(char parent[], int j)
{
    // Base Case : If j is source
    if (parent[j] == - 1)
        return;

    printPath(parent, parent[j]);

    printf("%d ", j);
}

// Print map
void printMap() {

    int v = 10;
    string mapDijstrak [10][10];
    string map[10][10] = {
            {" ", " ", " ", " A", " ", " ", " ", " ", " ", " "}, //0
            {" ", " ", " /", " ", "\\", " ", " ", " ", " ", " "}, //1
            {"+", "C", " ", " ", " ", "B", "+", " ", " ", " "}, //2
            {"|", " ", "\\", " ", "/", " ", "|", " ", " ", " "}, //3
            {"|", " ", "E", "-", "F", " ", "|", " ", " ", " "}, //4
            {"|", " ", "|", " ", "|", " ", "|", " ", " ", " "}, //5
            {"D", "-", "H", " ", "J", "-", "G", " ", " ", " "}, //6
            {"|", " ", "\\", " ", "/", " ", "|", " ", " ", " "}, //7
            {"+", "-", "-", "I", "-", "-", "+", " ", " ", " "}, //8
            {" ", " ", " ", " ", " ", " ", " ", " ", " ", " "}, //9
    };

    cout << "Full Map - Map #2" << endl;
    cout << "=================" << endl;
    for(int i = 0; i < v; i++) {
        for(int j = 0; j < v; j++) {
            cout << map[i][j] << " ";
        }
        cout << endl;
    }

    // first path = a,b,f,e,h,d
    mapDijstrak[0][1] = map[5][3]; // " "
    mapDijstrak[0][2] = map[5][3]; // " "
    mapDijstrak[0][3] = map[0][3]; // A
    mapDijstrak[1][0] = map[5][3]; // " "
    mapDijstrak[1][1] = map[5][3]; // " "
    mapDijstrak[1][4] = map[1][4]; // (\)
    mapDijstrak[2][1] = map[5][3]; // " "
    mapDijstrak[2][0] = map[5][3]; // " "
    mapDijstrak[2][5] = map[2][5]; // B
    mapDijstrak[2][6] = map[2][6]; // +
    mapDijstrak[2][4] = map[2][4]; // " "
    mapDijstrak[3][1] = map[3][1]; // " "
    mapDijstrak[3][2] = map[5][3]; // " "
    mapDijstrak[3][3] = map[3][3]; // " "
    mapDijstrak[3][4] = map[3][4]; // (/)
    mapDijstrak[4][1] = map[5][3]; // " "
    mapDijstrak[4][4] = map[4][4]; // F
    mapDijstrak[4][3] = map[4][3]; // -
    mapDijstrak[4][2] = map[4][2]; // E
    mapDijstrak[5][1] = map[5][1]; // " "
    mapDijstrak[5][2] = map[5][2]; // |
    mapDijstrak[5][3] = map[5][3]; // " "
    mapDijstrak[5][4] = map[5][3]; // " "
    mapDijstrak[6][2] = map[6][2]; // H
    mapDijstrak[6][1] = map[6][1]; // -
    mapDijstrak[6][0] = map[6][0]; // D

    // second path = c
    mapDijstrak[1][2] = map[1][2]; // (/)
    mapDijstrak[2][0] = map[5][3]; // " "
    mapDijstrak[2][0] = map[5][3]; // " "
    mapDijstrak[2][2] = map[2][1]; // C

    // third path = G, I
    mapDijstrak[3][0] = map[5][3]; // " "
    mapDijstrak[3][6] = map[3][6]; // |
    mapDijstrak[4][0] = map[5][3]; // " "
    mapDijstrak[4][6] = map[4][6]; // |
    mapDijstrak[5][0] = map[5][3]; // " "
    mapDijstrak[5][6] = map[5][6]; // |
    mapDijstrak[6][6] = map[6][6]; // G
    mapDijstrak[7][0] = map[5][3]; // " "
    mapDijstrak[7][1] = map[5][3]; // " "
    mapDijstrak[7][3] = map[5][3];
    mapDijstrak[7][4] = map[5][3]; // " "
    mapDijstrak[7][5] = map[5][3]; // " "
    mapDijstrak[7][6] = map[7][6]; // |
    mapDijstrak[8][0] = map[5][3]; // " "
    mapDijstrak[8][1] = map[5][3]; // " "
    mapDijstrak[8][6] = map[8][6]; // +
    mapDijstrak[8][4] = map[8][4]; // -
    mapDijstrak[8][5] = map[8][5]; // -
    mapDijstrak[8][3] = map[8][3]; // I

    //fourth path = J
    mapDijstrak[6][5] = map[6][5]; // -
    mapDijstrak[6][4] = map[6][4]; // J

    cout << "Dijstrak Map" << endl;
    cout << "============" << endl;

    for(int i = 0; i < v; i++) {
        for(int j = 0; j < v; j++) {
            cout << mapDijstrak[i][j] << " ";
        }
        cout << endl;
    }
}

// A utility function to print the constructed distance array
void printSolution(int dist[], int n,
                   char parent[])
{

    fstream indataCoordinate;
    indataCoordinate.open("A2planets.txt");

    int lineno;
    string p_name;
    int x[100],y[100],z[100];
    int weight;
    int profit;

    bool printCoord = false;

    for (lineno = 2; getline(indataCoordinate,coordinateDataset[lineno])  && lineno < 14; lineno++) //starts counter from 1 in increment
    {
        istringstream ss(coordinateDataset[lineno]);

        ss >> p_name >> x[lineno] >> y[lineno] >> z[lineno] >> weight >> profit;

        if(y[lineno] != -1) {
            printCoord = true;
        }
    }

    cout << endl;
    cout <<"Index\tPlanet\tCoordinate (x,y,z)\tDistance from Planet A" << endl;
    cout <<"====\t======\t==================\t======================" << endl;

    if(printCoord) {

        for (int i = 0, c = 4; i < V, c < 14; i++, c++) {
            cout << i << "\t" << alphabet[i] << "\t"<< "(" << x[c] << "," << y[c] << "," << z[c] << ")"
                 <<"\t\t"<<dist[i]<< endl;
        }

    }

    int src = 0;

    cout <<"\n\nVertex\t\t\tDistance\tPath (index)";
    cout << "\n======\t\t\t=========\t==========";

    for (int i=0; i<V; i++) {
        printf("\n%c -> %c, (%d -> %d) \t %d\t\t%d ",
               alphabet[0], alphabet[i], src, i, dist[i], src);
        printPath(parent, i);
    }
}

// Function that implements Dijkstra's single source shortest path algorithm
// for a graph represented using adjacency matrix representation
void dijkstra(int graph[V][V], int src)
{
    int dist[V]; // The output array.  dist[i] will hold the shortest
    // distance from src to i

    // Parent array to store
    // shortest path tree
    char parent[V];

    bool sptSet[V]; // sptSet[i] will be true if vertex i is included in shortest
    // path tree or shortest distance from src to i is finalized

    // Initialize all distances as INFINITE and stpSet[] as false
    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
        parent[0] = -1;
        sptSet[i] = false;
    }

    // Distance of source vertex from itself is always 0
    dist[src] = 0;

    // Find shortest path for all vertices
    for (int count = 0; count < V - 1; count++) {
        // Pick the minimum distance vertex from the set of vertices not
        // yet processed. u is always equal to src in the first iteration.
        int u = minDistance(dist, sptSet);

        // Mark the picked vertex as processed
        sptSet[u] = true;

        // Update dist value of the adjacent vertices of the picked vertex.
        for (int v = 0; v < V; v++)

            // Update dist[v] only if is not in sptSet, there is an edge from
            // u to v, and total weight of path from src to  v through u is
            // smaller than current value of dist[v]
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX
                && dist[u] + graph[u][v] < dist[v])
            {
                parent[v] = u;
                dist[v] = dist[u] + graph[u][v];
            }

    }

    // print the constructed distance array
    printSolution(dist, V, parent);
}

// driver program to test above function
int main()
{
    fstream indataDistance, indataProfit;
    stringstream ss;

    int lineno;
    bool readDist = false;

    int* dist = new int [100];

    indataDistance.open("A2planets.txt");
    indataProfit.open("A2planets.txt");

    //cout << "The distances are : ";
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

        cout << "\tA\tB\tC\tD\tE\tF\tG\tH\tI\tJ" << endl;

        for(i = 0; i < v; i++) {

            cout << alphabet[i] << '\t';

            for(j = 0; j < v; j++) {
                cout << vertArr[i][j] << "\t";
            }
            cout << endl;
        }
        cout << endl;
    }

    /* Let us create the example graph discussed above */
    dijkstra(vertArr, 0);

    cout << endl << endl;
    printMap();

    indataDistance.close();

    return 0;
}