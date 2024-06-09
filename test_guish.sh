#!/bin/bash

# Function to run a command in guish and check its output
run_test() {
    local command="$1"
    local expected_output="$2"
    local actual_output

    # Run the command in guish and capture the output
    actual_output=$(echo "$command" | ./guish)

    # Check if the actual output matches the expected output
    if [[ "$actual_output" == *"$expected_output"* ]]; then
        echo "Test passed: $command"
    else
        echo "Test failed: $command"
        echo "Expected: $expected_output"
        echo "Got: $actual_output"
        exit 1
    fi
}

# Test cases
run_test "echo Hello, World!" "Hello, World!"
run_test "hist" "1 echo"
run_test "r 1" "echo Hello, World!\nHello, World!"
run_test "r" "echo Hello, World!\nHello, World!"
run_test "foobar" "The program seems missing. Error code is: [error code]"
run_test "cp nonexistentfile destination" "cp: cannot stat 'nonexistentfile': No such file or directory\nThe program exited with error: 1"

echo "All tests passed."
