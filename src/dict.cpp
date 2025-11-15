/*
  dict.cpp
  
  Author: Paul Hamilton (paul@visualops.com)
  Date: 7-Nov-2025
    
  Licensed under [version 3 of the GNU General Public License] contained in LICENSE.
 
  https://github.com/visualopsholdings/dict
*/

#include "dict.hpp"

#include <rfl.hpp>
#include <rfl/json.hpp>
#include <rfl/yaml.hpp>
#include <boost/log/trivial.hpp>

using namespace std;
using namespace vops;
namespace fs = std::filesystem;

optional<string> Dict::getString(optional<DictO> obj, const string &name) {

  if (!obj) {
    return nullopt;
  }
  
  auto prop = obj->get(name);
  if (!prop) {
    return nullopt;
  }
  
  return getString(*prop);
  
}

optional<string> Dict::getStringG(optional<DictG> g, const string &name) {

  if (!g) {
    return nullopt;
  }
  auto obj = getObject(*g);
  if (!obj) {
    return nullopt;
  }
  
  return getString(*obj, name);
  
}

optional<long> Dict::getNum(optional<DictO> obj, const string &name) {

  if (!obj) {
    return nullopt;
  }
  
  auto prop = obj->get(name);
  if (!prop) {
    return nullopt;
  }
  
  return getNum(*prop);
  
}

optional<long> Dict::getNumG(optional<DictG> g, const string &name) {

  if (!g) {
    return nullopt;
  }
  auto obj = getObject(*g);
  if (!obj) {
    return nullopt;
  }
  
  return getNumG(*obj, name);
  
}

optional<bool> Dict::getBool(optional<DictO> obj, const string &name) {

  if (!obj) {
    return nullopt;
  }
  
  auto prop = obj->get(name);
  if (!prop) {
    return nullopt;
  }
  
  return getBool(*prop);
  
}

optional<bool> Dict::getBoolG(optional<DictG> g, const string &name) {

  if (!g) {
    return nullopt;
  }
  auto obj = getObject(*g);
  if (!obj) {
    return nullopt;
  }
  
  return getBool(*obj, name);
  
}

optional<DictO> Dict::getObject(optional<DictO> obj, const string &name) {

  if (!obj) {
    return nullopt;
  }
  
  auto prop = obj->get(name);
  if (!prop) {
    return nullopt;
  }
  
  return getObject(*prop);
  
}

optional<DictO> Dict::getObjectG(optional<DictG> g, const string &name) {

  if (!g) {
    return nullopt;
  }
  auto obj = getObject(*g);
  if (!obj) {
    return nullopt;
  }
  
  return getObject(*obj, name);
  
}

optional<DictG> Dict::getGeneric(optional<DictO> obj, const string &name) {

  if (!obj) {
    return nullopt;
  }
  
  auto prop = obj->get(name);
  if (!prop) {
    return nullopt;
  }
  
  return *prop;
  
}

optional<DictG> Dict::getGenericG(optional<DictG> g, const string &name) {

  if (!g) {
    return nullopt;
  }
  auto obj = getObject(*g);
  if (!obj) {
    return nullopt;
  }
  
  return getGeneric(*obj, name);
  
}

optional<DictV> Dict::getVector(optional<DictO> obj, const string &name) {

  if (!obj) {
    return nullopt;
  }
  
  auto prop = obj->get(name);
  if (!prop) {
    return nullopt;
  }
  
  return getVector(*prop);
  
}

optional<DictV> Dict::getVectorG(optional<DictG> g, const string &name) {

  if (!g) {
    return nullopt;
  }
  auto obj = getObject(*g);
  if (!obj) {
    return nullopt;
  }
  
  return getVector(*obj, name);
  
}

optional<DictO> Dict::getObject(const DictG &obj) {

  optional<DictO> dict;
  std::visit([&dict](const auto &field) {
  
    if constexpr (is_same<decay_t<decltype(field)>, DictO>()) {
      dict = field;
    }

  }, obj.variant());

  return dict;
  
}

optional<DictO> Dict::getObject(rfl::Result<DictG> result) {

  if (!result) {
    return nullopt;
  }
  return getObject(*result);
  
}

bool Dict::isVector(const DictG &obj) {

  bool found = false;
  std::visit([&found](const auto &field) {
  
    if constexpr (is_same<decay_t<decltype(field)>, DictV>()) {
      found = true;
    }

  }, obj.variant());

  return found;
  
}

