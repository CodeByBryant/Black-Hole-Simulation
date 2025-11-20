#!/bin/bash

set -e

# Get the directory where this script is located
SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

# Check if build directory exists
if [ ! -d "$SCRIPT_DIR/build" ]; then
    echo "Build directory not found. Building the project..."
    mkdir -p "$SCRIPT_DIR/build"
    cd "$SCRIPT_DIR/build"
    cmake ..
    make -j$(nproc || echo 4)
else
    echo "Build directory found."
fi

# Run the simulation
echo "Starting Black Hole Simulation..."
cd "$SCRIPT_DIR/build"
./blackhole_sim
