#!/bin/bash

# Work Flow
# 🕘 Start of Day:
# cd your/project
# git fetch                     # get latest refs (safe + fast)

# git checkout my-branch        # or create it if needed
# git pull --rebase             # sync your branch with remote (clean history)

# If it's a new branch:
# git checkout -b Day5-working_on:prompt
# git push -u origin Day5-working_on:prompt

# 👨‍💻 During the Day
# work, edit, test
# git status                   # check what changed
# git add .
# git commit -m "Fix prompt bug"

# 🌙 End of Day
# git push

# Navigate to your Minishell repo
cd ~/Code/42cursus/_CC/C\ III/-\>\ M.\ S./MiniShell/ || exit

echo -e "\n👋 ${BOLD}Good Day!${RESET}\n"

# Sync refs
git fetch

# Ask for the branch
read -e -p "What branch are you working on? > " BRANCH_NAME

if git show-ref --verify --quiet "refs/heads/$BRANCH_NAME"; then
   
    echo "✅ Branch exists. Switching to '$BRANCH_NAME'"
    git checkout "$BRANCH_NAME"
    
	# Check for uncommitted changes BEFORE pulling 
    if ! git diff --quiet || ! git diff --cached --quiet; then        echo "DEBUG🐞"
        echo "❕ Found Uncommited changes"
        git status
        git add .
        read -e -p "Enter your commit message:" commit_message
        git commit -m "$commit_message"
        git push
    fi

    UPSTREAM=$(git rev-parse --abbrev-ref --symbolic-full-name @{u} 2>/dev/null)
   
     if [ -z "$UPSTREAM" ]; then
        echo "🔄 No upstream set. Setting upstream and pushing..."
        git push -u origin "$BRANCH_NAME"
    else
        git pull --rebase
    fi

else 
    echo "❌ Branch '$BRANCH_NAME' not found."
    read -e -p "Do you want to create it? (y/n) > " ANSWER

    if [[ "$ANSWER" =~ ^[Yy]$ ]]; then
        git checkout -b "$BRANCH_NAME"
        git push -u origin "$BRANCH_NAME"
        echo "✅ Created and switched to '$BRANCH_NAME'"
    else
        echo -e "\n📋 Available branches:"
        git branch --list
        read -e -p "Choose existing branch > " EXISTING_BRANCH
        git checkout "$EXISTING_BRANCH"
        git pull --rebase
    fi
fi

