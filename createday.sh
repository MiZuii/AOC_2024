#!/bin/bash

day_dir="day$(date +%d)"
mkdir "$day_dir"
cat template.cpp >> "$day_dir"/puzzle1.cpp
cat template.cpp >> "$day_dir"/puzzle2.cpp
cd "$day_dir"
touch input.txt
cp ../template.mk Makefile
