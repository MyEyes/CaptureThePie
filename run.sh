#!/bin/sh
for d in level*/; do
  cd $d && ./run.sh
  cd ..
done
