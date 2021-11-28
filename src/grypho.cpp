#include "grypho.hpp"

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

Graph::Graph(string filename)//reading tgf and dot
{
  using std::cerr;
  if (filename.substr(filename.size()-4) != ".dot" &&
      filename.substr(filename.size()-4) != ".tgf") {
      cerr << "Error: file format is unsupported";
    }

  std::ifstream ifs(filename);
  if (!ifs.good()) {
      cerr << "Could not open file \"" << filename << "\"\n";
      exit(EXIT_FAILURE);
    }


  std::unordered_map<string, vertex> names;
  string line;

  //dot -- based on nodesoup's reader
  if (filename.substr(filename.size()-4) == ".dot"){

      auto name_to_vertex_id = [&names](string name, vector<neighbourhood>& g) -> vertex {
        if (name[name.size() - 1] == ';') {
            name.erase(name.end() - 1, name.end());
          }

        vertex v_id;
        auto it = names.find(name);
        if (it != names.end()) {
            return (*it).second;
          }

        v_id = g.size();
        names.insert({ name, v_id });
        g.resize(v_id + 1);
        return v_id;
      };

      // skip first line
      std::getline(ifs, line);

      while (std::getline(ifs, line)) {
          if (line[0] == '}') {
              break;
            }

          std::istringstream iss(line);
          string name, edge_sign, adj_name;
          iss >> name >> edge_sign >> adj_name;

          // add vertex if new
          vertex v_id = name_to_vertex_id(name, _adjacency_vector);

          assert(edge_sign == "--" || edge_sign.size() == 0);
          if (edge_sign != "--") {
              continue;
            }

          // add adjacent vertex if new
          vertex adj_id = name_to_vertex_id(adj_name, _adjacency_vector);

          // add edge if new
          if (std::find(_adjacency_vector[v_id].begin(), _adjacency_vector[v_id].end(), adj_id) == _adjacency_vector[v_id].end()) {
              _adjacency_vector[v_id].insert(adj_id);
              _adjacency_vector[adj_id].insert(v_id);
            }
        }


      _color.resize(_adjacency_vector.size(), 0);
      _degree.resize(_adjacency_vector.size(), 0);
      _label.resize(_adjacency_vector.size());

      for(size_t i = 0; i < _adjacency_vector.size(); ++i){
          _degree[i] = _adjacency_vector[i].size();
        }
      return;
    }
  else{//tgf
      using sstream = std::stringstream;

      vertex i = 0;
      while(!ifs.eof()){
          std::getline(ifs, line);
          sstream v(line);
          string id;
          v >> id;
          if (id == "#") break;

          if (names.count(id) == 1){
              std::cout << "Error: non-unique vertex\n";
              abort();
          } else {
              names[id] = i;
              _ID.push_back("");
              _label.push_back("");
              _ID[i] = id;
              std::getline(v, _label[i]);
              ++i;
          }
      }

      _adjacency_vector.resize(i);
      _degree.resize(i, 0);
      _color.resize(i, 0);

      while(!ifs.eof()){
          std::getline(ifs, line);
          sstream e(line);
          string v, u;
          e >> v >> u;

          if (names.count(v) == 0 || names.count(u) == 0){
              std::cout << "Error: undefined vertex in edge list";
              abort();
          } else {
              _adjacency_vector[names[v]].insert(names[u]);
              _adjacency_vector[names[u]].insert(names[v]);
              _degree[names[v]]++;
              _degree[names[u]]++;
          }
      }
      return;
    }
}


void Graph::save(string filename)//reading tgf and dot
{
    if (filename.substr(filename.size()-4) != ".tgf"){
	std::cout << "Error: only TGF format supported\n";
	return;
    }
    std::fstream graph(filename, std::ios::out);
    if(!graph){
	std::cout << "Error: unable to create file\n";
	return;
    }
    

    for(vertex v = 0; v < _adjacency_vector.size(); ++v){
	graph << id(v) << (_label[v] == "" ? "" : " " + _label[v]) << '\n';
    }
    
    graph << "#\n";

    std::set<edge> exported; //considering undirected graph

    for(vertex v = 0; v < _adjacency_vector.size(); ++v){
        for(vertex u = 0; u < _adjacency_vector.size(); ++u){
            edge e = {std::min(u,v), std::max(u,v)};
            if (_adjacency_vector[v].count(u) && !exported.count(e)){
                graph << id(e.first) << ' ' << id(e.second) << '\n';
                exported.insert(e);
              }
        }
    }
}



vector<nodesoup::Point2D> Graph::draw_coords_FR(unsigned width, unsigned height)
{
    nodesoup::adj_list_t g(_adjacency_vector.size());
    for(int i = 0; i < _adjacency_vector.size(); ++i){
	g[i].reserve(_adjacency_vector[i].size());
	g[i].insert(g[i].end(), _adjacency_vector[i].begin(), _adjacency_vector[i].end());
    }
    return nodesoup::fruchterman_reingold(g, width, height);
}
