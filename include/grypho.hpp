#ifndef GRYPHO_HPP
#define GRYPHO_HPP
//#include "matrix.hpp"
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <vector>
#include <string>
#include <set>

using std::vector;
using std::string;
using std::unordered_set;

using vertex = long long;
using value = long long;
using edge = std::pair<vertex, vertex>;
using attributes = vector<value>;
using permutation = vector<vertex>;
using neighbourhood = unordered_set<vertex>;


class Graph
{
protected:
    bool _directed;
    vector<neighbourhood> _adjacency_vector;
    attributes _color;
    attributes _degree;
    vector<string> _label;
    vector<string> _ID;
    //Matrix<T> _distance_matrix;
public:
    Graph(vector<edge>& edges, bool directed = false, bool base1 = false);
    Graph(vector<neighbourhood> adjv, bool directed = false);
    Graph(){};
    Graph(string filename); //.dot (using nodesoup's demo) and .tgf
    //Graph(Matrix<T> dm); //adjacency or distance matrix
    void save(string filename);
    
    bool directed();
    bool has(edge e);
    bool has(vertex v);
    void remove_edge(edge e);
    void add_edge(edge e);
    //void remove_vertex(vertex v);
    void add_vertex(neighbourhood adj);
    //void swap_name(vertex v, vertex u);
    value deg(vertex v);
    attributes& degrees();
    virtual vertex color(vertex v);
    vertex set_color(vertex v, value c);
    string id(vertex v);
    const vector<string>& ids();
    virtual string label(vertex v);
    const vector<string>& labels();
    virtual attributes& colors();
    virtual size_t count_colors();
    value max_degree();
    //Graph permuteRandom(unsigned seed);
    //Graph permute(std::vector<T> permutation);
    neighbourhood& operator()(vertex v);
    const vector< neighbourhood >& V();
    //inline T distance(T v1, T v2) { return _distance_matrix[v1][v2]; };
    //inline std::vector<T>& operator[] (const size_t i) { return _distance_matrix[i]; };
    //Matrix<T> getAdjMatrix() { return _distance_matrix & 1; };
    //Matrix<T> getDistMatrix() { return _distance_matrix; };
};

#endif
