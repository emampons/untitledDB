#!/bin/bash

# Args
RUN_TESTS=$1
CLEAN_UP=$2

# Assert Args
if ! [[ "$RUN_TESTS" =~ ^[0-1]+$ ]]; then
    echo "ERROR! Arg 1 (RUN_TESTS) must be 0 or 1!"
    exit 0
fi

if ! [[ "$CLEAN_UP" =~ ^[0-1]+$ ]]; then
    echo "ERROR! Arg 2 (CLEAN_UP) must be 0 or 1!"
    exit 0
fi

# Compile LeoDB
echo "Compiling LeoDB...  "

# Check if tests need to be compiled
if [[ "$RUN_TESTS" == 1  ]]; then
    echo "Compiling and Running Tests...  \n"
    cmake . -DBUILD_TESTS=1
    make
    scripts/runTests.sh
else
  echo "Compiling and Running Without Tests...  \n"
  cmake . -DBUILD_TESTS=0
  make
  printf "\nRunning leoDB...  \n"
  ./leodb
fi

# (Optional) Clean up
if [[ "$CLEAN_UP" == 1  ]]; then
  printf "\nCleaning Up...\n"
  scripts/cleanUp.sh
fi

