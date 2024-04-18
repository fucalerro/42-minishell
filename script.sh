#!/bin/bash

# Path to your source directory
SOURCE_DIR="src"

# Generate ctags for functions only
ctags --C-kinds=f -R $SOURCE_DIR

# Process the tags file, search each function name with ag
awk '{print $1}' tags | xargs -I {} ag --cc "{}" $SOURCE_DIR

