#!/bin/bash

doxygen Doxyfile
cd files/html
python3 -m http.server 8080 --bind localhost