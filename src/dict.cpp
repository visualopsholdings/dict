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

using namespace vops;
namespace fs = std::filesystem;

std::optional<std::string> Dict::getString(std::optional<DictO> obj, const std::string &name) {

  if (!obj) {
    return std::nullopt;
  }
  
  auto prop = obj->get(name);
  if (!prop) {
    return std::nullopt;
  }
  
  return getString(*prop);
  
}

std::optional<std::string> Dict::getStringG(std::optional<DictG> g, const std::string &name) {

  if (!g) {
    return std::nullopt;
  }
  auto obj = getObject(*g);
  if (!obj) {
    return std::nullopt;
  }
  
  return getString(*obj, name);
  
}

std::optional<long long> Dict::getNum(std::optional<DictO> obj, const std::string &name) {

  if (!obj) {
    return std::nullopt;
  }
  
  auto prop = obj->get(name);
  if (!prop) {
    return std::nullopt;
  }
  
  return getNum(*prop);
  
}

std::optional<long long> Dict::getNumG(std::optional<DictG> g, const std::string &name) {

  if (!g) {
    return std::nullopt;
  }
  
  auto obj = getObject(*g);
  if (!obj) {
    return std::nullopt;
  }
  
  return getNum(*obj, name);
  
}

std::optional<double> Dict::getDouble(std::optional<DictO> obj, const std::string &name) {

  if (!obj) {
    return std::nullopt;
  }
  
  auto prop = obj->get(name);
  if (!prop) {
    return std::nullopt;
  }
  
  return getDouble(*prop);
  
}

std::optional<double> Dict::getDoubleG(std::optional<DictG> g, const std::string &name) {

  if (!g) {
    return std::nullopt;
  }
  
  auto obj = getObject(*g);
  if (!obj) {
    return std::nullopt;
  }
  
  return getDouble(*obj, name);
  
}

std::optional<bool> Dict::getBool(std::optional<DictO> obj, const std::string &name) {

  if (!obj) {
    return std::nullopt;
  }
  
  auto prop = obj->get(name);
  if (!prop) {
    return std::nullopt;
  }
  
  return getBool(*prop);
  
}

std::optional<bool> Dict::getBoolG(std::optional<DictG> g, const std::string &name) {

  if (!g) {
    return std::nullopt;
  }
  auto obj = getObject(*g);
  if (!obj) {
    return std::nullopt;
  }
  
  return getBool(*obj, name);
  
}

std::optional<DictO> Dict::getObject(std::optional<DictO> obj, const std::string &name) {

  if (!obj) {
    return std::nullopt;
  }
  
  auto prop = obj->get(name);
  if (!prop) {
    return std::nullopt;
  }
  
  return getObject(*prop);
  
}

std::optional<DictO> Dict::getObjectG(std::optional<DictG> g, const std::string &name) {

  if (!g) {
    return std::nullopt;
  }
  auto obj = getObject(*g);
  if (!obj) {
    return std::nullopt;
  }
  
  return getObject(*obj, name);
  
}

std::optional<DictG> Dict::getGeneric(std::optional<DictO> obj, const std::string &name) {

  if (!obj) {
    return std::nullopt;
  }
  
  auto prop = obj->get(name);
  if (!prop) {
    return std::nullopt;
  }
  
  return *prop;
  
}

std::optional<DictG> Dict::getGenericG(std::optional<DictG> g, const std::string &name) {

  if (!g) {
    return std::nullopt;
  }
  auto obj = getObject(*g);
  if (!obj) {
    return std::nullopt;
  }
  
  return getGeneric(*obj, name);
  
}

std::optional<DictV> Dict::getVector(std::optional<DictO> obj, const std::string &name) {

  if (!obj) {
    return std::nullopt;
  }
  
  auto prop = obj->get(name);
  if (!prop) {
    return std::nullopt;
  }
  
  return getVector(*prop);
  
}

std::optional<DictV> Dict::getVectorG(std::optional<DictG> g, const std::string &name) {

  if (!g) {
    return std::nullopt;
  }
  auto obj = getObject(*g);
  if (!obj) {
    return std::nullopt;
  }
  
  return getVector(*obj, name);
  
}

std::optional<DictO> Dict::getObject(const DictG &obj) {

  std::optional<DictO> dict;
  std::visit([&dict](const auto &field) {
  
    if constexpr (std::is_same<std::decay_t<decltype(field)>, DictO>()) {
      dict = field;
    }

  }, obj.variant());

  return dict;
  
}

