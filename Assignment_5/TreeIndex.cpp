#include <bits/stdc++.h>
#include "VectorDataset.h"
#include "DataVector.h"
#include "DataVector.cpp"
// #include "Treeindex.h"

using namespace std;

int threshold = 500;
class TreeIndex
{
public:
    vector<DataVector> dataset;
    static TreeIndex *instance;

    TreeIndex()
    {
        if (!instance)
            instance = this;
    }

    ~TreeIndex() {}

public:
    static TreeIndex &GetInstance()
    {
        if (!instance)
            instance = new TreeIndex;
        return *instance;
    }

    void ReadData(vector<DataVector> &arr)
    {
        (*instance).dataset.clear();
        for (int i = 0; i < arr.size(); i++)
        {
            (*instance).dataset.push_back(arr[i]);
        }
    }
};
TreeIndex *TreeIndex::instance = nullptr;

class KDTreeIndex : public TreeIndex
{
public:
    struct Node
    {
        vector<DataVector> break_information;
        Node *left;
        Node *right;

        Node(vector<DataVector>::iterator begin, vector<DataVector>::iterator end) : break_information(begin, end), left(nullptr), right(nullptr) {}
    };

    Node *root = nullptr;

    static KDTreeIndex *instance;

    static KDTreeIndex &GetInstance()
    {
        if (!instance)
            instance = new KDTreeIndex;
        return *instance;
    }

    void ChooseSplitDimension(const vector<DataVector> &all_vectors, vector<DataVector>::iterator begin, vector<DataVector>::iterator end, int &split, double &median)
    {
        int dimension = all_vectors[0].v.size();
        double maxSpread = -1.0;

        for (int i = 0; i < dimension; ++i)
        {
            vector<double> i_dimen_values;
            for_each(begin, end, [&i_dimen_values, i](const DataVector &vec)
                     { i_dimen_values.push_back(vec.v[i]); });

            sort(i_dimen_values.begin(), i_dimen_values.end());
            double spread = i_dimen_values[i_dimen_values.size() - 1] - i_dimen_values[0];

            if (spread > maxSpread)
            {
                maxSpread = spread;
                split = i;
                median = i_dimen_values[(i_dimen_values.size() - 1) / 2];
            }
        }
    }

    Node *BuildKDTreeIndex(vector<DataVector> &data, vector<DataVector>::iterator begin, vector<DataVector>::iterator end)
    {
        if ((end - begin) <= threshold)
        {
            return new Node(begin, end);
        }

        int split_dimension;
        double median;
        ChooseSplitDimension(data, begin, end, split_dimension, median);
        int left_count = 0, right_count = 0;

        for_each(begin, end, [&split_dimension, &median, &left_count, &right_count](const DataVector &vec)
                 {
            if (vec.v[split_dimension] <= median) {
                left_count++;
            } else {
                right_count++;
            } });

        auto comparator = [split_dimension](const DataVector &a, const DataVector &b)
        {
            return a.v[split_dimension] < b.v[split_dimension];
        };

        sort(begin, end, comparator);

        vector<DataVector> node_info(1);
        node_info[0].setDimension(2);
        node_info[0].v[0] = split_dimension;
        node_info[0].v[1] = median;

        Node *currentNode = new Node(node_info.begin(), node_info.end());

        currentNode->left =BuildKDTreeIndex(data, begin, begin + left_count);
        currentNode->right = BuildKDTreeIndex(data, begin + left_count, end);

        return currentNode;
    }

    void ClearTreeIndex(Node *node)
    {
        if (node == nullptr)
            return;

        ClearTreeIndex(node->left);
        ClearTreeIndex(node->right);
        delete node;
    }

    void MakeKDTreeIndex(vector<DataVector> &data)
    {
        ClearTreeIndex(root);
        root = BuildKDTreeIndex(data, data.begin(), data.end());
    }

    double CalculateDistance(const DataVector &a, const DataVector &b)
    {
        double distance = 0.0;
        for (int i = 0; i < a.v.size(); ++i)
        {
            distance += pow(a.v[i] - b.v[i], 2);
        }
        return sqrt(distance);
    }

    struct CompareDist
    {
        bool operator()(pair<double, DataVector> const &p1, pair<double, DataVector> const &p2)
        {
            return p1.first < p2.first;
        }
    };

