cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

project(sfmlapp VERSION 0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(FetchContent)

set(BUILD_SHARED_LIBS OFF)
FetchContent_Declare(
 SFML
 GIT_REPOSITORY https://github.com/SFML/SFML.git
 GIT_TAG 2.5.1
)
FetchContent_MakeAvailable(SFML)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug
        CACHE STRING "Choose the type of build Debug, or Release" FORCE)
endif()

option(USE_INSTALL_RESOURCE_PATH
    "Set resource path to install loc" OFF)

if (NOT USE_INSTALL_RESOURCE_PATH)
    set(RESOURCE_PATH "${PROJECT_SOURCE_DIR}/content/")
else()
    set(RESOURCE_PATH
        "${CMAKE_INSTALL_PREFIX}/share/${CMAKE_PROJECT_NAME}/content/")
endif()

configure_file(include/config.h.in config.h)

add_executable(sfmlapp src/main.cpp src/Game.cpp src/EntityManager.cpp src/Vec2.cpp)

target_include_directories(sfmlapp
    PRIVATE "${PROJECT_BINARY_DIR}"
    "${CMAKE_CURRENT_SOURCE_DIR}/include")

target_link_libraries(sfmlapp sfml-window sfml-graphics sfml-system)

install(TARGETS sfmlapp DESTINATION bin)
install(DIRECTORY content 
    DESTINATION "${CMAKE_INSTALL_PREFIX}/share/${CMAKE_PROJECT_NAME}")

