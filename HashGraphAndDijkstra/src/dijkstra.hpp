#ifndef DIJKSTRA_HPP_
#define DIJKSTRA_HPP_

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>                    //Biggest int: std::numeric_limits<int>::max()
#include "array_stack.hpp"
#include "hash_graph.hpp"

namespace ics {


int hash(const std::string& s) {std::hash<std::string> str_hash; return str_hash(s);}


class Info {
  public:
    Info(){}
    int          cost     = std::numeric_limits<int>::max();
    std::string from      = "?";
    bool operator == (const Info& rhs) const {
      return cost == rhs.cost && from == rhs.from;
    }
    bool operator != (const Info& rhs) const {
      return !(*this == rhs);
    }
    friend std::ostream& operator << (std::ostream& outs, const Info& i) {
      outs << "Info[" << i.cost << "," << i.from << "]";
      return outs;
    }

};


//Return the final_map as specified in the description of extended Dijkstra algorithm
ics::HashMap<std::string,Info> extended_dijkstra(const ics::HashGraph<int>& g, std::string start_node) {
	ics::HashMap<std::string, Info> answer_map(hash);
	ics::HashMap<std::string, Info> info_map(hash);
	int max = std::numeric_limits<int>::max();
	for (auto node_info : g.all_nodes())
	{
		info_map.put(node_info.first, Info());
	}
	info_map[start_node].cost = 0;
	std::string min_node;// = start_node;
	while (!info_map.empty())
	{
		int min_size = std::numeric_limits<int>::max();
		for (ics::pair<std::string, Info> info : info_map)
		{
			if (info.second.cost < min_size)
			{
				min_node = info.first;
				min_size = info.second.cost;
			}
		}
		if (min_size == max)
		{
			break;
		}
		answer_map.put(min_node, info_map.erase(min_node));
		for (std::string node : g.out_nodes(min_node))
		{
			if (!answer_map.has_key(node))
			{
				ics::pair<std::string, std::string> e(min_node, node);
				int sum_cost = answer_map[min_node].cost + g.all_edges()[e];
				if (info_map[node].cost == max || info_map[node].cost > sum_cost)
				{
					info_map[node].cost = sum_cost;
					info_map[node].from = min_node;
				}
			}
		}
	}
	return answer_map;
}


//Return a string from the start node (implicit in answer_map) to the end node
//  (left to right, separated by a space)
std::string recover_path(ics::HashMap<std::string,Info> answer_map, std::string end_node) {
	ics::ArrayStack<std::string> as;
	std::string path;
	for (std::string location = end_node; location != "?"; location = answer_map[location].from)
	{
		as.push(location);
	}
	while (!as.empty())
	{
		path += as.pop() + " ";
	}
	return path;
}


}

#endif /* DIJKSTRA_HPP_ */
