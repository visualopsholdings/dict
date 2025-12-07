/*
  dictresult.cpp
  
  Author: Paul Hamilton (paul@visualops.com)
  Date: 17-Nov-2025
    
  Licensed under [version 3 of the GNU General Public License] contained in LICENSE.
 
  https://github.com/visualopsholdings/dict
*/

#include "dictresult.hpp"

#include "dict.hpp"

#include <sstream>
#include <boost/log/trivial.hpp>

using namespace vops;

Result::Result(std::optional<DictG> g): rfl::Result<DictG>(DictG()), _path("") {

  if (g) {
    rfl::Result<DictG>::operator=(rfl::Result<DictG>(*g)); 
  }
  else {
    rfl::Result<DictG>::operator=(rfl::Unexpected<rfl::Error>(rfl::Error("nullopt"))); 
  }
  
}

Result::Result(std::optional<DictG> g, const std::string &path): rfl::Result<DictG>(DictG()), _path(path) {

  if (g) {
    rfl::Result<DictG>::operator=(rfl::Result<DictG>(*g)); 
  }
  else {
    rfl::Result<DictG>::operator=(rfl::Unexpected<rfl::Error>(rfl::Error("nullopt"))); 
  }
  
}
  
Result::Result(const Result &prev, const rfl::Error &err): rfl::Result<DictG>(prev) {

  _path = prev._path;
//  rfl::Result<DictG>::operator=(rfl::Unexpected<rfl::Error>(rfl::Error(msg))); 
  rfl::Result<DictG>::operator=(rfl::Unexpected<rfl::Error>(err)); 
  
}

Result Result::object(const std::string &key) {

  BOOST_LOG_TRIVIAL(trace) << "Result::object "<< key;

  if (!has_value()) {
    BOOST_LOG_TRIVIAL(trace) << "unwinding error";
    return *this;
  }
  
  auto obj = Dict::getObject(*this);
  if (!obj) {
    return Result(*this, rfl::Error("Err: Dict is not an object"));
  }
  
  BOOST_LOG_TRIVIAL(trace) << Dict::toString(*obj);

  auto elem = obj->get(key);
  if (!elem) {
    return Result(*this, rfl::Error("Err: " + key + " not found"));
  }
  
  auto newpath = _path + "/" + key;
  BOOST_LOG_TRIVIAL(trace) << "success path now " << newpath;

  return Result(*elem, newpath);
  
}

DictO Result::object() {

  BOOST_LOG_TRIVIAL(trace) << "Result::object";

  if (!has_value()) {
    BOOST_LOG_TRIVIAL(error) << "error: " << *error() << " returning empty object";
    return DictO();
  }

  auto o = Dict::getObject(*this);
  if (!o) {
    BOOST_LOG_TRIVIAL(error) << "error: Dict is not an object returning empty object";
    return DictO();
  }
  
  return *o;
  
}

Result Result::vector(int index) {

  BOOST_LOG_TRIVIAL(trace) << "Result::vector " << index;

  if (!has_value()) {
    BOOST_LOG_TRIVIAL(trace) << "unwinding error";
    return *this;
  }
  
  auto v = Dict::getVector(*this);
  if (!v) {
    return Result(*this, rfl::Error("Err: Dict is not a vector"));
  }
  
  if (index >= v->size()) {
    std::stringstream ss;
    ss << "Err: index " << index << " is invalid";
    return Result(*this, rfl::Error(ss.str()));
  }
  
  std::stringstream ss;
  ss << _path << "/" << index;
  BOOST_LOG_TRIVIAL(trace) << "success path now " << ss.str();

  return Result((*v)[index], ss.str());

}

DictV Result::vector() {

  BOOST_LOG_TRIVIAL(trace) << "Result::vector";

  if (!has_value()) {
    BOOST_LOG_TRIVIAL(error) << "error: " << *error() << " returning empty vector";
    return DictV();
  }

  auto v = Dict::getVector(*this);
  if (!v) {
    BOOST_LOG_TRIVIAL(error) << "error: Dict is not a vector returning empty vector";
    return DictV();
  }
  
  return *v;
  
}

int Result::size() {

  BOOST_LOG_TRIVIAL(trace) << "Result::size";

  if (!has_value()) {
    BOOST_LOG_TRIVIAL(trace) << "unwinding error";
    return *errori();
  }
  
  auto v = Dict::getVector(*this);
  if (!v) {
    BOOST_LOG_TRIVIAL(trace) << "underlying error is Err: not a vector";
    return INT_MAX;
  }
  
  return v->size();
  
}

std::string Result::string() {

  BOOST_LOG_TRIVIAL(trace) << "Result::string";

  if (!has_value()) {
    BOOST_LOG_TRIVIAL(trace) << "unwinding error";
    return *error();
  }
  
  auto str = Dict::getString(*this);
  if (!str) {
    return "Err: not a string";
  }

  return *str;
  
}

std::optional<std::string> Result::error() {

  BOOST_LOG_TRIVIAL(trace) << "Result::error";

  if (has_value()) {
    return std::nullopt;
  }

  std::stringstream ss;
  if (!_path.empty()) {
    ss << "Path: " << _path << " ";
  }
  ss << rfl::Result<DictG>::error().what();
  
  return ss.str();
  
}

std::optional<int> Result::errori() {

  BOOST_LOG_TRIVIAL(trace) << "Result::error";

  if (has_value()) {
    return std::nullopt;
  }

  BOOST_LOG_TRIVIAL(trace) << *error();
  
  return INT_MAX;
  
}