std::optional<DictO> Dict::getObject(std::optional<DictG> obj) {

  if (!obj) {
    return std::nullopt;
  }
  return getObject(*obj);
  
}

std::optional<DictO> Dict::getObject(rfl::Result<DictG> result) {

  if (!result) {
    return std::nullopt;
  }
  return getObject(*result);
  
}

bool Dict::isVector(const DictG &obj) {

  bool found = false;
  std::visit([&found](const auto &field) {
  
    if constexpr (std::is_same<std::decay_t<decltype(field)>, DictV>()) {
      found = true;
    }

  }, obj.variant());

  return found;
  
}

std::optional<DictV> Dict::getVector(const DictG &obj) {

  std::optional<DictV> v;
  std::visit([&v](const auto &field) {
  
    if constexpr (std::is_same<std::decay_t<decltype(field)>, DictV>()) {
      v = field;
    }

  }, obj.variant());

  return v;
  
}

std::optional<DictV> Dict::getVector(rfl::Result<DictG> result) {

  if (!result) {
    return std::nullopt;
  }
  return getVector(*result);
  
}

std::optional<std::string> Dict::getString(const DictG &obj) {

  std::optional<std::string> str;
  std::visit([&str](const auto &field) {
  
    if constexpr (std::is_same<std::decay_t<decltype(field)>, std::string>()) {
      str = field;
    }

  }, obj.variant());

  return str;
  
}

std::optional<std::string> Dict::getString(rfl::Result<DictG> result) {

  if (!result) {
    return std::nullopt;
  }
  return getString(*result);
  
}

std::optional<long long> Dict::getNum(const DictG &obj) {

  std::optional<long long> i;
  std::visit([&i](const auto &field) {
  
    if constexpr (std::is_same<std::decay_t<decltype(field)>, long>() || std::is_same<std::decay_t<decltype(field)>, long long>()) {
      i = field;
    }

  }, obj.variant());

  return i;
  
}

std::optional<long long> Dict::getNum(rfl::Result<DictG> result) {

  if (!result) {
    return std::nullopt;
  }
  return getNum(*result);
  
}

std::optional<double> Dict::getDouble(const DictG &obj) {

  std::optional<double> i;
  std::visit([&i](const auto &field) {
  
    if constexpr (std::is_same<std::decay_t<decltype(field)>, long>() || std::is_same<std::decay_t<decltype(field)>, double>()) {
      i = field;
    }

  }, obj.variant());

  return i;
  
}

std::optional<double> Dict::getDouble(rfl::Result<DictG> result) {

  if (!result) {
    return std::nullopt;
  }
  return getDouble(*result);
  
}

std::optional<bool> Dict::getBool(const DictG &obj) {

  std::optional<bool> b;
  std::visit([&b](const auto &field) {
  
    if constexpr (std::is_same<std::decay_t<decltype(field)>, bool>()) {
      b = field;
    }
  }, obj.variant());

  return b;
  
}

std::optional<bool> Dict::getBool(rfl::Result<DictG> result) {

  if (!result) {
    return std::nullopt;
  }
  return getBool(*result);
  
}

std::string Dict::toString(const DictG &g, bool pretty, const std::string &format) {

  if (format == ".json") {
    if (pretty) {
      return rfl::json::write(g, rfl::json::pretty);
    }
    return rfl::json::write(g);
  }
  
  if (format == ".yml") {
    return rfl::yaml::write(g);
  }

  BOOST_LOG_TRIVIAL(error) << "invalid format " << format;
  return "???";

}

template<typename T>
std::optional<DictG> Dict::parse(T &s, const std::string &format) {

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
    return std::nullopt;
  }
  
  BOOST_LOG_TRIVIAL(error) << "could not parse std::string to " << format;
  return std::nullopt;

}

std::optional<DictG> Dict::parseString(const std::string &s, const std::string &format) {
  return parse(s, format);
}

std::optional<DictG> Dict::parseStream(std::istream &s, const std::string &format) {
  return parse(s, format);
}

