#ifndef DSI_H
#define DSI_H
#include <vector>
#include <iostream>
#include <string> 

using namespace std;

struct vertex;

struct adjVertex
{
    vertex * v;
    double weight;
};

struct vertex
{
    long double attitude; 
    long double ph; 
    int location[2]; 
    double strength; 
    vector <adjVertex> adj;
};

class Graph
{
    public:
        void addEdge(int loc1[2], int loc2[2], double num);
        void addVertex(int location[2]);
        void displayEdges();
        void reset(); 
        vertex * searchVertex(int loc[2]); 
        void displayAttitudes(); 
        void simulate(vertex * current, double constant); 
        void setAttitude(int loc[2], double strength); 
        void fullSimulate(double constant); 
        vector <vertex*> vertices;
        void setStrength(int location[2], double value); 
        void displayVerticesMatrix(int numRows, int numCols);
        void displayAttMatrix(int numRows, int numCols); 

    private:
        
};

#endif