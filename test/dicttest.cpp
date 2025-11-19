/*
  dicttest.cpp
  
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
  
  auto d = dictO({ { "hello", "world" } });
  
  auto hello = Dict::getString(d, "hello");
  
  BOOST_CHECK(hello);
  BOOST_CHECK_EQUAL(*hello, "world");
  
}

BOOST_AUTO_TEST_CASE( stringGTest )
{
  cout << "=== stringGTest ===" << endl;
  
  auto g = dictO({{ "hello", "world" }});
  
  auto hello = Dict::getStringG(g, "hello");
  
  BOOST_CHECK(hello);
  BOOST_CHECK_EQUAL(*hello, "world");
  
}

BOOST_AUTO_TEST_CASE( notString )
{
  cout << "=== notString ===" << endl;
  
  auto d = dictO({{ "hello", 42 }});
  
  BOOST_CHECK(!Dict::getString(d, "hello"));
  
}

BOOST_AUTO_TEST_CASE( num )
{
  cout << "=== num ===" << endl;
  
  auto d = dictO({{ "meaning", 42 }});
  
  auto meaning = Dict::getNum(d, "meaning");
  
  BOOST_CHECK(meaning);
  BOOST_CHECK_EQUAL(*meaning, 42);
  
}

BOOST_AUTO_TEST_CASE( numG )
{
  cout << "=== numG ===" << endl;
  
  DictG d = dictO({{ "meaning", 42 }});
  
  auto meaning = Dict::getNumG(d, "meaning");
  
  BOOST_CHECK(meaning);
  BOOST_CHECK_EQUAL(*meaning, 42);
  
}

BOOST_AUTO_TEST_CASE( bigNum )
{
  cout << "=== bigNum ===" << endl;
  
  long long bignum = 9223372036854775807;
  
  auto d = dictO({{ "big", bignum }});
  
  auto big = Dict::getNum(d, "big");
  
  BOOST_CHECK(big);
  BOOST_CHECK_EQUAL(*big, bignum);
  
}

BOOST_AUTO_TEST_CASE( notNum )
{
  cout << "=== notNum ===" << endl;
  
  auto d = dictO({ { "hello", "world" } });
  
  BOOST_CHECK(!Dict::getNum(d, "hello"));
  
}

BOOST_AUTO_TEST_CASE( boolTest )
{
  cout << "=== boolTest ===" << endl;
  
  auto d = dictO({ { "flag", true} });
  
  auto flag = Dict::getBool(d, "flag");
  
  BOOST_CHECK(flag);
  BOOST_CHECK_EQUAL(*flag, true);
  
}

BOOST_AUTO_TEST_CASE( notBool )
{
  cout << "=== notBool ===" << endl;
  
  auto d = dictO({ { "flag", 42 } });
  
  BOOST_CHECK(!Dict::getBool(d, "flag"));
  
}

BOOST_AUTO_TEST_CASE( object )
{
  cout << "=== object ===" << endl;
  
  auto d = dictO({
    { "obj", dictO({
      { "a", "hello" },
      { "b", 42 }
      })
    }
  });
  
  auto obj = Dict::getObject(d, "obj");
  BOOST_CHECK(obj);
  
}

BOOST_AUTO_TEST_CASE( vectorTest )
{
  cout << "=== vectorTest ===" << endl;
  
  auto d = dictO({
    { "v", DictV{ "hello", 42 } }
  });

  auto g = Dict::getGeneric(d, "v");
  BOOST_CHECK(g);
  BOOST_CHECK(Dict::isVector(*g));
  
  auto obj = Dict::getVector(d, "v");
  BOOST_CHECK(obj);
  
}

BOOST_AUTO_TEST_CASE( initialisation )
{
  cout << "=== initialisation ===" << endl;

  DictO o{dictO({ 
    { "xxx", dictO({ 
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

BOOST_AUTO_TEST_CASE( extraFields )
{
  cout << "=== extraFields ===" << endl;

  struct Obj {
    rfl::ExtraFields<rfl::Generic> extra_fields;
  };
  auto result = rfl::json::read<Obj>("{\"user\":\"6121bdfaec9e5a059715739c\"}");
  BOOST_CHECK(result);
  BOOST_CHECK_EQUAL(result->extra_fields.size(), 1);
  auto a = result->extra_fields.get("user");
  auto s = Dict::getString(a);
  BOOST_CHECK(s);
  BOOST_CHECK_EQUAL(*s, "6121bdfaec9e5a059715739c");

}






