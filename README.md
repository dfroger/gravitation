# gravitation

Example of library depending on m library (for debug purpose)

Bellow is a (Partial) copy of the discussion on the `conda@continuum.io`
mailing list.

I'm trying to package ITK libraries [0] on Centos 5.11 [1], and then link an
executable with these libraries on Ubuntu 14.04 .

ITK is built with CMake, which generates and install configuration files used
latter by CMake to link with ITK libraries, like with pkg-config.

Problem is that path to system libraries (/usr/lib64/libdl.so,
/usr/lib64/libm.so, /usr/lib64/librt.so) are hardcoded in these configuration
files, but these libraries are found on Ubuntu 14.04 in `/lib/x86_64-linux-gnu
or `/usr/lib/x86_64-linux-gnu`.

ITK is a big project, here is a minimal example to reproduce the problem:

    https://github.com/dfroger/gravitation

The conda package 'gravitation' built on Centos 5.11 contains among other these
files:
   - lib/libgravation.so
   - include/gravitation/gravitation.hxx
   - share/gravitation/GRAVITATION_LIBRARY-noconfig.cmake This file contains
     information for CMake to link with lib/libgravitation.so, and contains
     a reference to ""/usr/lib64/libm.so".

The conda package 'gravitation' is then installed on Ubuntu 14.04, and I want
to link the file example/main.cxx with lib/libgravitation.so

The CMakeLists.txt is:

    cmake_minimum_required(VERSION 2.8)
    cmake_policy(VERSION 2.8)
    project(GRAVITATION)
    set(version 0.1.0)

    find_package(gravitation REQUIRED)

    include_directories(${GRAVITATION_INCLUDE_DIRS})

    # Create executable.
    add_executable(gravitation-example main.cxx)
    target_link_libraries(gravitation-example ${GRAVITATION_LIBRARIES})

Configure:

    $ mkdir build
    $ cd build
    $ cmake ..

This creates a file build/CMakeFiles/gravitation-example.dir/build.make
containing the rule:

    gravitation-example: /usr/lib64/libm.so

Build:
    $ make

this causes the error:
    make[2]: *** No rule to make target `/usr/lib64/libm.so', needed by `gravitation-example'.

Indeed, on Ubuntu 14.04, m library is found at `/lib/x86_64-linux-gnu/libm.so.6`
or `/usr/lib/x86_64-linux-gnu/libm.so`
