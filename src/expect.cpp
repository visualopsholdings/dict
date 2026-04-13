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

tuple<bool, string, string, string, string, string, string> Expect::values(const string a1, const string a2, const string a3, const string a4, const string a5, const string a6) const {
  auto v1 = Dict::getString(_obj, a1);
  if (!v1) {
    BOOST_LOG_TRIVIAL(error) << "missing " << a1;
    return make_tuple(false, "", "", "", "", "", "");
  }
  auto v2 = Dict::getString(_obj, a2);
  if (!v2) {
    BOOST_LOG_TRIVIAL(error) << "missing " << a2;
    return make_tuple(false, "", "", "", "", "", "");
  }
  auto v3 = Dict::getString(_obj, a3);
  if (!v3) {
    BOOST_LOG_TRIVIAL(error) << "missing " << a3;
    return make_tuple(false, "", "", "", "", "", "");
  }
  auto v4 = Dict::getString(_obj, a4);
  if (!v4) {
    BOOST_LOG_TRIVIAL(error) << "missing " << a4;
    return make_tuple(false, "", "", "", "", "", "");
  }
  auto v5 = Dict::getString(_obj, a5);
  if (!v5) {
    BOOST_LOG_TRIVIAL(error) << "missing " << a5;
    return make_tuple(false, "", "", "", "", "", "");
  }
  auto v6 = Dict::getString(_obj, a6);
  if (!v6) {
    BOOST_LOG_TRIVIAL(error) << "missing " << a6;
    return make_tuple(false, "", "", "", "", "", "");
  }
  return make_tuple(true, *v1, *v2, *v3, *v4, *v5, *v6);
}

tuple<bool, string, string, string, string, string, string, string> Expect::values(const string a1, const string a2, const string a3, const string a4, const string a5, const string a6, const string a7) const {
  auto v1 = Dict::getString(_obj, a1);
  if (!v1) {
    BOOST_LOG_TRIVIAL(error) << "missing " << a1;
    return make_tuple(false, "", "", "", "", "", "", "");
  }
  auto v2 = Dict::getString(_obj, a2);
  if (!v2) {
    BOOST_LOG_TRIVIAL(error) << "missing " << a2;
    return make_tuple(false, "", "", "", "", "", "", "");
  }
  auto v3 = Dict::getString(_obj, a3);
  if (!v3) {
    BOOST_LOG_TRIVIAL(error) << "missing " << a3;
    return make_tuple(false, "", "", "", "", "", "", "");
  }
  auto v4 = Dict::getString(_obj, a4);
  if (!v4) {
    BOOST_LOG_TRIVIAL(error) << "missing " << a4;
    return make_tuple(false, "", "", "", "", "", "", "");
  }
  auto v5 = Dict::getString(_obj, a5);
  if (!v5) {
    BOOST_LOG_TRIVIAL(error) << "missing " << a5;
    return make_tuple(false, "", "", "", "", "", "", "");
  }
  auto v6 = Dict::getString(_obj, a6);
  if (!v6) {
    BOOST_LOG_TRIVIAL(error) << "missing " << a6;
    return make_tuple(false, "", "", "", "", "", "", "");
  }
  auto v7 = Dict::getString(_obj, a7);
  if (!v7) {
    BOOST_LOG_TRIVIAL(error) << "missing " << a7;
    return make_tuple(false, "", "", "", "", "", "", "");
  }
  return make_tuple(true, *v1, *v2, *v3, *v4, *v5, *v6, *v7);
}

tuple<bool, string, string, string, string, string, string, string, string> Expect::values(const string a1, const string a2, const string a3, const string a4, const string a5, const string a6, const string a7, const string a8) const {
  auto v1 = Dict::getString(_obj, a1);
  if (!v1) {
    BOOST_LOG_TRIVIAL(error) << "missing " << a1;
    return make_tuple(false, "", "", "", "", "", "", "", "");
  }
  auto v2 = Dict::getString(_obj, a2);
  if (!v2) {
    BOOST_LOG_TRIVIAL(error) << "missing " << a2;
    return make_tuple(false, "", "", "", "", "", "", "", "");
  }
  auto v3 = Dict::getString(_obj, a3);
  if (!v3) {
    BOOST_LOG_TRIVIAL(error) << "missing " << a3;
    return make_tuple(false, "", "", "", "", "", "", "", "");
  }
  auto v4 = Dict::getString(_obj, a4);
  if (!v4) {
    BOOST_LOG_TRIVIAL(error) << "missing " << a4;
    return make_tuple(false, "", "", "", "", "", "", "", "");
  }
  auto v5 = Dict::getString(_obj, a5);
  if (!v5) {
    BOOST_LOG_TRIVIAL(error) << "missing " << a5;
    return make_tuple(false, "", "", "", "", "", "", "", "");
  }
  auto v6 = Dict::getString(_obj, a6);
  if (!v6) {
    BOOST_LOG_TRIVIAL(error) << "missing " << a6;
    return make_tuple(false, "", "", "", "", "", "", "", "");
  }
  auto v7 = Dict::getString(_obj, a7);
  if (!v7) {
    BOOST_LOG_TRIVIAL(error) << "missing " << a7;
    return make_tuple(false, "", "", "", "", "", "", "", "");
  }
  auto v8 = Dict::getString(_obj, a8);
  if (!v8) {
    BOOST_LOG_TRIVIAL(error) << "missing " << a8;
    return make_tuple(false, "", "", "", "", "", "", "", "");
  }
  return make_tuple(true, *v1, *v2, *v3, *v4, *v5, *v6, *v7, *v8);
}
