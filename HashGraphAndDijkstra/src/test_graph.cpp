//#include <iostream>
//#include <fstream>
//#include <sstream>
//#include <algorithm>                 // std::random_shuffle
//#include <string>                    // std::hash<std::string>
//#include "ics46goody.hpp"
//#include "gtest/gtest.h"
//#include "array_set.hpp"
//#include "hash_graph.hpp"
//
//typedef ics::pair<std::string,std::string> EdgeType;
//typedef ics::HashGraph<int>               GraphType;
//
//
//class MapTest : public ::testing::Test {
//protected:
//    virtual void SetUp()    {}
//    virtual void TearDown() {}
//};
//
//
//EdgeType od(std::string o, std::string d)
//{return ics::make_pair(o,d);}
//
//void build_standard_graph(GraphType& g) {
//  g.add_edge("a","b",12);
//  g.add_edge("a","c",13);
//  g.add_edge("b","d",24);
//  g.add_edge("c","d",34);
//  g.add_edge("a","d",14);
//  g.add_edge("d","a",41);
//  g.add_node("e");
//}
//
//template<class T>
//int produces(ics::Iterator<T>& begin, ics::Iterator<T>& end) {
//  int count = 0;
//  while (begin != end) {
//    ++begin;
//    ++count;
//  }
//  return count;
//}
//
//TEST_F(MapTest, empty) {
////  try {
//  GraphType g;
//  ASSERT_TRUE(g.empty());
////  } catch (ics::IcsError& e) {
////    std::cout << "Exception: " << e.what() << std::endl;
////    FAIL(); //See above for reason
////  }
//}
//
//
//TEST_F(MapTest, size) {
////  try {
//  GraphType g;
//  ASSERT_EQ(0,g.node_count());
//  ASSERT_EQ(0,g.edge_count());
//  ASSERT_EQ(0, produces(g.all_nodes().ibegin(), g.all_nodes().iend()) );
//  ASSERT_EQ(0, produces(g.all_edges().ibegin(), g.all_edges().iend()) );
////  } catch (ics::IcsError& e) {
////    std::cout << "Exception: " << e.what() << std::endl;
////    FAIL(); //See above for reason
////  }
//}
//
//
//TEST_F(MapTest, add_node) {
////  try {
//  GraphType g;
//  g.add_node("a");
//  g.add_node("b");
//  g.add_node("b");
//  ASSERT_TRUE(g.has_node("a"));
//  ASSERT_TRUE(g.has_node("b"));
//  ASSERT_FALSE(g.has_node("c"));
//  ASSERT_EQ(2,g.node_count());
//  ASSERT_EQ(0,g.edge_count());
//  ASSERT_EQ(2, produces(g.all_nodes().ibegin(), g.all_nodes().iend()) );
////  } catch (ics::IcsError& e) {
////    std::cout << "Exception: " << e.what() << std::endl;
////    FAIL(); //See above for reason
////  }
//}
//
//
//TEST_F(MapTest, add_edge1) {
////  try {
//  GraphType g;
//
//  g.add_edge("a","b",12);
//
//  ASSERT_TRUE(g.has_node("a"));
//  ASSERT_TRUE(g.has_node("b"));
//
//  ASSERT_TRUE (g.has_edge("a","b"));
//  ASSERT_FALSE(g.has_edge("b","a"));
//  ASSERT_FALSE(g.has_edge("a","c"));
//  ASSERT_FALSE(g.has_edge("b","c"));
//  ASSERT_EQ(12,g.edge_value("a","b"));
//  ASSERT_THROW(g.edge_value("a","c"),ics::GraphError);
//  ASSERT_THROW(g.edge_value("b","c"),ics::GraphError);
//
//  ASSERT_EQ(1,g.out_degree("a"));
//  ASSERT_EQ(0,g.in_degree ("a"));
//  ASSERT_EQ(1,g.degree    ("a"));
//  ASSERT_EQ(0,g.out_degree("b"));
//  ASSERT_EQ(1,g.in_degree ("b"));
//  ASSERT_EQ(1,g.degree    ("b"));
//  ASSERT_THROW(g.out_degree("c"),ics::GraphError);
//  ASSERT_THROW(g.in_degree("c"), ics::GraphError);
//  ASSERT_THROW(g.out_degree("c"),ics::GraphError);
//
//  ASSERT_EQ(2,g.node_count());
//  ASSERT_EQ(1,g.edge_count());
//
//  ASSERT_EQ(2, produces(g.all_nodes().ibegin(), g.all_nodes().iend()) );
//  ASSERT_EQ(1, produces(g.all_edges().ibegin(), g.all_edges().iend()) );
//
//  g.add_edge("a","c",13);
//  ASSERT_TRUE(g.has_node("a"));
//  ASSERT_TRUE(g.has_node("b"));
//  ASSERT_TRUE(g.has_node("c"));
//
//  ASSERT_TRUE (g.has_edge("a","b"));
//  ASSERT_TRUE (g.has_edge("a","c"));
//  ASSERT_FALSE(g.has_edge("b","a"));
//  ASSERT_FALSE(g.has_edge("c","a"));
//  ASSERT_FALSE(g.has_edge("b","c"));
//  ASSERT_EQ(12,g.edge_value("a","b"));
//  ASSERT_EQ(13,g.edge_value("a","c"));
//  ASSERT_THROW(g.edge_value("b","c"),ics::GraphError);
//
//  ASSERT_EQ(2,g.out_degree("a"));
//  ASSERT_EQ(0,g.in_degree ("a"));
//  ASSERT_EQ(2,g.degree    ("a"));
//  ASSERT_EQ(0,g.out_degree("b"));
//  ASSERT_EQ(1,g.in_degree ("b"));
//  ASSERT_EQ(1,g.degree    ("b"));
//  ASSERT_EQ(0,g.out_degree("c"));
//  ASSERT_EQ(1,g.in_degree ("c"));
//  ASSERT_EQ(1,g.degree    ("c"));
//
//  ASSERT_EQ(3,g.node_count());
//  ASSERT_EQ(2,g.edge_count());
//
//  ASSERT_EQ(3, produces(g.all_nodes().ibegin(), g.all_nodes().iend()) );
//  ASSERT_EQ(2, produces(g.all_edges().ibegin(), g.all_edges().iend()) );
//
//
//  g.add_edge("b","c",23);
//  ASSERT_TRUE(g.has_node("a"));
//  ASSERT_TRUE(g.has_node("b"));
//  ASSERT_TRUE(g.has_node("c"));
//
//  ASSERT_TRUE (g.has_edge("a","b"));
//  ASSERT_TRUE (g.has_edge("a","c"));
//  ASSERT_TRUE (g.has_edge("b","c"));
//  ASSERT_FALSE(g.has_edge("b","a"));
//  ASSERT_FALSE(g.has_edge("c","a"));
//  ASSERT_FALSE(g.has_edge("c","b"));
//  ASSERT_EQ(12,g.edge_value("a","b"));
//  ASSERT_EQ(13,g.edge_value("a","c"));
//  ASSERT_EQ(23,g.edge_value("b","c"));
//
//  ASSERT_EQ(2,g.out_degree("a"));
//  ASSERT_EQ(0,g.in_degree ("a"));
//  ASSERT_EQ(2,g.degree    ("a"));
//  ASSERT_EQ(1,g.out_degree("b"));
//  ASSERT_EQ(1,g.in_degree ("b"));
//  ASSERT_EQ(2,g.degree    ("b"));
//  ASSERT_EQ(0,g.out_degree("c"));
//  ASSERT_EQ(2,g.in_degree ("c"));
//  ASSERT_EQ(2,g.degree    ("c"));
//
//  ASSERT_EQ(3,g.node_count());
//  ASSERT_EQ(3,g.edge_count());
//
//  ASSERT_EQ(3, produces(g.all_nodes().ibegin(), g.all_nodes().iend()) );
//  ASSERT_EQ(3, produces(g.all_edges().ibegin(), g.all_edges().iend()) );
//
//  {//node tests
//    ics::ArraySet<std::string> aout; aout.insert("b"); aout.insert("c");
//    ics::ArraySet<std::string> ain;
//    ics::ArraySet<std::string> bout; bout.insert("c");
//    ics::ArraySet<std::string> bin;  bin.insert("a");
//    ics::ArraySet<std::string> cout;
//    ics::ArraySet<std::string> cin;  cin.insert("a"); cin.insert("b");
//
//    ASSERT_EQ(g.out_nodes("a"),aout);
//    ASSERT_EQ(g.in_nodes ("a"),ain);
//    ASSERT_EQ(g.out_nodes("b"),bout);
//    ASSERT_EQ(g.in_nodes ("b"),bin);
//    ASSERT_EQ(g.out_nodes("c"),cout);
//    ASSERT_EQ(g.in_nodes ("c"),cin);
//  }
//
//  {//edge tests
//    ics::ArraySet<EdgeType> aout; aout.insert(od("a","b")); aout.insert(od("a","c"));
//    ics::ArraySet<EdgeType> ain;
//    ics::ArraySet<EdgeType> bout; bout.insert(od("b","c"));
//    ics::ArraySet<EdgeType> bin;  bin.insert(od("a","b"));
//    ics::ArraySet<EdgeType> cout;
//    ics::ArraySet<EdgeType> cin;  cin.insert(od("a","c")); cin.insert(od("b","c"));
//
//    ASSERT_EQ(g.out_edges("a"),aout);
//    ASSERT_EQ(g.in_edges ("a"),ain);
//    ASSERT_EQ(g.out_edges("b"),bout);
//    ASSERT_EQ(g.in_edges ("b"),bin);
//    ASSERT_EQ(g.out_edges("c"),cout);
//    ASSERT_EQ(g.in_edges ("c"),cin);
//  }
//
////} catch (ics::IcsError& e) {
////  std::cout << "Exception: " << e.what() << std::endl;
////  FAIL(); //See above for reason
////}
//}
//
//
//TEST_F(MapTest, add_edge2) {
////  try {
//  GraphType g;
//
//  build_standard_graph(g);
//
//  ASSERT_TRUE(g.has_node("a"));
//  ASSERT_TRUE(g.has_node("b"));
//  ASSERT_TRUE(g.has_node("c"));
//  ASSERT_TRUE(g.has_node("d"));
//  ASSERT_TRUE(g.has_node("e"));
//
//  ASSERT_TRUE(g.has_edge("a","b"));
//  ASSERT_TRUE(g.has_edge("a","c"));
//  ASSERT_TRUE(g.has_edge("b","d"));
//  ASSERT_TRUE(g.has_edge("c","d"));
//  ASSERT_TRUE(g.has_edge("a","d"));
//  ASSERT_TRUE(g.has_edge("d","a"));
//
//  ASSERT_EQ(12,g.edge_value("a","b"));
//  ASSERT_EQ(13,g.edge_value("a","c"));
//  ASSERT_EQ(24,g.edge_value("b","d"));
//  ASSERT_EQ(34,g.edge_value("c","d"));
//  ASSERT_EQ(14,g.edge_value("a","d"));
//  ASSERT_EQ(41,g.edge_value("d","a"));
//
//  ASSERT_EQ(3,g.out_degree("a"));
//  ASSERT_EQ(1,g.in_degree ("a"));
//  ASSERT_EQ(4,g.degree    ("a"));
//  ASSERT_EQ(1,g.out_degree("b"));
//  ASSERT_EQ(1,g.in_degree ("b"));
//  ASSERT_EQ(2,g.degree    ("b"));
//  ASSERT_EQ(1,g.out_degree("c"));
//  ASSERT_EQ(1,g.in_degree ("c"));
//  ASSERT_EQ(2,g.degree    ("c"));
//  ASSERT_EQ(1,g.out_degree("d"));
//  ASSERT_EQ(3,g.in_degree ("d"));
//  ASSERT_EQ(4,g.degree    ("d"));
//  ASSERT_EQ(0,g.out_degree("e"));
//  ASSERT_EQ(0,g.in_degree ("e"));
//  ASSERT_EQ(0,g.degree    ("e"));
//
//  ASSERT_EQ(5,g.node_count());
//  ASSERT_EQ(6,g.edge_count());
//
//  ASSERT_EQ(5, produces(g.all_nodes().ibegin(), g.all_nodes().iend()) );
//  ASSERT_EQ(6, produces(g.all_edges().ibegin(), g.all_edges().iend()) );
//
//
//  {//node tests
//    ics::ArraySet<std::string> aout; aout.insert("b"); aout.insert("c"); aout.insert("d");
//    ics::ArraySet<std::string> ain;  ain.insert("d");
//    ics::ArraySet<std::string> bout; bout.insert("d");
//    ics::ArraySet<std::string> bin;  bin.insert("a");
//    ics::ArraySet<std::string> cout; cout.insert("d");
//    ics::ArraySet<std::string> cin;  cin.insert("a");
//    ics::ArraySet<std::string> dout; dout.insert("a");
//    ics::ArraySet<std::string> din;  din.insert("b"); din.insert("c"); din.insert("a");
//    ics::ArraySet<std::string> eout;
//    ics::ArraySet<std::string> ein;
//
//    ASSERT_EQ(g.out_nodes("a"),aout);
//    ASSERT_EQ(g.in_nodes ("a"),ain);
//    ASSERT_EQ(g.out_nodes("b"),bout);
//    ASSERT_EQ(g.in_nodes ("b"),bin);
//    ASSERT_EQ(g.out_nodes("c"),cout);
//    ASSERT_EQ(g.in_nodes ("c"),cin);
//    ASSERT_EQ(g.out_nodes("d"),dout);
//    ASSERT_EQ(g.in_nodes ("d"),din);
//    ASSERT_EQ(g.out_nodes("e"),eout);
//    ASSERT_EQ(g.in_nodes ("e"),ein);
//  }
//
//  {//edge tests
//    ics::ArraySet<EdgeType> aout; aout.insert(od("a","b")); aout.insert(od("a","c")); aout.insert(od("a","d"));
//    ics::ArraySet<EdgeType> ain;  ain.insert(od("d","a"));
//    ics::ArraySet<EdgeType> bout; bout.insert(od("b","d"));
//    ics::ArraySet<EdgeType> bin;  bin.insert(od("a","b"));
//    ics::ArraySet<EdgeType> cout; cout.insert(od("c","d"));
//    ics::ArraySet<EdgeType> cin;  cin.insert(od("a","c"));
//    ics::ArraySet<EdgeType> dout; dout.insert(od("d","a"));
//    ics::ArraySet<EdgeType> din;  din.insert(od("b","d")); din.insert(od("c","d")); din.insert(od("a","d"));
//    ics::ArraySet<EdgeType> eout;
//    ics::ArraySet<EdgeType> ein;
//
//    ASSERT_EQ(g.out_edges("a"),aout);
//    ASSERT_EQ(g.in_edges ("a"),ain);
//    ASSERT_EQ(g.out_edges("b"),bout);
//    ASSERT_EQ(g.in_edges ("b"),bin);
//    ASSERT_EQ(g.out_edges("c"),cout);
//    ASSERT_EQ(g.in_edges ("c"),cin);
//    ASSERT_EQ(g.out_edges("d"),dout);
//    ASSERT_EQ(g.in_edges ("d"),din);
//    ASSERT_EQ(g.out_edges("e"),eout);
//    ASSERT_EQ(g.in_edges ("e"),ein);
//  }
////} catch (ics::IcsError& e) {
////  std::cout << "Exception: " << e.what() << std::endl;
////  FAIL(); //See above for reason
////}
//}
//
//
//TEST_F(MapTest, remove_edge) {
////  try {
//  GraphType g;
//
//  build_standard_graph(g);
//
//  g.remove_edge("a","b");
//  g.remove_edge("b","d");
//  g.remove_edge("d","b");  //non-existant; just return
//
//  ASSERT_TRUE(g.has_node("a"));
//  ASSERT_TRUE(g.has_node("b"));
//  ASSERT_TRUE(g.has_node("c"));
//  ASSERT_TRUE(g.has_node("d"));
//  ASSERT_TRUE(g.has_node("e"));
//
//  ASSERT_TRUE(g.has_edge("a","c"));
//  ASSERT_TRUE(g.has_edge("c","d"));
//  ASSERT_TRUE(g.has_edge("a","d"));
//  ASSERT_TRUE(g.has_edge("d","a"));
//
//  ASSERT_EQ(13,g.edge_value("a","c"));
//  ASSERT_EQ(34,g.edge_value("c","d"));
//  ASSERT_EQ(14,g.edge_value("a","d"));
//  ASSERT_EQ(41,g.edge_value("d","a"));
//
//  ASSERT_EQ(2,g.out_degree("a"));
//  ASSERT_EQ(1,g.in_degree ("a"));
//  ASSERT_EQ(3,g.degree    ("a"));
//  ASSERT_EQ(0,g.out_degree("b"));
//  ASSERT_EQ(0,g.in_degree ("b"));
//  ASSERT_EQ(0,g.degree    ("b"));
//  ASSERT_EQ(1,g.out_degree("c"));
//  ASSERT_EQ(1,g.in_degree ("c"));
//  ASSERT_EQ(2,g.degree    ("c"));
//  ASSERT_EQ(1,g.out_degree("d"));
//  ASSERT_EQ(2,g.in_degree ("d"));
//  ASSERT_EQ(3,g.degree    ("d"));
//  ASSERT_EQ(0,g.out_degree("e"));
//  ASSERT_EQ(0,g.in_degree ("e"));
//  ASSERT_EQ(0,g.degree    ("e"));
//
//  ASSERT_EQ(5,g.node_count());
//  ASSERT_EQ(4,g.edge_count());
//
//  ASSERT_EQ(5, produces(g.all_nodes().ibegin(), g.all_nodes().iend()) );
//  ASSERT_EQ(4, produces(g.all_edges().ibegin(), g.all_edges().iend()) );
//
//  {//node tests
//    ics::ArraySet<std::string> aout; aout.insert("c"); aout.insert("d");
//    ics::ArraySet<std::string> ain;  ain.insert("d");
//    ics::ArraySet<std::string> bout;
//    ics::ArraySet<std::string> bin;
//    ics::ArraySet<std::string> cout; cout.insert("d");
//    ics::ArraySet<std::string> cin;  cin.insert("a");
//    ics::ArraySet<std::string> dout; dout.insert("a");
//    ics::ArraySet<std::string> din;  din.insert("c"); din.insert("a");
//    ics::ArraySet<std::string> eout;
//    ics::ArraySet<std::string> ein;
//
//    ASSERT_EQ(g.out_nodes("a"),aout);
//    ASSERT_EQ(g.in_nodes ("a"),ain);
//    ASSERT_EQ(g.out_nodes("b"),bout);
//    ASSERT_EQ(g.in_nodes ("b"),bin);
//    ASSERT_EQ(g.out_nodes("c"),cout);
//    ASSERT_EQ(g.in_nodes ("c"),cin);
//    ASSERT_EQ(g.out_nodes("d"),dout);
//    ASSERT_EQ(g.in_nodes ("d"),din);
//    ASSERT_EQ(g.out_nodes("e"),eout);
//    ASSERT_EQ(g.in_nodes ("e"),ein);
//  }
//
//  {//edge tests
//    ics::ArraySet<EdgeType> aout; aout.insert(od("a","c")); aout.insert(od("a","d"));
//    ics::ArraySet<EdgeType> ain;  ain.insert(od("d","a"));
//    ics::ArraySet<EdgeType> bout;
//    ics::ArraySet<EdgeType> bin;
//    ics::ArraySet<EdgeType> cout; cout.insert(od("c","d"));
//    ics::ArraySet<EdgeType> cin;  cin.insert(od("a","c"));
//    ics::ArraySet<EdgeType> dout; dout.insert(od("d","a"));
//    ics::ArraySet<EdgeType> din;  din.insert(od("c","d")); din.insert(od("a","d"));
//    ics::ArraySet<EdgeType> eout;
//    ics::ArraySet<EdgeType> ein;
//
//    ASSERT_EQ(g.out_edges("a"),aout);
//    ASSERT_EQ(g.in_edges ("a"),ain);
//    ASSERT_EQ(g.out_edges("b"),bout);
//    ASSERT_EQ(g.in_edges ("b"),bin);
//    ASSERT_EQ(g.out_edges("c"),cout);
//    ASSERT_EQ(g.in_edges ("c"),cin);
//    ASSERT_EQ(g.out_edges("d"),dout);
//    ASSERT_EQ(g.in_edges ("d"),din);
//    ASSERT_EQ(g.out_edges("e"),eout);
//    ASSERT_EQ(g.in_edges ("e"),ein);
//  }
////} catch (ics::IcsError& e) {
////  std::cout << "Exception: " << e.what() << std::endl;
////  FAIL(); //See above for reason
////}
//}
//
//
//TEST_F(MapTest, remove_node) {
////  try {
//  GraphType g;
//
//  build_standard_graph(g);
//
//  g.remove_node("d");
//
//  ASSERT_TRUE(g.has_node("a"));
//  ASSERT_TRUE(g.has_node("b"));
//  ASSERT_TRUE(g.has_node("c"));
//  ASSERT_TRUE(g.has_node("e"));
//
//  ASSERT_TRUE(g.has_edge("a","b"));
//  ASSERT_TRUE(g.has_edge("a","c"));
//
//  ASSERT_EQ(12,g.edge_value("a","b"));
//  ASSERT_EQ(13,g.edge_value("a","c"));
//
//  ASSERT_EQ(2,g.out_degree("a"));
//  ASSERT_EQ(0,g.in_degree ("a"));
//  ASSERT_EQ(2,g.degree    ("a"));
//  ASSERT_EQ(0,g.out_degree("b"));
//  ASSERT_EQ(1,g.in_degree ("b"));
//  ASSERT_EQ(1,g.degree    ("b"));
//  ASSERT_EQ(0,g.out_degree("c"));
//  ASSERT_EQ(1,g.in_degree ("c"));
//  ASSERT_EQ(1,g.degree    ("c"));
//  ASSERT_THROW(g.out_degree("d"),ics::GraphError);
//  ASSERT_THROW(g.in_degree ("d"),ics::GraphError);
//  ASSERT_THROW(g. degree   ("d"),ics::GraphError);
//  ASSERT_EQ(0,g.out_degree("e"));
//  ASSERT_EQ(0,g.in_degree ("e"));
//  ASSERT_EQ(0,g.degree    ("e"));
//
//  ASSERT_EQ(4,g.node_count());
//  ASSERT_EQ(2,g.edge_count());
//
//  ASSERT_EQ(4, produces(g.all_nodes().ibegin(), g.all_nodes().iend()) );
//  ASSERT_EQ(2, produces(g.all_edges().ibegin(), g.all_edges().iend()) );
//
//
//  {//node tests
//    ics::ArraySet<std::string> aout; aout.insert("b"); aout.insert("c");
//    ics::ArraySet<std::string> ain;
//    ics::ArraySet<std::string> bout;
//    ics::ArraySet<std::string> bin;  bin.insert("a");
//    ics::ArraySet<std::string> cout;
//    ics::ArraySet<std::string> cin;  cin.insert("a");
//    ics::ArraySet<std::string> eout;
//    ics::ArraySet<std::string> ein;
//
//    ASSERT_EQ(g.out_nodes("a"),aout);
//    ASSERT_EQ(g.in_nodes ("a"),ain);
//    ASSERT_EQ(g.out_nodes("b"),bout);
//    ASSERT_EQ(g.in_nodes ("b"),bin);
//    ASSERT_EQ(g.out_nodes("c"),cout);
//    ASSERT_EQ(g.in_nodes ("c"),cin);
//    ASSERT_THROW(g.out_nodes("d"),ics::GraphError);
//    ASSERT_THROW(g.in_nodes("d"),ics::GraphError);
//    ASSERT_EQ(g.out_nodes("e"),eout);
//    ASSERT_EQ(g.in_nodes ("e"),ein);
//  }
//
//  {//edge tests
//    ics::ArraySet<EdgeType> aout; aout.insert(od("a","b")); aout.insert(od("a","c"));
//    ics::ArraySet<EdgeType> ain;
//    ics::ArraySet<EdgeType> bout;
//    ics::ArraySet<EdgeType> bin;  bin.insert(od("a","b"));
//    ics::ArraySet<EdgeType> cout;
//    ics::ArraySet<EdgeType> cin;  cin.insert(od("a","c"));
//    ics::ArraySet<EdgeType> eout;
//    ics::ArraySet<EdgeType> ein;
//
//    ASSERT_EQ(g.out_edges("a"),aout);
//    ASSERT_EQ(g.in_edges ("a"),ain);
//    ASSERT_EQ(g.out_edges("b"),bout);
//    ASSERT_EQ(g.in_edges ("b"),bin);
//    ASSERT_EQ(g.out_edges("c"),cout);
//    ASSERT_EQ(g.in_edges ("c"),cin);
//    ASSERT_THROW(g.out_edges("d"),ics::GraphError);
//    ASSERT_THROW(g.in_edges("d"),ics::GraphError);
//    ASSERT_EQ(g.out_edges("e"),eout);
//    ASSERT_EQ(g.in_edges ("e"),ein);
//  }
////} catch (ics::IcsError& e) {
////  std::cout << "Exception: " << e.what() << std::endl;
////  FAIL(); //See above for reason
////}
//}
//
//
//TEST_F(MapTest, relations) {
////  try {
//  GraphType g,g2;
//  build_standard_graph(g);
//  build_standard_graph(g2);
//
//  ASSERT_EQ(g,g2);
//
//  g.remove_edge("c","d");
//  ASSERT_NE(g,g2);
//
//  g2.remove_edge("c","d");
//  ASSERT_EQ(g,g2);
//
//  g.remove_node("d");
//  ASSERT_NE(g,g2);
//
//  g2.remove_node("d");
//  ASSERT_EQ(g,g2);
//
//
//  g2.remove_node("a");
//  ASSERT_NE(g,g2);
//
//  g.clear();
//  g2.clear();
//  ASSERT_EQ(g,g2);
////  } catch (ics::IcsError& e) {
////    std::cout << "Exception: " << e.what() << std::endl;
////    FAIL(); //See above for reason
////  }
//}
//
//
//TEST_F(MapTest, load) {
////  try {
//  GraphType g,g2;
//  build_standard_graph(g);
//  std::ifstream in("standard.txt");
//  g2.load(in,"/");
//  ASSERT_EQ(g,g2);
////  } catch (ics::IcsError& e) {
////    std::cout << "Exception: " << e.what() << std::endl;
////    FAIL(); //See above for reason
////  }
//}
//
//
//TEST_F(MapTest, store) {
////  try {
//  GraphType g,g2;
//  build_standard_graph(g);
//  std::ofstream out("store_test.txt");
//  g.store(out,"/");
//
//  std::ifstream in("store_test.txt");
//  g2.load(in,"/");
//  ASSERT_EQ(g,g2);
////  } catch (ics::IcsError& e) {
////    std::cout << "Exception: " << e.what() << std::endl;
////    FAIL(); //See above for reason
////  }
//}
//
//
//int main(int argc, char **argv) {
//  ::testing::InitGoogleTest(&argc, argv);
//  return RUN_ALL_TESTS();
//}