    void SearchLeafKNearest(Node *leafNode, const DataVector &target, int k, priority_queue<pair<double, DataVector>, vector<pair<double, DataVector>>, CompareDist> &q)
    {
        if (leafNode == nullptr)
            return;

        for (const DataVector &point : leafNode->break_information)
        {
            double distance = CalculateDistance(target, point);
            q.push(make_pair(distance, point));
            if (q.size() > k)
                q.pop();
        }
    }

    vector<DataVector> SearchKNearest(DataVector &test_vector, int k)
    {
        priority_queue<pair<double, DataVector>, vector<pair<double, DataVector>>, CompareDist> q;

        if (root == nullptr)
            return vector<DataVector>(0);

        Node *curr = root;

        while (curr->left != nullptr || curr->right != nullptr)
        {
            if (test_vector.v[curr->break_information[0].v[0]] > curr->break_information[0].v[1])
            {
                if (curr->right != nullptr)
                {
                    curr = curr->right;
                }
                else
                {
                    break;
                }
            }
            else
            {
                if (curr->left != nullptr)
                {
                    curr = curr->left;
                }
                else
                {
                    break;
                }
            }
        }

        SearchLeafKNearest(curr, test_vector, k, q);

        vector<DataVector> result;
        while (!q.empty())
        {
            result.push_back(q.top().second);
            q.pop();
        }
        reverse(result.begin(), result.end());
        return result;
    }
};
KDTreeIndex *KDTreeIndex::instance = nullptr;

class RDTreeIndex : public TreeIndex
{
public:
    struct Node
    {
        vector<DataVector> break_information;
        Node *left;
        Node *right;

        Node(vector<DataVector>::iterator begin, vector<DataVector>::iterator end) : break_information(begin, end), left(nullptr), right(nullptr) {}
    };

    Node *root = nullptr;

    static RDTreeIndex *instance;

    static RDTreeIndex &GetInstance()
    {
        if (!instance)
            instance = new RDTreeIndex;
        return *instance;
    }

    Node *BuildRDTreeIndex(vector<DataVector> &data, vector<DataVector>::iterator begin, vector<DataVector>::iterator end)
    {
        if ((end - begin) <= threshold)
        {
            return new Node(begin, end);
        }

        // Randomly select a dimension and median for split
        int split_dimension = rand() % data[0].v.size();
        double median = ((double)rand() / (RAND_MAX));

        auto comparator = [split_dimension](const DataVector &a, const DataVector &b)
        {
            return a.v[split_dimension] < b.v[split_dimension];
        };

        sort(begin, end, comparator);

        vector<DataVector> node_info(1);
        node_info[0].setDimension(2);
        node_info[0].v[0] = split_dimension;
        node_info[0].v[1] = median;

        Node *currentNode = new Node(node_info.begin(), node_info.end());

        int midPoint = (end - begin) / 2;
        currentNode->left = BuildRDTreeIndex(data, begin, begin + midPoint);
        currentNode->right = BuildRDTreeIndex(data, begin + midPoint, end);

        return currentNode;
    }

    void ClearTreeIndex(Node *node)
    {
        if (node == nullptr)
            return;

        ClearTreeIndex(node->left);
        ClearTreeIndex(node->right);
        delete node;
    }

    void MakeRDTreeIndex(vector<DataVector> &data)
    {
        ClearTreeIndex(root);
        root = BuildRDTreeIndex(data, data.begin(), data.end());
    }

    double CalculateDistance(const DataVector &a, const DataVector &b)
    {
        double sum = 0;
        for (int i = 0; i < a.v.size(); i++)
        {
            double diff = a.v[i] - b.v[i];
            sum += diff * diff;
        }
        return sqrt(sum);
    }

    void SearchLeafKNearest(Node *node, const DataVector &target, priority_queue<pair<double, Node *>> &knearest, int k)
    {
        if (node == nullptr)
            return;

        double distance = CalculateDistance(target, node->break_information[0]);
        knearest.push(make_pair(distance, node));

        if (knearest.size() > k)
            knearest.pop();

        int split_dimension = node->break_information[0].v[0];
        double median = node->break_information[0].v[1];

        if (target.v[split_dimension] < median)
        {
            SearchLeafKNearest(node->left, target, knearest, k);
            if (knearest.top().first > abs(median - target.v[split_dimension]))
                SearchLeafKNearest(node->right, target, knearest, k);
        }
        else
        {
            SearchLeafKNearest(node->right, target, knearest, k);
            if (knearest.top().first > abs(median - target.v[split_dimension]))
                SearchLeafKNearest(node->left, target, knearest, k);
        }
    }

