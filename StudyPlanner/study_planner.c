#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ENTRIES 100
#define MAX_LINE_LENGTH 100

typedef struct {
    char day[MAX_LINE_LENGTH];
    char time[MAX_LINE_LENGTH];
    char course[MAX_LINE_LENGTH];
    char room[MAX_LINE_LENGTH];
} ScheduleEntry;

// Function to compare two time strings (used for sorting)
int compare_times(const void *a, const void *b) {
    ScheduleEntry *entryA = (ScheduleEntry *)a;
    ScheduleEntry *entryB = (ScheduleEntry *)b;
    return strcmp(entryA->time, entryB->time);
}

// Function to read the schedule from a CSV file
int read_schedule(const char *filename, ScheduleEntry schedule[], int *num_entries) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return 0;
    }

    char line[MAX_LINE_LENGTH];
    *num_entries = 0;

    // Skip the header line
    fgets(line, sizeof(line), file);

    // Read each line of the CSV file
    while (fgets(line, sizeof(line), file)) {
        char *token;
        token = strtok(line, ",");
        if (token != NULL) {
            strcpy(schedule[*num_entries].day, token);
            token = strtok(NULL, ",");
            if (token != NULL) {
                strcpy(schedule[*num_entries].time, token);
                token = strtok(NULL, ",");
                if (token != NULL) {
                    strcpy(schedule[*num_entries].course, token);
                    token = strtok(NULL, ",");
                    if (token != NULL) {
                        strcpy(schedule[*num_entries].room, token);
                        // Remove newline character from room if present
                        schedule[*num_entries].room[strcspn(schedule[*num_entries].room, "\n")] = 0;
                        (*num_entries)++;
                    }
                }
            }
        }
    }

    fclose(file);
    return 1;
}

// Function to print the schedule for a given day
void print_daily_schedule(ScheduleEntry schedule[], int num_entries, const char *day) {
    ScheduleEntry daily_schedule[MAX_ENTRIES];
    int daily_count = 0;

    // Filter the schedule for the selected day
    for (int i = 0; i < num_entries; i++) {
        if (strcasecmp(schedule[i].day, day) == 0) {
            daily_schedule[daily_count] = schedule[i];
            daily_count++;
        }
    }

    if (daily_count == 0) {
        printf("No classes today\n");
        return;
    }

    // Sort the daily schedule by time
    qsort(daily_schedule, daily_count, sizeof(ScheduleEntry), compare_times);

    // Print the schedule
    printf("On %s you have:\n", day);
    for (int i = 0; i < daily_count; i++) {
        printf("%s %s, %s\n", daily_schedule[i].time, daily_schedule[i].course, daily_schedule[i].room);
    }
}

int main() {
    const char *filename = "schedule.csv"; // Replace with your CSV file name
    ScheduleEntry schedule[MAX_ENTRIES];
    int num_entries = 0;

    // Read the schedule from the CSV file
    if (!read_schedule(filename, schedule, &num_entries)) {
        return 1;
    }

    // Main loop to interact with the user
    while (1) {
        char day[MAX_LINE_LENGTH];
        printf("Enter day: ");
        if (fgets(day, sizeof(day), stdin) == NULL) {
            break; // Exit on EOF
        }

        // Remove newline character from input
        day[strcspn(day, "\n")] = 0;

        // Check if the user wants to stop
        if (strcasecmp(day, "stop") == 0) {
            printf("Program stopped.\n");
            break;
        }

        // Print the schedule for the selected day
        print_daily_schedule(schedule, num_entries, day);
    }

    return 0;
}
