#include "DSI.hpp"
#include <cmath>
#include <vector>
#include <queue>
#include <iostream>
#include <string> 

using namespace std;

void Graph::addEdge(int loc1[2], int loc2[2], double num)
{
    for (unsigned int i = 0; i < vertices.size(); i++)
    {
        if (vertices[i] -> location[0] == loc1[0] && vertices[i] -> location[1] == loc1[1])
        {
            for(unsigned int j = 0; j < vertices.size(); j++)
            {
                if (vertices[j] -> location[0] == loc2[0] && vertices[j] -> location[1] == loc2[1] && i != j)
                {
                    bool found = false; 
                    for (int k = 0; k < vertices[j] -> adj.size(); k++) //we do not want to duplicate edges 
                    {
                        if (vertices[j] -> adj[k].v -> location[0] == loc1[0] && vertices[j] -> adj[k].v -> location[1] == loc1[1])
                        {
                            found = true; 
                        }
                    }
                    if (found == false)
                    {
                        adjVertex av;
                        av.v = vertices[j];
                        av.weight = num;
                        vertices[i]->adj.push_back(av);
                        //another vertex for edge in other direction
                        adjVertex av2;
                        av2.v = vertices[i];
                        av2.weight = num;
                        vertices[j]->adj.push_back(av2);
                    }
                }
            }
        }
    }
}

void Graph::addVertex(int loc[2])
{
    bool found = false;
    for(unsigned int i = 0; i < vertices.size(); i++)
    {
        if (vertices[i] -> location[0] == loc[0] && vertices[i] -> location[1] == loc[1])
        {
            found = true;
            cout << "Vertex found. A copy will not be entered." << endl;
        }
    }
    if (found == false)
    {
        vertex * v = new vertex;
        v -> location[0] = loc[0];
        v -> location[1] = loc[1]; 
        v -> attitude = 0.0; 
        v -> strength = 1; 
        v -> ph = 0.0; 
        vertices.push_back(v);
    }
}

void Graph::displayEdges()
{
    //loop through all vertices and adjacent vertices
    for(int i = 0; i < vertices.size(); i++)
    {
        cout << vertices[i] -> location[0] << "," << vertices[i] -> location[1] <<":"<<endl;
        for(unsigned int j = 0; j < vertices[i]->adj.size(); j++)
        {
            cout << " --> " << vertices[i]->adj[j].v -> location[0] << "," << vertices[i]->adj[j].v -> location[1] << "; distance = " <<vertices[i]->adj[j].weight << endl;
        }
        cout<<endl;
    }
}

void Graph::reset()
{
    for (int i = 0; i < vertices.size(); i++)
    {
        vertices[i] -> attitude = 0.0; 
        vertices[i] -> ph = 0.0; 
    }
}

vertex * Graph::searchVertex(int loc[2])
{
    vertex *vStart = NULL;
    for(unsigned int i = 0; i < vertices.size(); i++)
    {
        if (vertices[i] -> location[0] == loc[0] && vertices[i] -> location[1] == loc[1])
        {
            vStart = vertices[i];
        }
    }
    return vStart;
}

void Graph::displayAttitudes()
{
    for (int i = 0; i < vertices.size(); i++)
    {
        cout << vertices[i] -> location[0] << " , " << vertices[i] -> location[1] << ", " << vertices[i] -> attitude << endl; 
    }
}

void Graph::simulate(vertex * current, double constant)
{
    long double delta = 0.0; 
    for(int i = 0; i < current->adj.size(); i++)
    {
        delta = ((current -> ph - current ->adj[i].v -> ph) * 1.0) / (current -> adj[i].weight * 1.0); //social impact = s/d; attitude strength of the other divided by the distance 
        delta = delta * current -> strength; 
        delta = delta / current -> adj[i].v -> strength; 
        current -> adj[i].v -> attitude = (current -> adj[i].v -> attitude + ((delta * 1.0) / (constant * 1.0 ))); 
    }
    return;
}

void Graph::setAttitude(int loc[2], double strength)
{
    for (int i = 0; i < vertices.size(); i++)
    {
        if (vertices[i] -> location[0] == loc[0] && vertices[i] -> location[1] == loc[1])
        {
            vertices[i] -> attitude = strength; 
            vertices[i] -> ph = strength; 
            return;
        }
    }
}

void Graph::fullSimulate(double constant)
{
    
    for (int i = 0; i < vertices.size(); i++)
    {
        simulate(vertices[i], constant); 
    }
    //reset ph to equal attitude 
    for (int i = 0; i < vertices.size(); i++)
    {
        vertices[i] -> ph = vertices[i] -> attitude; 
    }
    
}

void Graph::setStrength(int loc[2], double value)
{
    for (int i = 0; i < vertices.size(); i++)
    {
        if (vertices[i] -> location[0] == loc[0] && vertices[i] -> location[1] == loc[1])
        {
            vertices[i] -> strength = value;
            return; 
        }
    }
    cout << " Cannot set strength because the vertex was not found." << endl; 
}

void Graph::displayVerticesMatrix(int numRows, int numCols)
{
    if (numRows * numCols > vertices.size())
    {
        cout << "The number of rows and/ or columns is/ are too large. Stay within memory bounds, good sir." << endl;
        return;
    }
    if (numRows * numCols < vertices.size())
    {
        cout << "Warning: The number of rows and/ or columns is/ are too few. Not all elements will be presented." << endl; 
    }
    for (int r = 0; r < numRows; r++)
    {
        for (int c = 0; c < numCols; c++)
        {
            cout << vertices[r * numCols + c] -> location[0] << "," << vertices[r * numCols + c] -> location[1] << " | "; 
        }
        cout << endl; 
    }
}

void Graph::displayAttMatrix(int numRows, int numCols)
{
    for (int r = 0; r < numRows; r++)
    {
        for (int c = 0; c < numCols; c++)
        {
            cout << vertices[r * numCols + c] -> location[0] << "," << vertices[r * numCols + c] -> location[1] <<"; " << vertices[r * numCols + c] -> attitude; 
            cout << " | "; 
        }
        cout << endl; 
    }
}