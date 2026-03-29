/*
  expecttest.cpp
  
  Author: Paul Hamilton (paul@visualops.com)
  Date: 29-Nov-2026
  
  Licensed under [version 3 of the GNU General Public License] contained in LICENSE.
 
  https://github.com/visualopsholdings/dict
*/


#include "dict.hpp"
#include "expect.hpp"

#include <boost/log/trivial.hpp>

#define BOOST_AUTO_TEST_MAIN
#include <boost/test/unit_test.hpp>

using namespace std;
using namespace vops;

auto obj = dictO({
  { "x", "a" },
  { "y", "b" },
  { "z", "hello" },
});
  
BOOST_AUTO_TEST_CASE( good1 )
{
  cout << "=== good1 ===" << endl;
  
  auto [good, x] = Expect(obj).values("x");
  
  BOOST_CHECK(good);
  BOOST_CHECK_EQUAL(x, "a");
 
}

BOOST_AUTO_TEST_CASE( bad1 )
{
  cout << "=== bad1 ===" << endl;
  
  auto [good, x] = Expect(obj).values("a");
  
  BOOST_CHECK(!good);
 
}

BOOST_AUTO_TEST_CASE( good2 )
{
  cout << "=== good2 ===" << endl;
  
  auto [good, x, y] = Expect(obj).values("x", "y");
  
  BOOST_CHECK(good);
  BOOST_CHECK_EQUAL(x, "a");
  BOOST_CHECK_EQUAL(y, "b");
 
}

BOOST_AUTO_TEST_CASE( bad2 )
{
  cout << "=== bad2 ===" << endl;
  
  auto [good, x, y] = Expect(obj).values("x", "a");
  
  BOOST_CHECK(!good);
 
}

BOOST_AUTO_TEST_CASE( good3 )
{
  cout << "=== good3 ===" << endl;
  
  auto [good, x, y, z] = Expect(obj).values("x", "y", "z");
  
  BOOST_CHECK(good);
  BOOST_CHECK_EQUAL(x, "a");
  BOOST_CHECK_EQUAL(y, "b");
  BOOST_CHECK_EQUAL(z, "hello");
 
}

BOOST_AUTO_TEST_CASE( bad3 )
{
  cout << "=== bad3 ===" << endl;
  
  auto [good, x, y, z] = Expect(obj).values("x", "a", "z");
  
  BOOST_CHECK(!good);
 
}

