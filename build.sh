#!/bin/bash
echo "-- Custom Bash Cleaning"
if [ -d "./install"  ] ; then
	rm -rf ./install
	echo "-- Old Install Directory Deleted with sucess"
fi

mkdir build
cd build
cmake ..
make 
make install
mv ./install ../
rm -rf ../build