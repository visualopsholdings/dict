/*
  ptrtest.cpp
  
  Author: Paul Hamilton (paul@visualops.com)
  Date: 13-Nov-2025
  
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

auto objSimple = dictO({
  { "aaa", "xxx" },
  { "bbb", "yyy" },
  { "ccc", "zzz" }
});
auto objSimplePath = "/bbb";

auto objPaths = dictO({
  { "aaa", dictO({
    { "bbb", dictO({
      { "ccc", dictO({
        { "ddd", "eee" }
        })  
      }
      })  
    }
    }) 
  },
  { "xxx", "yyy" },
  { "zzz", "222" }
});
auto objPathsPath = "/aaa/bbb/ccc/ddd";

auto vecSimple = DictV({ "aaa", "bbb", "ccc" });
auto vecSimplePath = "/1";

auto vecPaths = dictO({
  { "aaa", DictV{
    "xxx",
    dictO({ 
      { "bbb", dictO({
        { "ccc", DictV{ "ddd", "eee" } }
      })  
      }
    }),
    "zzz"
  }
  }
});

string vecPathsPath = "/aaa/1/bbb/ccc/1";

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
string complexObjPath = "/accesses/2/users";

BOOST_AUTO_TEST_CASE( findObjSimple )
{
  cout << "=== findObjSimple ===" << endl;
  
  auto result = Dict::find_pointer(objSimple, objSimplePath);
  BOOST_CHECK_EQUAL(Dict(result).string(), "yyy");

}
  
BOOST_AUTO_TEST_CASE( findObjPaths )
{
  cout << "=== findObjPaths ===" << endl;
  
  auto result = Dict::find_pointer(objPaths, objPathsPath);
  BOOST_CHECK_EQUAL(Dict(result).string(), "eee");

}
  
BOOST_AUTO_TEST_CASE( findVecSimple )
{
  cout << "=== findVecSimple ===" << endl;
  
  auto result = Dict::find_pointer(vecSimple, vecSimplePath);
  BOOST_CHECK_EQUAL(Dict(result).string(), "bbb");

}
  
BOOST_AUTO_TEST_CASE( findVecPaths )
{
  cout << "=== findVecPaths ===" << endl;
  
  auto result = Dict::find_pointer(vecPaths, vecPathsPath);
  BOOST_CHECK_EQUAL(Dict(result).string(), "eee");

}
  
BOOST_AUTO_TEST_CASE( findVecIndexError )
{
  cout << "=== findVecIndexError ===" << endl;
  
  auto input = dictO({
    { "aaa", DictV{
      dictO({ 
        { "bbb", dictO({
          { "ccc", DictV{ "ddd", "eee" } }
        })  
        }
      })
    }
    }
  });

  string path = "/aaa/1/bbb/ccc/1";
  auto result = Dict::find_pointer(input, path);
  BOOST_CHECK(Dict(result).error());

}
  
BOOST_AUTO_TEST_CASE( findComplex )
{
  cout << "=== findComplex ===" << endl;
  
  auto result = Dict::find_pointer(complexObj, complexObjPath);
  BOOST_CHECK_EQUAL(Dict(result).size(), 2);
  BOOST_CHECK_EQUAL(Dict(result).vector(0).string(), "667d0baedfb1ed18430d8ed3");
  BOOST_CHECK_EQUAL(Dict(result).vector(1).string(), "667d0baedfb1ed18430d8ed4");
//  cout << Dict::toString(*result) << endl;
  
}

BOOST_AUTO_TEST_CASE( setObjSimple )
{
  cout << "=== setObjSimple ===" << endl;
  
  auto result = Dict::set_at_pointer(objSimple, objSimplePath, "111");
  BOOST_CHECK_EQUAL(Dict(result).object("aaa").string(), "xxx");
  BOOST_CHECK_EQUAL(Dict(result).object("bbb").string(), "111");
  BOOST_CHECK_EQUAL(Dict(result).object("ccc").string(), "zzz");
//  cout << Dict::toString(*result) << endl;

}
  
BOOST_AUTO_TEST_CASE( setObjPaths )
{
  cout << "=== setObjPaths ===" << endl;
  
  auto result = Dict::set_at_pointer(objPaths, objPathsPath, "111");
//  cout << Dict::toString(*result) << endl;
  BOOST_CHECK_EQUAL(Dict(result).object("aaa").object("bbb").object("ccc").object("ddd").string(), "111");
  BOOST_CHECK_EQUAL(Dict(result).object("xxx").string(), "yyy");
  BOOST_CHECK_EQUAL(Dict(result).object("zzz").string(), "222");

}
  
BOOST_AUTO_TEST_CASE( setVecSimple )
{
  cout << "=== setVecSimple ===" << endl;
  
  auto result = Dict::set_at_pointer(vecSimple, vecSimplePath, "111");
//  cout << Dict::toString(*result) << endl;
  BOOST_CHECK_EQUAL(Dict(result).size(), 3);
  BOOST_CHECK_EQUAL(Dict(result).vector(0).string(), "aaa");
  BOOST_CHECK_EQUAL(Dict(result).vector(1).string(), "111");
  BOOST_CHECK_EQUAL(Dict(result).vector(2).string(), "ccc");

}
  
BOOST_AUTO_TEST_CASE( setVecPaths )
{
  cout << "=== setVecPaths ===" << endl;
  
  auto result = Dict::set_at_pointer(vecPaths, vecPathsPath, "111");
//  cout << Dict::toString(*result) << endl;
  auto aaa = Dict(result).object("aaa").vector();
  BOOST_CHECK_EQUAL(aaa.size(), 3);
  BOOST_CHECK_EQUAL(Dict(aaa).vector(0).string(), "xxx");
  BOOST_CHECK_EQUAL(Dict(aaa).vector(2).string(), "zzz");

  auto ccc = Dict(aaa).vector(1).object("bbb").object("ccc").vector();
  BOOST_CHECK_EQUAL(ccc.size(), 2);
  BOOST_CHECK_EQUAL(Dict(ccc).vector(1).string(), "111");

}
  
BOOST_AUTO_TEST_CASE( setComplex )
{
  cout << "=== setComplex ===" << endl;
  
  auto value = DictV{"667d0baedfb1ed18430d8ed4"};
  
  auto result = Dict::set_at_pointer(complexObj, complexObjPath, value);
//  cout << Dict::toString(*result) << endl;
  BOOST_CHECK_EQUAL(Dict(result).object("accesses").vector(2).object("users").size(), 1);
  BOOST_CHECK_EQUAL(Dict(result).object("accesses").vector(2).object("users").vector(0).string(), "667d0baedfb1ed18430d8ed4");
  
}
