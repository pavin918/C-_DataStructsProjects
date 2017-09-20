#ifndef DRIVER_SET_HPP_
#define DRIVER_SET_HPP_

#include <string>
#include <iostream>
#include <fstream>
#include "ics46goody.hpp"
#include "ics_exceptions.hpp"
#include "iterator.hpp"
#include "set.hpp"
#include "hash_set.hpp"


namespace ics {

typedef ics::HashSet<std::string> SetType;

class DriverSet {
  public:
    static int hash(const std::string& s) {std::hash<std::string> str_hash; return str_hash(s);}
    DriverSet() : s(hash) {process_commands("");}

  private:
    SetType s;

    SetType& prompt_set(std::string preface, std::string message = "  Enter element for s2") {
      static SetType s2(hash);
      s2.clear();
      for (;;) {
        std::string e = ics::prompt_string(preface + message + "(QUIT to quit)");
        if (e == "QUIT")
          break;
        s2.insert(e);
      }
      return s2;
    }

    std::string menu_prompt (std::string preface) {
      std::cout << "\n\n"+preface+"set s = " << s.str() << std::endl;
      std::cout << preface+"Mutators         Accessors              General" << std::endl;
      std::cout << preface+"  i  - insert      m  - empty             l  - load from file" << std::endl;
      std::cout << preface+"  I  - insert      s  - size              it - iterator commands" << std::endl;
      std::cout << preface+"  e  - erase       c  - contains          q  - quit" << std::endl;
      std::cout << preface+"  E  - erase       C  - contains"  << std::endl;
      std::cout << preface+"  x  - clear       <  - <<"        << std::endl;
      std::cout << preface+"  R  - retain      r  - relations" << std::endl;
      std::cout << preface+"  =  - ="      << std::endl;

      std::string allowable[] = {"i","I","e","E","x","R","=","m","s","c","C","<","r","l","it","q",""};
      return ics::prompt_string("\n"+preface+"Enter set command","",allowable);
    }

  void process_iterator_commands(SetType& s, std::string preface) {
    std::string allowable[] = {"<","e","*","+","+o","c","*a","ea","f","q",""};
    ics::Iterator<std::string>& i = s.abegin();
    for (;;)
      try {
        std::cout << "\n"+preface+"i = " << i.str() << std::endl;
        std::string i_command = ics::prompt_string(preface+
            "Enter iterator command(<[<]/e[rase]/*/+[+e]/+[+]o/c[ommands]/*a[ll]/ea[ll]/f[or]/q[uit])","",allowable);
        if (i_command == "<")
          std::cout << preface+"  << = " << i << std::endl;
        else if (i_command == "e")
          std::cout << preface+"  erase = " << i.erase() << std::endl;
        else if (i_command == "*")
          std::cout << preface+"  * = " << *i << std::endl;
        else if (i_command == "+")
          ++i;
        else if (i_command == "+o")
          i++;
        else if (i_command == "c")
          process_commands(preface);
        else if (i_command == "*a") {
          std::cout << preface+"  initially i = " << i << std::endl;
          for (; i != s.aend(); ++i)
            std::cout << preface+"  *(all) = " << *i << std::endl;
          std::cout << preface+"  finally i = " << i << std::endl;
        }
        else if (i_command == "ea") {
          std::cout << preface+"  initially i = " << i << std::endl;
         for (; i != s.aend(); ++i)
            std::cout << preface+"  erase(all) = " << i.erase() << std::endl;
          std::cout << preface+"  finally i = " << i << std::endl;
        }
        else if (i_command == "f") {
          for (auto v : s)
            std::cout << preface+"  *(all) = " << v << std::endl;
        }
        else if (i_command == "q")
          break;

      } catch (ics::IcsError& e) {
        std::cout << preface+"  " << e.what() << std::endl;
      }
  };


