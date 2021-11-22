# Ray tracing in a week(end)

This is my implementation of the excellent [Ray Tracing In One Weekend](https://raytracing.github.io/books/RayTracingInOneWeekend.html) and [Ray Tracing: The Next Week](https://raytracing.github.io/books/RayTracingTheNextWeek.html) books. Some book chapters were marked in tags, however this is not the norm since I was not disciplined from the beginning.

## Building and Running

### Pre-requisites
1. CMake v3.14
2. GCC v8.x or Clang 5

### Instructions
This project was designed to run with minimal external dependencies. The only dependencies are [glm](https://github.com/g-truc/glm) and [CLI11](https://github.com/CLIUtils/CLI11), which are header-only libraries. Both are downloaded at build time by CMake. Making it unnecessary to download and configure them manually. However, if you use another build-system, this must be adjusted to your needs. A possible list of commands to build the project is:

```bash
git clone https://github.com/schardong/raytracing.git # to download our raytracer
mkdir raytracing/build
cd raytracing/build
cmake ..
make -j
```

Of course, this is only an example, you may alter it to suit your needs.

To build the code, we use CMake (v3.14) to provide a minimum of portability between operating systems. The main ray tracer algorithm is built as a stand-alone library, to which the client code may be linked.

There are some tests inside the `test` folder, which are used to demonstrate the basic steps and functionality of our library. The `src/main.cpp` file contains the latest implementation and is meant only as a testing ground for new functionality.

## Samples

First book cover (using a bounding-volume hierarchy)
![Image from book 1](/img/book1_cover_BVH.png)

First book cover + textured ground
![Image from book 1 + textured ground](/img/book1_cover_tex.png)

Using light-emitting materials and Perlin textures
![Emitters and Perlin textures](/img/emitters.png)
