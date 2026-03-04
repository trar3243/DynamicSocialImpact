#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath> 
#include <fstream>
#include "DSI.hpp"

using namespace std; 

long double calcVar(Graph g)
{
    //first, average 
    long double average = 0; 
    long double sum = 0; 
    long double n = g.vertices.size(); 
    long double sigma = 0; 
    long double var = 0; 
    for (int i = 0; i < g.vertices.size(); i++)
    {
        sum = sum + g.vertices[i] -> attitude; 
    }
    average = sum / n; 
    
    for (int i = 0; i < g.vertices.size(); i++)
    {
        sigma = sigma + pow(g.vertices[i] -> attitude - average, 2);  
    }
    var = sigma / (n - 1); 
    //cout << "Variance = " << var << endl;
    return var; 
}

void exportVar(long double varArr[], int size)
{
    ofstream out_file; 
    out_file.open("variance.csv"); 
    if(out_file.fail()) // if there was a failure in opening the output file 
    {
        cout << "failed to open the output file "<< endl;
        return; 
    }
    out_file << "Iteration" << ',' << "Variance" << endl; // titles 
    for (int i = 0; i < size; i++)
    {
        out_file << i << ',' << varArr[i] << "\n"; 
    } 
}

void addVertices(Graph & g, int numCols, int numRows)
{
    for (int i = 0; i < numRows; i++)
    {
        for (int j = 0; j < numCols; j++)
        {
            int newLoc[2] = {i,j}; 
            g.addVertex(newLoc); 
        }
    }
}

void addEdges(Graph & g)
{
    double distance = 0; 
    double rowDiff = 0; 
    double colDiff = 0; 
    for (int i = 0; i < g.vertices.size(); i++)
    {
        for (int j = 0; j < g.vertices.size(); j++)
        {
            if (j != i)
            {
                rowDiff = abs(g.vertices[i] -> location[0] - g.vertices[j] -> location[0]);
                colDiff = abs(g.vertices[i] -> location[1] - g.vertices[j] -> location[1]); 
                distance = sqrt(pow(rowDiff,2) + pow(colDiff,2));
                g.addEdge(g.vertices[i] -> location, g.vertices[j] -> location, distance);
            }
        }
    }
}

double displaySumAtt(Graph g)
{
    double sum = 0; 
    for (int i = 0; i < g.vertices.size(); i++)
    {
        sum = sum + g.vertices[i] -> attitude; 
    }
    cout << "Sum = " << sum << endl;
    return sum; 
}

void displayCatAttMatrix(Graph g, int numCols, int numRows, long double strengthVal, bool varStrength, double initialAvg)
{
    long double average = 0.0; 
    long double sum = 0.0; 
    double numElem = g.vertices.size(); 
    for (int i = 0; i < g.vertices.size(); i++)
    {
        sum = sum + g.vertices[i] -> attitude; 
    }

    average = (sum * 1.0) / (numElem * 1.0); 
    cout << "Average = " << average << endl;
    int i = 0; 
    int y = 0; 
    int k = 0; 
    for (int r = 0; r < numRows; r++)
    {
        for (int c = 0; c < numCols; c++)
        {
            if (g.vertices[r * numCols + c] -> attitude > initialAvg)
            {
                cout << " X ";
                i++; 
            }
            else
            {
                cout << " - ";
            }
            if (g.vertices[r * numCols + c] -> attitude > average && g.vertices[r * numCols + c] -> strength == strengthVal)
            {
                y++;
            }
            if (g.vertices[r * numCols + c] -> attitude <= average && g.vertices[r * numCols + c] -> strength == strengthVal)
            {
                k++; 
            }
        }
        cout << endl; 
    }
    cout << "Number of X's = " << i << endl;
    cout << "Number of dashes = " << numCols * numRows - i << endl;
    if (varStrength)
    {
        cout << "Number of high strength X's = " << y << endl;
        cout << "Number of low strength X's = " << i-y << endl;
        cout << "Number of high strength dashes = " << k << endl;
        cout << "Number of low strength dashes = " << (numCols * numRows - i) - k << endl;
    }
}

void resetAtt(Graph & g, double baseStrength)
{
    for (int i = 0; i < g.vertices.size(); i++)
    {
        g.vertices[i] -> attitude = baseStrength; 
    }
}

void randomAssigAtt(Graph & g, double strength)
{
    int random = 0; 
    for (int i = 0; i < g.vertices.size(); i++)
    {
        random = rand() % 2; 
        if (random == 1)
        {
            g.vertices[i] -> attitude = strength; 
            g.vertices[i] -> ph = strength;
        }
    }
}

void randomAssignStrength(Graph & g, double value)
{
    int random = 0; 
    for (int i = 0; i < g.vertices.size(); i++)
    {
        random = rand() % 7; 
        if (random == 0)
        {
            g.vertices[i] -> strength = value; 
        }
    }
}

double calcAverage(Graph g)
{
    double sum = 0; 
    for (int i = 0; i < g.vertices.size(); i++)
    {
        sum = sum + g.vertices[i] -> attitude; 
    }
    double average = (sum * 1.0) / (g.vertices.size() * 1.0);
    return average; 
}

void simulate(Graph & g, int iterations, int factor, double constant, int numCols, int numRows, double strengthVal, bool varStrength, long double varArr[])
{
    varArr[0] = calcVar(g); 
    if (varStrength)
    {
        for (int i = 0; i < iterations; i++)
        {
            g.fullSimulate(constant);
            varArr[i + 1] = calcVar(g); 
            if ((i + 1) % factor == 0)
            {
                cout << "Iteration " << i + 1 << endl; 
                displayCatAttMatrix(g, numCols, numRows, strengthVal, varStrength, calcAverage(g)); 
                displaySumAtt(g);
                cout << endl << endl;
            }
        }
    }
    else
    {
        cout << endl;
        double initialAvg = calcAverage(g);
        for (int i = 0; i < iterations; i++)
        {
            g.fullSimulate(constant);
            varArr[i + 1] = calcVar(g); 
            if ((i + 1) % factor == 0)
            {
                cout << "Iteration " << i + 1 << endl; 
                displayCatAttMatrix(g, numCols, numRows, strengthVal, varStrength, initialAvg); 
                displaySumAtt(g);
                varArr[i + 1] = calcVar(g); 
                cout << endl << endl;
            }
        }
    }
    
}

int main()
{
    int numRows = 50;
    int numCols = 50; 

    Graph g; 

    addVertices(g, numRows, numCols); 
    g.displayVerticesMatrix(numRows, numCols);
    addEdges(g); 
    randomAssigAtt(g, 10);
    
    cout << "Before any simulation (iterations = 0)" << endl;
    displayCatAttMatrix(g, numCols, numRows, 10, false, calcAverage(g));
    displaySumAtt(g);
    calcVar(g); 
    cout << endl;

    //simulate(Graph & g, int iterations, int factor, double constant, int numCols, int numRows, double strengthVal, bool varStrength)
    int iterations = 50;
    long double varArr[iterations]; 
    int factor = 25; 
    double constant = 25; 
    double strengthVal = 50; 
    bool varStrength = 0; 
    simulate(g, iterations, factor, constant, numCols, numRows, strengthVal, varStrength, varArr);

    for (int i = 0; i < iterations + 1; i++)
    {
        cout << varArr[i] << endl;
    }
    exportVar(varArr, iterations + 1);
    

    return 0; 
}