#!/bin/bash

mkdir build
cd build
cmake ..
make 
make install
mv ./install ../
rm -rf ../build