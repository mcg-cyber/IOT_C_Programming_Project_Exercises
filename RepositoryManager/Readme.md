### Repository Manager

### Data Structure:

## RepositoryEntry stores the alias and link for each repository.
## repositories is an array of RepositoryEntry to hold all entries.
## entry_count keeps track of the number of entries.

## File Handling:

## load_repositories() reads repository data from a file at startup.
## save_repositories() writes the current repository data back to the file.

### Commands:

## add: Adds a new repository entry.
## show: Displays the repository link for a given alias or all links.
## list: Lists all aliases.
## delete: Deletes a repository entry.
## help: Displays a list of available commands.
## quit: Exits the program and saves changes.

### Error Handling:
## Checks for duplicate aliases.
## Handles invalid commands and missing aliases.

### User Interaction:
## The program continuously prompts the user for commands until quit is entered.

### File Format:
# The file repositories.txt stores the repository data in the following format:

### Copy
## alias1 link1
## alias2 link2

### Notes:
## The program assumes the file repositories.txt is in the same directory as the executable.
## The maximum number of entries is set to 100, but this can be adjusted by modifying MAX_ENTRIES.
## The program saves changes to the file after every modification. If you prefer to save only at the end, move the save_repositories() call to the quit command block.

