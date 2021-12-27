#include "grypho.hpp"
#include <iostream>

int main(int argc, char* argv[])
{
  if (argc != 3) {
      std::cerr << "Missing filenames\n";
      exit(EXIT_FAILURE);
    }

  string source_filename(argv[1]);
  string tgf_filename(argv[2]);
  int S_vx = -1;
  unordered_set<vertex> sub;
  while(S_vx != 0){
      std::cin >> S_vx;
      if(S_vx != 0){
          sub.insert(std::to_string(S_vx+1));
      }
  }

  Graph g(source_filename);
  g.S(sub).save(tgf_filename);
}
