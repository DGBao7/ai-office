cmake_minimum_required(VERSION 3.20)

project(AIOffice LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_AUTOMOC ON)

find_package(CURL REQUIRED)
find_package(nlohmann_json REQUIRED)
find_package(Qt6 REQUIRED COMPONENTS Widgets)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    "${CMAKE_SOURCE_DIR}/src/*.cpp"
)

add_executable(AIOffice
    main.cpp
    ${SOURCES}
)

target_compile_definitions(AIOffice PRIVATE
    ENV_FILE_PATH="${CMAKE_SOURCE_DIR}/.env"
)

target_include_directories(AIOffice PRIVATE
    "${CMAKE_SOURCE_DIR}/include"
    "${CMAKE_SOURCE_DIR}"
)

target_link_libraries(AIOffice PRIVATE
    CURL::libcurl
    nlohmann_json::nlohmann_json
    Qt6::Widgets
)