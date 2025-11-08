/*
  simpletest.cpp
  
  Author: Paul Hamilton (paul@visualops.com)
  Date: 7-Nov-2025
  
  Licensed under [version 3 of the GNU General Public License] contained in LICENSE.
 
  https://github.com/visualopsholdings/dict
*/


#include "dict.hpp"

#include <iostream>
#include <rfl/json.hpp>

#define BOOST_AUTO_TEST_MAIN
#include <boost/test/unit_test.hpp>

using namespace std;
using namespace vops;

BOOST_AUTO_TEST_CASE( stringTest )
{
  cout << "=== stringTest ===" << endl;
  
  DictO d;
  d["hello"] = "world";
  
  auto hello = Dict::getString(d, "hello");
  
  BOOST_CHECK(hello);
  BOOST_CHECK_EQUAL(*hello, "world");
  
}

BOOST_AUTO_TEST_CASE( notString )
{
  cout << "=== notString ===" << endl;
  
  DictO d;
  d["hello"] = 42;
  
  BOOST_CHECK(!Dict::getString(d, "hello"));
  
}

BOOST_AUTO_TEST_CASE( num )
{
  cout << "=== num ===" << endl;
  
  DictO d;
  d["meaning"] = 42;
  
  auto meaning = Dict::getNum(d, "meaning");
  
  BOOST_CHECK(meaning);
  BOOST_CHECK_EQUAL(*meaning, 42);
  
}

BOOST_AUTO_TEST_CASE( notNum )
{
  cout << "=== notNum ===" << endl;
  
  DictO d;
  d["hello"] = "world";
  
  BOOST_CHECK(!Dict::getNum(d, "hello"));
  
}

BOOST_AUTO_TEST_CASE( boolTest )
{
  cout << "=== boolTest ===" << endl;
  
  DictO d;
  d["flag"] = true;
  
  auto flag = Dict::getBool(d, "flag");
  
  BOOST_CHECK(flag);
  BOOST_CHECK_EQUAL(*flag, true);
  
}

BOOST_AUTO_TEST_CASE( notBool )
{
  cout << "=== notBool ===" << endl;
  
  DictO d;
  d["flag"] = 42;
  
  BOOST_CHECK(!Dict::getBool(d, "flag"));
  
}

BOOST_AUTO_TEST_CASE( object )
{
  cout << "=== object ===" << endl;
  
  DictO d;
  DictO o;
  o["a"] = "hello";
  o["b"] = 42;  
  d["obj"] = o;
  
  auto obj = Dict::getObject(d, "obj");
  BOOST_CHECK(obj);
  
}

BOOST_AUTO_TEST_CASE( vectorTest )
{
  cout << "=== vectorTest ===" << endl;
  
  DictO d;
  DictV v;
  v.push_back("hello");
  v.push_back(42);
  d["v"] = v;
  
  auto g = Dict::getGeneric(d, "v");
  BOOST_CHECK(g);
  BOOST_CHECK(Dict::isVector(*g));
  
  auto obj = Dict::getVector(d, "v");
  BOOST_CHECK(obj);
  
}

BOOST_AUTO_TEST_CASE( initialisation )
{
  cout << "=== initialisation ===" << endl;

  DictO o{makeDictO({ 
    { "xxx", makeDictO({ 
        {"yyy", DictV{ "aaa", "bbb", "ccc"} } 
      }) 
    }
  })};
  auto s = Dict::toString(o);
  struct Obj {
    struct {
      vector<string> yyy;
    } xxx;
  };
  auto result = rfl::json::read<Obj>(s);
  BOOST_CHECK(result);
  BOOST_CHECK_EQUAL(result->xxx.yyy.size(), 3);
  BOOST_CHECK_EQUAL(result->xxx.yyy[0], "aaa");

}





