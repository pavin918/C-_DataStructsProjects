//#include <iostream>
//#include <sstream>
//#include <algorithm>                 // std::random_shuffle
//#include "ics46goody.hpp"
//#include "gtest/gtest.h"
//#include "array_set.hpp"             // must leave in
//#include "array_priority_queue.hpp"  // must leave in
//#include "hash_set.hpp"
//
//typedef ics::HashSet<std::string> SetType;
//typedef ics::HashSet<int>         SetType2;
//
//int test_size  = ics::prompt_int ("Enter large scale test size");
//int trace      = ics::prompt_bool("Trace large scale test",false);
//int speed_size = ics::prompt_int ("Enter large scale speed test size");
//
//
//bool gt_string (const std::string& a, const std::string& b) {return a < b;}
//bool gt_int    (const int& a, const int& b) {return a < b;}
//static int hash_str(const std::string& s) {std::hash<std::string> str_hash; return str_hash(s);}
//static int hash_int(const int& i        ) {std::hash<int> int_hash; return int_hash(i);}
//
//
//class SetTest : public ::testing::Test {
//protected:
//    virtual void SetUp()    {}
//    virtual void TearDown() {}
//};
//
//
//void load(SetType& s, std::string values) {
//  std::string* v = new std::string[values.size()];
//  for (unsigned i=0; i<values.size(); ++i)
//    v[i] = values[i];
//  for (unsigned i=0; i<values.size(); ++i)
//    s.insert(v[i]);
//  //delete[] v;
//}
//
//
//::testing::AssertionResult contains(SetType& s, std::string values) {
//  std::string* v = new std::string[values.size()];
//  for (unsigned i=0; i<values.size(); ++i)
//    v[i] = values[i];
//  for (unsigned i=0; i<values.size(); ++i)
//    if (!s.contains(v[i]))
//      return ::testing::AssertionFailure();
//  delete[] v;
//  return ::testing::AssertionSuccess();
//}
//
//
//::testing::AssertionResult not_contains(SetType& s, std::string values) {
//  std::string* v = new std::string[values.size()];
//  for (unsigned i=0; i<values.size(); ++i)
//    v[i] = values[i];
//  for (unsigned i=0; i<values.size(); ++i)
//    if (s.contains(v[i]))
//      return ::testing::AssertionFailure();
//  delete[] v;
//  return ::testing::AssertionSuccess();
//}
//
//
//
//TEST_F(SetTest, empty) {
//  SetType s(hash_str);
//  ASSERT_TRUE(s.empty());
//}
//
//
//TEST_F(SetTest, size) {
//  SetType s(hash_str);
//  ASSERT_EQ(0,s.size());
//}
//
//
//TEST_F(SetTest, contains) {
//  SetType s(hash_str);
//  ASSERT_FALSE(s.contains("a"));
//}
//
//TEST_F(SetTest, insert) {
//  SetType s(hash_str);
//  ASSERT_FALSE(s.contains("x"));
//
//  ASSERT_EQ(1,s.insert("a"));
//  ASSERT_FALSE(s.empty());
//  ASSERT_EQ(1, s.size());
//  ASSERT_TRUE(contains(s,"a"));
//  ASSERT_FALSE(s.contains("x"));
//
//  ASSERT_EQ(1,s.insert("b"));
//  ASSERT_FALSE(s.empty());
//  ASSERT_EQ(2, s.size());
//
//  ASSERT_TRUE(contains(s,"ab"));
//  ASSERT_FALSE(s.contains("x"));
//
//  ASSERT_EQ(1,s.insert("c"));
//  ASSERT_FALSE(s.empty());
//  ASSERT_EQ(3, s.size());
//  ASSERT_TRUE(contains(s,"abc"));
//  ASSERT_FALSE(s.contains("x"));
//
//  ASSERT_EQ(1,s.insert("d"));
//  ASSERT_FALSE(s.empty());
//  ASSERT_EQ(4, s.size());
//  ASSERT_TRUE(contains(s,"abcd"));
//  ASSERT_FALSE(s.contains("x"));
//
//  ASSERT_EQ(1,s.insert("e"));
//  ASSERT_FALSE(s.empty());
//  ASSERT_EQ(5, s.size());
//  ASSERT_TRUE(contains(s,"abcde"));
//  ASSERT_FALSE(s.contains("x"));
//
//  ASSERT_EQ(1,s.insert("f"));
//  ASSERT_FALSE(s.empty());
//  ASSERT_EQ(6, s.size());
//  ASSERT_TRUE(contains(s,"abcdef"));
//  ASSERT_FALSE(s.contains("x"));
//
//  ASSERT_EQ(1,s.insert("g"));
//  ASSERT_FALSE(s.empty());
//  ASSERT_EQ(7, s.size());
//  ASSERT_TRUE(contains(s,"abcdefg"));
//  ASSERT_FALSE(s.contains("x"));
//
//  ASSERT_EQ(1,s.insert("h"));
//  ASSERT_FALSE(s.empty());
//  ASSERT_EQ(8, s.size());
//  ASSERT_TRUE(contains(s,"abcdefgh"));
//  ASSERT_FALSE(s.contains("x"));
//
//  ASSERT_EQ(0,s.insert("a"));
//  ASSERT_EQ(8, s.size());
//
//  ASSERT_EQ(0,s.insert("b"));
//  ASSERT_EQ(8, s.size());
//
//  ASSERT_EQ(0,s.insert("c"));
//  ASSERT_EQ(8, s.size());
//
//  ASSERT_EQ(0,s.insert("d"));
//  ASSERT_EQ(8, s.size());
//
//  ASSERT_EQ(0,s.insert("e"));
//  ASSERT_EQ(8, s.size());
//
//  ASSERT_EQ(0,s.insert("f"));
//  ASSERT_EQ(8, s.size());
//
//  ASSERT_EQ(0,s.insert("g"));
//  ASSERT_EQ(8, s.size());
//
//  ASSERT_EQ(0,s.insert("h"));
//  ASSERT_EQ(8, s.size());
//}
//
//
//TEST_F(SetTest, operator_rel) {// == and != and (strict) subset
//  SetType s1(hash_str),s2(hash_str);
//  ASSERT_EQ   (s1,s2);
//  ASSERT_FALSE(s1 != s2);
//  ASSERT_FALSE(s1 <  s2);
//  ASSERT_TRUE (s1 <= s2);
//  ASSERT_TRUE (s1 >= s2);
//  ASSERT_FALSE(s1 >  s2);
//
//  s1.insert("a");
//  ASSERT_NE   (s1,s2);
//  ASSERT_FALSE(s1 == s2);
//  ASSERT_FALSE(s1 <  s2);
//  ASSERT_FALSE(s1 <= s2);
//  ASSERT_TRUE (s1 >= s2);
//  ASSERT_TRUE (s1 >  s2);
//
//  s1.insert("b");
//  ASSERT_NE   (s1,s2);
//  ASSERT_FALSE(s1 == s2);
//  ASSERT_FALSE(s1 <  s2);
//  ASSERT_FALSE(s1 <= s2);
//  ASSERT_TRUE (s1 >= s2);
//  ASSERT_TRUE (s1 >  s2);
//
//  s1.insert("c");
//  ASSERT_NE   (s1,s2);
//  ASSERT_FALSE(s1 == s2);
//  ASSERT_FALSE(s1 <  s2);
//  ASSERT_FALSE(s1 <= s2);
//  ASSERT_TRUE (s1 >= s2);
//  ASSERT_TRUE (s1 >  s2);
//
//  s2.insert("c");
//  ASSERT_NE   (s1,s2);
//  ASSERT_FALSE(s1 == s2);
//  ASSERT_FALSE(s1 <  s2);
//  ASSERT_FALSE(s1 <= s2);
//  ASSERT_TRUE (s1 >= s2);
//  ASSERT_TRUE (s1 >  s2);
//
//  s2.insert("b");
//  ASSERT_NE   (s1,s2);
//  ASSERT_FALSE(s1 == s2);
//  ASSERT_FALSE(s1 <  s2);
//  ASSERT_FALSE(s1 <= s2);
//  ASSERT_TRUE (s1 >= s2);
//  ASSERT_TRUE (s1 >  s2);
//
//  s2.insert("a");
//  ASSERT_EQ   (s1,s2);
//  ASSERT_FALSE(s1 != s2);
//  ASSERT_FALSE(s1 <  s2);
//  ASSERT_TRUE (s1 <= s2);
//  ASSERT_TRUE (s1 >= s2);
//  ASSERT_FALSE(s1 >  s2);
//
//  s2.insert("d");
//  ASSERT_NE   (s1,s2);
//  ASSERT_FALSE(s1 == s2);
//  ASSERT_TRUE (s1 <  s2);
//  ASSERT_TRUE (s1 <= s2);
//  ASSERT_FALSE(s1 >= s2);
//  ASSERT_FALSE(s1 >  s2);
//
//  s2.insert("e");
//  ASSERT_NE   (s1,s2);
//  ASSERT_FALSE(s1 == s2);
//  ASSERT_TRUE (s1 <  s2);
//  ASSERT_TRUE (s1 <= s2);
//  ASSERT_FALSE(s1 >= s2);
//  ASSERT_FALSE(s1 >  s2);
//
//  s1.insert("e");
//  ASSERT_NE   (s1,s2);
//  ASSERT_FALSE(s1 == s2);
//  ASSERT_TRUE (s1 <  s2);
//  ASSERT_TRUE (s1 <= s2);
//  ASSERT_FALSE(s1 >= s2);
//  ASSERT_FALSE(s1 >  s2);
//
//  s1.insert("d");
//  ASSERT_EQ   (s1,s2);
//  ASSERT_FALSE(s1 != s2);
//  ASSERT_FALSE(s1 <  s2);
//  ASSERT_TRUE (s1 <= s2);
//  ASSERT_TRUE (s1 >= s2);
//  ASSERT_FALSE(s1 >  s2);
//
//  s1.erase("c");
//  ASSERT_NE   (s1,s2);
//  ASSERT_FALSE(s1 == s2);
//  ASSERT_TRUE (s1 <  s2);
//  ASSERT_TRUE (s1 <= s2);
//  ASSERT_FALSE(s1 >= s2);
//  ASSERT_FALSE(s1 >  s2);
//
//  s2.erase("c");
//  ASSERT_EQ   (s1,s2);
//  ASSERT_FALSE(s1 != s2);
//  ASSERT_FALSE(s1 <  s2);
//  ASSERT_TRUE (s1 <= s2);
//  ASSERT_TRUE (s1 >= s2);
//  ASSERT_FALSE(s1 >  s2);
//
//  ASSERT_EQ(s1,s1);
//  ASSERT_EQ(s2,s2);
//}
//
//
//TEST_F(SetTest, operator_stream_insert) {// <<
//  std::ostringstream value;
//  SetType s(hash_str);
//  value << s;
//  ASSERT_EQ("set[]", value.str());
//
//  value.str("");
//  s.insert("c");
//  value << s;
//  ASSERT_EQ("set[c]", value.str());
//
//  //Cannot further test: order not fixed
//}
//
//
//TEST_F(SetTest, insert_iterator_param) {
//  SetType s(hash_str),s1(hash_str);
//  load(s1,"abcdefghij");
//  s.insert(s1.ibegin(),s1.iend());
//  ASSERT_FALSE(s.empty());
//  ASSERT_EQ(10, s.size());
//  ASSERT_EQ(s,s1);
//}
//
//
//TEST_F(SetTest, contains_iterator_param) {
//  SetType s(hash_str),s1(hash_str),s2(hash_str);
//  load(s,"abcdefghij");
//  load(s1,"abdij");
//  load(s2,"abdxij");
//  ASSERT_TRUE(s.contains(s1.ibegin(),s1.iend()));
//  ASSERT_FALSE(s.contains(s2.ibegin(),s2.iend()));
//}
//
//
//TEST_F(SetTest, clear) {
//  SetType s(hash_str);
//  s.clear();
//  ASSERT_TRUE(s.empty());
//  ASSERT_EQ(0, s.size());
//  ASSERT_FALSE(s.contains("a"));
//
//  load(s,"a");
//  s.clear();
//  ASSERT_TRUE(s.empty());
//  ASSERT_EQ(0, s.size());
//  ASSERT_FALSE(s.contains("a"));
//
//  load(s,"ab");
//  s.clear();
//  ASSERT_TRUE(s.empty());
//  ASSERT_EQ(0, s.size());
//  ASSERT_FALSE(s.contains("a"));
//  ASSERT_FALSE(s.contains("b"));
//
//  load(s,"bac");
//  s.clear();
//  ASSERT_TRUE(s.empty());
//  ASSERT_EQ(0, s.size());
//  ASSERT_FALSE(s.contains("a"));
//  ASSERT_FALSE(s.contains("b"));
//  ASSERT_FALSE(s.contains("c"));
//
//  load(s,"dcba");
//  s.clear();
//  ASSERT_TRUE(s.empty());
//  ASSERT_EQ(0, s.size());
//  ASSERT_FALSE(s.contains("a"));
//  ASSERT_FALSE(s.contains("b"));
//  ASSERT_FALSE(s.contains("c"));
//  ASSERT_FALSE(s.contains("d"));
//
//  load(s,"bcead");
//  s.clear();
//  ASSERT_TRUE(s.empty());
//  ASSERT_EQ(0, s.size());
//  ASSERT_FALSE(s.contains("a"));
//  ASSERT_FALSE(s.contains("b"));
//  ASSERT_FALSE(s.contains("c"));
//  ASSERT_FALSE(s.contains("d"));
//  ASSERT_FALSE(s.contains("e"));
//}
//
//
//TEST_F(SetTest, erase) {
//  SetType s(hash_str);
//  load(s,"fcijbdegah");
//  ASSERT_EQ(1,s.erase("a"));
//  ASSERT_EQ(0,s.erase("x"));
//  ASSERT_TRUE(contains(s,"bcdefghij"));
//  ASSERT_TRUE(not_contains(s,"a"));
//  ASSERT_EQ(0,s.erase("a"));
//
//  ASSERT_EQ(1,s.erase("b"));
//  ASSERT_EQ(0,s.erase("x"));
//  ASSERT_TRUE(contains(s,"cdefghij"));
//  ASSERT_TRUE(not_contains(s,"ab"));
//  ASSERT_EQ(0,s.erase("b"));
//
//  ASSERT_EQ(1,s.erase("c"));
//  ASSERT_EQ(0,s.erase("x"));
//  ASSERT_TRUE(contains(s,"defghij"));
//  ASSERT_TRUE(not_contains(s,"abc"));
//  ASSERT_EQ(0,s.erase("c"));
//
//  ASSERT_EQ(1,s.erase("d"));
//  ASSERT_EQ(0,s.erase("x"));
//  ASSERT_TRUE(contains(s,"efghij"));
//  ASSERT_TRUE(not_contains(s,"abcd"));
//  ASSERT_EQ(0,s.erase("d"));
//
//  ASSERT_EQ(1,s.erase("e"));
//  ASSERT_EQ(0,s.erase("x"));
//  ASSERT_TRUE(contains(s,"fghij"));
//  ASSERT_TRUE(not_contains(s,"abcde"));
//  ASSERT_EQ(0,s.erase("e"));
//
//  ASSERT_EQ(1,s.erase("f"));
//  ASSERT_EQ(0,s.erase("x"));
//  ASSERT_TRUE(contains(s,"ghij"));
//  ASSERT_TRUE(not_contains(s,"abcdef"));
//  ASSERT_EQ(0,s.erase("f"));
//
//  ASSERT_EQ(1,s.erase("g"));
//  ASSERT_EQ(0,s.erase("x"));
//  ASSERT_TRUE(contains(s,"hij"));
//  ASSERT_TRUE(not_contains(s,"abcdefg"));
//  ASSERT_EQ(0,s.erase("g"));
//
//  ASSERT_EQ(1,s.erase("h"));
//  ASSERT_EQ(0,s.erase("x"));
//  ASSERT_TRUE(contains(s,"ij"));
//  ASSERT_TRUE(not_contains(s,"abcdefgh"));
//  ASSERT_EQ(0,s.erase("h"));
//
//  ASSERT_EQ(1,s.erase("i"));
//  ASSERT_EQ(0,s.erase("x"));
//  ASSERT_TRUE(contains(s,"j"));
//  ASSERT_TRUE(not_contains(s,"abcdefghi"));
//  ASSERT_EQ(0,s.erase("i"));
//
//  ASSERT_EQ(1,s.erase("j"));
//  ASSERT_EQ(0,s.erase("x"));
//  ASSERT_TRUE(not_contains(s,"abcdefghij"));
//  ASSERT_EQ(0,s.erase("j"));
//
//  ASSERT_EQ(0,s.erase("a"));
//  ASSERT_EQ(0,s.erase("e"));
//  ASSERT_EQ(0,s.erase("j"));
//
//  ASSERT_TRUE(s.empty());
//  ASSERT_EQ(0, s.size());
//}
//
//
//TEST_F(SetTest, erase_iterator_param) {
//  SetType s(hash_str),s1(hash_str),s2(hash_str);
//  load(s,"abcdefghij");
//  load(s1,"abdij");
//  ASSERT_EQ(5,s.erase(s1.ibegin(),s1.iend()));
//  ASSERT_FALSE(s.empty());
//  ASSERT_EQ(5, s.size());
//  load(s2,"cefgh");
//  ASSERT_EQ(s,s2);
//}
//
//
//TEST_F(SetTest, retains_iterator_param) {
//  SetType s(hash_str),s1(hash_str);
//  load(s,"abcdefghij");
//  load(s1,"abdij");
//  s.retain(s1.ibegin(),s1.iend());
//  ASSERT_EQ(s,s1);
//
//  s.clear();
//  s1.clear();
//  load(s,"abdij");
//  SetType s2(s);
//  load(s1,"abcdefghij");
//  s.retain(s1.ibegin(),s1.iend());
//  ASSERT_EQ(s,s2);
//
//  SetType s3(hash_str);
//  s.retain(s3.ibegin(),s3.iend());
//  ASSERT_EQ(s,s3);
//}
//
//
//TEST_F(SetTest, assignment) {
//  SetType s1(hash_str),s2(hash_str);
//  load(s2,"abcde");
//  s1 = s2;
//  ASSERT_EQ(s1,s2);
//
//  s2.clear();
//  load(s2,"ab");
//  s1 = s2;
//  ASSERT_EQ(s1,s2);
//
//  s2.clear();
//  load(s2,"abcdefghij");
//  s1 = s2;
//  ASSERT_EQ(s1,s2);
//
//}
//
//
//TEST_F(SetTest, iterator_plusplus) {
//  SetType s(hash_str),s_iter(hash_str);
//  load(s,"abcde");
//  ics::Iterator<std::string>& end = s.iend();
//
//  ics::Iterator<std::string>& i = s.ibegin();
//  s_iter.insert(*i);
//  for (int x=0; x<4; ++x) {
//    std::string out1 = *(++i);
//    std::string out2 = *i;
//    ASSERT_EQ(out1,out2);
//    s_iter.insert(out1);
//  }
//  ASSERT_EQ(end, ++i);
//  ASSERT_EQ(end, i);
//  ASSERT_EQ(end, ++i);
//  ASSERT_EQ(s,s_iter);
//
//  s_iter.clear();
//  ics::Iterator<std::string>& j = s.ibegin();
//  for (int x=0; x<5; ++x) {
//    std::string out1 = *j;
//    std::string out2 = *(j++);
//    ASSERT_EQ(out1,out2);
//    s_iter.insert(out1);
//  }
//  ASSERT_EQ(end, j);
//  ASSERT_EQ(end, j++);
//  ASSERT_EQ(end, j);
//  ASSERT_EQ(end, j++);
//  ASSERT_EQ(s,s_iter);
//}
//
//
//TEST_F(SetTest, iterator_simple) {
//  std::string qvalues[] ={"a","b","c","d","e","f","g","h","i","j"};
//  ics::ArrayPriorityQueue<std::string> q(gt_string);
//
//  SetType s(hash_str);
//  load(s,"abcdefghij");
//  SetType s2(s);
//
//  //for-each iterator (using .begin/.end)
//  for (std::string x : s)
//    q.enqueue(x);
//  int i = 0;
//  for (std::string x : q)
//    ASSERT_EQ(qvalues[i++],x);
//  ASSERT_EQ(10,s.size());
//
//  //explicit iterator (using .ibegin/.iend and ++it)
//  q.clear();
//  for (ics::Iterator<std::string>& it = s.ibegin(); it != s.iend(); ++it)
//    q.enqueue(*it);
//  i = 0;
//  for (std::string x : q)
//    ASSERT_EQ(qvalues[i++],x);
//  ASSERT_EQ(10,s.size());
//
//  //explicit iterator (using .ibegin/.iend and it++)
//  q.clear();
//  for (ics::Iterator<std::string>& it = s.ibegin(); it != s.iend(); it++)
//    q.enqueue(*it);
//  i = 0;
//  for (std::string x : q)
//    ASSERT_EQ(qvalues[i++],x);
//  ASSERT_EQ(10,s.size());
//
//  //all these iterations didn't change the set
//  ASSERT_EQ(s,s2);
//}
//
//
//TEST_F(SetTest, iterator_erase) {
//  std::vector<std::string> erased;
//  SetType s(hash_str);
//  load(s,"abcdefghihj");
//  ics::Iterator<std::string>& it = s.ibegin();
//
//  erased.push_back(it.erase());
//  ASSERT_THROW(it.erase(),ics::CannotEraseError);
//  ASSERT_THROW(*it,ics::IteratorPositionIllegal);
//
//  ++it;
//
//  ++it;
//  erased.push_back(it.erase());
//  ASSERT_THROW(it.erase(),ics::CannotEraseError);
//  ASSERT_THROW(*it,ics::IteratorPositionIllegal);
//  ++it;
//  erased.push_back(it.erase());
//  ASSERT_THROW(it.erase(),ics::CannotEraseError);
//  ASSERT_THROW(*it,ics::IteratorPositionIllegal);
//
//  ++it;
//
//  ++it;
//  erased.push_back(it.erase());
//  ASSERT_THROW(it.erase(),ics::CannotEraseError);
//  ASSERT_THROW(*it,ics::IteratorPositionIllegal);
//
//  ++it;
//  ++it;
//
//  ++it;
//  erased.push_back(it.erase());
//  ASSERT_THROW(it.erase(),ics::CannotEraseError);
//  ASSERT_THROW(*it,ics::IteratorPositionIllegal);
//  ++it;
//  erased.push_back(it.erase());
//  ASSERT_THROW(it.erase(),ics::CannotEraseError);
//  ASSERT_THROW(*it,ics::IteratorPositionIllegal);
//
//  ++it;
//  ASSERT_THROW(it.erase(),ics::CannotEraseError);
//  ASSERT_THROW(*it,ics::IteratorPositionIllegal);
//
//  SetType s2(hash_str);
//  load(s2,ics::join(erased));
//  ASSERT_EQ(6,s2.size());
//  for (std::string x : s2)
//    ASSERT_FALSE(s.contains(x));
//  for (std::string x : s)
//    ASSERT_FALSE(s2.contains(x));
//
//
//  //erase all in the set
//  s.clear();
//  load(s,"abcdefghihj");
//  for (ics::Iterator<std::string>& it = s.ibegin(); it != s.iend(); ++it)
//    ASSERT_FALSE(s.contains(it.erase()));
//  ASSERT_TRUE(s.empty());
//  ASSERT_EQ(0,s.size());
//}
//
//
//TEST_F(SetTest, iterator_exception_concurrent_modification_error) {
//  SetType s(hash_str);
//  load(s,"fcijbdegabh");
//  ics::Iterator<std::string>& it = s.ibegin();
//
//  s.erase("a");
//  ASSERT_THROW(it.erase(),ics::ConcurrentModificationError);
//  ASSERT_THROW(++it,ics::ConcurrentModificationError);
//  ASSERT_THROW(it++,ics::ConcurrentModificationError);
//  ASSERT_THROW(*it,ics::ConcurrentModificationError);
//}
//
//
//TEST_F(SetTest, constructors) {
//  SetType s(hash_str);
//  load(s,"fcijbdegah");
//  ASSERT_TRUE(contains(s,"abcdefghij"));
//
//  load(s,"fcijbdegah");
//  SetType s2(s);
//  ASSERT_TRUE(contains(s2,"abcdefghij"));
//  ASSERT_EQ(s,s2);
//  s.clear();
//  ASSERT_NE(s,s2);
//
//  load(s,"fcifjbdaegah");
//  SetType s3({"f", "c", "i", "f", "j", "b", "d", "a", "e", "g", "a", "h"},hash_str);
//  ASSERT_TRUE(contains(s3,"abcdefghij"));
//  ASSERT_EQ(s,s3);
//  s.clear();
//  ASSERT_NE(s,s3);
//
//  load(s,"fcifjbdaegah");
//  SetType s4(s.ibegin(),s.iend(),hash_str);
//  ASSERT_TRUE(contains(s4,"abcdefghij"));
//  ASSERT_EQ(s,s4);
//  s.clear();
//  ASSERT_NE(s,s4);
//}
//
//
//TEST_F(SetTest, large_scale) {
//  SetType2 ls(hash_int);
//  ics::ArraySet<int> ls_ref;
//
//
//  std::vector<int> values;
//  for (int i=0; i<test_size; ++i)
//    values.push_back(i);
//  std::random_shuffle(values.begin(),values.end());
//
//
//  for (int test=1; test<=5; ++test) {
//    int inserted = 0;
//    int erased   = 0;
//    while (erased != test_size) {
//      int to_insert = ics::rand_range(0,test_size-inserted);
//      if (trace)
//        std::cout << "Inserted " << to_insert << std::endl;
//      for (int i=0; i <to_insert; ++i) {
//        ls_ref.insert(values[inserted]);
//        ASSERT_EQ(1,ls.insert(values[inserted++]));
//      };
//      ASSERT_EQ(ls,ls_ref);
//
//      int to_erase = ics::rand_range(0,inserted-erased);
//      if (trace)
//        std::cout << "Erased " << to_erase << std::endl;
//      for (int i=0; i <to_erase; ++i) {
//        ASSERT_EQ(1,ls.erase(values[erased]));
//        ls_ref.erase(values[erased]);
//        ++erased;
//      }
//      ASSERT_EQ(ls,ls_ref);
//    }
//  }
//  ASSERT_TRUE(ls.empty());
//  ASSERT_EQ(0,ls.size());
//}
//
//
//TEST_F(SetTest, large_scale_speed) {
//  SetType2 ls(hash_int);
//
//  std::vector<int> values;
//  for (int i=0; i<speed_size; ++i)
//    values.push_back(i);
//  std::random_shuffle(values.begin(),values.end());
//
//  for (int test=1; test<=5; ++test) {
//    int inserted = 0;
//    int erased   = 0;
//    while (erased != speed_size) {
//      int to_insert = ics::rand_range(0,speed_size-inserted);
//      for (int i=0; i <to_insert; ++i)
//        ls.insert(values[inserted++] );
//      for (int v : ls)
//        ;
//
//      int to_erase = ics::rand_range(0,inserted-erased);
//      for (int i=0; i <to_erase; ++i)
//        ls.erase(values[erased++]);
//      for (int v : ls)
//        ;
//    }
//  }
//}
//
//
//int main(int argc, char **argv) {
//  ::testing::InitGoogleTest(&argc, argv);
//  return RUN_ALL_TESTS();
//}
