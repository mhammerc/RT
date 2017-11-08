# RT

This is our full-featured raytracer.

https://www.youtube.com/watch?v=DvWrLdIM9mo&list=PLffb33rgTvvnFtewQDzyHzqqMk0s0gW2f

 * Dynamic interface and object manipulation (blender-like)
 * Textures (from image or dynamically generated)
 * Antialiasing
 * Reflection and refraction
 * [Constructive Solid Geometry](https://en.wikipedia.org/wiki/Constructive_solid_geometry)
 * Torus (fourth degree equation)
 * Polygons (.obj parser and renderer)
 * Multithreading
 * Save and open scenes in [CSON](https://github.com/bevry/cson)
 * All in C, with GTK+3 and libc as the only dependencies

## How to launch

On Ubuntu you must install ```libgtk-3-dev```. Install the equivalent or your distro.

    make
    ./rt

## Look at the screen captures!

![Screen capture](https://raw.githubusercontent.com/mhammerc/RT/develop/Screenshot%20from%202017-11-07%2014-14-40.png "Screen capture")
![Screen capture](https://raw.githubusercontent.com/mhammerc/RT/develop/Screenshot%20from%202017-11-07%2014-24-16.png "Screen capture")
![Screen capture](https://raw.githubusercontent.com/mhammerc/RT/develop/Screenshot%20from%202017-11-07%2015-11-14.png "Screen capture")
