#include "grypho.hpp"

Graph::Graph(adj_t adjv, bool directed) :
    //_directed(directed),
    _adjacency_vector(adjv)
{
    recount_edges();
}


bool Graph::has(edge e) const
{
  if(!has(min(e.first, e.second))) return false;
  return _adjacency_vector.at(min(e.first, e.second)).count(max(e.first, e.second));
}


void Graph::remove_edge(edge e)
{
  if(has(e)){
      _adjacency_vector[e.first].erase(e.second);
      //if(!_directed){
          _adjacency_vector[e.second].erase(e.first);
      //}
      _weight.erase(e);
      _edges--;
  }
}


void Graph::add_edge(edge e)
{
  if(!has(e)){
      _edges++;
      _adjacency_vector[e.first].insert(e.second);
      //if(!_directed){
          _adjacency_vector[e.second].insert(e.first);
      //}
  }
}


void Graph::add_vertex(neighbourhood adj)
{
  add_vertex(std::to_string(size()), adj);
}

void Graph::add_vertex(vertex v, neighbourhood adj, value c, string label)
{
    if(!has(v)){
        _adjacency_vector[v] = {};
        for(const vertex& u : adj){
            if(has(u)){
                _adjacency_vector[v].insert(u);
                //if(!_directed){
                _adjacency_vector[u].insert(v);
                //}
                _edges++;
            }
        }
        set_color(v, c);
        set_label(v, label);
    }
}


value Graph::deg(const vertex& v) const { return _adjacency_vector.at(v).size(); }

//attributes& Graph::degrees() { return _degree; }

value Graph::color(const vertex& v) const {
    if(_color.count(v)){
        return _color.at(v);
    } else {
        return defaultColor;
    }
}

value Graph::set_color(const vertex& v, value c) {
    if(has(v)){
        if (c){
            return _color[v] = c;
        } else {
            _color.erase(v);
        }
    }
    return defaultColor;
}

const attributes& Graph::colors() const { return _color; }

size_t Graph::count_colors() const
{
  unordered_set<value> colors;
  for(auto& [v, _] : V()){
      colors.insert(color(v));
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

Graph::Graph(vector<edge>& edges, bool directed) //: _directed(directed)
{
    for(auto it = edges.begin(); it != edges.end(); ++it){
        auto& [v, u] = *it;

        _adjacency_vector[v].insert(u);
        if (!directed) {
            _adjacency_vector[u].insert(v);
        }
    }
    _edges = edges.size();
    //_distance_matrix.resize(size);
}


const string& Graph::label(const vertex& v) const
{
    if(_label.count(v)){
        return _label.at(v);
    } else {
        return defaultLabel;
    }
}

const unordered_map<vertex, string>& Graph::labels() const
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
    return false;// _directed;
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
    for(auto& [v, _] : _adjacency_vector){
        res.add_vertex(v);
        res.set_color(v, color(v));
        res.set_label(v, label(v));
    }
    for(auto& [v, _] : _adjacency_vector){
        for(auto& [u, _] : _adjacency_vector){
            if(v != u && !has({v,u})){
                res._adjacency_vector[v].insert(u);
            }
        }
    }
    res.recount_edges();
    return res;
}

double Graph::weight(edge e) const
{
    //if (!_directed){
        e = {std::min(e.first, e.second), std::max(e.first, e.second)};
    //}
    return _weight.count(e) == 0 ? 1 : _weight.at(e);
}

void Graph::set_weight(edge e, double v)
{
    //if (!_directed) {
        e = {std::min(e.first, e.second), std::max(e.first, e.second)};
    //}
    if (v == 1 && _weight.count(e)){
        _weight.erase(e);
    } else {
        _weight[e] = v;
    }
}


bool Graph::has(edge_leg e) const
{
    return has({std::to_string(e.first), std::to_string(e.second)});
}
bool Graph::has(vertex_leg v) const{
    return has(std::to_string(v));
}
string Graph::label(vertex_leg v) const
{
    return label(std::to_string(v));
}
value Graph::color(vertex_leg v) const
{
    return color(std::to_string(v));
}
value Graph::set_color(vertex_leg v, value c)
{
    return set_color(std::to_string(v), c);
}
const neighbourhood& Graph::operator()(vertex_leg v) const
{
    return operator()(std::to_string(v));
}
const neighbourhood& Graph::V(vertex_leg v) const
{
    return V(std::to_string(v));
}


void Graph::remove_vertex(vertex v)
{
    if(has(v)){
        for(const vertex& u : _adjacency_vector[v]){
            _adjacency_vector[u].erase(v);
            edge e = {std::min(v, u), std::max(v, u)};
            _weight.erase(e);
        }
        _color.erase(v);
        _label.erase(v);
        _edges -= _adjacency_vector[v].size();
        _adjacency_vector.erase(v);
    }
}

Graph Graph::N(const vertex& v) const
{
    return S(V(v));
}

const string& Graph::set_label(const vertex& v, const string l)
{
    if(has(v)){
        if (l != defaultLabel){
            return _label[v] = l;
        } else {
            _label.erase(v);
        }
    }
    return defaultLabel;
}

Graph Graph::S(const unordered_set<vertex>& target) const
{
    Graph res;
    for(const vertex& v : target){
        for(const vertex& u : target){
            if(v < u && has({v,u})){
                res._adjacency_vector[v].insert(u);
                res._adjacency_vector[u].insert(v);
            }
        }
        res.set_color(v, color(v));
        res.set_label(v, label(v));
    }
    res.recount_edges();
    return res;
}

double Graph::density() const
{
    return (double) _edges / (size() * (size()-1) / 2);
}

size_t Graph::edges() const
{
    return _edges;
}

void Graph::recount_edges()
{
    _edges = 0;
    for(auto& [_, n] : V()){
        _edges += n.size();
    }
    //if (!_directed)
        _edges >>= 1;
}


const string Graph::fileFormat = "Graph format: (*.tgf *.cgf *.dot)";
const string Graph::defaultLabel = "";
const value Graph::defaultColor = 0;