  void process_commands(std::string preface) {
    for (;;) try {
      std::string command = menu_prompt(preface);

      if (command == "i") {
        std::string e = ics::prompt_string(preface+"  Enter element to add");
        std::cout << preface+"  insert = " << s.insert(e) << std::endl;
      }

      else if (command == "I") {
        SetType s2(prompt_set(preface));
        std::cout << "  insert = " << s.insert(s2.abegin(),s2.aend()) << std::endl;;
      }

      else if (command == "e") {
        std::string e = ics::prompt_string(preface+"  Enter element to erase");
        std::cout << preface+"  erase = " << s.erase(e) << std::endl;
      }

      else if (command == "E") {
        SetType s2(prompt_set(preface));
        std::cout << "  erase = " << s.erase(s2.abegin(),s2.aend()) << std::endl;;
      }

      else if (command == "x")
        s.clear();

      else if (command == "R") {
        SetType s2(prompt_set(preface));
        std::cout << "  retain = " << s.retain(s2.abegin(),s2.aend()) << std::endl;
      }

      else if (command == "=") {
        SetType s2(prompt_set(preface));
        s = s2;
        std::cout << "  s now = " << s << std::endl;
      }

      else if (command == "m")
        std::cout << preface+"  empty = " << s.empty();

      else if (command == "s")
        std::cout << preface+"  size = " << s.size() << std::endl;


      else if (command == "c") {
        std::string e = ics::prompt_string(preface+"  Enter element to erase");
        std::cout << preface+"  contains = " << s.contains(e) << std::endl;
      }

      else if (command == "C") {
        SetType s2(prompt_set(preface));
        std::cout << "  contains = " << s.contains(s2.abegin(),s2.aend()) << std::endl;
      }

      else if (command == "<")
        std::cout << preface+"  << = " << s << std::endl;

      else if (command == "r") {
        std::cout << preface+"  s == s = " << (s == s) << std::endl;
        std::cout << preface+"  s != s = " << (s != s) << std::endl;
        std::cout << preface+"  s <= s = " << (s <= s) << std::endl;
        std::cout << preface+"  s <  s = " << (s <  s) << std::endl;
        std::cout << preface+"  s >  s = " << (s >  s) << std::endl;
        std::cout << preface+"  s >= s = " << (s >= s) << std::endl;

        SetType s2(prompt_set(preface));
        std::cout << preface+"  s = " << s << " ?? s2 = " << s2 << std::endl;
        std::cout << preface+"  s == s2 = " << (s == s2) << std::endl;
        std::cout << preface+"  s != s2 = " << (s != s2) << std::endl;
        std::cout << preface+"  s <= s2 = " << (s <= s2) << std::endl;
        std::cout << preface+"  s <  s2 = " << (s <  s2) << std::endl;
        std::cout << preface+"  s >  s2 = " << (s >  s2) << std::endl;
        std::cout << preface+"  s >= s2 = " << (s >= s2) << std::endl;
      }

      else if (command == "l") {
        std::ifstream in_set;
        ics::safe_open(in_set,preface+"  Enter file name to read", "load.txt");
        std::string e;
        while (getline(in_set,e))
          s.insert(e);
        in_set.close();
      }

      else if (command == "it")
        process_iterator_commands(s, "it:  "+preface);

      else if (command == "q")
        break;

      else
        std::cout << preface+"\""+command+"\" is unknown command" << std::endl;

    } catch (ics::IcsError& e) {
      std::cout << preface+"  " << e.what() << std::endl;
    }

  };


//void print_it(const ics::Set<std::string>& x) {
//  std::cout << "printing started" << std::endl;
//  std::cout << x <<std::endl;
//  std::cout << "printing done" << std::endl;
//}
//std::cout<<"Starting" << std::endl;
//SetType a;
//SetType b(1);
//SetType c(b);
//
//a.insert("a");
//a.insert("b");
//b = a;
//
//std::cout << b << "/" << a << std::endl;
////a.erase("a");
//std::cout << b << "/" << a << std::endl;
//print_it(a);
//SetType d(a.begin(),a.end());
////a.erase("a");
////a.clear();
//std::cout << a << "---" << d << std::endl;
//
////  a.erase(d.begin(),d.end());
////  std::cout << a << "---" << d << std::endl;
//
//std::cout << a.empty() << std::endl;
//std::cout << a.size() << std::endl;
//std::cout << a.contains("a") << std::endl;
//std::cout << a.str() << std::endl;
//std::cout << (a==b) << std::endl;
//std::cout << a << std::endl;
//
//SetType::ArraySetIterator x(&a,0);
//std::cout << x.str() << std::endl;
//std::cout << " * " << (*x) << std::endl;
//
//std::cout << ++x << std::endl;
//
//std::cout << x.str() << std::endl;
//std::cout << " * " << (*x) << std::endl;
//
//SetType::ArraySetIterator y(&a,0);
//std::cout << "equal?" << (x == y) << std::endl;
//y++;
//std::cout << "equal?" << (x == y) << std::endl;
//
//std::cout<<"Done" << std::endl;

};

}

#endif /* DRIVER_SET_HPP_ */
