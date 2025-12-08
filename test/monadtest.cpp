/*
  monadtest.cpp
  
  Author: Paul Hamilton (paul@visualops.com)
  Date: 17-Nov-2025
  
  Licensed under [version 3 of the GNU General Public License] contained in LICENSE.
 
  https://github.com/visualopsholdings/dict
*/


#include "dict.hpp"

#include <iostream>
#include <rfl/json.hpp>

#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>

#define BOOST_AUTO_TEST_MAIN
#include <boost/test/unit_test.hpp>

using namespace std;
using namespace vops;

void setupLog() {
  boost::log::core::get()->set_filter(boost::log::trivial::severity >= boost::log::trivial::debug);
}

auto simpleStringObj = dictO({ { "aaaa", "bbbb" } });
auto simpleNumObj = dictO({ { "aaaa", 42 } });
auto simpleBoolObj = dictO({ { "aaaa", true } });

DictV emptyV;
auto complexObj = dictO({
  { "accesses", DictV{
    dictO({
      { "name", "view" },
      { "groups", emptyV },
      { "users", DictV{"667d0baedfb1ed18430d8ed3"} }
    }),
    dictO({
      { "name", "edit" },
      { "groups", DictV{"667d0bae39ae84d0890a2141"} },
      { "users", emptyV }
    }),
    dictO({
      { "name", "exec" },
      { "groups", emptyV },
      { "users", DictV{"667d0baedfb1ed18430d8ed3", "667d0baedfb1ed18430d8ed4"} }
    })
  }}
});

BOOST_AUTO_TEST_CASE( simple )
{
  cout << "=== simple ===" << endl;
  
  setupLog();

  BOOST_CHECK_EQUAL(Dict(simpleStringObj).object("aaaa").string(), "bbbb");
  
}

BOOST_AUTO_TEST_CASE( simpleError )
{
  cout << "=== simpleError ===" << endl;

  setupLog();

  BOOST_CHECK(!Dict(simpleStringObj).object("aaaa").error());
  
}

BOOST_AUTO_TEST_CASE( missingElemData )
{
  cout << "=== missingElemData ===" << endl;

  setupLog();

  BOOST_CHECK_EQUAL(Dict(simpleStringObj).object("cccc").string(), "Err: cccc not found");
  
}

BOOST_AUTO_TEST_CASE( badElemTypeData )
{
  cout << "=== badElemTypeData ===" << endl;

  setupLog();

  BOOST_CHECK_EQUAL(Dict(simpleNumObj).object("aaaa").string(), "Err: not a string");
  
}

BOOST_AUTO_TEST_CASE( missingElemError )
{
  cout << "=== missingElemError ===" << endl;

  setupLog();

  auto elem = Dict(simpleStringObj).object("cccc");
  BOOST_CHECK(elem.error());
  BOOST_CHECK_EQUAL(*elem.error(), "Err: cccc not found");
  
}

BOOST_AUTO_TEST_CASE( missingPaths )
{
  cout << "=== missingPaths ===" << endl;

  setupLog();

  // it's a vector!
  BOOST_CHECK(Dict(complexObj).object("accesses").object("aaaaa").error());
  BOOST_CHECK_EQUAL(Dict(complexObj).object("accesses").object("aaaaa").string(), "Path: /accesses Err: Dict is not an object");
  
  // use the vector, but now it's a bad index.
  BOOST_CHECK_EQUAL(Dict(complexObj).object("accesses").vector(3).object("bbbbb").string(), "Path: /accesses Err: index 3 is invalid");
  
  // use the vector, but now it's a bad member.
  BOOST_CHECK_EQUAL(Dict(complexObj).object("accesses").vector(2).object("bbbbb").string(), "Path: /accesses/2 Err: bbbbb not found");
  
  // use the vector, but now it's a bad member.
  BOOST_CHECK_EQUAL(Dict(complexObj).object("accesses").vector(2).object("users").size(), 2);
  
}

BOOST_AUTO_TEST_CASE( boolean )
{
  cout << "=== boolean ===" << endl;
  
  setupLog();

  BOOST_CHECK(Dict(simpleBoolObj).object("aaaa").boolean());
  
}

BOOST_AUTO_TEST_CASE( num )
{
  cout << "=== num ===" << endl;
  
  setupLog();

  BOOST_CHECK_EQUAL(Dict(simpleNumObj).object("aaaa").num(), 42);
  
}


