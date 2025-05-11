#!/bin/bash

# Colors
GREEN="\033[0;32m"
RED="\033[0;31m"
BLUE="\033[0;34m"
YELLOW="\033[0;33m"
RESET="\033[0m"

# Paths
MINISHELL_EXEC="../minishell"
BASH_SHELL="/bin/bash"

# Counters
TOTAL_TESTS=0
PASSED_TESTS=0
SECTION_TESTS=0
SECTION_PASSED=0

# Check if minishell exists
if [ ! -f "$MINISHELL_EXEC" ]; then
    echo -e "${RED}Error: Minishell executable not found at $MINISHELL_EXEC${RESET}"
    exit 1
fi

print_result() {
    STATUS="$1"
    CMD="$2"
    BASH_OUT="$3"
    MINI_OUT="$4"
    
    if [ "$STATUS" = "OK" ]; then
        echo -e "${GREEN}[OK]${RESET}   $CMD"
        ((PASSED_TESTS++))
        ((SECTION_PASSED++))
    else
        echo -e "${RED}[FAIL]${RESET} $CMD"
        echo -e "  ${BLUE}Expected:${RESET} [${BASH_OUT}]"
        echo -e "  ${BLUE}Got     :${RESET} [${MINI_OUT}]"
    fi
}

run_test() {
    ((TOTAL_TESTS++))
    ((SECTION_TESTS++))
    CMD="$1"

    # Get Bash output
    BASH_OUTPUT=$($BASH_SHELL -c "$CMD" 2>/dev/null)

    # Convert to array for minishell call
    read -ra CMD_ARRAY <<< "$CMD"
    MINI_OUTPUT=$($MINISHELL_EXEC "${CMD_ARRAY[@]}" 2>/dev/null)

    if [ "$MINI_OUTPUT" = "$BASH_OUTPUT" ]; then
        print_result "OK" "$CMD" "$BASH_OUTPUT" "$MINI_OUTPUT"
    else
        print_result "FAIL" "$CMD" "$BASH_OUTPUT" "$MINI_OUTPUT"
    fi
}

print_section() {
    SECTION_NAME="$1"
    echo -e "\n${YELLOW}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━${RESET}"
    echo -e "${YELLOW}TESTING: $SECTION_NAME${RESET}"
    echo -e "${YELLOW}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━${RESET}\n"
    SECTION_TESTS=0
    SECTION_PASSED=0
}

print_section_summary() {
    echo -e "\n${BLUE}Section Summary:${RESET} ${SECTION_PASSED}/${SECTION_TESTS} tests passed\n"
}

# ============================================================================
print_section "BASIC ECHO TESTS"
# ============================================================================

# Easy tests - basic functionality
run_test "echo hello"
run_test "echo hello world"
run_test "echo Hello, World!"
run_test "echo"
run_test "echo multiple     spaces"
run_test "echo hello    world    test"
run_test "echo welcome to minishell"

print_section_summary

# ============================================================================
print_section "ECHO OPTION -n TESTS"
# ============================================================================

# Testing -n option
run_test "echo -n hello"
run_test "echo -n"
run_test "echo -n hello world"
run_test "echo -nn hello"
run_test "echo -nnnnnnn hello world"
run_test "echo -n -n -n hello"
run_test "echo -n-n hello"    # This should treat -n-n as a word, not an option

print_section_summary

if [ $PASSED_TESTS -eq $TOTAL_TESTS ]; then
    echo -e "${GREEN}All tests passed! Your echo implementation looks complete!${RESET}"
else
    echo -e "${RED}Some tests failed. Review the failed tests to improve your implementation.${RESET}"
fi