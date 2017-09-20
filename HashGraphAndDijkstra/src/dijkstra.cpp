#include <string>
#include <iostream>
#include <fstream>
#include "ics46goody.hpp"
#include "array_queue.hpp"
#include "hash_graph.hpp"
#include "dijkstra.hpp"


std::string get_node_in_graph(const ics::HashGraph<int>& g, std::string prompt, bool allow_QUIT) {
  std::string node;
  for(;;) {
    node = ics::prompt_string(prompt + " (must be in graph" + (allow_QUIT ? " or QUIT" : "") + ")");
    if ((allow_QUIT && node == "QUIT") || g.has_node(node))
      break;
  }
  return node;
}


int main() {
  try {
	  ics::HashGraph<int> hg;
	  std::ifstream graph_file;
	  ics::safe_open(graph_file, "Enter graph file name", "flightcost.txt");
	  hg.load(graph_file, ";");
	  std::cout << hg << std::endl;
	  std::string start = get_node_in_graph(hg, "Enter start node", false);
	  ics::HashMap<std::string, ics::Info> answer = ics::extended_dijkstra(hg, start);
	  std::cout << answer << "\n" << std::endl;
	  for (;;)
	  {
		  std::string end = get_node_in_graph(hg, "Enter stop node", true);
		  if (end == "QUIT")
			  break;
		  std::string path = ics::recover_path(answer, end);
		  std::cout << "Cost is " << answer[end].cost << "; path is " << path << "\n" << std::endl;
	  }
  } catch (ics::IcsError& e) {
    std::cout << e.what() << std::endl;
  }

  return 0;
}