DictG resolveJSONIncludes(const fs::path &path, const DictG &g, bool silent) {

  auto obj = vops::Dict::getObject(g);
  if (obj) {
    DictO newobj;
    for (auto i: *obj) {
      auto k = get<0>(i);
//      BOOST_LOG_TRIVIAL(trace) << "processing " << k;
      if (k == "...") {
        auto s = vops::Dict::getString(get<1>(i));
        if (!s) {
          BOOST_LOG_TRIVIAL(error) << "include must be string path";
          continue;
        }
        if ((*s)[0] != '<' || (*s)[s->size()-1] != '>') {
          BOOST_LOG_TRIVIAL(error) << "invalid include filename format. Must have <> around it.";
          continue;
        }
        auto p = path / (s->substr(1, s->size()-2));
        if (!fs::exists(p)) {
          if (!silent) {
            BOOST_LOG_TRIVIAL(error) << "external include missing " << p.string();
          }
          continue;
        }
        auto d = vops::Dict::parseFile(p, silent);
        if (d) {
          auto o = Dict::getObject(*d);
          if (!o) {
            BOOST_LOG_TRIVIAL(error) << "only support including objects";
            continue;
          }
          newobj = *o;
        }
      }
      else {
        newobj[k] = resolveJSONIncludes(path, get<1>(i), silent);
      }
    }
    return newobj;
  }
  else {
    auto v = vops::Dict::getVector(g);
    if (v) {
      DictV v2;
      transform(v->begin(), v->end(), back_inserter(v2), [path, silent](auto e) {
        return resolveJSONIncludes(path, e, silent);
      });
      return v2;
    }
  }
  return g;
}

std::optional<DictG> Dict::parseFile(const std::string &fn, bool silentinclude) {

  fs::path p = fn;

  if (p.extension() == ".json") {
    auto g = rfl::json::load<DictG>(fn);
    if (g) {
      return resolveJSONIncludes(p.parent_path(), *g, silentinclude);
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
    return std::nullopt;
  }
  
  BOOST_LOG_TRIVIAL(error) << "could not parse " << fn;
  return std::nullopt;
  
}

DictO Dict::removeKey(const DictO &m, const std::string &key) {

  DictO m2;
  
  // TBD: how do we do this with copy_if etc.
  for (auto i: m) {
    auto k = get<0>(i);
    if (k != key) {
      m2[k] = get<1>(i);
    }
  }
  
  return m2;
}

DictO Dict::filterKeys(const DictO &m, const std::vector<std::string> &keys) {

  DictO m2;

  // TBD: how do we do this with copy_if etc.
  for (auto i: m) {
    auto k = get<0>(i);
    if (find(keys.begin(), keys.end(), k) == keys.end()) {
      m2[k] = get<1>(i);
    }
  }
  
  return m2;
  
}

std::optional<std::string> Dict::getFirstKey(const DictO &d) {
  for (auto i: d) {
    return i.first;
  }
  return std::nullopt;
}

std::optional<DictO> Dict::diff(const DictO &obj1, const DictO &obj2) {

  std::optional<DictO> d;
  
  // test values for all keys in obj1.
  for (auto i: obj1) {
    std::optional<DictG> diffval;
    auto s2 = Dict::getString(obj2, get<0>(i));
    if (s2) {
      // value is a string.
      auto s1 = Dict::getString(obj1, get<0>(i));
      if (s1 && *s1 == *s2) {
        continue;
      }
      diffval = *s2;
    }
    else {
      auto n2 = Dict::getNum(obj2, get<0>(i));
      if (n2) {
        auto n1 = Dict::getNum(obj1, get<0>(i));
        if (n1 && *n1 == *n2) {
          continue;
        }
        diffval = *n2;
      }
      else {
        auto b2 = Dict::getBool(obj2, get<0>(i));
        if (b2) {
          auto b1 = Dict::getBool(obj1, get<0>(i));
          if (b1 && *b1 == *b2) {
              continue;
          }
          diffval = *b2;
        }
        else {
          auto d2 = Dict::getDouble(obj2, get<0>(i));
          if (d2) {
            auto d1 = Dict::getDouble(obj1, get<0>(i));
            if (d1 && *d1 == *d2) {
              continue;
            }
            diffval = *d2;
          }
          else {
            auto g2 = Dict::getGeneric(obj2, get<0>(i));
            if (!g2) {
              // only in 1.
              diffval = *Dict::getGeneric(obj1, get<0>(i));;
            }
            else {
              BOOST_LOG_TRIVIAL(warning) << "ignoring " << get<0>(i);
            }
          }
        }
      }
    }
    
    // wd found a difference
    if (diffval) {
      if (!d) {
        d = DictO();
      }
      (*d)[get<0>(i)] = *diffval;
    }

  }
  
  // add in all obj2 keys that aren't in obj1.
  for (auto i: obj2) {
    auto s1 = Dict::getGeneric(obj1, get<0>(i));
    if (!s1) {
      if (!d) {
        d = DictO();
      }
      (*d)[get<0>(i)] = get<1>(i);
    }
  }
    
  return d;
}


