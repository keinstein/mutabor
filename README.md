[![Build Status](https://travis-ci.org/keinstein/mutabor.svg?branch=master)](https://travis-ci.org/keinstein/mutabor)

Building from GIT
==================

Requirements
------------

The following libraries are known to work. Minimal versions (marked with “>=”) indicate
versions that introduced new features that are used.

- Boost (1.54)
- wxWidgets (>=3.0)
- autoconf (>=2.67)
- automake (1.14.1)
- gettext (0.18.3)
- For realtime MIDI input and output the following packages are used :
  - ALSA or Jack (Linux),
  - CoreMidi or Jack (Mac OS X)
  - WinMM (Windows)
- git
- pkg-config
- NSIS (for a windows installer)

Optional packages that can be helpful (omitting these is not well-tested)
- TeX4HT (20090611)
- cppunit (1.12)
- inkscape (0.48.4)
- bison (3.0)
- flex  (2.5.35)

Step by step
------------

To compile MUTABOR from the git repositiory do the following:

1. clone the repositiory (For Development omit the depth parameter)
2. Fetch the submodules
3. create the configuration script (some files have to be installed)
4. configure the build
   Note that configure has several configuration options which might be interesting

    ./configure --help

5. build MUTABOR
6. install MUTABOR

In short: open a shell and enter the following commands

    git clone --depth 1 --single-branch --branch master git://git.code.sf.net/p/mutabor/code mutabor-code
    cd mutabor-code
    git submodule init
    git submodule update
    autoreconf -i
    ./configure
    make
    make install


