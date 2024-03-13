#include <bits/stdc++.h>
#include "DataVector.h"
using namespace std;

DataVector::DataVector(int dimension)
{
    // cout<<" datavector Constructor called\n";
    v.resize(dimension); // setting the size as dimension
}

DataVector::~DataVector()
{
    v.clear(); // clearing the vector
}

DataVector::DataVector(const DataVector &other)
{
    v = other.v; // copying the vector using copy constructor
}

DataVector &DataVector::operator=(const DataVector &other)
{
    v = other.v;  // copying the vector using assignment operator
    return *this; // returing this pointer
}

void DataVector::setDimension(int dimension)
{
    v.resize(dimension); // resetting the size of the vector
}

DataVector DataVector::operator+(const DataVector &other)
{
    DataVector final_vector(v.size()); // creating a new vector of same size
    for (int i = 0; i < v.size(); i++)
    {
        // adding the corresponding dimensions of the two vectors
        final_vector.v[i] = v[i] + other.v[i];
    }
    return final_vector; // returning the final vector
}

DataVector DataVector::operator-(const DataVector &other)
{
    DataVector final_vector(v.size()); // creating a new vector of same size
    for (int i = 0; i < v.size(); i++)
    {
        // subtracting the corresponding dimensions of the two vectors
        final_vector.v[i] = v[i] - other.v[i];
    }
    return final_vector; // returning the final vector
}

double DataVector::operator*(const DataVector &other)
{
    double dot_product = 0; // initializing the dot product as 0
    for (int i = 0; i < v.size(); i++)
    {
        // multiplying the corresponding dimensions of the two vectors and adding them
        dot_product += v[i] * other.v[i];
    }
    return dot_product; // returning the dot product
}

double DataVector::norm()
{
    return sqrt((*this) * (*this)); // returning the square root of the dot product of the vector with itself
}

double DataVector::dist(const DataVector &other)
{
    return sqrt(((*this) - other) * ((*this) - other)); // returning the distance between the two vectors
}

double DataVector::squared_dist(DataVector &other)
{
    return norm() + (other * other) - 2 * (*this * other); // returning the distance between the two vectors
}

DataVector DataVector::data_input(string line)
{
    //setDimension(784);     // creating a new vector of size 784
    stringstream ss(line); // creating a stringstream object
    string word;           // creating a string to store the words
    while (getline(ss, word, ','))
    {                      // reading the words from the stringstream object
        v.push_back(stod(word)); // converting the string to double and storing it in the vector
    }
    return *this; // returning the final vector
}

void DataVector::print()
{
    for (int i = 0; i < v.size(); i++)
    {
        cout << v[i] << " "; // printing the elements of the vector
    }
    cout << "completed"
         << "\n";
}