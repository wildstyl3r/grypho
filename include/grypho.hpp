#ifndef GRYPHO_HPP
#define GRYPHO_HPP
//#include "matrix.hpp"
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <vector>
#include <string>
#include <set>
#include <map>

using std::map;
using std::vector;
using std::string;
using std::unordered_set;
using std::unordered_map;

using vertex = string;
using vertex_leg = long long;
using value = long long;
using edge = std::pair<vertex, vertex>;
using edge_leg = std::pair<vertex_leg, vertex_leg>;
using attributes = unordered_map<vertex, value>;
using permutation = vector<vertex>;
using neighbourhood = unordered_set<vertex>;
using adj_t = unordered_map<vertex, neighbourhood>;


class Graph
{
protected:
    bool _directed;
    adj_t _adjacency_vector;
    attributes _color;
    unordered_map<vertex, string> _label;
    //vector<string> _ID;
    map<edge, double> _weight;
    //Matrix<T> _distance_matrix;
public:
    static constexpr char format[] = "Graph format: (*.tgf *.cgf *.dot)";
    Graph(vector<edge>& edges, bool directed = false);
    Graph(adj_t adjv, bool directed = false);
    Graph(){};
    Graph(string filename); //.dot (using nodesoup's demo) and .tgf
    //Graph(Matrix<T> dm); //adjacency or distance matrix
    void save(string filename);
    
    //legacy
    bool has(edge_leg e) const;
    bool has(vertex_leg v) const;
    virtual string label(vertex_leg v) const;
    virtual value color(vertex_leg v) const;
    value set_color(vertex_leg v, value c);
    const neighbourhood& operator()(vertex_leg v) const;
    const neighbourhood& V(vertex_leg v) const;

    bool directed() const;
    bool has(edge e) const;
    bool has(const vertex& v) const;
    void remove_edge(edge e);
    void add_edge(edge e);
    void remove_vertex(vertex v);
    void add_vertex(neighbourhood adj);
    void add_vertex(vertex v, neighbourhood adj = {}, value c = 0, string label = "");
    value deg(const vertex& v) const;
    //attributes& degrees();
    virtual value color(const vertex& v) const;
    value set_color(const vertex& v, value c);
    vector<vertex> ids() const;
    virtual string label(const vertex& v) const;
    const unordered_map<vertex, string>& labels();
    virtual attributes& colors();
    virtual size_t count_colors() const;
    value max_degree() const;
    double weight(edge e) const;
    void set_weight(edge e, double v);
    //Graph permuteRandom(unsigned seed);
    //Graph permute(std::vector<T> permutation);
    const neighbourhood& operator()(const vertex& v) const;
    const neighbourhood& V(const vertex& v) const;
    const adj_t& V() const;
    Graph operator!() const;
    Graph N(const vertex& v) const;
    size_t size() const;
    //inline T distance(T v1, T v2) { return _distance_matrix[v1][v2]; };
    //inline std::vector<T>& operator[] (const size_t i) { return _distance_matrix[i]; };
    //Matrix<T> getAdjMatrix() { return _distance_matrix & 1; };
    //Matrix<T> getDistMatrix() { return _distance_matrix; };
};

#endif
