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

using namespace std;
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

optional<DictO> Dict::getObject(const DictG &obj) {

  optional<DictO> dict;
  std::visit([&dict](const auto &field) {
  
    if constexpr (is_same<decay_t<decltype(field)>, DictO>()) {
      dict = field;
    }

  }, obj.variant());

  return dict;
  
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

optional<string> Dict::getString(const DictG &obj) {

  optional<string> str;
  std::visit([&str](const auto &field) {
  
    if constexpr (is_same<decay_t<decltype(field)>, string>()) {
      str = field;
    }

  }, obj.variant());

  return str;
  
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

optional<bool> Dict::getBool(const DictG &obj) {

  optional<bool> b;
  std::visit([&b](const auto &field) {
  
    if constexpr (is_same<decay_t<decltype(field)>, bool>()) {
      b = field;
    }
  }, obj.variant());

  return b;
  
}

string Dict::toString(const DictG &g, const string &format) {

  if (format == ".json") {
    return rfl::json::write(g, rfl::json::pretty);
  }
  else if (format == ".yml") {
    return rfl::yaml::write(g);
  }
  else {
    cerr << "invalid format " << format << endl;
    return "???";
  }

}

optional<DictG> Dict::parseStream(istream &s, const string &format) {

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
    cerr << "invalid format " << format << endl;
    return nullopt;
  }
  
  cerr << "could not parse stream to " << format << endl;
  return nullopt;
  
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
    cerr << "invalid format " << p.extension() << endl;
    return nullopt;
  }
  
  cerr << "could not parse stream to " << p.extension() << endl;
  return nullopt;
  
}
