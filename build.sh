#!/bin/sh
for d in level*; do
 cd $d && ./build.sh
 cd ..
done
