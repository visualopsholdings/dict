/*
  difftest.cpp
  
  Author: Paul Hamilton (paul@visualops.com)
  Date: 2-Oct-2026
  
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

BOOST_AUTO_TEST_CASE( simple )
{
  cout << "=== simple ===" << endl;
  
  auto d1 = dictO({ { "hello", "world" }, { "aaa", 1 }, { "bbb", "x" } });
  auto d2 = dictO({ { "hello", "guy" }, { "aaa", 1 }, { "bbb", "x" } });
  
  auto diff = Dict::diff(d1, d2);
  BOOST_CHECK(diff);
//  cout << Dict::toString(*diff) << endl;
  auto s = Dict::getString(*diff, "hello");
  BOOST_CHECK_EQUAL(*s, "guy");
  
}

BOOST_AUTO_TEST_CASE( onlyIn1 )
{
  cout << "=== onlyIn1 ===" << endl;
  
  auto d1 = dictO({ { "hello", "world" }, { "aaa", 1 }, { "bbb", "x" } });
  auto d2 = dictO({ { "aaa", 1 }, { "bbb", "x" } });
  
  auto diff = Dict::diff(d1, d2);
  BOOST_CHECK(diff);
//  cout << Dict::toString(*diff) << endl;
  auto s = Dict::getString(*diff, "hello");
  BOOST_CHECK_EQUAL(*s, "world");
  
}

BOOST_AUTO_TEST_CASE( onlyIn2 )
{
  cout << "=== onlyIn2 ===" << endl;
  
  auto d1 = dictO({ { "aaa", 1 }, { "bbb", "x" } });
  auto d2 = dictO({ { "hello", "world" }, { "aaa", 1 }, { "bbb", "x" }  });
  
  auto diff = Dict::diff(d1, d2);
  BOOST_CHECK(diff);
//  cout << Dict::toString(*diff) << endl;
  auto s = Dict::getString(*diff, "hello");
  BOOST_CHECK_EQUAL(*s, "world");
  
}

BOOST_AUTO_TEST_CASE( same )
{
  cout << "=== same ===" << endl;
  
  auto d1 = dictO({ { "hello", "world" }, { "aaa", 1 }, { "bbb", "x" } });
  auto d2 = dictO({ { "hello", "world" }, { "aaa", 1 }, { "bbb", "x" } });
  
  auto diff = Dict::diff(d1, d2);
  BOOST_CHECK(!diff);
  
}

BOOST_AUTO_TEST_CASE( numDiff )
{
  cout << "=== numDiff ===" << endl;
  
  auto d1 = dictO({ { "hello", 1 }, { "aaa", 1 }, { "bbb", "x" } });
  auto d2 = dictO({ { "hello", 2 }, { "aaa", 1 }, { "bbb", "x" } });
  
  auto diff = Dict::diff(d1, d2);
  BOOST_CHECK(diff);
//  cout << Dict::toString(*diff) << endl;
  auto s = Dict::getNum(*diff, "hello");
  BOOST_CHECK_EQUAL(*s, 2 );
  
}

BOOST_AUTO_TEST_CASE( boolDiff )
{
  cout << "=== boolDiff ===" << endl;
  
  auto d1 = dictO({ { "hello", true }, { "aaa", 1 }, { "bbb", "x" } });
  auto d2 = dictO({ { "hello", false }, { "aaa", 1 }, { "bbb", "x" } });
  
  auto diff = Dict::diff(d1, d2);
  BOOST_CHECK(diff);
//  cout << Dict::toString(*diff) << endl;
  auto s = Dict::getBool(*diff, "hello");
  BOOST_CHECK(!*s);
  
}

BOOST_AUTO_TEST_CASE( objIgnore )
{
  cout << "=== boolDiff ===" << endl;
  
  auto d1 = dictO({ { "hello", dictO({ { "aaaa", 1 } }) }, { "aaa", 1 }, { "bbb", "x" } });
  auto d2 = dictO({ { "hello", dictO({ { "aaaa", 2 } }) }, { "aaa", 1 }, { "bbb", "x" } });
  
  auto diff = Dict::diff(d1, d2);
  BOOST_CHECK(!diff);
  
}

BOOST_AUTO_TEST_CASE( vecIgnore )
{
  cout << "=== vecIgnore ===" << endl;
  
  auto d1 = dictO({ { "hello", DictV{ "aaaa", 1 } }, { "aaa", 1 }, { "bbb", "x" } });
  auto d2 = dictO({ { "hello", DictV{ "aaaa", 2 } }, { "aaa", 1 }, { "bbb", "x" } });
  
  auto diff = Dict::diff(d1, d2);
  BOOST_CHECK(!diff);
  
}





