# gravitation

Bellow is a (partial) copy of the discussion on the `conda@continuum.io`
mailing list.

## Intro

I'm trying to package [ITK libraries](https://github.com/heimdali/heimdali/tree/2d9f12c7db78d7b8b25d7b573880497dbb8e032b/conda-recipe/itk)
on [Centos 5.11](https://github.com/dfroger/conda-build-env/tree/a878cc82a2d77c353a15c5e11e34505caa383e26),
and then link an executable with these libraries on Ubuntu 14.04 .

ITK is built with CMake, which generates and install configuration files used
latter by CMake to link with ITK libraries, like with pkg-config.

Problem is that path to system libraries: 
  - `/usr/lib64/libdl.so`,
  - `/usr/lib64/libm.so`, 
  - `/usr/lib64/librt.so`)

are hardcoded in these configuration files, but these libraries are found on
Ubuntu 14.04 in `/lib/x86_64-linux-gnu` or `/usr/lib/x86_64-linux-gnu`.

ITK is a big project, so this repo is a minimal example to reproduce the problem.

## How to reproduce the problem 

The conda package `gravitation` built on Centos 5.11 contains among other these
files:
   - `lib/libgravation.so`
   - `include/gravitation/gravitation.hxx`
   - `share/gravitation/GRAVITATION_LIBRARY-noconfig.cmake` This file contains
     information for CMake to link with `lib/libgravitation.so`, and contains
     a reference to `/usr/lib64/libm.so`.

The conda package 'gravitation' is then installed on Ubuntu 14.04, and I want
to link the file `example/main.cxx` with `lib/libgravitation.so`

### Configure

    $ mkdir build
    $ cd build
    $ cmake ..

This creates a file `build/CMakeFiles/gravitation-example.dir/build.make`
containing the rule:

    gravitation-example: /usr/lib64/libm.so

### Build

    $ make

this causes the error:

    make[2]: *** No rule to make target `/usr/lib64/libm.so', needed by `gravitation-example'.

Indeed, on Ubuntu 14.04, m library is found at `/lib/x86_64-linux-gnu/libm.so.6`
or `/usr/lib/x86_64-linux-gnu/libm.so`
