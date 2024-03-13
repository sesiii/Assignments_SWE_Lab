#ifndef MY_HEADER_FILE_H
#define MY_HEADER_FILE_H

/**
 * @file DataVector.h
 * @author kovvuru kasyap
 * @date 05-02-2024
 * @brief A class to represent a vector of data
*/


#include <bits/stdc++.h>
using namespace std;

/**
 * @class DataVector
 * @brief A class to represent a vector of data
 */
class DataVector
{   // private members
public:
    vector<double> v;

public:
    // public members
    /**
     * @brief Constructor for DataVector
     * @param dimension The dimension of the vector
    */ 
    DataVector(int dimension = 0);

    /**
      @brief Destructor for DataVector
    */ 
    ~DataVector();

    /**
      @brief Copy constructor for DataVector
      @param other The DataVector to be copied
    */
    DataVector(const DataVector &other);

    /**
      @brief Assignment operator for DataVector
      @param other The DataVector to be assigned
      @return The DataVector after assignment
    */
    DataVector &operator=(const DataVector &other);

    /**
      @brief fucntion to set the dimension of the vector
      @return The dimension of the vector
    */
    void setDimension(int dimension = 0);

    /**
      @brief function to add 2 DataVectors
      @param other The DataVector to be added
      @return The DataVector after addition
    */
    DataVector operator+(const DataVector &other);

    /**
      @brief function to subtract 2 DataVectors
      @param other The DataVector to be subtracted
      @return The DataVector after subtraction
    */
    DataVector operator-(const DataVector &other);

    /**
      @brief function to multiply 2 DataVectors
      @param other The DataVector to be multiplied
      @return The dot product of the 2 DataVectors
    */
    double operator*(const DataVector &other);

    /**
      @brief function for magnitude of the DataVector
      @return The magnitude of the DataVector
    */
    double norm();

    /**
      @brief function to calculate the distance between 2 DataVectors
      @param other The DataVector to calculate the distance from
      @return The distance between the 2 DataVectors
    */
    double dist(const DataVector &other);

    /**
      @brief function to calculate the squared distance between 2 DataVectors
      @param other The DataVector to calculate the squared distance from
      @return The squared distance between the 2 DataVectors
    */
    double squared_dist(DataVector &other);

    /**
      @brief function to input the DataVector from a string
      @param line The string to be input
      @return The DataVector after input
    */
    DataVector data_input(string line);

    /**
      @brief function to print the DataVector
    */
    void print();
};

#endif
