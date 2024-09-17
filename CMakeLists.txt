cmake_minimum_required(VERSION 3.20)

project(skyblock_pricing CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)

FetchContent_Declare(
  simdjson
  GIT_REPOSITORY https://github.com/simdjson/simdjson.git
  GIT_TAG  tags/v3.10.1
  GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(simdjson)

find_package(CURL REQUIRED)

add_executable(${PROJECT_NAME}
    "${CMAKE_SOURCE_DIR}/tests/memoryleak.cpp"
#    "${CMAKE_SOURCE_DIR}/tests/main.cpp"
# add_library(${PROJECT_NAME} STATIC
    "${CMAKE_SOURCE_DIR}/src/api.cpp"
    "${CMAKE_SOURCE_DIR}/src/conversions.cpp"
    "${CMAKE_SOURCE_DIR}/src/log.cpp"
    "${CMAKE_SOURCE_DIR}/src/pricinglibrary.cpp"
    "${CMAKE_SOURCE_DIR}/src/item.cpp"
    "${CMAKE_SOURCE_DIR}/src/timing.cpp"
    "${CMAKE_SOURCE_DIR}/src/auctionhouse.cpp"
    "${CMAKE_SOURCE_DIR}/src/file.cpp"
    "${CMAKE_SOURCE_DIR}/src/json.cpp"
    "${CMAKE_SOURCE_DIR}/src/parsing.cpp"
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        "${CMAKE_SOURCE_DIR}/include/public/"
        "${CURL_INCLUDE_DIRS}"
    PRIVATE 
        "${CMAKE_SOURCE_DIR}/include/private/"
)

if (MSVC) 
    target_compile_options(${PROJECT_NAME} PUBLIC
        $<$<CONFIG:Debug>:/MDd>
        $<$<CONFIG:Release>:/MD>
    )
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    target_compile_options(${PROJECT_NAME} PUBLIC 
        $<$<CONFIG:Debug>:-ggdb -pthread -Wall -Wpedantic -Wextra -fsanitize=address>
        $<$<CONFIG:Release>:-O3 -s -pthread>
    )
    target_link_options(${PROJECT_NAME} PUBLIC
        $<$<CONFIG:Debug>:-ggdb -pthread -Wall -Wpedantic -Wextra -fsanitize=address>
        $<$<CONFIG:Release>:-O3 -s -pthread>
    )
else ()
    message(FATAL_ERROR "Your compiler is not supported")
endif ()

target_link_libraries(${PROJECT_NAME} 
    PUBLIC 
        ${CURL_LIBRARIES}
        simdjson
)
