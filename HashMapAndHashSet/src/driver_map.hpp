#ifndef DRIVER_MAP_HPP_
#define DRIVER_MAP_HPP_

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include "ics46goody.hpp"
#include "ics_exceptions.hpp"
#include "iterator.hpp"
#include "map.hpp"
#include "hash_map.hpp"


namespace ics {

typedef ics::pair<std::string,std::string>    MapEntry;
typedef ics::HashMap<std::string,std::string> MapType;

class DriverMap {
  public:
    static int hash(const std::string& s) {std::hash<std::string> str_hash; return str_hash(s);}
    DriverMap() : m(hash)
    {process_commands("");}

  private:
    MapType m;

    MapType& prompt_map(std::string preface, std::string message = "  Enter element for m2") {
      static MapType m2(hash);
      m2.clear();
      for (;;) {
        std::string k = ics::prompt_string(preface + message + "key (QUIT to quit)");
        if (k == "QUIT")
          break;
        std::string v = ics::prompt_string(preface + message + "value");
        m2.put(k,v);
      }
      return m2;
    }

    std::string menu_prompt (std::string preface) {
      std::cout << "\n\n"+preface+"map m = " << m.str() << std::endl;
      std::cout << preface+"Mutators         Accessors              General" << std::endl;
      std::cout << preface+"  [  - put:[]      g  - get:[]            lf - load from file"    << std::endl;
      std::cout << preface+"  p  - put         m  - empty             l{ - load from {}"      << std::endl;
      std::cout << preface+"  P  - put         s  - size              it - iterator commands" << std::endl;
      std::cout << preface+"  e  - erase       k  - contains_key      q  - quit"              << std::endl;
      std::cout << preface+"  x  - clear       v  - contains_value" << std::endl;
      std::cout << preface+"  =  - =           <  - <<"             << std::endl;
      std::cout << preface+"                   r  - relations"      << std::endl;

      std::string allowable[] = {"[","p","P","e","x","=","g","m","s","k","v","<","r","lf","l{","it","q",""};
      return ics::prompt_string("\n"+preface+"Enter set command","",allowable);
    }

  void process_iterator_commands(MapType& m, std::string preface) {
    std::string allowable[] = {"<","e","*","+","+o","c","*a","ea","f","q",""};
    ics::Iterator<MapEntry>& i = m.ibegin();
    for (;;)
      try {
        std::cout << "\n"+preface+"i = " << i.str() << std::endl;
        std::string i_command = ics::prompt_string(preface+
            "Enter iterator command(<[<]/e[rase]/*/+[+e]/+[+]o/c[ommands]/*a[ll]/ea[ll]/f[or]/q[uit])","",allowable);
        if (i_command == "<")
          std::cout << preface+"  << = " << i << std::endl;
        else if (i_command == "e") {
          MapEntry erased = i.erase();
          std::cout << preface+"  erase = " << erased.first << "->" << erased.second << std::endl;
        }
        else if (i_command == "*") {
          MapEntry& erased = *i;
          std::cout << preface+"  * = " << erased.first << "->" << erased.second << std::endl;
        }
        else if (i_command == "+")
          ++i;
        else if (i_command == "+o")
          i++;
        else if (i_command == "c")
          process_commands(preface);
        else if (i_command == "*a") {
          std::cout << preface+"  initially i = " << i << std::endl;
          for (; i != m.iend(); ++i)
            std::cout << preface+"  *(all) = " << (*i).first << "->" << (*i).second << std::endl;
          std::cout << preface+"  finally i = " << i << std::endl;
        }
        else if (i_command == "ea") {
          std::cout << preface+"  initially i = " << i << std::endl;
          for (; i != m.iend(); ++i) {
            MapEntry erased = i.erase();
            std::cout << preface+"  erase(all) = " << erased.first << "->" << erased.second << std::endl;
          }
          std::cout << preface+"  finally i = " << i << std::endl;
        }
        else if (i_command == "f") {
          for (auto/*MapEntry*/ me : m)
            std::cout << preface+"  *(all) = " << me.first << "->" << me.second << std::endl;
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

      if (command == "[") {
        std::string k = ics::prompt_string(preface+"  Enter key   to put");
        std::string v = ics::prompt_string(preface+"  Enter value to put");
        std::cout << preface+"  m[k]=v = " << (m[k]=v) << std::endl;
      }

      else if (command == "p") {
        std::string k = ics::prompt_string(preface+"  Enter key   to put");
        std::string v = ics::prompt_string(preface+"  Enter value to put");
        std::cout << preface+"  put = " << m.put(k,v) << std::endl;
      }

      else if (command == "P") {
        MapType m2(prompt_map(preface));
        std::cout << preface+"  put = " << m.put(m2.ibegin(),m2.iend()) << std::endl;
      }

      else if (command == "e") {
        std::string e = ics::prompt_string(preface+"  Enter key to erase");
        std::cout << preface+"  erase = " << m.erase(e) << std::endl;
      }

      else if (command == "x")
        m.clear();

      else if (command == "=") {
        MapType m2(prompt_map(preface));
        m = m2;
        std::cout << "  s now = " << m << std::endl;
      }

      else if (command == "g") {
        std::string k = ics::prompt_string(preface+"  Enter key to get");
        std::cout << preface+"  get = " << m[k] << std::endl;
      }

      else if (command == "m")
        std::cout << preface+"  empty = " << m.empty();

      else if (command == "s")
        std::cout << preface+"  size = " << m.size() << std::endl;

      else if (command == "k") {
        std::string k = ics::prompt_string(preface+"  Enter key to check");
        std::cout << preface+"  contains_key = " << m.has_key(k) << std::endl;
      }

      else if (command == "v") {
        std::string v = ics::prompt_string(preface+"  Enter value to check");
        std::cout << preface+"  contains_value = " << m.has_value(v) << std::endl;
      }

      else if (command == "<")
        std::cout << preface+"  << = " << m << std::endl;

      else if (command == "r") {
        std::cout << preface+"  m == m = " << (m == m) << std::endl;
        std::cout << preface+"  m != m = " << (m != m) << std::endl;

        MapType m2(prompt_map(preface));
        std::cout << preface+"  m = " << m << " ?? m2 = " << m2 << std::endl;
        std::cout << preface+"  m == m2 = " << (m == m2) << std::endl;
        std::cout << preface+"  m != m2 = " << (m != m2) << std::endl;
      }

      else if (command == "l") {
        std::ifstream in_set;
        ics::safe_open(in_set,preface+"  Enter file name to read", "loadmap.txt");
        std::string line;
        while (getline(in_set,line)) {
          std::vector<std::string> line_2 = ics::split(line,";");
          std::string k = line_2[0];
          std::string v = line_2[1];
          m.put(k,v);
        }
        in_set.close();
      }

      else if (command == "l{") {
        MapType temp({MapEntry("a","1"), MapEntry("b","2"), MapEntry("c","3"), MapEntry("d","4"), MapEntry("e","5")},hash);
        m = temp;
      }

      else if (command == "it")
        process_iterator_commands(m, "it:  "+preface);

      else if (command == "q")
        break;

      else
        std::cout << preface+"\""+command+"\" is unknown command" << std::endl;

    } catch (ics::IcsError& e) {
      std::cout << preface+"  " << e.what() << std::endl;
    }

  };

};

}

#endif /* DRIVER_MAP_HPP_ */
