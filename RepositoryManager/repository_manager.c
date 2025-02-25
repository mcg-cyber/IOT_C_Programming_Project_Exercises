#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ALIAS_LENGTH 50
#define MAX_LINK_LENGTH 200
#define MAX_ENTRIES 100

typedef struct {
    char alias[MAX_ALIAS_LENGTH];
    char link[MAX_LINK_LENGTH];
} RepositoryEntry;

RepositoryEntry repositories[MAX_ENTRIES];
int entry_count = 0;

const char *filename = "repositories.txt";

void load_repositories() {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("No existing repository file found. Starting with an empty list.\n");
        return;
    }

    while (fscanf(file, "%s %s", repositories[entry_count].alias, repositories[entry_count].link) != EOF) {
        entry_count++;
        if (entry_count >= MAX_ENTRIES) break;
    }

    fclose(file);
}

void save_repositories() {
    FILE *file = fopen(filename, "w");
    if (!file) {
        printf("Error: Could not save repositories to file.\n");
        return;
    }

    for (int i = 0; i < entry_count; i++) {
        fprintf(file, "%s %s\n", repositories[i].alias, repositories[i].link);
    }

    fclose(file);
}

void add_repository(const char *alias, const char *link) {
    if (entry_count >= MAX_ENTRIES) {
        printf("Error: Maximum number of entries reached.\n");
        return;
    }

    for (int i = 0; i < entry_count; i++) {
        if (strcmp(repositories[i].alias, alias) == 0) {
            printf("Error: Alias '%s' already exists.\n", alias);
            return;
        }
    }

    strncpy(repositories[entry_count].alias, alias, MAX_ALIAS_LENGTH);
    strncpy(repositories[entry_count].link, link, MAX_LINK_LENGTH);
    entry_count++;
    printf("Added: %s -> %s\n", alias, link);
    save_repositories();
}

void show_repository(const char *alias) {
    if (strcmp(alias, "all") == 0) {
        for (int i = 0; i < entry_count; i++) {
            printf("%s -> %s\n", repositories[i].alias, repositories[i].link);
        }
        return;
    }

    for (int i = 0; i < entry_count; i++) {
        if (strcmp(repositories[i].alias, alias) == 0) {
            printf("%s -> %s\n", repositories[i].alias, repositories[i].link);
            return;
        }
    }

    printf("Error: Alias '%s' not found.\n", alias);
}

void list_aliases() {
    for (int i = 0; i < entry_count; i++) {
        printf("%s\n", repositories[i].alias);
    }
}

void delete_repository(const char *alias) {
    for (int i = 0; i < entry_count; i++) {
        if (strcmp(repositories[i].alias, alias) == 0) {
            for (int j = i; j < entry_count - 1; j++) {
                strcpy(repositories[j].alias, repositories[j + 1].alias);
                strcpy(repositories[j].link, repositories[j + 1].link);
            }
            entry_count--;
            printf("Deleted: %s\n", alias);
            save_repositories();
            return;
        }
    }

    printf("Error: Alias '%s' not found.\n", alias);
}

void print_help() {
    printf("Available commands:\n");
    printf("  add <alias> <repository link> - Add a new repository entry\n");
    printf("  show <alias>|all - Show the repository link for a given alias or all links\n");
    printf("  list - List all aliases\n");
    printf("  delete <alias> - Delete a repository entry\n");
    printf("  help - Show this help message\n");
    printf("  quit - Exit the program\n");
}

int main() {
    char command[20];
    char alias[MAX_ALIAS_LENGTH];
    char link[MAX_LINK_LENGTH];

    load_repositories();

    while (1) {
        printf("> ");
        scanf("%s", command);

        if (strcmp(command, "add") == 0) {
            scanf("%s %s", alias, link);
            add_repository(alias, link);
        } else if (strcmp(command, "show") == 0) {
            scanf("%s", alias);
            show_repository(alias);
        } else if (strcmp(command, "list") == 0) {
            list_aliases();
        } else if (strcmp(command, "delete") == 0) {
            scanf("%s", alias);
            delete_repository(alias);
        } else if (strcmp(command, "help") == 0) {
            print_help();
        } else if (strcmp(command, "quit") == 0) {
            break;
        } else {
            printf("Error: Unknown command '%s'. Type 'help' for a list of commands.\n", command);
        }
    }

    save_repositories();
    printf("Exiting program. Changes saved.\n");
    return 0;
}
