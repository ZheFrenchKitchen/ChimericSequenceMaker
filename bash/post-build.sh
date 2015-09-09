#!/bin/bash

echo "POST-BUILD SCRIPT";

for var in "$@"
do
    echo "$var"
done

#rm -rf ./build/* 