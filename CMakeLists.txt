cmake_minimum_required(VERSION 3.2)

project(encryption VERSION 1.0.0 LANGUAGES CXX)

add_executable(encryption src/main.cpp src/encryption.cpp )


target_link_libraries(encryption)

ADD_DEFINITIONS("-DBOOST_ALL_NO_LIB")

target_include_directories(encryption
    PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/boost/libs/multiprecision/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/boost/libs/config/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/boost/libs/random/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/boost/libs/core/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/boost/libs/system/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/boost/libs/type_traits/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/boost/libs/assert/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/boost/libs/static_assert/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/boost/libs/integer/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/boost/libs/throw_exception/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/boost/libs/array/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/boost/libs/range/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/boost/libs/preprocessor/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/boost/libs/mpl/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/boost/libs/iterator/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/boost/libs/io/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/boost/libs/concept_check/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/boost/libs/utility/include>
    
)

