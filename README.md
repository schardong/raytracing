# Ray tracing in a week(end)

This is my implementation of the excellent [Ray Tracing In One Weekend](https://raytracing.github.io/books/RayTracingInOneWeekend.html) and [Ray Tracing: The Next Week](https://raytracing.github.io/books/RayTracingTheNextWeek.html) books. I tried to adhere to a C++17 standard and some book chapters were separated in tags.

## Building and Running

This project was designed to run with minimal external dependencies. The only dependency is [glm](https://github.com/g-truc/glm), which is a header only library. You only need to place the `glm` folder from the repository inside the `ext` folder in the project root.

To build the code, we use CMake (v3.11) to provide a minimum of portability between operating systems. The main ray tracer library is built as a stand-alone library, to which the client code may be linked.

There are some tests inside the `test` folder, which are used to demonstrate the basic steps and functionality of our library.

## Samples

First book cover (using a bounding-volume hiearchy)
![Image from book 1](/img/book1_cover_BVH.png)

First book cover + textured ground
![Image from book 1 + textured ground](/img/book1_cover_tex.png)
