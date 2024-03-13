#include "VectorDataset.h"
#include "DataVector.h"
#include <bits/stdc++.h>
using namespace std;
VectorDataset::VectorDataset(int k)
{
    n = k;
    // cout<<"Constructor called\n";
    v.resize(n); // setting the size of the vector as n
    for (int i = 0; i < n; i++)
    {
        v[i].setDimension(784); // setting the dimension of each vector as 3
    }
}

VectorDataset::~VectorDataset()
{
    cout << "Destructor called\n";
    v.clear(); // clearing the vector
}

void VectorDataset::ReadDataset(const string filename)
{
    ifstream file(filename); // opening the file
    if (!file.is_open())
    {
        cout << "File not found\n";
        return;
    }
    string line; // string to store each line
    int i = 0;   // counter to keep track of the number of lines
    while (getline(file, line))
    {                          // reading each line
        v[i].data_input(line); // calling the data_input function to input the data
        i++;                   // incrementing the counter
    }
    file.close(); // closing the file
}

void VectorDataset::print()
{
    cout << v.size() << '\n';
    for (int i = 0; i < v.size(); i++)
    {
        v[i].print(); // printing the vector
    }
}

const vector<DataVector> &VectorDataset::values()
{
    return v;
}


void VectorDataset::add_DataVector(const DataVector &new_vector)
{
    v.push_back(new_vector);
}