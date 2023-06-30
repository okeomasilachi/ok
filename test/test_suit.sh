#!/bin/bash

# Test cases
test_cases=(
    "echo Hello, world!"                   # Simple echo command
    "ls -l"                                # List files in long format
    "echo Hello && echo World"             # Command with multiple statements (&&)
    "echo Hello || echo World"             # Command with multiple statements (||)
    "ls non_existent_directory"            # Command with non-existent directory
)

# Function to compare the output of two commands
compare_output() {
    local expected_output="$1"
    local actual_output="$2"
    local expected_stream="$3"
    local actual_stream="$4"
    local expected_exit_status="$5"
    local actual_exit_status="$6"

    if [[ "$expected_output" == "$actual_output" && \
          "$expected_stream" == "$actual_stream" && \
          "$expected_exit_status" == "$actual_exit_status" ]]; then
        echo "PASS"
    else
        echo "FAIL"
        echo "Expected Output: $expected_output"
        echo "your shell Output: $actual_output"
        echo "Expected Stream: $expected_stream"
        echo "your shell Stream: $actual_stream"
        echo "Expected Exit Status: $expected_exit_status"
        echo "your shell Exit Status: $actual_exit_status"
    fi
}

# Run the test suite
for test_case in "${test_cases[@]}"; do
    echo "Test case: $test_case"

    # Execute the command in your shell and capture the output and stream
    your_shell_output=$(shell "$test_case" 2>&1)
    your_shell_exit_status=$?

    # Execute the same command in sh shell and capture the output and stream
    sh_shell_output=$(sh -c "$test_case" 2>&1)
    sh_shell_exit_status=$?

    echo "Your shell output:"
    echo "$your_shell_output"

    echo "sh shell output:"
    echo "$sh_shell_output"

    echo "Result:"
    compare_output "$sh_shell_output" "$your_shell_output" "stdout" "stdout" "$sh_shell_exit_status" "$your_shell_exit_status"

    if [[ $? -ne 0 ]]; then
        echo "Expected (sh shell):"
        echo "$sh_shell_output"
    fi

    echo "----------------------------------------"
done