optional<DictV> Dict::getVector(const DictG &obj) {

  optional<DictV> v;
  std::visit([&v](const auto &field) {
  
    if constexpr (is_same<decay_t<decltype(field)>, DictV>()) {
      v = field;
    }

  }, obj.variant());

  return v;
  
}

optional<DictV> Dict::getVector(rfl::Result<DictG> result) {

  if (!result) {
    return nullopt;
  }
  return getVector(*result);
  
}

optional<string> Dict::getString(const DictG &obj) {

  optional<string> str;
  std::visit([&str](const auto &field) {
  
    if constexpr (is_same<decay_t<decltype(field)>, string>()) {
      str = field;
    }

  }, obj.variant());

  return str;
  
}

optional<string> Dict::getString(rfl::Result<DictG> result) {

  if (!result) {
    return nullopt;
  }
  return getString(*result);
  
}

optional<long> Dict::getNum(const DictG &obj) {

  optional<long> i;
  std::visit([&i](const auto &field) {
  
    if constexpr (is_same<decay_t<decltype(field)>, long>() || is_same<decay_t<decltype(field)>, long long>()) {
      i = field;
    }
  }, obj.variant());

  return i;
  
}

optional<long> Dict::getNum(rfl::Result<DictG> result) {

  if (!result) {
    return nullopt;
  }
  return getNum(*result);
  
}

optional<bool> Dict::getBool(const DictG &obj) {

  optional<bool> b;
  std::visit([&b](const auto &field) {
  
    if constexpr (is_same<decay_t<decltype(field)>, bool>()) {
      b = field;
    }
  }, obj.variant());

  return b;
  
}

optional<bool> Dict::getBool(rfl::Result<DictG> result) {

  if (!result) {
    return nullopt;
  }
  return getBool(*result);
  
}

string Dict::toString(const DictG &g, const string &format) {

  if (format == ".json") {
    return rfl::json::write(g, rfl::json::pretty);
  }
  else if (format == ".yml") {
    return rfl::yaml::write(g);
  }
  else {
    BOOST_LOG_TRIVIAL(error) << "invalid format " << format;
    return "???";
  }

}

template<typename T>
optional<DictG> Dict::parse(T &s, const string &format) {

  if (format == ".json") {
    auto g = rfl::json::read<DictG>(s);
    if (g) {
      return *g;
    }
  }
  else if (format == ".yml") {
    auto g = rfl::yaml::read<DictG>(s);
    if (g) {
      return *g;
    }
  }
  else {
    BOOST_LOG_TRIVIAL(error) << "invalid format " << format;
    return nullopt;
  }
  
  BOOST_LOG_TRIVIAL(error) << "could not parse string to " << format;
  return nullopt;

}

optional<DictG> Dict::parseString(string &s, const string &format) {
  return parse(s, format);
}

optional<DictG> Dict::parseStream(istream &s, const string &format) {
  return parse(s, format);
}

optional<DictG> Dict::parseFile(const string &fn) {

  fs::path p = fn;

  if (p.extension() == ".json") {
    auto g = rfl::json::load<DictG>(fn);
    if (g) {
      return *g;
    }
  }
  else if (p.extension() == ".yml") {
    auto g = rfl::yaml::load<DictG>(fn);
    if (g) {
      return *g;
    }
  }
  else {
    BOOST_LOG_TRIVIAL(error) << "invalid format " << p.extension();
    return nullopt;
  }
  
  BOOST_LOG_TRIVIAL(error) << "could not parse stream to " << p.extension();
  return nullopt;
  
}

bool extractPath(const string &path, string *loc, string *remain) {

  if (path.size() == 0) {
    BOOST_LOG_TRIVIAL(error) << "path is empty";
    return false;
  }
  if (path[0] != '/') {
    BOOST_LOG_TRIVIAL(error) << "path must start with /";
    return false;
  }
  
  auto rem = path.substr(1);
  auto slash = rem.find('/');
  *loc = rem.substr(0, slash);
  *remain = slash == string::npos ? "" : rem.substr(slash);
  return true;
  
}

optional<DictG> Dict::getVecPath(const DictV &v, const string &path) {

  string loc;
  string remain;
  if (!extractPath(path, &loc, &remain)) {
    return nullopt;
  }
  
  int index;
  stringstream ss(loc);
  ss >> index;

  if (index >= v.size()) {
    BOOST_LOG_TRIVIAL(error) << "index beyind end of vector " << index;
    return nullopt;
  }
  
  auto subobj = v[index];
  
  if (remain.size() > 0) {
    return getGPath(subobj, remain);
  }

  return subobj;
  
}

