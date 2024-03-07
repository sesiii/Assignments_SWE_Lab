#include <fstream>
#include <sstream>
#include "DataVector.cpp"
#include <string>
#include <vector>
#include <queue>
#include <utility>
#include <omp.h>

/**
 * @class VectorDataset
 * @brief A class that represents a dataset of vectors.
 */
class VectorDataset
{
    std::vector<DataVector> dataset; ///< A vector to store the dataset

public:
    /**
     * @brief Load data from a CSV file and calculate the distance to a custom vector.
     * @param filename The name of the CSV file.
     * @param custom The custom vector.
     */
    void loadFromCSV(const std::string &filename, const DataVector &custom)
    {
        std::ifstream file(filename);
        std::string line;
        std::vector<std::vector<double>> all_values;
        while (std::getline(file, line))
        {
            std::istringstream ss(line);
            std::string value;
            std::vector<double> values;
            while (std::getline(ss, value, ','))
            {
                values.push_back(std::stod(value)); //
            }
            all_values.push_back(values);
        }

        #pragma omp parallel for
        for (int i = 0; i < all_values.size(); i++)
        {
            DataVector dv(all_values[i]);
            dataset.push_back(dv);
            double distance = dv.dist(custom);
        }
    }

    /**
     * @brief Overload the subscript operator to access elements in the dataset.
     * @param idx The index of the element.
     * @return A reference to the element at the specified index.
     */
    DataVector& operator[](std::size_t idx) {
        return dataset[idx];
    }

    /**
     * @brief Overload the subscript operator to access elements in the dataset (const version).
     * @param idx The index of the element.
     * @return A const reference to the element at the specified index.
     */
    const DataVector& operator[](std::size_t idx) const {
        return dataset[idx];
    }

    /**
     * @brief Load data from a CSV file.
     * @param filename The name of the CSV file.
     */
    void loadFromCSV(const std::string &filename)
    {
        std::ifstream file(filename);
        std::string line;
        std::vector<std::vector<double>> all_values;
        while (std::getline(file, line))
        {
            std::istringstream ss(line);
            std::string value;
            std::vector<double> values;
            while (std::getline(ss, value, ','))
            {
                values.push_back(std::stod(value));
            }
            all_values.push_back(values);
        }

        #pragma omp parallel for
        for (int i = 0; i < all_values.size(); i++)
        {
            DataVector dv(all_values[i]);
            dataset.push_back(dv);
        }
    }

    /**
     * @brief Get the dataset.
     * @return A const reference to the dataset.
     */
    const std::vector<DataVector> &getDataset() const
    {
        return dataset;
    }

    /**
     * @brief Add a data vector to the dataset.
     * @param dv The data vector to add.
     */
    void add_DataVector(const DataVector &dv)
    {
        dataset.push_back(dv);
    }

    /**
     * @brief Print the dataset.
     */
    void print()
    {
        for (int i = 0; i < dataset.size(); i++)
        {
            std::cout << dataset[i] << '\n';
        }
    }
};