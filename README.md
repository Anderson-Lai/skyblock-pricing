# A C++ library to price items in Hypixel Skyblock

## Documentation

Documentation on how to use and link against this library can be found [here](/docs/usage.md)

## Goals

- Rewrite my old library with a better api and code practices
- Possibly improve performance
- Make linking against the library easier

## Build Process

**Prequisites**
- CMake 3.20 or higher
- A C++ compiler that supports C++20
- Curl

Installing curl and other dependenies on debian-based Linux distros:  
``` sh
sudo apt install libcurl4-openssl-dev
sudo apt install cmake  
sudo apt install gcc  
```

Building the project:  
``` sh
cd scripts
./release.sh
```
## Licenses

This project is licensed under the Apache 2.0 License, and the licenses of libraries linked against can be found in the [LICENSES](/LICENSES)
directory. Further information can be found in the [NOTICE.md](/NOTICE.md) file.
