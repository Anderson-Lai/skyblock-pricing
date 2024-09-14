## A C++ library to price items in Hypixel Skyblock

### Documentation:

Documentation on how to use and link against this library can be found [here](/docs/usage.md)

### Goals:

- Rewrite my old library with a better api and code practices
- Possibly improve performance
- Make linking against the library easier

### Build Process:

**Prequisites**:
- CMake 3.20 or higher
- A C++ compiler that supports C++20
- Curl

Installing curl on debian-based Linux distros:  
``` sh
sudo apt install libcurl4-openssl-dev
```

``` sh
cd scripts
./release.sh
```
### Licenses:

This project is licensed under the Apache 2.0 License. Further information can be found in the [NOTICE](/NOTICE.md) file, and the licenses of the
libraries that this project links against can be found in the [LICENSES](/LICENSES) directory.
