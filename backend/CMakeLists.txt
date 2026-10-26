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
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

add_executable(AIOffice
    main.cpp
    ${SOURCES}
)

if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/.env")
    set(ENV_PATH "${CMAKE_CURRENT_SOURCE_DIR}/.env")
elseif(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/../.env")
    set(ENV_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../.env")
else()
    set(ENV_PATH "${CMAKE_CURRENT_SOURCE_DIR}/.env")

    message(WARNING "Cannot find .env file")
endif()

target_compile_definitions(AIOffice PRIVATE
    "ENV_FILE_PATH=\"${ENV_PATH}\""
)

target_include_directories(AIOffice PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
    "${CMAKE_CURRENT_SOURCE_DIR}"
)

target_link_libraries(AIOffice PRIVATE
    CURL::libcurl
    nlohmann_json::nlohmann_json
    Qt6::Widgets
)