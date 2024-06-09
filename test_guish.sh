#!/bin/bash

# Function to run a command and check its output
run_command() {
    local command=$1
    local expected_output=$2

    # Run the command in the shell
    output=$(echo "$command" | ./guish)

    # Check if the output matches the expected output
    if [[ "$output" == *"$expected_output"* ]]; then
        echo "Test passed: $command"
    else
        echo "Test failed: $command"
        echo "Expected: $expected_output"
        echo "Got: $output"
        exit 1
    fi
}

# Test cases
run_command "echo Hello, World!" "Hello, World!"
run_command "hist" "1 echo Hello, World!"
run_command "r 1" "echo Hello, World!\nHello, World!"
run_command "r" "echo Hello, World!\nHello, World!"
run_command "foobar" "The program seems missing. Error code is: [error code]"
run_command "cp nonexistentfile destination" "cp: cannot stat 'nonexistentfile': No such file or directory\nThe program exited with error: 1"

echo "All tests passed."
