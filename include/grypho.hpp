//#include "matrix.hpp"
#ifndef GRYPHO_HPP
#define GRYPHO_HPP
#include "nodesoup.hpp"
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <cassert>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
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
    vector<neighbourhood> _adjacency_vector;
    attributes _color;
    attributes _degree;
    vector<string> _label;
    vector<string> _ID;
    //Matrix<T> _distance_matrix;
public:
    Graph(edge* begin, edge* end, bool directed = false, bool base1 = false); //list of edges
    Graph(vector<neighbourhood> adjv) : _adjacency_vector(adjv), _color(adjv.size(), 0), _degree(adjv.size(), 0), _label(adjv.size())
	{
	    for(size_t i = 0; i < _adjacency_vector.size(); ++i){
		_degree[i] = adjv[i].size();
	    }
	}
    Graph(attributes degree) : _color(degree.size(), 0), _degree(degree), _label(degree.size()) //partial initialization
	{
	    _adjacency_vector.resize(degree.size());
	}
    Graph(string filename); //.dot (using nodesoup's demo) and .tgf
    //Graph(Matrix<T> dm); //adjacency or distance matrix
    void save(string filename);
    
    bool has_edge(vertex v, vertex u) { return _adjacency_vector[v].count(u); };
    void remove_edge(vertex v, vertex u);
    void add_edge(vertex v, vertex u);
    void remove_vertex(vertex v);
    void add_vertex(neighbourhood adj);
    void swap_name(vertex v, vertex u);
    value deg(vertex v) 
	{
	    return _degree[v];
	}
    attributes& deg()
	{
	    return _degree;
	}
    vertex color(vertex v)
	{
	    return _color[v];
	}
    vertex set_color(vertex v, value c)
	{
	    return _color[v] = c;
	}
    string id(vertex v)
	{
	    if (_ID.size() > v){
		return _ID[v];
	    } else {
		return std::to_string(v+1);
	    }
	}
    attributes& colors()
	{
	    return _color;
	}
    value count_colors()
	{
	    return *std::max_element(_color.begin(), _color.end());
	}
    vertex max_degree();
    //Graph permuteRandom(unsigned seed);
    //Graph permute(std::vector<T> permutation);
    inline neighbourhood& operator()(const vertex v) { return _adjacency_vector[v]; };
    const vector< neighbourhood >& V() { return _adjacency_vector; };
    vector<nodesoup::Point2D> draw_coords_FR(unsigned width, unsigned height);
    //inline T distance(T v1, T v2) { return _distance_matrix[v1][v2]; };
    //inline std::vector<T>& operator[] (const size_t i) { return _distance_matrix[i]; };
    //Matrix<T> getAdjMatrix() { return _distance_matrix & 1; };
    //Matrix<T> getDistMatrix() { return _distance_matrix; };
};

#endif
