# dict

C++ can express generic "dictionary" objects using cppreflect.

-- https://github.com/getml/reflect-cpp

This project defines a utility class called "Dict" which contains useful
functions for dealing with dictionaries in C++ along with some typedefs
for reflect-cpp to make the types shorter and clearer.

A future for this code is to implement a lot of this code as a Monad, that
is why optional is used a lot and is already chained internally.

## Prerequsists

#### Linux

```
sudo apt-get install -y git g++ gcc build-essential git make \
  pkg-config cmake libyaml-cpp-dev
```

#### Mac

```
brew install bison yaml-cpp pkg-config
```

### CMake

We need CMake 3.30.

#### Linux

```
sudo apt remove -y --purge --auto-remove cmake
```

#### From source (Mac and linux)
```
wget https://cmake.org/files/v3.30/cmake-3.30.5.tar.gz
tar -xzvf cmake-3.30.5.tar.gz
cd cmake-3.30.5
./bootstrap
make -j$(nproc)
sudo make install
```

### Boost

#### from source (Mac and linux)

```
wget https://github.com/boostorg/boost/releases/download/boost-1.85.0/boost-1.85.0-b2-nodocs.tar.gz
tar xzf boost-1.85.0-b2-nodocs.tar.gz 
cd boost-1.85.0
./bootstrap.sh --prefix=/usr/local
sudo ./b2 install boost.stacktrace.from_exception=off
```

### cpp-reflect

#### from source (Mac and linux)

```
git clone https://github.com/getml/reflect-cpp.git
cd reflect-cpp
git submodule update --init
./vcpkg/bootstrap-vcpkg.sh # Linux, macOS
./vcpkg/bootstrap-vcpkg.bat # Windows
cmake -S . -B build -DCMAKE_CXX_STANDARD=20 -DCMAKE_BUILD_TYPE=Release -DREFLECTCPP_YAML=ON
cmake --build build -j 4 # gcc, clang
cmake --build build --config Release -j 4 # MSVC
cd build
sudo make install
```

## Building and testing

Build this project:

```
git clone https://github.com/visualopsholdings/dict.git
cd dict
mkdir build
cd build
cmake ..
make
make test
```

## Usage

## License

Dict is licensed under [version 3 of the GNU General Public License] contained in LICENSE.

## Change Log

### 7-Nov-2025

- Broke "dict" out from flo::Generic and made it it's own project.

