#!/bin/bash

# Define colors
GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m' # No Color

# Initialize counters
total_tests=0
passed_tests=0

# Read commands from file
while IFS= read -r cmd
do
    # Check if the line is a title
    if [[ $cmd == \#* ]]; then
        # Print the title (remove the '#' character)
        echo -e "${NC}${cmd#\#}${NC}"
    else
        # Increment total tests counter
        ((total_tests++))

        # Run the commands in mini-shell and bash, then compare outputs
        output_minishell=$(echo "$cmd" | ./minishell | sed '1d;$d')
        output_bash=$(bash -c "$cmd")

        # Compare outputs
        if diff <(echo "$output_minishell") <(echo "$output_bash") > /dev/null; then
            # If outputs are the same, increment passed tests counter
            ((passed_tests++))
            echo -e "\t${GREEN}done!${NC} : $cmd"
        else
            # If outputs differ
            echo -e "\t${RED}failed${NC} : $cmd"
        fi
    fi
done < cmd_test.txt

# Print the test summary
if [ $passed_tests -eq $total_tests ]; then
    echo -e "\n${GREEN}${passed_tests}/${total_tests} tests passed${NC}\n"
else
    echo -e "\n${RED}${passed_tests}/${total_tests} tests passed${NC}\n"
fi

