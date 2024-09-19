## Linking against the library

This library has been configured to be linked statically. To link dynamically, go to the CMakeLists.txt and change the add\_library() type from STATIC to SHARED.  

Linking with CMake:  
``` cmake
FetchContent_Declare(
    skyblock_pricing 
    GIT_REPOSITORY https://github.com/Anderson-Lai/skyblock-pricing.git
    GIT_TAG master
)
FetchContent_MakeAvailable(skyblock_pricing)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        skyblock_pricing
)
```
