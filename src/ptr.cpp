/*
  ptr.cpp
  
  Author: Paul Hamilton (paul@visualops.com)
  Date: 13-Nov-2025
    
  Licensed under [version 3 of the GNU General Public License] contained in LICENSE.
 
  https://github.com/visualopsholdings/dict
*/

#include "dict.hpp"

#include <boost/log/trivial.hpp>

using namespace vops;

bool extractPath(const std::string &path, std::string *loc, std::string *remain) {

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
  *remain = slash == std::string::npos ? "" : rem.substr(slash);
  return true;
  
}

std::optional<DictG> Dict::getVecPath(const DictV &v, const std::string &path) {

  std::string loc;
  std::string remain;
  if (!extractPath(path, &loc, &remain)) {
    return std::nullopt;
  }
  
  int index;
  std::stringstream ss(loc);
  ss >> index;

  if (index >= v.size()) {
    BOOST_LOG_TRIVIAL(error) << "index beyond end of vector " << index;
    return std::nullopt;
  }
  
  auto subobj = v[index];
  
  if (remain.size() > 0) {
    return getGPath(subobj, remain);
  }

  return subobj;
  
}

std::optional<DictG> Dict::getObjPath(const DictO &obj, const std::string &path) {

  std::string loc;
  std::string remain;
  if (!extractPath(path, &loc, &remain)) {
    return std::nullopt;
  }
  
  auto subobj = obj.get(loc);

  if (!subobj.has_value()) {
    BOOST_LOG_TRIVIAL(error) << subobj.error().what();
    return std::nullopt;
  }
  
  
  if (remain.size() > 0) {
    return getGPath(subobj.value(), remain);
  }
  
  return subobj.value();

}

std::optional<DictG> Dict::getGPath(const DictG &g, const std::string &path) {

  auto obj = Dict::getObject(g);
  if (!obj) {
    auto vec = Dict::getVector(g);
    if (!vec) {
      BOOST_LOG_TRIVIAL(error) << "only objects and vectors supported";
      return std::nullopt;
    }
    return getVecPath(*vec, path);
  }

  return getObjPath(*obj, path);
  
}

std::optional<DictG> Dict::find_pointer(const DictG &g, const std::string &path) {

  return getGPath(g, path);

}

std::optional<DictO> Dict::setObjPath(const DictO &obj, const std::string &path, const DictG &value) {

//  BOOST_LOG_TRIVIAL(trace) << "setObjPath " << path << ", " << toString(value);

  std::string loc;
  std::string remain;
  if (!extractPath(path, &loc, &remain)) {
    return std::nullopt;
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
//    BOOST_LOG_TRIVIAL(trace) << toString(obj);
    auto o = obj.get(loc);
    if (!o) {
      BOOST_LOG_TRIVIAL(error) << loc << " not found";
      return std::nullopt;
    }
    auto result = setGPath(*o, remain, value);
    newobj[loc] = *result;
    return newobj;
  }
  
  newobj[loc] = value;
  
  return newobj;
  
}

std::optional<DictV> Dict::setVecPath(const DictV &v, const std::string &path, const DictG &value) {

//  BOOST_LOG_TRIVIAL(trace) << "setVecPath " << path << ", " << toString(value);
//  BOOST_LOG_TRIVIAL(trace) << toString(v);

  std::string loc;
  std::string remain;
  if (!extractPath(path, &loc, &remain)) {
    return std::nullopt;
  }

//  BOOST_LOG_TRIVIAL(trace) << loc << ", " << remain;

  int index;
  std::stringstream ss(loc);
  ss >> index;

  if (index >= v.size()) {
    BOOST_LOG_TRIVIAL(error) << "index beyond end of vector " << index;
    return std::nullopt;
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
//    BOOST_LOG_TRIVIAL(trace) << toString(v[index]);
    auto result = setGPath(v[index], remain, value);
    if (!result) {
      return std::nullopt;
    }
    newv[index] = *result;
    return newv;
  }
  
//  BOOST_LOG_TRIVIAL(trace) << "before " << toString(newv);
  newv[index] = value;
//  BOOST_LOG_TRIVIAL(trace) << "after " << toString(newv);
  
  return newv;

}

std::optional<DictG> Dict::setGPath(const DictG &g, const std::string &path, const DictG &value) {

//  BOOST_LOG_TRIVIAL(trace) << "setGPath " << path << ", " << toString(value);

  auto obj = getObject(g);
  if (!obj) {
    auto vec = getVector(g);
    if (!vec) {
      BOOST_LOG_TRIVIAL(error) << "only objects and vectors supported";
      return std::nullopt;
    }
    auto result = setVecPath(*vec, path, value);
    if (!result) {
      return std::nullopt;
    }
    return *result;
  }
  
  auto result = setObjPath(*obj, path, value);
  if (!result) {
    return std::nullopt;
  }
  return *result;
  
}

std::optional<DictG> Dict::set_at_pointer(const DictG &g, const std::string &path, const DictG &value) {

  return setGPath(g, path, value);
  

}