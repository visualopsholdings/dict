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

#include <rfl.hpp>
#include <optional>

namespace vops {

typedef rfl::Generic DictG;
  // a "Generic" type containing any sort of thing.
  // under the covers reflectcpp uses a variant for this.
  
typedef rfl::Object<rfl::Generic> DictO;
  // an "object" in the dictionary is fundamentally a dictionary.
  // so syntax like:
  // DictO o;
  // o["hello"] = "world";

typedef std::vector<rfl::Generic> DictV;
  // a vector of dictionaries.
  
class Dict {

public:

  static std::optional<DictO> getObject(const DictG &obj);
    // given a generic object, get an Object out of it.
    
  static std::optional<std::string> getString(const DictG &obj);
  static std::optional<std::string> getString(rfl::Result<DictG> result);
    // given a generic object, get a string out of it.
    
  static std::optional<long> getNum(const DictG &obj);
  static std::optional<long> getNum(rfl::Result<DictG> result);
    // given a generic object, get a long out of it.
    
  static std::optional<bool> getBool(const DictG &obj);
  static std::optional<bool> getBool(rfl::Result<DictG> result);
    // given a generic object, get a boolean out of it.
    
  static bool isVector(const DictG &obj);
    // Return true IF this is a vector.

  static std::optional<DictV> getVector(const DictG &obj);
    // given a generic object, get a vector out of it.

  static std::optional<DictO> getObject(std::optional<DictO> dict, const std::string &name);
    // get an object out of the dictionary with the property name.
    // This is chainable.
    
  static std::optional<DictG> getGeneric(std::optional<DictO> dict, const std::string &name);
    // get a generic out of the dictionary with the property name.
    // This is chainable.
    
  static std::optional<std::string> getString(std::optional<DictO> dict, const std::string &name);
    // get a string out of the dictionary with the property name.
    // This is chainable.
    
  static std::optional<long> getNum(std::optional<DictO> dict, const std::string &name);
    // get a long out of the dictionary with the property name.
    // This is chainable.
    
  static std::optional<bool> getBool(std::optional<DictO> dict, const std::string &name);
    // get a bool out of the dictionary with the property name.
    // This is chainable.
    
  static std::optional<DictV> getVector(std::optional<DictO> dict, const std::string &name);
    // get a string out of the dictionary with the property name.
    // This is chainable.

  static std::string toString(const DictG &g, const std::string &format=".json");
    // dump the generic out as JSON or YML.

  static std::optional<DictG> parseString(const std::string &s, const std::string &format=".json");
  static std::optional<DictG> parseStream(std::istream &s, const std::string &format=".json");
  static std::optional<DictG> parseFile(const std::string &fn);
    // given a stream, and a format the stream is in (.json, .yml) parse it.
    
};

// a really helpful function for initialising DictO's because they don't accept
// map initilisers.
// this allows:
//   DictO o{makeDictO({ 
//     { "xxx", makeDictO({ 
//         {"yyy", DictV{ "aaa", "bbb", "ccc"} } 
//       }) 
//     }
//   })};

inline DictO makeDictO(const std::map<std::string, DictG> &map) {
  DictO o;
  for_each(map.begin(), map.end(), [&o](auto e) { o[get<0>(e)] = get<1>(e); });
  return o;
}

} // vops

#endif // H_dict
