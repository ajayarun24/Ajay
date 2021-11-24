#!/bin/bash

# This is a shell script to run all tests sequentially.

TEST_PARSING="test-parsing"
TEST_ADDER="test-adder"

echo "Testing Parsing"
cd parsedData/
./$TEST_PARSING
cd ..

echo "Testing Adder"
cd BFS/
./$TEST_ADDER
cd ..
