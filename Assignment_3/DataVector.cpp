#include "DataVector.h"
#include <algorithm> // for std::transform
#include <numeric> // for std::inner_product
using namespace std;

// Overload the addition operator to add two DataVectors element-wise
DataVector DataVector::operator+(const DataVector &other) const {
    vector<double> result(v.size());
    transform(v.begin(), v.end(), other.v.begin(), result.begin(), plus<double>());
    return DataVector(result);
}

// Overload the subtraction operator to subtract two DataVectors element-wise
DataVector DataVector::operator-(const DataVector& other) const {
    if (v.size() != other.v.size()) {
        throw std::invalid_argument("Vectors must be the same size to subtract.");
    }

    vector<double> result(v.size());
    transform(v.begin(), v.end(), other.v.begin(), result.begin(), minus<double>());
    return DataVector(result);
}

// Calculate the Manhattan distance between two DataVectors
double DataVector::dist(const DataVector &other) const {
    double sum = 0.0;
    for (size_t i = 0; i < v.size(); i++)
    {
        sum += abs(v[i] - other.v[i]);
    }
    return sum;
}

// Overload the multiplication operator to calculate the dot product of two DataVectors
double DataVector::operator*(const DataVector &other) const {
    return inner_product(v.begin(), v.end(), other.v.begin(), 0.0);
}

// Overload the stream insertion operator to print a DataVector
ostream &operator<<(ostream &os, const DataVector &dv) {
    for (int i = 0; i < dv.getDimension(); i++) {
        os << dv[i] << " ";
    }
    return os;
}

// Overload the less than operator to compare two DataVectors based on their norms
bool DataVector::operator<(const DataVector &rhs) const {
    return norm() < rhs.norm();
}