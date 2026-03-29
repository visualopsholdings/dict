/*
  expect.cpp
  
  Author: Paul Hamilton (paul@visualops.com)
  Date: 29-Mar-2026
    
  Licensed under [version 3 of the GNU General Public License] contained in LICENSE.
 
  https://github.com/visualopsholdings/dict
*/

#include "expect.hpp"

using namespace vops;
using namespace std;

tuple<bool, string> Expect::values(const string a1) {
  auto v1 = Dict::getString(_ref, a1);
  if (!v1) {
    return make_tuple(false, "");
  }
  return make_tuple(true, *v1);
}

tuple<bool, string, string> Expect::values(const string a1, const string a2) {
  auto v1 = Dict::getString(_ref, a1);
  if (!v1) {
    return make_tuple(false, "", "");
  }
  auto v2 = Dict::getString(_ref, a2);
  if (!v2) {
    return make_tuple(false, "", "");
  }
  return make_tuple(true, *v1, *v2);
}

tuple<bool, string, string, string> Expect::values(const string a1, const string a2, const string a3) {
  auto v1 = Dict::getString(_ref, a1);
  if (!v1) {
    return make_tuple(false, "", "", "");
  }
  auto v2 = Dict::getString(_ref, a2);
  if (!v2) {
    return make_tuple(false, "", "", "");
  }
  auto v3 = Dict::getString(_ref, a3);
  if (!v3) {
    return make_tuple(false, "", "", "");
  }
  return make_tuple(true, *v1, *v2, *v3);
}
