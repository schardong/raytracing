# Ray tracing in a week(end)

This is my implementation of the excellent [Ray Tracing In One Weekend](https://raytracing.github.io/books/RayTracingInOneWeekend.html) and [Ray Tracing: The Next Week](https://raytracing.github.io/books/RayTracingTheNextWeek.html) books. I tried to adhere to a C++17 standard and some book chapters were separated in tags.

## Building and Running

This project was designed to run with minimal external dependencies. The only dependency is [glm](https://github.com/g-truc/glm), which is a header only library. You only need to place the `glm` folder inside the `ext` folder in the project root.

To build the code, we use CMake (v3.11) to provide a minimum of portability.

## Samples

First book cover
![Image from book 1](/img/book1_cover_1400-1000-100_BVH.ppm)

First book cover + textured ground
![Image from book 1 + textured ground](/img/book1_cover_tex.ppm)
