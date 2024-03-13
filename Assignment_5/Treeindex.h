#ifndef TREEINDEX_H
#define TREEINDEX_H

#include <vector>
#include <queue>
#include <cmath>
#include <algorithm>

using namespace std;

class DataVector
{
public:
    vector<double> v;
    void setDimension(int dimension) { v.resize(dimension); }
};

class TreeIndex
{
public:
    vector<DataVector> dataset;
    static TreeIndex *instance;

    TreeIndex();
    ~TreeIndex();

    static TreeIndex &GetInstance();
    void ReadData(vector<DataVector> &arr);
};

struct CompareDist {
    bool operator()(const pair<double, DataVector>& a, const pair<double, DataVector>& b) {
        return a.first > b.first;
    }
};


class KDTreeIndex : public TreeIndex
{
public:
    struct Node;
    Node *root;
    static KDTreeIndex *instance;

    static KDTreeIndex &GetInstance();
    void ChooseSplitDimension(const vector<DataVector> &all_vectors, vector<DataVector>::iterator begin, vector<DataVector>::iterator end, int &split, double &median);
    Node *BuildKDTreeIndex(vector<DataVector> &data, vector<DataVector>::iterator begin, vector<DataVector>::iterator end);
    void ClearTreeIndex(Node *node);
    void MakeKDTreeIndex(vector<DataVector> &data);
    double CalculateDistance(const DataVector &a, const DataVector &b);
    void SearchLeafKNearest(Node *leafNode, const DataVector &target, int k, priority_queue<pair<double, DataVector>, vector<pair<double, DataVector>>, CompareDist> &q);
    vector<DataVector> SearchKNearest(DataVector &test_vector, int k);
};

class RDTreeIndex : public TreeIndex
{
public:
    struct Node;
    Node *root;
    static RDTreeIndex *instance;

    static RDTreeIndex &GetInstance();
    Node *BuildRDTreeIndex(vector<DataVector> &data, vector<DataVector>::iterator begin, vector<DataVector>::iterator end);
    void ClearTreeIndex(Node *node);
    void MakeRDTreeIndex(vector<DataVector> &data);
    double CalculateDistance(const DataVector &a, const DataVector &b);
    void SearchLeafKNearest(Node *node, const DataVector &target, priority_queue<pair<double, Node *>> &knearest, int k);
    vector<DataVector> SearchKNearest(const DataVector &target, int k);
};

#endif // TREEINDEX_H