    vector<DataVector> SearchKNearest(const DataVector &target, int k)
    {
        priority_queue<pair<double, Node *>> knearest;
        SearchLeafKNearest(root, target, knearest, k);

        vector<DataVector> result;
        while (!knearest.empty())
        {
            result.push_back(knearest.top().second->break_information[0]);
            knearest.pop();
        }
        return result;
    }
};
RDTreeIndex *RDTreeIndex::instance = nullptr;

VectorDataset input_dataset, result_dataset;
DataVector test_vector;

int main()
{
    input_dataset.ReadDataset("test.csv");
    TreeIndex a;
    a.ReadData(input_dataset.v);

    int TreeIndex_choice;
    cout << "1. KDTree\n";
    cout << "2. RDTree\n";
    cout << "Choose the type of Tree to use(1 for KDTree, 2 for RDTree): ";
    cin >> TreeIndex_choice;

    if (TreeIndex_choice == 1)
    {
        KDTreeIndex b;
        
        b.MakeKDTreeIndex(a.dataset);

        auto start_time = std::chrono::high_resolution_clock::now();
        vector<DataVector> ans = b.SearchKNearest(a.dataset[100], 10);
        auto end_time = std::chrono::high_resolution_clock::now();

        int index;
        while (true) {
            cout << "Enter the index of the target vector: ";
            cin >> index;

            if (index < 0 || index >= a.dataset.size()) {
                cout << "Invalid index. Please enter a number between 0 and " << a.dataset.size() - 1 << ".\n";
            } else {
                break; // Exit the loop if the index is valid
            }
        }

        cout << "The target vector is at index " << index << " in the dataset: \n\n\n\n\n\n\n" << '\n';
        for (double val : a.dataset[index].v)
        {
            cout << val << ' ';
        }
        cout << '\n';

        cout << "\n\n The 10 nearest neighbors along with their distances are:\n\n " << '\n';
        for (int i = 0; i < ans.size(); i++)
        {
            double distance = b.CalculateDistance(a.dataset[100], ans[i]);
            cout << "Neighbor " << i + 1 << ": ";
            for (int j = 0; j < ans[i].v.size(); j++)
            {
                cout << ans[i].v[j] << ' ';
            }
            cout << " Distance: " << distance << '\n';
        }

        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
        std::cout << "Time taken: " << duration.count() << " microseconds" << std::endl;
        return 0;
    }
    else if (TreeIndex_choice == 2)
    {
        RDTreeIndex b;
        b.MakeRDTreeIndex(a.dataset);

        auto start_time = std::chrono::high_resolution_clock::now();
        vector<DataVector> ans = b.SearchKNearest(a.dataset[100], 10);
        auto end_time = std::chrono::high_resolution_clock::now();

        int index;
        while (true) {
            cout << "Enter the index of the target vector: ";
            cin >> index;

            if (index < 0 || index >= a.dataset.size()) {
                cout << "Invalid index. Please enter a number between 0 and " << a.dataset.size() - 1 << ".\n";
            } else {
                break; // Exit the loop if the index is valid
            }
        }

        cout << "The target vector is at index " << index << " in the dataset: " << '\n';
        for (double val : a.dataset[index].v)
        {
            cout << val << ' ';
        }
        cout << '\n';

        cout << "\n\n The 10 nearest neighbors along with their distances are:\n\n " << '\n';
        for (int i = 0; i < ans.size(); i++)
        {
            double distance = b.CalculateDistance(a.dataset[100], ans[i]);
            cout << "Neighbor " << i + 1 << ": ";
            for (int j = 0; j < ans[i].v.size(); j++)
            {
                cout << ans[i].v[j] << ' ';
            }
            cout << " Distance: " << distance << '\n';
        }

        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
        std::cout << "Time taken: " << duration.count() << " microseconds" << std::endl;
        return 0;
    }
    else
    {
        cout << "Invalid choice. Please enter 1 for KDTree or 2 for RDTree.\n";
        return 1; 
    }

    return 0;
}