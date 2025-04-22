#!/usr/bin/env bash

DEADLINE="2025-06-13 18:00:00"

# Get current time
NOW=$(date +%s)

# Convert deadline to seconds since epoch (macOS compatible)
DEADLINE_SECONDS=$(date -j -f "%Y-%m-%d %H:%M:%S" "$DEADLINE" +%s)

# Calculate the difference in seconds
SECONDS_REMAINING=$((DEADLINE_SECONDS - NOW))

if [ $SECONDS_REMAINING -le 0 ]; then
    echo "The deadline has passed!"
    exit 0
fi

# Calculate days, hours, minutes, and seconds
DAYS=$((SECONDS_REMAINING / 86400))
SECONDS_REMAINING=$((SECONDS_REMAINING % 86400))

HOURS=$((SECONDS_REMAINING / 3600))
SECONDS_REMAINING=$((SECONDS_REMAINING % 3600))

MINUTES=$((SECONDS_REMAINING / 60))
SECONDS=$((SECONDS_REMAINING % 60))

# Display the remaining time in a readable format
echo "Time remaining until deadline (2025-04-20 18:37):"
echo "$DAYS days, $HOURS hours, $MINUTES minutes, and $SECONDS seconds"