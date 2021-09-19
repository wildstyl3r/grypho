#include "matrix.hpp"
#include <set>
#include <functional>

template <typename T> class Graph
{
    Matrix<T> _distance_matrix;
    vector< pair<T, T> > _edge_vector;
    vector< set<T> > _adjacency_vector;
public:
    Graph();
    Graph(pair<T, T>* begin, pair<T, T>* end, bool directed = false);
    Graph(Matrix<T>);
    Graph(vector<set<T>>);

    inline Matrix<T> getAdjacencyMatrix() {return _distance_matrix & 1};
    bool hasEdge(T v1, T v2);
    void removeEdge(T v1, T v2);
    void addEdge(T v1, T v2);
    void swapName(T v1, T v2);
};