optional<DictG> Dict::getObjPath(const DictO &obj, const string &path) {

  string loc;
  string remain;
  if (!extractPath(path, &loc, &remain)) {
    return nullopt;
  }
  
  auto subobj = obj.get(loc);

  if (!subobj.has_value()) {
    BOOST_LOG_TRIVIAL(error) << subobj.error().what();
    return nullopt;
  }
  
  
  if (remain.size() > 0) {
    return getGPath(subobj.value(), remain);
  }
  
  return subobj.value();

}

optional<DictG> Dict::getGPath(const DictG &g, const string &path) {

  auto obj = Dict::getObject(g);
  if (!obj) {
    auto vec = Dict::getVector(g);
    if (!vec) {
      BOOST_LOG_TRIVIAL(error) << "only objects and vectors supported";
      return nullopt;
    }
    return getVecPath(*vec, path);
  }

  return getObjPath(*obj, path);
  
}

optional<DictG> Dict::find_pointer(const DictG &g, const string &path) {

  return getGPath(g, path);

}

optional<DictG> setGPath(const DictG &g, const string &path, const DictG &value);

optional<DictO> setObjPath(const DictO &obj, const string &path, const DictG &value) {

  BOOST_LOG_TRIVIAL(trace) << "setObjPath " << path << ", " << Dict::toString(value);

  string loc;
  string remain;
  if (!extractPath(path, &loc, &remain)) {
    return nullopt;
  }

//  BOOST_LOG_TRIVIAL(trace) << loc << ", " << remain;

  DictO newobj;
  
  // copy all other fields.
  for (auto e: obj) {
    if (get<0>(e) != loc) {
      newobj[get<0>(e)] = get<1>(e);
    }
  }
  
  if (remain.size() > 0) {
//    BOOST_LOG_TRIVIAL(trace) << Dict::toString(obj);
    auto o = obj.get(loc);
    if (!o) {
      BOOST_LOG_TRIVIAL(error) << loc << " not found";
      return nullopt;
    }
    auto result = setGPath(*o, remain, value);
    newobj[loc] = *result;
    return newobj;
  }
  
  newobj[loc] = value;
  
  return newobj;
  
}

optional<DictV> setVecPath(const DictV &v, const string &path, const DictG &value) {

  BOOST_LOG_TRIVIAL(trace) << "setVecPath " << path << ", " << Dict::toString(value);
//  BOOST_LOG_TRIVIAL(trace) << Dict::toString(v);

  string loc;
  string remain;
  if (!extractPath(path, &loc, &remain)) {
    return nullopt;
  }

//  BOOST_LOG_TRIVIAL(trace) << loc << ", " << remain;

  int index;
  stringstream ss(loc);
  ss >> index;

  if (index >= v.size()) {
    BOOST_LOG_TRIVIAL(error) << "index beyind end of vector " << index;
    return nullopt;
  }
  
  DictV newv;
  
  // copy all other indexes.
  int i=0;
  for (auto e: v) {
    if (i != index) {
      newv.push_back(e);
    }
    else {
      newv.push_back(0);
    }
    i++;
  }
  
  if (remain.size() > 0) {
//    BOOST_LOG_TRIVIAL(trace) << Dict::toString(v[index]);
    auto result = setGPath(v[index], remain, value);
    if (!result) {
      return nullopt;
    }
    newv[index] = *result;
    return newv;
  }
  
//  BOOST_LOG_TRIVIAL(trace) << "before " << Dict::toString(newv);
  newv[index] = value;
//  BOOST_LOG_TRIVIAL(trace) << "after " << Dict::toString(newv);
  
  return newv;

}

optional<DictG> setGPath(const DictG &g, const string &path, const DictG &value) {

  BOOST_LOG_TRIVIAL(trace) << "setGPath " << path << ", " << Dict::toString(value);

  auto obj = Dict::getObject(g);
  if (!obj) {
    auto vec = Dict::getVector(g);
    if (!vec) {
      BOOST_LOG_TRIVIAL(error) << "only objects and vectors supported";
      return nullopt;
    }
    auto result = setVecPath(*vec, path, value);
    if (!result) {
      return nullopt;
    }
    return *result;
  }
  
  auto result = setObjPath(*obj, path, value);
  if (!result) {
    return nullopt;
  }
  return *result;
  
}

optional<DictG> Dict::set_at_pointer(const DictG &g, const string &path, const DictG &value) {

  return setGPath(g, path, value);
  

}
