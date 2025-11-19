/*
  dict.hpp
  
  Author: Paul Hamilton (paul@visualops.com)
  Date: 7-Nov-2025
    
  helpers for cppreflect.
    
  Licensed under [version 3 of the GNU General Public License] contained in LICENSE.
 
  https://github.com/visualopsholdings/dict
*/

#ifndef H_dict
#define H_dict

#include "dictresult.hpp"

namespace vops {

class Dict {

public:
  Dict(std::optional<DictG> g): _dict(g) {}
  Dict() {}
  
  static std::optional<DictO> getObject(const DictG &obj);
  static std::optional<DictO> getObject(std::optional<DictG> obj);
  static std::optional<DictO> getObject(rfl::Result<DictG> result);
    // given a generic object, get an Object out of it.
    
  static std::optional<std::string> getString(const DictG &obj);
  static std::optional<std::string> getString(rfl::Result<DictG> result);
    // given a generic object, get a string out of it.
    
  static std::optional<long long> getNum(const DictG &obj);
  static std::optional<long long> getNum(rfl::Result<DictG> result);
    // given a generic object, get a long out of it.
    
  static std::optional<bool> getBool(const DictG &obj);
  static std::optional<bool> getBool(rfl::Result<DictG> result);
    // given a generic object, get a boolean out of it.
    
  static bool isVector(const DictG &obj);
    // Return true IF this is a vector.

  static std::optional<DictV> getVector(const DictG &obj);
  static std::optional<DictV> getVector(rfl::Result<DictG> result);
    // given a generic object, get a vector out of it.

  static std::optional<DictO> getObjectG(std::optional<DictG> g, const std::string &name);
  static std::optional<DictO> getObject(std::optional<DictO> dict, const std::string &name);
    // get an object out of the dictionary with the property name.
    // This is chainable.
    
  static std::optional<DictG> getGenericG(std::optional<DictG> g, const std::string &name);
  static std::optional<DictG> getGeneric(std::optional<DictO> dict, const std::string &name);
    // get a generic out of the dictionary with the property name.
    // This is chainable.
    
  static std::optional<std::string> getStringG(std::optional<DictG> g, const std::string &name);
  static std::optional<std::string> getString(std::optional<DictO> dict, const std::string &name);
    // get a string out of the dictionary with the property name.
    // This is chainable.
    
  static std::optional<long long> getNumG(std::optional<DictG> g, const std::string &name);
  static std::optional<long long> getNum(std::optional<DictO> dict, const std::string &name);
    // get a long out of the dictionary with the property name.
    // This is chainable.
    
  static std::optional<bool> getBoolG(std::optional<DictG> g, const std::string &name);
  static std::optional<bool> getBool(std::optional<DictO> dict, const std::string &name);
    // get a bool out of the dictionary with the property name.
    // This is chainable.
    
  static std::optional<DictV> getVectorG(std::optional<DictG> g, const std::string &name);
  static std::optional<DictV> getVector(std::optional<DictO> dict, const std::string &name);
    // get a string out of the dictionary with the property name.
    // This is chainable.

  static std::string toString(const DictG &g, bool pretty=true, const std::string &format=".json");
    // dump the generic out as JSON or YML.

  template<typename T>
  static std::optional<DictG> parse(T &s, const std::string &format);
  
  static std::optional<DictG> parseString(const std::string &s, const std::string &format=".json");
  static std::optional<DictG> parseStream(std::istream &s, const std::string &format=".json");
  static std::optional<DictG> parseFile(const std::string &fn);
    // given a stream, and a format the stream is in (.json, .yml) parse it.
    
  static std::optional<DictG> find_pointer(const DictG &g, const std::string &path);
  static std::optional<DictG> set_at_pointer(const DictG &g, const std::string &path, const DictG &value);
    // boost::json style find pointer, except set_at_pointer returns a new value.

  // monad entry points.
  Result object(const std::string &key) {
    return Result(_dict).object(key);
  }
  DictO object() {
    return Result(_dict).object();
  }
  Result vector(int index) {
    return Result(_dict).vector(index);
  }
  DictV vector() {
    return Result(_dict).vector();
  }
  std::string string() {
    return Result(_dict).string();
  }
  int size() {
    return Result(_dict).size();
  }
  bool error() {
    return !(Result(_dict).has_value());
  }

private:    

  static std::optional<DictG> getGPath(const DictG &g, const std::string &path);
  static std::optional<DictG> getVecPath(const DictV &v, const std::string &path);
  static std::optional<DictG> getObjPath(const DictO &obj, const std::string &path);
  static std::optional<DictG> setGPath(const DictG &g, const std::string &path, const DictG &value);
  static std::optional<DictO> setObjPath(const DictO &obj, const std::string &path, const DictG &value);
  static std::optional<DictV> setVecPath(const DictV &v, const std::string &path, const DictG &value);

  std::optional<DictG> _dict;
  
};

// a really helpful function for initialising DictO's because they don't accept
// map initilisers.
// this allows:
//   DictO o{dictO({ 
//     { "xxx", dictO({ 
//         {"yyy", DictV{ "aaa", "bbb", "ccc"} } 
//       }) 
//     }
//   })};

inline DictO dictO(const std::map<std::string, DictG> &map) {
  DictO o;
  for_each(map.begin(), map.end(), [&o](auto e) { o[get<0>(e)] = get<1>(e); });
  return o;
}

} // vops

#endif // H_dict
