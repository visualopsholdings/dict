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

std::optional<long> Dict::getNum(std::optional<DictO> obj, const std::string &name) {

  if (!obj) {
    return std::nullopt;
  }
  
  auto prop = obj->get(name);
  if (!prop) {
    return std::nullopt;
  }
  
  return getNum(*prop);
  
}

std::optional<long> Dict::getNumG(std::optional<DictG> g, const std::string &name) {

  if (!g) {
    return std::nullopt;
  }
  auto obj = getObject(*g);
  if (!obj) {
    return std::nullopt;
  }
  
  return getNumG(*obj, name);
  
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

std::optional<long> Dict::getNum(const DictG &obj) {

  std::optional<long> i;
  std::visit([&i](const auto &field) {
  
    if constexpr (std::is_same<std::decay_t<decltype(field)>, long>() || std::is_same<std::decay_t<decltype(field)>, long long>()) {
      i = field;
    }
  }, obj.variant());

  return i;
  
}

std::optional<long> Dict::getNum(rfl::Result<DictG> result) {

  if (!result) {
    return std::nullopt;
  }
  return getNum(*result);
  
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

std::optional<DictG> Dict::parseFile(const std::string &fn) {

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
    return std::nullopt;
  }
  
  BOOST_LOG_TRIVIAL(error) << "could not parse stream to " << p.extension();
  return std::nullopt;
  
}
