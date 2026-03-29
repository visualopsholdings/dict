/*
  expect.cpp
  
  Author: Paul Hamilton (paul@visualops.com)
  Date: 29-Mar-2026
    
  Licensed under [version 3 of the GNU General Public License] contained in LICENSE.
 
  https://github.com/visualopsholdings/dict
*/

#include "expect.hpp"

#include <boost/log/trivial.hpp>

using namespace vops;
using namespace std;

tuple<bool, string> Expect::values(const string a1) const {
  auto v1 = Dict::getString(_obj, a1);
  if (!v1) {
    BOOST_LOG_TRIVIAL(error) << "missing " << a1;
    return make_tuple(false, "");
  }
  return make_tuple(true, *v1);
}

tuple<bool, string, string> Expect::values(const string a1, const string a2) const {
  auto v1 = Dict::getString(_obj, a1);
  if (!v1) {
    BOOST_LOG_TRIVIAL(error) << "missing " << a1;
    return make_tuple(false, "", "");
  }
  auto v2 = Dict::getString(_obj, a2);
  if (!v2) {
    BOOST_LOG_TRIVIAL(error) << "missing " << a2;
    return make_tuple(false, "", "");
  }
  return make_tuple(true, *v1, *v2);
}

tuple<bool, string, string, string> Expect::values(const string a1, const string a2, const string a3) const {
  auto v1 = Dict::getString(_obj, a1);
  if (!v1) {
    BOOST_LOG_TRIVIAL(error) << "missing " << a1;
    return make_tuple(false, "", "", "");
  }
  auto v2 = Dict::getString(_obj, a2);
  if (!v2) {
    BOOST_LOG_TRIVIAL(error) << "missing " << a2;
    return make_tuple(false, "", "", "");
  }
  auto v3 = Dict::getString(_obj, a3);
  if (!v3) {
    BOOST_LOG_TRIVIAL(error) << "missing " << a3;
    return make_tuple(false, "", "", "");
  }
  return make_tuple(true, *v1, *v2, *v3);
}

tuple<bool, string, string, string, string> Expect::values(const string a1, const string a2, const string a3, const string a4) const {
  auto v1 = Dict::getString(_obj, a1);
  if (!v1) {
    BOOST_LOG_TRIVIAL(error) << "missing " << a1;
    return make_tuple(false, "", "", "", "");
  }
  auto v2 = Dict::getString(_obj, a2);
  if (!v2) {
    BOOST_LOG_TRIVIAL(error) << "missing " << a2;
    return make_tuple(false, "", "", "", "");
  }
  auto v3 = Dict::getString(_obj, a3);
  if (!v3) {
    BOOST_LOG_TRIVIAL(error) << "missing " << a3;
    return make_tuple(false, "", "", "", "");
  }
  auto v4 = Dict::getString(_obj, a4);
  if (!v4) {
    BOOST_LOG_TRIVIAL(error) << "missing " << a4;
    return make_tuple(false, "", "", "", "");
  }
  return make_tuple(true, *v1, *v2, *v3, *v4);
}

tuple<bool, string, string, string, string, string> Expect::values(const string a1, const string a2, const string a3, const string a4, const string a5) const {
  auto v1 = Dict::getString(_obj, a1);
  if (!v1) {
    BOOST_LOG_TRIVIAL(error) << "missing " << a1;
    return make_tuple(false, "", "", "", "", "");
  }
  auto v2 = Dict::getString(_obj, a2);
  if (!v2) {
    BOOST_LOG_TRIVIAL(error) << "missing " << a2;
    return make_tuple(false, "", "", "", "", "");
  }
  auto v3 = Dict::getString(_obj, a3);
  if (!v3) {
    BOOST_LOG_TRIVIAL(error) << "missing " << a3;
    return make_tuple(false, "", "", "", "", "");
  }
  auto v4 = Dict::getString(_obj, a4);
  if (!v4) {
    BOOST_LOG_TRIVIAL(error) << "missing " << a4;
    return make_tuple(false, "", "", "", "", "");
  }
  auto v5 = Dict::getString(_obj, a5);
  if (!v5) {
    BOOST_LOG_TRIVIAL(error) << "missing " << a5;
    return make_tuple(false, "", "", "", "", "");
  }
  return make_tuple(true, *v1, *v2, *v3, *v4, *v5);
}
