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
  BOOST_CHECK(result);
  BOOST_CHECK_EQUAL(*Dict::getString(*result), "yyy");

}
  
BOOST_AUTO_TEST_CASE( findObjPaths )
{
  cout << "=== findObjPaths ===" << endl;
  
  auto result = Dict::find_pointer(objPaths, objPathsPath);
  BOOST_CHECK(result);
  auto sss = Dict::getString(*result);
  BOOST_CHECK(sss);
  BOOST_CHECK_EQUAL(*sss, "eee");

}
  
BOOST_AUTO_TEST_CASE( findVecSimple )
{
  cout << "=== findVecSimple ===" << endl;
  
  auto result = Dict::find_pointer(vecSimple, vecSimplePath);
  BOOST_CHECK(result);
  auto sss = Dict::getString(*result);
  BOOST_CHECK(sss);
  BOOST_CHECK_EQUAL(*sss, "bbb");

}
  
BOOST_AUTO_TEST_CASE( findVecPaths )
{
  cout << "=== findVecPaths ===" << endl;
  
  auto result = Dict::find_pointer(vecPaths, vecPathsPath);
  BOOST_CHECK(result);
  auto sss = Dict::getString(*result);
  BOOST_CHECK(sss);
  BOOST_CHECK_EQUAL(*sss, "eee");

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
  BOOST_CHECK(!result);

}
  
BOOST_AUTO_TEST_CASE( findComplex )
{
  cout << "=== findComplex ===" << endl;
  
  auto result = Dict::find_pointer(complexObj, complexObjPath);
  BOOST_CHECK(result);
  auto v = result->to_array();
  BOOST_CHECK(v);
  BOOST_CHECK_EQUAL(v->size(), 2);
  BOOST_CHECK_EQUAL(v.value()[0].to_string().value(), "667d0baedfb1ed18430d8ed3");
  BOOST_CHECK_EQUAL(v.value()[1].to_string().value(), "667d0baedfb1ed18430d8ed4");
//  cout << Dict::toString(*result) << endl;
  
}

BOOST_AUTO_TEST_CASE( setObjSimple )
{
  cout << "=== setObjSimple ===" << endl;
  
  auto result = Dict::set_at_pointer(objSimple, objSimplePath, "111");
  BOOST_CHECK(result);
  BOOST_CHECK_EQUAL(result->to_object()->get("aaa")->to_string().value(), "xxx");
  BOOST_CHECK_EQUAL(result->to_object()->get("bbb")->to_string().value(), "111");
  BOOST_CHECK_EQUAL(result->to_object()->get("ccc")->to_string().value(), "zzz");
//  cout << Dict::toString(*result) << endl;

}
  
BOOST_AUTO_TEST_CASE( setObjPaths )
{
  cout << "=== setObjPaths ===" << endl;
  
  auto result = Dict::set_at_pointer(objPaths, objPathsPath, "111");
  BOOST_CHECK(result);
//  cout << Dict::toString(*result) << endl;
  BOOST_CHECK_EQUAL(result->to_object()->get("aaa")->to_object()->get("bbb")->to_object()->get("ccc")->to_object()->get("ddd")->to_string().value(), "111");
  BOOST_CHECK_EQUAL(result->to_object()->get("xxx")->to_string().value(), "yyy");
  BOOST_CHECK_EQUAL(result->to_object()->get("zzz")->to_string().value(), "222");

}
  
BOOST_AUTO_TEST_CASE( setVecSimple )
{
  cout << "=== setVecSimple ===" << endl;
  
  auto result = Dict::set_at_pointer(vecSimple, vecSimplePath, "111");
  BOOST_CHECK(result);
//  cout << Dict::toString(*result) << endl;
  BOOST_CHECK_EQUAL(result->to_array()->size(), 3);
  BOOST_CHECK_EQUAL(result->to_array().value()[0].to_string().value(), "aaa");
  BOOST_CHECK_EQUAL(result->to_array().value()[1].to_string().value(), "111");
  BOOST_CHECK_EQUAL(result->to_array().value()[2].to_string().value(), "ccc");

}
  
BOOST_AUTO_TEST_CASE( setVecPaths )
{
  cout << "=== setVecPaths ===" << endl;
  
  auto result = Dict::set_at_pointer(vecPaths, vecPathsPath, "111");
  BOOST_CHECK(result);
//  cout << Dict::toString(*result) << endl;
  auto aaa = result->to_object()->get("aaa")->to_array();
  BOOST_CHECK(aaa);
  BOOST_CHECK_EQUAL(aaa->size(), 3);
  BOOST_CHECK_EQUAL(aaa.value()[0].to_string().value(), "xxx");
  BOOST_CHECK_EQUAL(aaa.value()[2].to_string().value(), "zzz");

  auto ccc = aaa.value()[1].to_object()->get("bbb")->to_object()->get("ccc")->to_array();
  BOOST_CHECK(ccc);
  BOOST_CHECK_EQUAL(ccc->size(), 2);
  BOOST_CHECK_EQUAL(ccc.value()[1].to_string().value(), "111");

}
  
BOOST_AUTO_TEST_CASE( setComplex )
{
  cout << "=== setComplex ===" << endl;
  
  auto value = DictV{"667d0baedfb1ed18430d8ed4"};
  
  auto result = Dict::set_at_pointer(complexObj, complexObjPath, value);
  BOOST_CHECK(result);
//  cout << Dict::toString(*result) << endl;
  BOOST_CHECK_EQUAL(result->to_object()->get("accesses")->to_array().value()[2].to_object()->get("users")->to_array()->size(), 1);
  BOOST_CHECK_EQUAL(result->to_object()->get("accesses")->to_array().value()[2].to_object()->get("users")->to_array().value()[0].to_string().value(), "667d0baedfb1ed18430d8ed4");
  
}

BOOST_AUTO_TEST_CASE( monad )
{
  cout << "=== monad ===" << endl;

  // these should not crash, but they do.
//  auto result1 = complexObj.get("accesses")->to_object()->get("aaaaa")->to_object()->get("bbbbb");
  // should return an error (non value) that says accesses/aaaaa is not a thing.
  // and should look like this.
//  auto result = complexObj.get("accesses").object("aaaaa").object("bbbbb");
  
//  auto result2 = complexObj.get("accesses").value().to_array().value()[3].to_object()->get("users");
  // should return an error (non value) that says accesses/3 is not a thing.
  // and should look like this.
//  auto result = complexObj.get("accesses").array(3).object("users");

}


