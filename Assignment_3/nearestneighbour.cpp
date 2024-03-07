#include "VectorDataset.cpp"
#include <bits/stdc++.h>
#include <chrono>
#include <iostream>
#include <queue>
#include <vector>
#include <cmath>
#include <omp.h>
#include <fstream>

/**
 * @brief Find the k nearest neighbors of a test vector in a dataset.
 * @param DataSet The dataset.
 * @param test_vector The test vector.
 * @param k The number of neighbors to find.
 * @return A vector of pairs, where each pair contains a data vector and its distance to the test vector.
 */
vector<pair<DataVector, double>> knearestneighbor(VectorDataset &DataSet, DataVector &test_vector, int k)
{
    /// @brief The dataset.
    vector<DataVector> our_data = DataSet.getDataset();

    /// @brief The nearest neighbors and their indices.
    vector<pair<double, int>> nearest(k, {numeric_limits<double>::max(), -1});

    /// @brief Parallel loop to calculate distances.
    #pragma omp parallel for
    for (int i = 0; i < our_data.size(); i++)
    {
        /// @brief The distance between the test vector and the current data vector.
        double dist = test_vector.dist(our_data[i]);

        /// @brief Critical section to update the nearest neighbors.
        #pragma omp critical
        {
            for (int j = 0; j < k; j++)
            {
                if (dist < nearest[j].first)
                {
                    nearest.insert(nearest.begin() + j, {dist, i});
                    nearest.pop_back();
                    break;
                }
            }
        }
    }

    /// @brief The answer to return.
    vector<pair<DataVector, double>> answer;

    /// @brief Loop to create the answer vector.
    for (const auto &pair : nearest)
    {
        answer.push_back({our_data[pair.second], pair.first});
    }

    return answer;
}

/**
 * @brief The main function.
 * @return 0 on success.
 */
int main()
{
    /// @brief The training dataset.
    VectorDataset v2;

    /// @brief The start time.
    auto start = std::chrono::high_resolution_clock::now();

    /// @brief Load the training dataset from a CSV file.
    v2.loadFromCSV("train.csv");

    /// @brief The test dataset.
    VectorDataset v1;

    /// @brief Load the test dataset from a CSV file.
    v1.loadFromCSV("test.csv");

    /// @brief The number of nearest neighbors to find.
    int k;

    cout << "Enter the value of k: ";
    cin >> k;

    /// @brief The test vectors.
    vector<DataVector> testVectors = v1.getDataset();

    /// @brief The count of test vectors.
    int testVectorCount = 1;

    /// @brief Parallel loop to find the nearest neighbors for each test vector.
    #pragma omp parallel for
    for (int i = 0; i < testVectors.size(); i++)
    {
        /// @brief The nearest neighbors for the current test vector.
        vector<pair<DataVector, double>> nearestNeighbors = knearestneighbor(v2, testVectors[i], k);

        /// @brief Sort the neighbors in increasing order of distance.
        std::sort(nearestNeighbors.begin(), nearestNeighbors.end(), [](const auto &a, const auto &b)
                  { return a.second < b.second; });

        /// @brief Critical section to print the results.
        #pragma omp critical
        {
            cout << "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^"
                 << "\n\n";
            std::cout << "Test Vector " << testVectorCount << ":\n " << testVectors[i] << "\n";
            cout << "\n--\n"
                 << k << " Nearest Neighbors:";
            cout << " \n-----------------------------\n";

            /// @brief The count of neighbors.
            int neighborCount = 1;

            /// @brief Loop to print the neighbors.
            for (const auto &pair : nearestNeighbors)
            {
                std::cout << "Neighbor " << neighborCount << ": " << pair.first << "(Distance: " << sqrt(pair.second) << ")"
                          << "\n\n";
                neighborCount++;
            }
            std::cout << "\n";

            testVectorCount++;
        }
    }

    /// @brief The end time.
    auto end = std::chrono::high_resolution_clock::now();

    /// @brief The duration of the program.
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    std::cout << "Total time taken: " << duration.count()/1000 << "s\n";

    return 0;
}