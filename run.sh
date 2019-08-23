#!/bin/sh
for d in level*/; do
  $d/run.sh &
done
