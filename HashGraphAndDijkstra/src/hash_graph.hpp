#ifndef HASH_GRAPH_HPP_
#define HASH_GRAPH_HPP_


#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <initializer_list>
#include "ics_exceptions.hpp"
#include "iterator.hpp"
#include "pair.hpp"
#include "heap_priority_queue.hpp"
#include "hash_set.hpp"
#include "hash_map.hpp"


namespace ics {

template<class T>
class HashGraph {

  //Forward declaration: see the return type of all_nodes
  private:
    class LocalInfo;

  public:
    //Commands
    HashGraph();
    HashGraph(HashGraph& g);
    virtual ~HashGraph() {}
    void add_node    (std::string node_name);
    void add_edge    (std::string origin, std::string destination, T value);
    void remove_node (std::string node_name);
    void remove_edge (std::string origin, std::string destination);
    void clear       ();
    void load (std::ifstream& in_file,  std::string separator = ";");
    void store(std::ofstream& out_file, std::string separator = ";");

    //Queries
    bool empty      () const;
    int  node_count () const;
    int  edge_count () const;
    bool has_node   (std::string node_name) const;
    bool has_edge   (std::string origin, std::string destination) const;
    T    edge_value (std::string origin, std::string destination) const;
    int  in_degree  (std::string node_name) const;
    int  out_degree (std::string node_name) const;
    int  degree     (std::string node_name) const;

    const ics::HashMap<std::string,LocalInfo>&                all_nodes () const;
    const ics::HashMap<ics::pair<std::string,std::string>,T>& all_edges () const;

    const ics::HashSet<std::string>& out_nodes(std::string node_name) const;
    const ics::HashSet<std::string>& in_nodes (std::string node_name) const;
    const ics::HashSet<ics::pair<std::string,std::string>>& out_edges (std::string node_name) const;
    const ics::HashSet<ics::pair<std::string,std::string>>& in_edges  (std::string node_name) const;

    //Operators
    HashGraph<T>& operator = (const HashGraph<T>& rhs);
    bool operator == (const HashGraph<T>& rhs) const;
    bool operator != (const HashGraph<T>& rhs) const;

  private:
    //All methods and operators relating to LocalInfo are defined below, followed by
    //  friend functions for insertion onto output streams of HashGrah and LocalInfo
    class LocalInfo {
      public:
        LocalInfo()                : from_graph(nullptr), out_nodes(hash_str), in_nodes(hash_str), out_edges(hash_pair_str), in_edges(hash_pair_str) {}
        LocalInfo(HashGraph<T>* g) : from_graph(g),       out_nodes(hash_str), in_nodes(hash_str), out_edges(hash_pair_str), in_edges(hash_pair_str) {}
        void connect(HashGraph<T>* g) {from_graph = g;}

        bool operator == (const LocalInfo& rhs) const {
          return this->in_nodes == rhs.in_nodes && this->out_nodes == rhs.out_nodes &&
                 this->in_edges == rhs.in_edges && this->out_edges == rhs.out_edges;
        }
        bool operator != (const LocalInfo& rhs) const {
          return !(*this == rhs);
        }

        //from_graph should point to the HashGraph LocalInfo is in, so LocalInfo
        //  methods (see <<)
        HashGraph<T>* from_graph;
        ics::HashSet<std::string>                        out_nodes;
        ics::HashSet<std::string>                        in_nodes;
        ics::HashSet<ics::pair<std::string,std::string>> out_edges;
        ics::HashSet<ics::pair<std::string,std::string>> in_edges;
   };//LocalInfo

    //These two friend << operators are easier to define here because of
    //  the nested LocalInfo in HashGraph, which both use; the nodes in HashGraph
    //  appear in alphabetical order; the four sets
    template<class T2>
    friend std::ostream& operator << (std::ostream& outs, const HashGraph<T2>& g) {
      if (g.empty()) {
        outs << "graph[]";
      }else{
        outs << "graph[\n";
        ics::HeapPriorityQueue<ics::pair<std::string,LocalInfo>> nodes(g.node_values.ibegin(),g.node_values.iend(), g.LocalInfo_gt);
        for (ics::pair<std::string,LocalInfo> x : nodes)
          outs << "  " << x << std::endl;
        outs << "]";
      }
      return outs;
    }

