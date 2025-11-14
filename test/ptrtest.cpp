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

BOOST_AUTO_TEST_CASE( findObjSimple )
{
  cout << "=== findObjSimple ===" << endl;
  
  auto input = dictO({
    { "aaa", "bbb" }
  });
  string path = "/aaa";
  auto result = Dict::find_pointer(input, path);
  BOOST_CHECK(result);
  auto sss = Dict::getString(*result);
  BOOST_CHECK(sss);
  BOOST_CHECK_EQUAL(*sss, "bbb");

}
  
BOOST_AUTO_TEST_CASE( findObjPaths )
{
  cout << "=== findObjPaths ===" << endl;
  
  auto input = dictO({
    { "aaa", dictO({
      { "bbb", dictO({
        { "ccc", dictO({
          { "ddd", "eee" }
          })  
        }
        })  
      }
      }) 
    }
  });
  string path = "/aaa/bbb/ccc/ddd";
  auto result = Dict::find_pointer(input, path);
  BOOST_CHECK(result);
  auto sss = Dict::getString(*result);
  BOOST_CHECK(sss);
  BOOST_CHECK_EQUAL(*sss, "eee");

}
  
BOOST_AUTO_TEST_CASE( findVecSimple )
{
  cout << "=== findVecSimple ===" << endl;
  
  auto input = DictV({ "aaa", "bbb" });
  string path = "/1";
  auto result = Dict::find_pointer(input, path);
  BOOST_CHECK(result);
  auto sss = Dict::getString(*result);
  BOOST_CHECK(sss);
  BOOST_CHECK_EQUAL(*sss, "bbb");

}
  
BOOST_AUTO_TEST_CASE( findVecPaths )
{
  cout << "=== findVecPaths ===" << endl;
  
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

  string path = "/aaa/0/bbb/ccc/1";
  auto result = Dict::find_pointer(input, path);
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
  
  DictV empty;
  auto input = dictO({
    { "accesses", DictV{
      dictO({
        { "name", "view" },
        { "groups", empty },
        { "users", DictV{"667d0baedfb1ed18430d8ed3"} }
      }),
      dictO({
        { "name", "edit" },
        { "groups", DictV{"667d0bae39ae84d0890a2141"} },
        { "users", empty }
      }),
      dictO({
        { "name", "exec" },
        { "groups", empty },
        { "users", DictV{"667d0baedfb1ed18430d8ed3", "667d0baedfb1ed18430d8ed4"} }
      })
    }}
  });
  string path = "/accesses/2/users";
  
  auto result = Dict::find_pointer(input, path);
  BOOST_CHECK(result);
  auto v = Dict::getVector(*result);
  BOOST_CHECK(v);
  BOOST_CHECK_EQUAL(v->size(), 2);
  BOOST_CHECK_EQUAL(*Dict::getString((*v)[0]), "667d0baedfb1ed18430d8ed3");
  BOOST_CHECK_EQUAL(*Dict::getString((*v)[1]), "667d0baedfb1ed18430d8ed4");
//  cout << Dict::toString(*result) << endl;
  
}

BOOST_AUTO_TEST_CASE( setComplex )
{
  cout << "=== setComplex ===" << endl;
  
  DictV empty;
  auto input = dictO({
    { "accesses", DictV{
      dictO({
        { "name", "view" },
        { "groups", empty },
        { "users", DictV{"667d0baedfb1ed18430d8ed3"} }
      }),
      dictO({
        { "name", "edit" },
        { "groups", DictV{"667d0bae39ae84d0890a2141"} },
        { "users", empty }
      }),
      dictO({
        { "name", "exec" },
        { "groups", empty },
        { "users", DictV{"667d0baedfb1ed18430d8ed3", "667d0baedfb1ed18430d8ed4"} }
      })
    }}
  });
  string path = "/accesses/2/users";
  auto value = DictV{"667d0baedfb1ed18430d8ed4"};
  
  auto result = Dict::set_at_pointer(input, path, value);
  BOOST_CHECK(!result);
  
//   auto out = dictO({
//     { "accesses", DictV{
//       dictO({
//         { "name", "view" },
//         { "groups", empty },
//         { "users", DictV{"667d0baedfb1ed18430d8ed3"} }
//       }),
//       dictO({
//         { "name", "edit" },
//         { "groups", DictV{"667d0bae39ae84d0890a2141"} },
//         { "users", empty }
//       }),
//       dictO({
//         { "name", "exec" },
//         { "groups", empty },
//         { "users", DictV{"667d0baedfb1ed18430d8ed4"} }
//       })
//     }}
//   });
  
}
