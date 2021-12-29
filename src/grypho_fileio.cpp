#include "grypho.hpp"
#include <cassert>
#include <fstream>
#include <iostream>
#include <sstream>

Graph::Graph(string filename)//reading tgf and dot
{
  using std::cerr;
  using sstream = std::stringstream;
  string file_ext = filename.substr(filename.size()-4);

  std::ifstream ifs(filename);
  if (!ifs.good()) {
      cerr << "Could not open file \"" << filename << "\"\n";
      return;
    }


  std::unordered_map<string, vertex> names;
  string line;

  //dot -- based on nodesoup's reader
  if (file_ext == ".dot"){
      // skip first line
      std::getline(ifs, line);

      while (std::getline(ifs, line)) {
          if (line[0] == '}') {
              break;
            }

          std::istringstream iss(line);
          vertex v, u;
          string edge_sign;
          iss >> v >> edge_sign >> u;

          if(v[v.size()-1] == ';'){
              v.resize(v.size()-1);
          }
          if(u[u.size()-1] == ';'){
              u.resize(u.size()-1);
          }

          assert(edge_sign == "--" || edge_sign.size() == 0);
          if (edge_sign != "--") {
              continue;
            }

          _adjacency_vector[v].insert(u);
          _adjacency_vector[u].insert(v);
        }

    } else if (file_ext == ".tgf") {//tgf      

      std::unordered_map<string, value> colors;

      while(!ifs.eof()){
          std::getline(ifs, line);
          sstream v(line);
          string id, color, label;
          v >> id >> color; std::getline(v, label);
          if (id == "#") break;

          if (V().count(id) == 1){
              std::cout << "Error: non-unique vertex\n";
              abort();
            } else {
              _adjacency_vector[id] = {};
              if (colors.count(color) == 0){
                  value new_color = colors.size();
                  colors[color] = new_color;
                }
              _color[id] = colors[color];
              _label[id] = color != "" && label != "" ? color + " " + label : color + label;
            }
        }

      while(!ifs.eof()){
          std::getline(ifs, line);
          if (line == "") continue;;
          sstream e(line);
          vertex v, u;
          e >> v >> u;

          if (V().count(v) == 0 || V().count(u) == 0){
              std::cout << "Error: undefined vertex in edge list";
              abort();
            } else {
              _adjacency_vector[v].insert(u);
              _adjacency_vector[u].insert(v);
            }
        }
    } else if (file_ext == ".cgf") {//cgf

      while(!ifs.eof()){
          std::getline(ifs, line);
          if (line == "") continue;;
          sstream e(line);
          vertex v, u;
          e >> v >> u;
          _adjacency_vector[v].insert(u);
          _adjacency_vector[u].insert(v);
      }
  } else {

      while(!ifs.eof()){
          std::getline(ifs, line);
          if (line == "") continue;;
          sstream e(line);
          string type;
          vertex v, u;
          e >> type >> v >> u;

          if (type == "e" && v != "" && u != ""){
              _adjacency_vector[v].insert(u);
              _adjacency_vector[u].insert(v);
          }
      }
  }
  recount_edges();
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


    for(auto& [v, _] : V()){
        graph << v << (_label[v] == "" ? "" : " " + _label[v]) << '\n';
    }

    graph << "#\n";

    std::set<edge> exported; //considering undirected graph

    for(auto& [v, _] : V()){
        for(auto& [u, _] : V()){
            edge e = {std::min(u,v), std::max(u,v)};
            if (has(e) && !exported.count(e)){
                graph << e.first << ' ' << e.second << '\n';
                exported.insert(e);
              }
        }
    }
}