    friend std::ostream& operator << (std::ostream& outs, const LocalInfo& li) {
      outs << "LocalInfo[" << std::endl << "    out_nodes=" << li.out_nodes << std::endl;

      outs << "    out_edges=set[";
      if (li.out_edges.size() != 0) {
        ics::Iterator<ics::pair<std::string,std::string>>& i = li.out_edges.ibegin();
        outs << "->" << i->second << "(" << li.from_graph->edge_values[*i] << ")";
        ++i;
        for (/*See above*/; i != li.out_edges.iend(); ++i)
          outs << ",->" << i->second << "(" << li.from_graph->edge_values[*i] << ")";
        }
      outs << "]" << std::endl;

      outs << "    in_nodes =" << li.in_nodes << std::endl;

      outs << "    in_edges =set[";
      if (li.in_edges.size() != 0) {
        ics::Iterator<ics::pair<std::string,std::string>>& i = li.in_edges.ibegin();
        outs << i->first << "->(" << li.from_graph->edge_values[*i] << ")";
        ++i;
        for (/*See above*/; i != li.in_edges.iend(); ++i)
          outs << "," << i->first << "->(" << li.from_graph->edge_values[*i] << ")";
        }
      outs << "]" << std::endl << "  ]";
      return outs;
    }

    private:
      ics::HashMap<std::string,LocalInfo>                node_values;
      ics::HashMap<ics::pair<std::string,std::string>,T> edge_values;

      //Static methods for hashing (in the maps) and for printing in alphabetic
      //  order the nodes in a graph (see << for HashGraph<T>)
      static int hash_str(const std::string& s)
      {std::hash<std::string> str_hash; return str_hash(s);}

      static int hash_pair_str(const ics::pair<std::string,std::string>& s)
      {std::hash<std::string> str_hash; return str_hash(s.first)*str_hash(s.second);}

