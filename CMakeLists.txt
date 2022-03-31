cmake_minimum_required(VERSION 3.2)

project(encryption VERSION 1.0.0 LANGUAGES CXX)

add_executable(encryption src/main.cpp src/encryption uint256_t/uint256_t.cpp)


target_link_libraries(encryption)

target_include_directories(encryption
    PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/uint256_t>
)

