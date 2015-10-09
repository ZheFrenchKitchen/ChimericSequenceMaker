ChimericSequenceMaker
=============

A utility to convert a genome to a "chimeric" one (add/remove sequences at given positions).

ChimericSequenceMaker has been developped for fun in C++ by ZheFrench. 

This is a side project to discover C/C++ ecosystem and to play with CMake, Travis CI and other stuffs.

[ChimericSequenceMaker](https://github.com/ZheFrenchKitchen/#ChimericSequenceMaker) is ,for sure , a great tool but it's still in developpment.

The main functionality should work correctly.


## Features

- Add / Delete sequences using genome positions and chromosome name.
- Retrace your changes to give new positions of the genes on the reorganized genome. Useful to give a look with IGV then on an alignement produce with this new reference genome.


## Directory contents

* `src/` - The source files for the app.
* `src/main/static` - Static Library.
* `src/main/shared` - Shared Library.

## Prerequisites

- The basic program build tools. On Ubuntu and Debian these are available in the meta-package build-essential. On other distributions, you may need to install the GNU C++ compiler separately. The package is going to have c++ or g++ in its name. If you can't find the equivalent of build-essential meta-package for your distribution, be sure to install the "make" utility as well.
- CMake, the cross platform build system.

On Mac OsX (using [homebrew](http://brew.sh/) :
```bash
brew install cmake 
```

On Linux (Ubuntu distribution) :
```bash
sudo apt-get install build-essential
sudo apt-get install cmake
```

## Installation

To build the standalone program using CMake under Linux:

### Manually

1 - Download  via git.

```bash
git clone https://github.com/ZheFrenchKitchen/ChimericSequenceMaker
```

2 - Move inside downloaded directory : 

Execute : 
```bash
./build.sh
```

A directory call 'INSTALL' is created where you will find the executable under the bin directory.

### Homebrew (preferred)

//TODO: I'd like to make a configuration file to install symply using homebrew on MacOsX.

## How to use it

Two Inputs : 
- Path/To/Dir/ where are your chromosomes used as reference sequences to modify.
- A file which describes upgrades (coordinates & sequences)

Chromosome | Start | End | Sequence Patch
------------ | ------------- | ------------ | -------------
chr2 | 5 | 9 | AAAAAAAAAA
chr2 | 30 | 34| G
chr2 | 50 | 54 | AAAAAAAAAAAAAAA

```bash
./install/bin/ChimericSequenceMaker patch /Path/To/Dir/positions.txt /Path/To/Dir/chr/
```
