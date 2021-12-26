#include "grypho.hpp"

Graph::Graph(adj_t adjv, bool directed) :
    _directed(directed),
    _adjacency_vector(adjv)
{}


bool Graph::has(edge e) const
{
  return _adjacency_vector.at(e.first).count(e.second);
}


void Graph::remove_edge(edge e)
{
  _adjacency_vector[e.first].erase(e.second);
  _adjacency_vector[e.second].erase(e.first);
  _weight.erase(e);
}


void Graph::add_edge(edge e)
{
  _adjacency_vector[e.first].insert(e.second);
  _adjacency_vector[e.second].insert(e.first);
}


void Graph::add_vertex(neighbourhood adj)
{
  vertex v = std::to_string(size());
  add_vertex(v, adj);
}

void Graph::add_vertex(vertex v, neighbourhood adj, value c, string label)
{
    _adjacency_vector[v] = adj;
    if(!_directed){
        for(const vertex& u : adj){
            _adjacency_vector[u].insert(v);
        }
    }
    _color[v] = c;
    _label[v] = label;
}


value Graph::deg(const vertex& v) const { return _adjacency_vector.at(v).size(); }

//attributes& Graph::degrees() { return _degree; }

value Graph::color(const vertex& v) const {
    if(_color.count(v)){
        return _color.at(v);
    } else {
        return 0;
    }
}

value Graph::set_color(vertex& v, value c) {
    if(has(v)){
        return _color[v] = c;
    }
    return 0;
}

attributes& Graph::colors() { return _color; }

size_t Graph::count_colors() const
{
  unordered_set<value> colors;
  for(auto& [_, c] :_color){
      colors.insert(c);
    }
  return colors.size();
}

value Graph::max_degree()  const{
    value res = 0;
    for(auto& n : _adjacency_vector){
        res = std::max(res, (value)n.second.size());
    }
    return res;
}

//Graph permuteRandom(unsigned seed);
//Graph permute(std::vector<T> permutation);
const neighbourhood& Graph::operator()(const vertex& v) const { return _adjacency_vector.at(v); };

const adj_t& Graph::V() const { return _adjacency_vector; };

//inline T distance(T v1, T v2) { return _distance_matrix[v1][v2]; };
//inline std::vector<T>& operator[] (const size_t i) { return _distance_matrix[i]; };
//Matrix<T> getAdjMatrix() { return _distance_matrix & 1; };
//Matrix<T> getDistMatrix() { return _distance_matrix; };

Graph::Graph(vector<edge>& edges, bool directed) : _directed(directed)
{
    for(auto it = edges.begin(); it != edges.end(); ++it){
        auto& [v, u] = *it;

        _adjacency_vector[v].insert(u);
        if (!directed) {
            _adjacency_vector[u].insert(v);
        }
    }
    //_distance_matrix.resize(size);
}


string Graph::label(const vertex& v) const
{
    if(_label.count(v)){
        return _label.at(v);
    } else {
        return "";
    }
}

const unordered_map<vertex, string>& Graph::labels()
{
    return _label;
}

vector<vertex> Graph::ids() const
{
    vector<vertex> res;
    for(auto& [v, _] : _adjacency_vector){
        res.push_back(v);
    }
    return res;
}

bool Graph::directed() const
{
    return _directed;
}

bool Graph::has(const vertex& v) const
{
    return _adjacency_vector.count(v);
}

const neighbourhood& Graph::V(const vertex& v) const { return _adjacency_vector.at(v); };

size_t Graph::size() const{
    return _adjacency_vector.size();
}

Graph Graph::operator!() const
{
    Graph res;
    for(auto& [v, _] : _adjacency_vector)
        for(auto& [u, _] : _adjacency_vector){
            if(_adjacency_vector.at(v).count(u) == 0){
                res._adjacency_vector[v].insert(u);
            }
        }
    for(auto& [v, _] : _adjacency_vector){
        res._color[v] = color(v);
        res._label[v] = label(v);
    }
    return res;
}

double Graph::weight(edge e) const
{
    if (!_directed){
        e = {std::min(e.first, e.second), std::max(e.first, e.second)};
    }
    return _weight.count(e) == 0 ? 1 : _weight.at(e);
}

void Graph::set_weight(edge e, double v)
{
    if (!_directed) {
        e = {std::min(e.first, e.second), std::max(e.first, e.second)};
    }
    if (v == 1 && _weight.count(e)){
        _weight.erase(e);
    } else {
        _weight[e] = v;
    }
}


bool Graph::has(edge_leg e) const
{
    edge e1 = {std::to_string(e.first), std::to_string(e.second)};
    return has(e1);
}
bool Graph::has(vertex_leg v) const{
    vertex v1 = std::to_string(v);
    return has(v1);
}
string Graph::label(vertex_leg v) const
{
    vertex v1 = std::to_string(v);
    return label(v1);
}
value Graph::color(vertex_leg v) const
{
    vertex v1 = std::to_string(v);
    return color(v1);
}
value Graph::set_color(vertex_leg v, value c)
{
    vertex v1 = std::to_string(v);
    return set_color(v1, c);
}
const neighbourhood& Graph::operator()(vertex_leg v) const
{
    vertex v1 = std::to_string(v);
    return operator()(v1);
}
const neighbourhood& Graph::V(vertex_leg v) const
{
    vertex v1 = std::to_string(v);
    return V(v1);
}


void Graph::remove_vertex(vertex v)
{
    for(auto& u : _adjacency_vector[v]){
        _adjacency_vector[u].erase(v);
    }
    _color.erase(v);
    _label.erase(v);
    _adjacency_vector.erase(v);
}

Graph Graph::N(const vertex& v) const
{
    Graph res;
    for(auto& w : _adjacency_vector.at(v)){
        res._adjacency_vector[w] = {};
        for(auto& u : _adjacency_vector.at(v)){
            if(_adjacency_vector.at(w).count(u) == 1){
                res._adjacency_vector[w].insert(u);
            }
        }
    }
    for(auto& w : _adjacency_vector.at(v)){
        res._color[v] = color(w);
        res._label[v] = label(w);
    }
    return res;
}
