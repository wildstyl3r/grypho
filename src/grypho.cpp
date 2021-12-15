#include "grypho.hpp"

Graph::Graph(vector<neighbourhood> adjv, bool directed) :
    _directed(directed),
    _adjacency_vector(adjv),
    _color(adjv.size(), 0),
    _label(adjv.size())
    {}


bool Graph::has(edge e) const
{
  return _adjacency_vector[e.first].count(e.second);
}


void Graph::remove_edge(edge e)
{
  _adjacency_vector[e.first].erase(e.second);
  _adjacency_vector[e.second].erase(e.first);
}


void Graph::add_edge(edge e)
{
  _adjacency_vector[e.first].insert(e.second);
  _adjacency_vector[e.second].insert(e.first);
}


void Graph::add_vertex(neighbourhood adj)
{
  vertex v = size();
  _adjacency_vector.push_back(adj);
  if(!_directed){
      for(vertex u : adj){
          _adjacency_vector[u].insert(v);
      }
  }
  _color.push_back(0);
  _label.push_back("");
}


value Graph::deg(vertex v) const { return _adjacency_vector[v].size(); }

//attributes& Graph::degrees() { return _degree; }

vertex Graph::color(vertex v) const { return _color[v]; }

vertex Graph::set_color(vertex v, value c) { return _color[v] = c; }

string Graph::id(vertex v) const
    {
        if (_ID.size() > v){
            return _ID[v];
        } else {
            return std::to_string(v+1);
        }
    }


attributes& Graph::colors() { return _color; }

size_t Graph::count_colors() const
{
  unordered_set<value> colors;
  for(auto color :_color){
      colors.insert(color);
    }
  return colors.size();
}

value Graph::max_degree()  const{
    value res = 0;
    for(auto& n : _adjacency_vector){
        res = std::max(res, (value)n.size());
    }
    return res;
}

//Graph permuteRandom(unsigned seed);
//Graph permute(std::vector<T> permutation);
neighbourhood& Graph::operator()(vertex v) { return _adjacency_vector[v]; };

const vector< neighbourhood >& Graph::V() { return _adjacency_vector; };

//inline T distance(T v1, T v2) { return _distance_matrix[v1][v2]; };
//inline std::vector<T>& operator[] (const size_t i) { return _distance_matrix[i]; };
//Matrix<T> getAdjMatrix() { return _distance_matrix & 1; };
//Matrix<T> getDistMatrix() { return _distance_matrix; };

Graph::Graph(vector<edge>& edges, bool directed, bool base1) : _directed(directed)
{
    vertex size = 0;
    for(auto edge : edges){
        size = std::max(size, edge.first);
        size = std::max(size, edge.second);
    }
    size++;
    resize(size);
    for(auto it = edges.begin(); it != edges.end(); ++it){
        vertex v = it->first - base1, u = it->second - base1;

        _adjacency_vector[v].insert(u);
        if (!directed) {
            _adjacency_vector[u].insert(v);
        }

        vertex vmax = std::max(v, u);
        if (vmax+1 > size) {
            size = vmax+1;
        }
    }

    //_distance_matrix.resize(size);
}


string Graph::label(vertex v) const
{
    return _label[v];
}

const vector<string>& Graph::labels()
{
    return _label;
}

const vector<string>& Graph::ids()
{
    return _ID;
}

bool Graph::directed() const
{
    return _directed;
}

bool Graph::has(vertex v) const
{
    return 0 <= v && v < size();
}

neighbourhood& Graph::V(vertex v) { return _adjacency_vector[v]; };

void Graph::resize(size_t size){
    _adjacency_vector.resize(size);
    _ID.resize(size);
    _color.resize(size, 0);
    _label.resize(size);
}

size_t Graph::size() const{
    return _adjacency_vector.size();
}

Graph Graph::operator!() const
{
    Graph res;
    res.resize(size());
    for(vertex v = 0; v < size(); ++v)
        for(vertex u = 0; u < size(); ++u){
            if(_adjacency_vector[v].count(u) == 0){
                res._adjacency_vector[v].insert(u);
            }
        }
    for(vertex v = 0; v < size(); ++v){
        res._color[v] = _color[v];
        res._ID[v]    = _ID[v];
        res._label[v] = _label[v];
    }
}
