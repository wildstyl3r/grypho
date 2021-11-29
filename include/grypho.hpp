#ifndef GRYPHO_HPP
#define GRYPHO_HPP
//#include "matrix.hpp"
#include "nodesoup.hpp"
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
using coord = nodesoup::Point2D;


class Graph
{
protected:
    vector<neighbourhood> _adjacency_vector;
    attributes _color;
    attributes _degree;
    vector<string> _label;
    vector<string> _ID;
    //Matrix<T> _distance_matrix;
public:
    Graph(edge* begin, edge* end, bool directed = false, bool base1 = false); //list of edges
    Graph(vector<neighbourhood> adjv);
    Graph(attributes degree);
    Graph(string filename); //.dot (using nodesoup's demo) and .tgf
    //Graph(Matrix<T> dm); //adjacency or distance matrix
    void save(string filename);
    
    bool has_edge(edge e);
    void remove_edge(edge e);
    void add_edge(edge e);
    //void remove_vertex(vertex v);
    void add_vertex(neighbourhood adj);
    //void swap_name(vertex v, vertex u);
    value deg(vertex v);
    attributes& degrees();
    vertex color(vertex v);
    vertex set_color(vertex v, value c);
    string id(vertex v);
    attributes& colors();
    size_t count_colors();
    value max_degree();
    //Graph permuteRandom(unsigned seed);
    //Graph permute(std::vector<T> permutation);
    inline neighbourhood& operator()(const vertex v);
    const vector< neighbourhood >& V();
    vector<coord> draw_coords_FR(unsigned width, unsigned height);
    //inline T distance(T v1, T v2) { return _distance_matrix[v1][v2]; };
    //inline std::vector<T>& operator[] (const size_t i) { return _distance_matrix[i]; };
    //Matrix<T> getAdjMatrix() { return _distance_matrix & 1; };
    //Matrix<T> getDistMatrix() { return _distance_matrix; };
};

#endif
