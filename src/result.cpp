/*
  result.cpp
  
  Author: Paul Hamilton (paul@visualops.com)
  Date: 17-Nov-2025
    
  Licensed under [version 3 of the GNU General Public License] contained in LICENSE.
 
  https://github.com/visualopsholdings/dict
*/

#include "dict.hpp"

#include <sstream>
#include <boost/log/trivial.hpp>

using namespace vops;

Result::Result(std::optional<DictG> g): _path("") {

  if (g) {
    _data = *g;
    _error = false;
  }
  else {
    _error = true;
  }
  
}

Result::Result(std::optional<DictG> g, const std::string &path): _path(path) {

  if (g) {
    _data = *g;
    _error = false;
  }
  else {
    _error = true;
  }
}
  
Result::Result(const Result &prev, bool error, const std::string &msg) {

  _path = prev._path;
  _error = error;
  _data = msg;
  
}

Result Result::object(const std::string &key) {

//  BOOST_LOG_TRIVIAL(trace) << "Result::object";

  if (_error) {
//    BOOST_LOG_TRIVIAL(trace) << "unwinding error";
    return *this;
  }
  
  auto obj = Dict::getObject(get<1>(_data));
  if (!obj) {
    return Result(*this, true, "Err: Dict is not an object");
  }
  
  auto elem = obj->get(key);
  if (!elem) {
    return Result(*this, true, "Err: " + key + " not found");
  }
  
  auto newpath = _path + "/" + key;
//  BOOST_LOG_TRIVIAL(trace) << "success path now " << newpath;

  return Result(*elem, newpath);
  
}

DictO Result::object() {

  if (_error) {
    BOOST_LOG_TRIVIAL(error) << "error: " << *error() << " returning empty object";
    return DictO();
  }

  auto o = Dict::getObject(get<1>(_data));
  if (!o) {
    BOOST_LOG_TRIVIAL(error) << "error: Dict is not an object returning empty object";
    return DictO();
  }
  
  return *o;
  
}

Result Result::vector(int index) {

//  BOOST_LOG_TRIVIAL(trace) << "Result::vector";

  if (_error) {
//    BOOST_LOG_TRIVIAL(trace) << "unwinding error";
    return *this;
  }
  
  auto v = Dict::getVector(get<1>(_data));
  if (!v) {
    return Result(*this, true, "Err: Dict is not a vector");
  }
  
  if (index >= v->size()) {
    std::stringstream ss;
    ss << "Err: index " << index << " is invalid";
    return Result(*this, true, ss.str());
  }
  
  std::stringstream ss;
  ss << _path << "/" << index;
//  BOOST_LOG_TRIVIAL(trace) << "success path now " << ss.str();

  return Result((*v)[index], ss.str());

}

DictV Result::vector() {

  if (_error) {
    BOOST_LOG_TRIVIAL(error) << "error: " << *error() << " returning empty vector";
    return DictV();
  }

  auto v = Dict::getVector(get<1>(_data));
  if (!v) {
    BOOST_LOG_TRIVIAL(error) << "error: Dict is not a vector returning empty vector";
    return DictV();
  }
  
  return *v;
  
}

int Result::size() {

//  BOOST_LOG_TRIVIAL(trace) << "Result::size";

  if (_error) {
//    BOOST_LOG_TRIVIAL(trace) << "unwinding error";
    return *errori();
  }
  
  auto v = Dict::getVector(get<1>(_data));
  if (!v) {
    BOOST_LOG_TRIVIAL(trace) << "underlying error is Err: not a vector";
    return INT_MAX;
  }
  
  return v->size();
  
}

std::string Result::string() {

//  BOOST_LOG_TRIVIAL(trace) << "Result::string";

  if (_error) {
//    BOOST_LOG_TRIVIAL(trace) << "unwinding error";
    return *error();
  }
  
  auto str = Dict::getString(get<1>(_data));
  if (!str) {
    return "Err: not a string";
  }

  return *str;
  
}

std::optional<std::string> Result::error() {

//  BOOST_LOG_TRIVIAL(trace) << "Result::error";

  if (!_error) {
    return std::nullopt;
  }

  std::stringstream ss;
  if (!_path.empty()) {
    ss << "Path: " << _path << " ";
  }
  ss << get<0>(_data);
  
  return ss.str();
  
}

std::optional<int> Result::errori() {

//  BOOST_LOG_TRIVIAL(trace) << "Result::error";

  if (!_error) {
    return std::nullopt;
  }

  BOOST_LOG_TRIVIAL(trace) << *error();
  
  return INT_MAX;
  
}


