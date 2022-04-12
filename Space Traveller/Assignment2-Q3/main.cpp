#include <iostream>
#include <string>
#include <vector>
#include <bits/stdc++.h>

using namespace std;
string* distanceDataset = new string[100];
int* dist = new int [100];

//////////////////////////////////////////////////////////////////////////////////////////////

typedef  pair<int, int> iPair;

struct Graph
{
    int V, E;
    vector< pair<int, iPair> > edges;

    // Constructor
    Graph(int V, int E)
    {
        this->V = V;
        this->E = E;
    }

    // Utility function to add an edge
    void addEdge(int u, int v, int w)
    {
        edges.push_back({w, {u, v}});
    }

    // Function to find MST using Kruskal's
    // MST algorithm
    int kruskalMST();
};

// To represent Disjoint Sets
struct DisjointSets
{
    int *parent, *rnk;
    int n;

    // Constructor.
    DisjointSets(int n)
    {
        // Allocate memory
        this->n = n;
        parent = new int[n+1];
        rnk = new int[n+1];

        // Initially, all vertices are in
        // different sets and have rank 0.
        for (int i = 0; i <= n; i++)
        {
            rnk[i] = 0;

            //every element is parent of itself
            parent[i] = i;
        }
    }

    // Find the parent of a node 'u'
    // Path Compression
    int find(int u)
    {
        /* Make the parent of the nodes in the path
           from u--> parent[u] point to parent[u] */
        if (u != parent[u])
            parent[u] = find(parent[u]);
        return parent[u];
    }

    // Union by rank
    void merge(int x, int y)
    {
        x = find(x), y = find(y);

        /* Make tree with smaller height
           a subtree of the other tree  */
        if (rnk[x] > rnk[y])
            parent[y] = x;
        else // If rnk[x] <= rnk[y]
            parent[x] = y;
        if (rnk[x] == rnk[y])
            rnk[y]++;
    }
};

int Graph::kruskalMST()
{
    int mst_wt = 0; // Initialize result

    // Sort edges in increasing order on basis of cost
    sort(edges.begin(), edges.end());

    // Create disjoint sets
    DisjointSets ds(V);

    // Iterate through all sorted edges
    vector< pair<int, iPair> >::iterator it;
    for (it=edges.begin(); it!=edges.end(); it++)
    {
        int u = it->second.first;
        int v = it->second.second;
        int set_u = ds.find(u);
        int set_v = ds.find(v);

        // Check if the selected edge is creating
        // a cycle or not (Cycle is created if u
        // and v belong to same set)
        if (set_u != set_v)
        {
            // Current edge will be in the MST
            // so print it
            cout << u << " -> " << v << " = " << mst_wt << " + " << it->first << endl;

            // Update MST weight
            mst_wt += it->first;

            // Merge two sets
            ds.merge(set_u, set_v);
        }
    }
    return mst_wt;
}

//////////////////////////////////////////////////////////////////////////////////////////////


int main() {

    fstream indataDistance, indataProfit;
    stringstream ss;
    int V = 10, E = 15;
    int PToNumU,PToNumV;
    Graph g(V, E);

    int lineno;
    indataDistance.open("A2planets.txt");

    cout << "Edges" << "\t\t\t" << "Distance" << endl;
    cout << "====================" << "\t" << "========" << endl;

    for (lineno = 0; getline(indataDistance, distanceDataset[lineno]) && lineno < 50; lineno++) //starts counter from 1 in increment
    {
        string toGo, goTo;
        string whitespace = " ";
        istringstream sb(distanceDataset[lineno]);

        sb >> toGo >> whitespace >> goTo >> whitespace >> dist[lineno];

        if(lineno >= 16) {

            //cout << dist[lineno] << " ";
            //cout << distanceDataset[lineno] << endl;

            cout << toGo << " to " << goTo << "  =  " << dist[lineno] << endl;

            if(toGo == "Planet_A"){
                PToNumU = 0;
            }
            else if(toGo == "Planet_B"){
                PToNumU = 1;
            }
            else if(toGo == "Planet_C"){
                PToNumU = 2;
            }
            else if(toGo == "Planet_D"){
                PToNumU = 3;
            }
            else if(toGo == "Planet_E"){
                PToNumU = 4;
            }
            else if(toGo == "Planet_F"){
                PToNumU = 5;
            }
            else if(toGo == "Planet_G"){
                PToNumU = 6;
            }
            else if(toGo == "Planet_H" ){
                PToNumU = 7;
            }
            else if(toGo == "Planet_I"){
                PToNumU = 8;
            }
            else if(toGo == "Planet_J"){
                PToNumU = 9;
            }


            if(goTo == "Planet_A"){
                PToNumV = 0;
            }
            else if(goTo == "Planet_B"){
                PToNumV = 1;
            }
            else if(goTo == "Planet_C"){
                PToNumV = 2;
            }
            else if(goTo == "Planet_D"){
                PToNumV = 3;
            }
            else if(goTo == "Planet_E"){
                PToNumV = 4;
            }
            else if(goTo == "Planet_F"){
                PToNumV = 5;
            }
            else if(goTo == "Planet_G"){
                PToNumV = 6;
            }
            else if(goTo == "Planet_H"){
                PToNumV = 7;
            }
            else if(goTo == "Planet_I"){
                PToNumV = 8;
            }
            else if(goTo == "Planet_J"){
                PToNumV = 9;
            }

            //Let us create above shown weighted and undirected graph
            // A0 B1 C2 D3 E4 F5 G6 H7 I8 J9
            //  making above shown graph
            g.addEdge(PToNumU, PToNumV, dist[lineno]);
        }
    }

    cout << "\nA(0),B(1),C(2),D(3),E(4),F(5),G(6),H(7),I(8),J(9)\n";
    cout << "\nEdges of MST are \n";

    int mst_wt = g.kruskalMST();

    cout << "\nWeight of MST is " << mst_wt;
    cout << endl << endl;

    cout << "====Kruskal Map====" << endl;
    cout << "         A    " << endl;
    cout << "          \\  " << endl;
    cout << "     C      B+" << endl;
    cout << "       \\   / |" << endl;
    cout << "        E-F  |" << endl;
    cout << "        |    |" << endl;
    cout << "      D-H  J-G" << endl;
    cout << "           |  " << endl;
    cout << "          I-  " << endl;

    indataProfit.close();
    indataDistance.close();
    return 0;
}
