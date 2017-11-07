# RT

Our RT it a full-featured raytracer.

 * Dynamic interface and object manipulation (blender-like)
 * Textures (from image or dynamically generated)
 * Antialiasing
 * Reflection and refraction
 * [Constructive Solid Geometry](https://en.wikipedia.org/wiki/Constructive_solid_geometry)
 * Torus (fourth degree equation)
 * Polygons (.obj parser and renderer)
 * Multithreading
 * Save and open scenes in CSON format
 * All in C, with GTK+3 as the only dependency

## How to launch

On Ubuntu you must install ```libgtk-3-dev```. Install the equivalent or your distro.

    make
    ./rt

## Look at the screen captures!

![Screen capture](https://raw.githubusercontent.com/mhammerc/RT/develop/Screenshot%20from%202017-11-07%2014-14-40.png "Screen capture")
![Screen capture](https://raw.githubusercontent.com/mhammerc/RT/develop/Screenshot%20from%202017-11-07%2014-24-16.png "Screen capture")
