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

BOOST_AUTO_TEST_CASE( find_pointer )
{
  cout << "=== find_pointer ===" << endl;
  
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
  BOOST_CHECK(!result);
  
//  auto out = DictV{"667d0baedfb1ed18430d8ed3","667d0baedfb1ed18430d8ed4"};
  
}

BOOST_AUTO_TEST_CASE( set_at_pointer )
{
  cout << "=== set_at_pointer ===" << endl;
  
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
