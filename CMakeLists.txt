cmake_minimum_required(VERSION 3.14)

project(raytracer VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(LIBTRACE_SRC "src/aabb.cpp;src/bvhnode.cpp;src/camera.cpp;src/checkerstexture.cpp;src/constanttexture.cpp;src/dielectric.cpp;src/diffuselight.cpp;src/geomgen.cpp;src/hitobjectlist.cpp;src/lambertian.cpp;src/metal.cpp;src/perlintexture.cpp;src/ray.cpp;src/rect.cpp;src/sphere.cpp;src/trace.cpp;src/utils.cpp")

include(FetchContent)
# Fetching GLM
FetchContent_Declare(
  glm
  GIT_REPOSITORY https://github.com/g-truc/glm
  GIT_TAG        0.9.9.8
)

# Fetching CLI11 for command-line parsing
FetchContent_Declare(
  cli11
  GIT_REPOSITORY https://github.com/CLIUtils/CLI11
  GIT_TAG        v2.1.2
)
FetchContent_MakeAvailable(glm cli11)

message("GLM Source dir: " ${glm_SOURCE_DIR})
message("CLI11 source dir: " ${cli11_SOURCE_DIR})

add_library(trace ${LIBTRACE_SRC})
target_compile_features(trace PUBLIC cxx_std_17)
target_include_directories(trace
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        ${glm_SOURCE_DIR}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_CURRENT_SOURCE_DIR}/ext
)

# Client program
add_executable(demo_rt "src/main.cpp")
target_include_directories(demo_rt
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_CURRENT_SOURCE_DIR}/ext
    PUBLIC
        ${glm_SOURCE_DIR}
        ${cli11_SOURCE_DIR}/include
)
target_link_libraries(demo_rt trace)

# Tests
add_executable(t_lambertian_spheres "test/lambertian_spheres.cpp")
target_include_directories(t_lambertian_spheres
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_CURRENT_SOURCE_DIR}/ext
    PUBLIC
        ${glm_SOURCE_DIR}
)
target_link_libraries(t_lambertian_spheres trace)

add_executable(t_normal_spheres "test/normal_spheres.cpp")
target_include_directories(t_normal_spheres
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_CURRENT_SOURCE_DIR}/ext
    PUBLIC
        ${glm_SOURCE_DIR}
)
target_link_libraries(t_normal_spheres trace)

add_executable(t_book1 "test/book1_cover.cpp")
target_include_directories(t_book1
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_CURRENT_SOURCE_DIR}/ext
    PUBLIC
        ${glm_SOURCE_DIR}
)
target_link_libraries(t_book1 trace)