      static bool LocalInfo_gt(const ics::pair<std::string,LocalInfo>& a,
                              const ics::pair<std::string,LocalInfo>& b)
      {return a.first < b.first;}
};//HashGraph



//Default constructor
template<class T>
HashGraph<T>::HashGraph () : node_values(hash_str), edge_values(hash_pair_str)  {
//Write code here
}


//Copy constructor
template<class T>
HashGraph<T>::HashGraph (HashGraph& g) : node_values(hash_str), edge_values(hash_pair_str) {
//Write code here
	node_values = g.node_values;
	for (ics::pair<std::string, LocalInfo> kv : node_values)
	{
		node_values[kv.first].connect(this);
	}
	edge_values = g.edge_values;
}


//Add node_name to the graph if it is not already there.
//Ensure its from_graph refers to this graph.
template<class T>
void HashGraph<T>::add_node (std::string node_name) {
//Write code here
	if (!node_values.has_key(node_name))
	{
		node_values.put(node_name, LocalInfo(this));
	}
}


//Add an edge from origin to destination with value
//Add these node names and update edge_values and the LocalInfos of each node
template<class T>
void HashGraph<T>::add_edge (std::string origin, std::string destination, T value) {
//Write code here
	ics::pair<std::string, std::string> edge(origin, destination);
	if (!edge_values.has_key(edge))
	{
		edge_values.put(edge, value);
		add_node(origin);
		add_node(destination);
		node_values[origin].out_nodes.insert(destination);
		node_values[destination].in_nodes.insert(origin);
		node_values[origin].out_edges.insert(edge);
		node_values[destination].in_edges.insert(edge);
	}
}


//Remove all uses of node_name from the graph: update node_values, edge_values,
//  and all the LocalInfo in which it appears as an origin or destination node
//If the node_name is not in the graph, do nothing
//Hint: you cannot iterate over a set that you are changing, so you might have
// to copy a set and then iterate over it while removing values from the original set
template<class T>
void HashGraph<T>::remove_node (std::string node_name){
//Write code here

	ics::HashMap<std::string, LocalInfo> hm = node_values;
	for (ics::pair<std::string, LocalInfo> nodes : hm)
	{
		node_values[nodes.first].out_nodes.erase(node_name);
		node_values[nodes.first].in_nodes.erase(node_name);
		remove_edge(nodes.first, node_name);
		remove_edge(node_name, nodes.first);
	}

	ics::HashMap<ics::pair<std::string, std::string>, T> edges = edge_values;
	for (ics::pair<ics::pair<std::string, std::string>, T> edge : edges)
	{
		if (edge.first.first == node_name || edge.first.second == node_name)
		{
			edge_values.erase(edge.first);
		}
	}
	node_values.erase(node_name);
}


//Remove all uses of this edge from the graph: update edge_values and all the
//  LocalInfo in which its origin and destination node appears
//If the edge is not in the graph, do nothing
//Hint: Simpler than remove_node: write and test this one first
template<class T>
void HashGraph<T>::remove_edge (std::string origin, std::string destination) {
//Write code here
	ics::pair<std::string, std::string> edge(origin, destination);
	if (edge_values.has_key(edge))
	{
		edge_values.erase(edge);
		node_values[origin].out_edges.erase(edge);
		node_values[origin].out_nodes.erase(destination);
		node_values[destination].in_edges.erase(edge);
		node_values[destination].in_nodes.erase(origin);
	}
}


//Clear the graph of all nodes and edges
template<class T>
void HashGraph<T>::clear() {
//Write code here
	node_values.clear();
	edge_values.clear();
}


//Load the nodes and edges for a graph from a text file whose form is
// (a) a node name (one per line, one any number of lines)
// (b) the word "NODESABOVEEDGESBELOW"
// (c) an origin node, destination node, and value (one triple per line,
//       with the values separated by separator, on any number of lines)
//Hint: use ics::split and istringstream (the extaction dual of ostreamstring)
template<class T>
void HashGraph<T>::load (std::ifstream& in_file, std::string separator) {
//Write code here
	std::string line;
	std::getline(in_file, line);
	while (line != "NODESABOVEEDGESBELOW")
	{
		add_node(line);
		std::getline(in_file, line);
	}
	while (std::getline(in_file, line))
	{
		std::string origin(ics::split(line, separator).at(0));
		std::string destination(ics::split(line, separator).at(1));

		std::istringstream iss(ics::split(line, separator).at(2));
		T value;
		iss >> value;
		add_edge(origin, destination, value);
	}
	in_file.close();
}


//Store the nodes and edges in a graph into a text file whose form is specified
//  above for the load method; files written by store should be readable by load
//Hint: this is the easier of the two methods: write and test it first
template<class T>
void HashGraph<T>::store(std::ofstream& out_file, std::string separator) {
//Write code here
	for (ics::pair<std::string, LocalInfo> nodes : node_values)
	{
		out_file << nodes.first << std::endl;
	}
	out_file << "NODESABOVEEDGESBELOW" << std::endl;
	for (ics::pair<ics::pair<std::string, std::string>, T> edges : edge_values)
	{
		out_file << edges.first.first << separator << edges.first.second << separator << edges.second << std::endl;
	}
}


//Returns whether a graph is empty
template<class T>
bool HashGraph<T>::empty() const {
//Write code here
	return node_values.empty() && edge_values.empty();
}


//Returns the number of nodes in a graph
template<class T>
int HashGraph<T>::node_count() const {
//Write code here
	return node_values.size();
}


//Returns the number of edges in a graph
template<class T>
int HashGraph<T>::edge_count() const {
//Write code here
	return edge_values.size();
}


//Returns whether or not node_name is in the graph
template<class T>
bool HashGraph<T>::has_node(std::string node_name) const {
//Write code here
	return node_values.has_key(node_name);
}

//Returns whether or not the edge is in the graph
template<class T>
bool HashGraph<T>::has_edge(std::string origin, std::string destination) const {
//Write code here
	return edge_values.has_key(ics::pair<std::string, std::string>(origin, destination));
}


//Returns the value of the edge in the graph; if the edge is not in the graph,
//  throw a GraphError exception with appropriate descriptive text
template<class T>
T HashGraph<T>::edge_value(std::string origin, std::string destination) const {
//Write code here
	if (!has_edge(origin, destination))
	{
		std::ostringstream message;
		message << "Edge from " << origin << " to " << destination << " does not exist in the graph";
		throw ics::GraphError(message.str());
	}
	return edge_values[ics::pair<std::string, std::string>(origin, destination)];
}


//Returns the in-degree of node_name; if that node is not in the graph,
//  throw a GraphError exception with appropriate descriptive text
template<class T>
int HashGraph<T>::in_degree(std::string node_name) const {
//Write code here
	if (!has_node(node_name))
	{
		std::ostringstream message;
		message << "Node " << node_name << " does not exist in the graph";
		throw ics::GraphError(message.str());
	}
	return node_values[node_name].in_edges.size();
}


//Returns the out-degree of node_name; if that node is not in the graph,
//  throw a GraphError exception with appropriate descriptive text
template<class T>
int HashGraph<T>::out_degree(std::string node_name) const {
//Write code here
	if (!has_node(node_name))
	{
		std::ostringstream message;
		message << "Node " << node_name << " does not exist in the graph";
		throw ics::GraphError(message.str());
	}
	return node_values[node_name].out_edges.size();
}


//Returns the degree of node_name; if that node is not in the graph,
//  throw a GraphError exception with appropriate descriptive text.
template<class T>
int HashGraph<T>::degree(std::string node_name) const {
//Write code here
	if (!has_node(node_name))
	{
		std::ostringstream message;
		message << "Node " << node_name << " does not exist in the graph";
		throw ics::GraphError(message.str());
	}
	return out_degree(node_name) + in_degree(node_name);
}


//Returns a reference to the all_nodes map;
//  the user should not mutate its data structure: call Graph commands instead
template<class T>
auto HashGraph<T>::all_nodes () const -> const ics::HashMap<std::string,LocalInfo>& {
//Write code here
	return node_values;
}


//Returns a reference to the all_edges map;
//  the user should not mutate its data structure: call Graph commands instead
template<class T>
const ics::HashMap<ics::pair<std::string,std::string>,T>& HashGraph<T>::all_edges () const {
//Write code here
	return edge_values;
}

//Returns a reference to the out_nodes set in the LocalInfo for node_name;
//  the user should not mutate its data structure: call Graph commands instead; if
//  that node is not in the graph, throw a GraphError exception with appropriate
//  descriptive text
template<class T>
const ics::HashSet<std::string>& HashGraph<T>::out_nodes(std::string node_name) const {
//Write code here
	if (!has_node(node_name))
	{
		std::ostringstream message;
		message << "Node " << node_name << " does not exist in the graph";
		throw ics::GraphError(message.str());
	}
	return node_values[node_name].out_nodes;
}


//Returns a reference to the in_nodes set in the LocalInfo for node_name;
//  the user should not mutate its data structure: call Graph commands instead; if
//  that node is not in the graph, throw a GraphError exception with appropriate
//  descriptive text
template<class T>
const ics::HashSet<std::string>& HashGraph<T>::in_nodes(std::string node_name) const{
//Write code here
	if (!has_node(node_name))
	{
		std::ostringstream message;
		message << "Node " << node_name << " does not exist in the graph";
		throw ics::GraphError(message.str());
	}
	return node_values[node_name].in_nodes;
}


//Returns a reference to the out_edges set in the LocalInfo for node_name;
//  the user should not mutate its data structure: call Graph commands instead; if
//  that node is not in the graph, throw a GraphError exception with appropriate
//  descriptive text
template<class T>
const ics::HashSet<ics::pair<std::string,std::string>>& HashGraph<T>::out_edges (std::string node_name) const {
//Write code here
	if (!has_node(node_name))
	{
		std::ostringstream message;
		message << "Node " << node_name << " does not exist in the graph";
		throw ics::GraphError(message.str());
	}
	return node_values[node_name].out_edges;
}


//Returns a reference to the in_edges set in the LocalInfo for node_name;
//  the user should not mutate its data structure: call Graph commands instead; if
//  that node is not in the graph, throw a GraphError exception with appropriate
//  descriptive text
template<class T>
const ics::HashSet<ics::pair<std::string,std::string>>& HashGraph<T>::in_edges (std::string node_name) const {
//Write code here
	if (!has_node(node_name))
	{
		std::ostringstream message;
		message << "Node " << node_name << " does not exist in the graph";
		throw ics::GraphError(message.str());
	}
	return node_values[node_name].in_edges;
}


//Copy the specified graph into this and return the newly copied graph
//Hint: each copied LocalInfo object should reset from_graph to the this new graph
template<class T>
HashGraph<T>& HashGraph<T>::operator = (const HashGraph<T>& rhs){
//Write code here
	if (this == &rhs)
		return *this;

	node_values = rhs.node_values;
	for (ics::pair<std::string, LocalInfo> kv : node_values)
	{
		node_values[kv.first].connect(this);
	}
	edge_values = rhs.edge_values;
	return *this;
}


//Return whether two graphs are the same
template<class T>
bool HashGraph<T>::operator == (const HashGraph<T>& rhs) const{
//Write code here
	if (this == &rhs)
		return true;
	return node_values == rhs.node_values && edge_values == rhs.edge_values;
}


//Return whether two graphs are different
template<class T>
bool HashGraph<T>::operator != (const HashGraph<T>& rhs) const{
//Write code here
	return !(*this == rhs);
}

}

#endif /* HASH_GRAPH_HPP_ */
