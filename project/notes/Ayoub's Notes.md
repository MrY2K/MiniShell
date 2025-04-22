# [[Git]] Collaboration for Two People: The Simple Approach
When two people need to collaborate on a project using Git, the simplest effective workflow is the GitHub Flow model, which balances simplicity with good practices. Here's how to set it up:

## The Basic Setup
1. Create a shared repository on GitHub (or another Git hosting service)
2. Both collaborators clone the repository to their local machines
3. Establish a main branch (often called `main` or `master`) that always contains stable, deployable code

## The Daily Workflow
The simplest effective workflow follows these steps:
1. **Always start fresh**: Pull the latest changes from the main branch before starting work
```
git pull origin main
```
2.  **Create a feature branch**: Work on your specific task in isolation
```
git checkout -b feature-name
```
3. **Make changes**: Edit files, implement features, fix bugs
4. **Commit frequently**: Make small, focused commits with clear messages
```
git add .
git commit -m "Add clear description of what changed"
```

5. **Push your branch**: Share your work with your partner
```
git push origin feature-name
```
6. **Create a pull request**: Ask your partner to review your changes through GitHub's interface
7. **Review each other's code**: Discuss changes, suggest improvements
8. **Merge to main**: Once approved, merge the feature branch into main
```
git checkout main git merge feature-name git push origin main
```
9. {BUT WE KEEP BRANCHES FOR HISTORY} **Delete the feature branch**: Keep things tidy after merging
```
git branch -d feature-name git push origin --delete feature-name
```
## Communication Practices
For a two-person team, communication is straightforward but crucial:
- Have a quick daily check-in about what you're each working on
- Use pull request comments for code-specific discussions
- Agree on coding standards and commit message formats upfront
- Consider using GitHub issues to track tasks and bugs
## Handling Conflicts
When both of you edit the same files, you might encounter merge conflicts. To resolve them:
1. Pull the latest main branch
2. Merge main into your feature branch
3. Resolve conflicts by editing the marked sections in files
4. Commit the resolved changes

The beauty of this approach is its simplicity while still maintaining code quality and stability. It scales well if your team grows later, and it's widely understood across the industry.

## cheatsheet:

```bash
git checkout -b feature-a
```

list all branches:
```bash
git branch -a
```

commit :
```bash
git commit -m "New Feature/Function"
```

Push to your ranch
```bash
git push origin feature-a
```

when the changes are done and ready to be pushed
we do a pill request in github
and merge the pull request

check out the main 
```bash
get checkout main
```

git pull 

murge branches
```bash
git merge main
```