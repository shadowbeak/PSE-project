#!/bin/bash

rm -rf docs
doxygen Doxyfile
cd docs/html
python3 -m http.server 8080 --bind localhos