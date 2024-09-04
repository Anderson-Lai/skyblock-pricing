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
    "${CMAKE_SOURCE_DIR}/tests/main.cpp"
# add_library(${PROJECT_NAME}
    "${CMAKE_SOURCE_DIR}/src/api.cpp"
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        "${CMAKE_SOURCE_DIR}/include/public/"
        "${CURL_INCLUDE_DIRS}"
    PRIVATE 
        "${CMAKE_SOURCE_DIR}/include/private/"
)


target_link_libraries(${PROJECT_NAME} 
    PUBLIC 
        ${CURL_LIBRARIES}
        simdjson
)
