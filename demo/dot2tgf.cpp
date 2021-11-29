#include "grypho.hpp"
#include "iostream"

int main(int argc, char* argv[])
{
  if (argc != 3) {
      std::cerr << "Missing filenames\n";
      exit(EXIT_FAILURE);
    }

  string source_filename(argv[1]);
  string tgf_filename(argv[2]);
  Graph g(source_filename);
  g.save(tgf_filename);
}
