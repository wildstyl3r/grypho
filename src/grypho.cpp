#include "grypho.hpp"
#include "nodesoup.hpp"

Graph::Graph(vector<neighbourhood> adjv) : _adjacency_vector(adjv), _color(adjv.size(), 0), _degree(adjv.size(), 0), _label(adjv.size())
    {
        for(size_t i = 0; i < _adjacency_vector.size(); ++i){
            _degree[i] = adjv[i].size();
        }
    }
Graph::Graph(attributes degree) : _color(degree.size(), 0), _degree(degree), _label(degree.size()) //partial initialization
    {
        _adjacency_vector.resize(degree.size());
    }


bool Graph::has_edge(edge e)
{
  return _adjacency_vector[e.first].count(e.second);
}


void Graph::remove_edge(edge e)
{
  _adjacency_vector[e.first].erase(e.second);
  _adjacency_vector[e.second].erase(e.first);
  _degree[e.first] = _adjacency_vector[e.first].size();
  _degree[e.second] = _adjacency_vector[e.second].size();
}


void Graph::add_edge(edge e)
{
  _adjacency_vector[e.first].insert(e.second);
  _adjacency_vector[e.second].insert(e.first);
  _degree[e.first] = _adjacency_vector[e.first].size();
  _degree[e.second] = _adjacency_vector[e.second].size();
}


void Graph::add_vertex(neighbourhood adj)
{
  _adjacency_vector.push_back(adj);
  _degree.push_back(_adjacency_vector.back().size());
  _color.push_back(0);
  _label.push_back("");
}


value Graph::deg(vertex v) { return _degree[v]; }

attributes& Graph::degrees() { return _degree; }

vertex Graph::color(vertex v) { return _color[v]; }

vertex Graph::set_color(vertex v, value c) { return _color[v] = c; }

string Graph::id(vertex v)
    {
        if (_ID.size() > v){
            return _ID[v];
        } else {
            return std::to_string(v+1);
        }
    }


attributes& Graph::colors() { return _color; }

size_t Graph::count_colors()
{
  unordered_set<value> colors;
  for(auto color :_color){
      colors.insert(color);
    }
  return colors.size();
}

value Graph::max_degree() { return *std::max_element(_degree.begin(), _degree.end()); }

//Graph permuteRandom(unsigned seed);
//Graph permute(std::vector<T> permutation);
neighbourhood& Graph::operator()(const vertex v) { return _adjacency_vector[v]; };

const vector< neighbourhood >& Graph::V() { return _adjacency_vector; };

//inline T distance(T v1, T v2) { return _distance_matrix[v1][v2]; };
//inline std::vector<T>& operator[] (const size_t i) { return _distance_matrix[i]; };
//Matrix<T> getAdjMatrix() { return _distance_matrix & 1; };
//Matrix<T> getDistMatrix() { return _distance_matrix; };

Graph::Graph(edge* begin, edge* end, bool directed, bool base1)
{
    vertex size = 0;
    for(edge* it = begin; it != end; ++it){
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
    _degree.resize(size, 0);
    _color.resize(size, 0);
    _label.resize(size);

    for(edge* it = begin; it != end; ++it){
	vertex v = it->first - base1, u = it->second - base1;

	_degree[v]++;
	//_distance_matrix[v][u] = 1;
	if (!directed) {
	    _degree[u]++;
	    //_distance_matrix[v][u] = 1;
	}
    }
}


vector<std::pair<unsigned, unsigned>> Graph::draw_coords_FR(unsigned width, unsigned height)
{
    nodesoup::adj_list_t g(_adjacency_vector.size());
    for(int i = 0; i < _adjacency_vector.size(); ++i){
	g[i].reserve(_adjacency_vector[i].size());
	g[i].insert(g[i].end(), _adjacency_vector[i].begin(), _adjacency_vector[i].end());
    }
    auto vecPoint = nodesoup::fruchterman_reingold(g, width, height);
    vector<std::pair<unsigned, unsigned>> coords;
    for (auto& coord : vecPoint){
        coords.push_back({coord.x, coord.y});
      }
    return coords;
}
