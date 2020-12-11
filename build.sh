#!/bin/bash

script_dir=$(dirname "$0")
rm -rf $script_dir/build
mkdir $script_dir/build
cd $script_dir/build

cmake ..
cmake --build . --config Release
