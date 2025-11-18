/*
  result.hpp
  
  Author: Paul Hamilton (paul@visualops.com)
  Date: 17-Nov-2025
    
  Our result monad.
    
  Licensed under [version 3 of the GNU General Public License] contained in LICENSE.
 
  https://github.com/visualopsholdings/dict
*/

#ifndef H_result
#define H_result

#include <optional>
#include <string>
#include <rfl.hpp>

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
  
class Result : public rfl::Result<DictG> {
  
public:
  Result(std::optional<DictG> g);
  Result(std::optional<DictG> g, const std::string &path);
  Result(const Result &prev, const rfl::Error &err);
  
  std::string string();
    // return the current result as a string. If we are in error then return that
    // error as a string.
    
  Result object(const std::string &key);
    // if the current result is an object, return a sub object with 
    // the key.
    // or an error.
    
  DictO object();
    // if the current result is an object, return the object.
    // or log the error and return an empty object.
    
  Result vector(int index);
    // if the current result is a vector, return a sub object with 
    // the index.
    // or an error.
  
  DictV vector();
    // if the current result is an vector, return the vector.
    // or log the error and return an empty vector.
  
  int size();
    // if the current result is a vector, return the size
    // if an error, log the error and return the largest number.
    

  std::optional<std::string> error();
    // if there is an error, return that error as a string.
    
  std::optional<int> errori();
    // if there is an error, return the biggest integer.
    
private:

  std::string _path;
  
};

};

#endif // H_result
