#!/bin/bash

# todo add project root folder here
# Navigate to the repository directory
cd /Users/ajelloul/Desktop/unix_bash || exit

git pull

# Stage all changes
git add .

# Prompt the user for a commit message
echo "Enter your commit message:"
read -r commit_message

# Commit the changes with the provided message
git commit -m "$commit_message"

# Push the changes to the remote repository
git push