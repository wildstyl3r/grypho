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
    //bool _directed;
    size_t _edges;
    adj_t _adjacency_vector;
    attributes _color;
    unordered_map<vertex, string> _label;
    //vector<string> _ID;
    map<edge, double> _weight;
    //Matrix<T> _distance_matrix;
public:
    static const string fileFormat;
    static const value defaultColor;
    static const string defaultLabel;
    Graph(vector<edge>& edges, bool directed = false);
    Graph(adj_t adjv, bool directed = false);
    Graph():_edges(0){};
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
    const neighbourhood& add_vertex(neighbourhood adj);
    const neighbourhood& add_vertex(vertex v, neighbourhood adj = {}, value c = defaultColor, string label = defaultLabel);
    value deg(const vertex& v) const;
    virtual value color(const vertex& v) const;
    value set_color(const vertex& v, value c);
    const string& set_label(const vertex& v, const string l);
    vector<vertex> ids() const;
    virtual const string& label(const vertex& v) const;
    const unordered_map<vertex, string>& labels() const;
    virtual const attributes& colors() const;
    virtual size_t count_colors() const;
    value max_degree() const;
    double weight(edge e) const;
    void set_weight(edge e, double v);
    const neighbourhood& operator()(const vertex& v) const;
    const neighbourhood& V(const vertex& v) const;
    const adj_t& V() const;
    Graph operator!() const;
    Graph N(const vertex& v) const;
    size_t size() const;
    Graph S(const unordered_set<vertex>& target) const;
    size_t edges() const;
    double density() const;
    //inline T distance(T v1, T v2) { return _distance_matrix[v1][v2]; };
    //inline std::vector<T>& operator[] (const size_t i) { return _distance_matrix[i]; };
    //Matrix<T> getAdjMatrix() { return _distance_matrix & 1; };
    //Matrix<T> getDistMatrix() { return _distance_matrix; };
private:
    void recount_edges();
};

#endif
