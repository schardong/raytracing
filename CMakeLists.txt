cmake_minimum_required(VERSION 3.11)

project(raytracer VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(LIBTRACE_SRC "src/aabb.cpp;src/bvhnode.cpp;src/camera.cpp;src/checkerstexture.cpp;src/constanttexture.cpp;src/dielectric.cpp;src/diffuselight.cpp;src/geomgen.cpp;src/hitobjectlist.cpp;src/lambertian.cpp;src/metal.cpp;src/perlintexture.cpp;src/ray.cpp;src/rect.cpp;src/sphere.cpp;src/trace.cpp;src/utils.cpp")

# include(ExternalProject)
# ExternalProject_Add(glm
#   GIT_REPOSITORY https://github.com/g-truc/glm.git
#   CONFIGURE_COMMAND ""
#   BUILD_COMMAND ""
#   BUILD_ALWAYS OFF
#   INSTALL_DIR ${CMAKE_CURRENT_BINARY_DIR}/ext/
#   INSTALL_COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_BINARY_DIR}/glm-prefix/src/glm/glm ${CMAKE_CURRENT_SOURCE_DIR}/ext/glm
#   )

add_library(trace ${LIBTRACE_SRC})
target_compile_features(trace PUBLIC cxx_std_17)
target_include_directories(trace
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
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
)
target_link_libraries(demo_rt trace)

# Tests
add_executable(t_lambertian_spheres "test/lambertian_spheres.cpp")
target_include_directories(t_lambertian_spheres
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_CURRENT_SOURCE_DIR}/ext
)
target_link_libraries(t_lambertian_spheres trace)

add_executable(t_normal_spheres "test/normal_spheres.cpp")
target_include_directories(t_normal_spheres
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_CURRENT_SOURCE_DIR}/ext
)
target_link_libraries(t_normal_spheres trace)

add_executable(t_book1 "test/book1_cover.cpp")
target_include_directories(t_book1
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_CURRENT_SOURCE_DIR}/ext
)
target_link_libraries(t_book1 trace)
