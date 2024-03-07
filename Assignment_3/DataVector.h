// DataVector.h
#ifndef DATAVECTOR_H
#define DATAVECTOR_H

#include <vector>
#include <cmath>
#include <iostream>
using namespace std;

/**
 * @class DataVector
 * @brief A class that represents a vector of data.
 */
class DataVector
{
    vector<double> v; ///< The vector of data.
    string label; ///< The label of the data vector.

public:
    /**
     * @brief Construct a new Data Vector object with a specified dimension.
     * @param dimension The dimension of the data vector.
     */
    DataVector(int dimension = 0) : v(dimension, 0.0) {}

    /**
     * @brief Construct a new Data Vector object from a vector of values.
     * @param values The values to initialize the data vector with.
     */
    DataVector(const vector<double> &values) : v(values) {}

    /**
     * @brief Destroy the Data Vector object.
     */
    ~DataVector() {}

    /**
     * @brief Copy constructor for the Data Vector object.
     * @param other The other Data Vector object to copy from.
     */
    DataVector(const DataVector &other) : v(other.v) {}

    /**
     * @brief Assignment operator for the Data Vector object.
     * @param other The other Data Vector object to assign from.
     * @return A reference to the assigned Data Vector object.
     */
    DataVector &operator=(const DataVector &other)
    {
        v = other.v;
        return *this;
    }

    /**
     * @brief Set the dimension of the data vector.
     * @param dimension The dimension to set.
     */
    void setDimension(int dimension = 0) { v.resize(dimension, 0.0); }

    /**
     * @brief Get the dimension of the data vector.
     * @return The dimension of the data vector.
     */
    int getDimension() const { return v.size(); }

    /**
     * @brief Access an element of the data vector.
     * @param index The index of the element to access.
     * @return A reference to the element at the specified index.
     */
    double &operator[](int index) { return v[index]; }

    /**
     * @brief Access an element of the data vector.
     * @param index The index of the element to access.
     * @return A const reference to the element at the specified index.
     */
    const double &operator[](int index) const { return v[index]; }

    /**
     * @brief Add another Data Vector to this Data Vector.
     * @param other The other Data Vector to add.
     * @return The resulting Data Vector after addition.
     */
    DataVector operator+(const DataVector &other) const;

    /**
     * @brief Subtract another Data Vector from this Data Vector.
     * @param other The other Data Vector to subtract.
     * @return The resulting Data Vector after subtraction.
     */
    DataVector operator-(const DataVector &other) const;

    /**
     * @brief Compute the dot product of this Data Vector with another Data Vector.
     * @param other The other Data Vector to compute the dot product with.
     * @return The dot product of the two Data Vectors.
     */
    double operator*(const DataVector &other) const;

    /**
     * @brief Compute the norm of this Data Vector.
     * @return The norm of the Data Vector.
     */
    double norm() const { return sqrt(*this * *this); }

    /**
     * @brief Compute the distance between this Data Vector and another Data Vector.
     * @param other The other Data Vector to compute the distance with.
     * @return The distance between the two Data Vectors.
     */
    double dist(const DataVector &other) const ;

    /**
     * @brief Output the Data Vector to a stream.
     * @param os The output stream to write to.
     * @param v The Data Vector to write.
     * @return A reference to the output stream.
     */
    friend ostream &operator<<(ostream &os, const DataVector &v);

    /**
     * @brief Get the label of the Data Vector.
     * @return The label of the Data Vector.
     */
    string getLabel() const {
        return label;
    }

    /**
     * @brief Compare this Data Vector with another Data Vector.
     * @param rhs The other Data Vector to compare with.
     * @return True if this Data Vector is less than the other Data Vector, false otherwise.
     */
    bool operator<(const DataVector &rhs) const;

    /**
     * @brief Compare two Data Vectors.
     * @param lhs The first Data Vector to compare.
     * @param rhs The second Data Vector to compare.
     * @return True if the first Data Vector is less than the second Data Vector, false otherwise.
     */
    friend bool operator<(const DataVector &lhs, const DataVector &rhs);
};

#endif