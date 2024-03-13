/**
 * @file VectorDataset.h
 * @author kovvuru kasyap
 * @date 05-02-2024
 * @brief A class to represent a dataset of vectors
 */

#include "DataVector.h"

/**
 * @class VectorDataset
 * @brief A class to represent a dataset of vectors
 */
class VectorDataset
{ // private members
    public:
    int n;
    vector<DataVector> v;

public:
    // public members
    /**
     * @brief Constructor for VectorDataset
     * @param k The number of vectors in the dataset
     */
    VectorDataset(int k=0)
    {
        n = k;
        // cout<<"Constructor called\n";
        v.resize(n); // setting the size of the vector as n
    }

    /**
      @brief Destructor for VectorDataset
    */
    ~VectorDataset()
    {
        // cout << "Destructor called\n";
        v.clear(); // clearing the vector
    }

    /**
      @brief to read data from a csv file
      @param other the csv file to be read
    */
    void ReadDataset(string filename)
    {
        ifstream file(filename); // opening the file
        if (!file.is_open())
        {
            cout << "File not found\n";
            return;
        }
        string line; // string to store each line
        while (getline(file, line))
        {      
            DataVector temp;
            temp.data_input(line);                    // reading each line
            v.push_back(temp); // calling the data_input function to input the data
        }
        file.close(); // closing the file
    }

    /**
      @brief to print the dataset
    */
    void print()
    {
        cout << v.size() << '\n';
        for (int i = 0; i < v.size(); i++)
        {
            v[i].print(); // printing the vector
        }
    }
    
    /**
      @brief to add a new vector to the dataset
      @param new_vector The new vector to be added
    */
    void add_DataVector(const DataVector &new_vector)
    {
        v.push_back(new_vector);
    }

    /**
     * @brief to access the ith vector
     * @param i the index of the DtaVector
     * @return the ith DataVector
     */
    DataVector &access_element(int i)
    {
        return v[i];
    }
    
    /**
     * @brief to return the size of the dataset
     * @return the size of the dataset
     */
    int size()
    {
        return v.size();
    }
};