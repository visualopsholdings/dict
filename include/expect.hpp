/*
  expect.hpp
  
  Author: Paul Hamilton (paul@visualops.com)
  Date: 29-Mar-2026
    
  Consise argument parsing.

  Licensed under [version 3 of the GNU General Public License] contained in LICENSE.
 
  https://github.com/visualopsholdings/dict
*/

#ifndef H_expect
#define H_expect

#include "dict.hpp"

#include <tuple>
#include <string>

namespace vops {

class Expect {
  
public:
  Expect(DictO &obj): _ref(obj) {};
    
  // I need to lesrn meta programming to build all this :-)
  std::tuple<bool, std::string> values(const std::string a1);
  std::tuple<bool, std::string, std::string> values(const std::string a1, const std::string a2);
  std::tuple<bool, std::string, std::string, std::string> values(const std::string a1, const std::string a2, const std::string a3);
 
private:
  DictO& _ref;
   
};

};

#endif // H_expect
