// VectorDataset.h
#include "DataVector.h"
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include <utility>
using namespace std;

class VectorDataset {
    vector<DataVector> dataset; // A vector to store the dataset

public:
    // Load data from a CSV file and add a custom vector to each data vector
    void loadFromCSV(const string &filename, const DataVector &customVector);

    // Load data from a CSV file
    void loadFromCSV(const string &filename);

    // Find the k nearest neighbors of a given vector in the dataset
    vector<DataVector> kNearestNeighbors(const DataVector &v, int k);

    // Add a data vector to the dataset
    void add(const DataVector &dv);

    // Get the size of the dataset
    int size() const { return dataset.size(); }

    // Get the dataset
    const vector<DataVector> &getDataset() const { return dataset; }
};