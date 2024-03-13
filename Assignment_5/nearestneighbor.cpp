
#include "VectorDataset.h"
#include <bits/stdc++.h>

using namespace std;
/**
 * @brief Function to find the k nearest neighbors
 * @param DataSet The dataset of vectors
 * @param test_vector The vector for which the neighbors are to be found
 * @param k The number of neighbors to be found
 * @return The dataset of k nearest neighbors
 */
VectorDataset knearestneighbor(VectorDataset &DataSet, DataVector &test_vector, int k)
{
    set<pair<double, int>> s; // creating a set to store the distances and the index of the vectors
    int n = DataSet.size();
    size_t set_size = s.size();
    pair<double, int> temp;
    for (int i = 0; i < n; i++)
    { // iterating through the vectors
        temp = {test_vector.squared_dist(DataSet.access_element(i)), i};
        s.insert(temp); // inserting the distance and the index into the set
        set_size++;
        if (set_size > k)
        {
            s.erase(*s.rbegin()); // erasing the last element if the size of the set exceeds k
            set_size--;
        }
    }
    VectorDataset answer(0);
    for (auto k : s)  
    {                                                            // iterating through the set
        answer.add_DataVector(DataSet.access_element(k.second)); // adding the k nearest neighbors to the answer dataset
        cout<<DataSet.access_element(k.second).dist(test_vector)<<'\n'; // printing the distance of the k nearest neighbors from the test vector
    }
    answer.print(); // printing the answer dataset
    return answer;  // returning the answer dataset
}

int main()
{
    VectorDataset v_train(0);
    v_train.ReadDataset("train.csv");
    // v2.print();
    VectorDataset v_test(0);
    v_test.ReadDataset("test.csv");
    // v1.print();
    cout << "Enter the value of k: " << '\n';
    int k;
    cin >> k;
    int &k_ref = k;
    auto start = chrono::high_resolution_clock::now();
    // for (int i = 0; i < 100; i++)
    // {
    //     cout << "This loop no :" << i + 1 << '\n';
    //     knearestneighbor(v_train, v_test.access_element(i), k);
    // }
    knearestneighbor(v_train, v_test.access_element(25), k);
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
    cout << "Time taken by function: "
         << duration.count() << " milliseconds" << endl;
    return 0;
}