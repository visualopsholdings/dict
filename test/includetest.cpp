/*
  includetest.cpp
  
  Author: Paul Hamilton (paul@visualops.com)
  Date: 27-Jun-2026
  
  Licensed under [version 3 of the GNU General Public License] contained in LICENSE.
 
  https://github.com/visualopsholdings/dict
*/


#include "dict.hpp"

#include <boost/log/trivial.hpp>

#define BOOST_AUTO_TEST_MAIN
#include <boost/test/unit_test.hpp>

using namespace std;
using namespace vops;

BOOST_AUTO_TEST_CASE( simple )
{
  cout << "=== simple ===" << endl;
 
  std::filesystem::path path = "../dict-src/test";
  if (!std::filesystem::exists(path)) {
    path = "../test";
  }


  auto d = Dict::parseFile(path / "include.json");
  BOOST_CHECK(d);
  cout << Dict::toString(*d) << endl;
  auto v = Dict::getVector(*d);
  BOOST_CHECK(v);
  BOOST_CHECK_EQUAL(v->size(), 1);
  auto obj = Dict::getObjectG((*v)[0], "obj");
  BOOST_CHECK(obj);
  auto name = Dict::getString(*obj, "name");
  BOOST_CHECK(name);
  BOOST_CHECK_EQUAL(*name, "included obj");
  
  auto s = Dict::getStringG((*v)[0], "teststring");
  BOOST_CHECK(s);
  BOOST_CHECK_EQUAL(*s, "string");
  
  auto n = Dict::getNumG((*v)[0], "testnum");
  BOOST_CHECK(n);
  BOOST_CHECK_EQUAL(*n, 1);
 
}
