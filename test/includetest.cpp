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
  
  // make sure objects are retained.
  auto aaa = Dict::getString(*obj, "aaa");
  BOOST_CHECK(aaa);
  BOOST_CHECK_EQUAL(*aaa, "string");
  
  auto bbb = Dict::getNum(*obj, "bbb");
  BOOST_CHECK(bbb);
  BOOST_CHECK_EQUAL(*bbb, 1);
  
  auto ccc = Dict::getStringG((*v)[0], "ccc");
  BOOST_CHECK(ccc);
  BOOST_CHECK_EQUAL(*ccc, "string");
  
  auto ddd = Dict::getNumG((*v)[0], "ddd");
  BOOST_CHECK(ddd);
  BOOST_CHECK_EQUAL(*ddd, 2);
 
}
