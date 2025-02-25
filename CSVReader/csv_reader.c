#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE_LENGTH 100
#define MAX_ROOMS 100
#define MAX_TEMPERATURES 100
#define DEFAULT_FILENAME "Temperatures.csv"

typedef struct {
    char room[MAX_LINE_LENGTH];
    float temperature;
} TemperatureData;

// Function to trim leading and trailing whitespace from a string
void trimWhitespace(char *str) {
    int start = 0, end = strlen(str) - 1;

    // Trim leading spaces
    while (isspace((unsigned char)str[start])) {
        start++;
    }

    // Trim trailing spaces
    while (end >= start && isspace((unsigned char)str[end])) {
        end--;
    }

    // Null-terminate the trimmed string
    str[end + 1] = '\0';

    // Shift the string to the beginning if necessary
    if (start > 0) {
        memmove(str, str + start, end - start + 2);
    }
}

int main() {
    FILE *file;
    char filename[MAX_LINE_LENGTH];
    char line[MAX_LINE_LENGTH];
    TemperatureData data[MAX_TEMPERATURES];
    char rooms[MAX_ROOMS][MAX_LINE_LENGTH];
    int roomCount = 0;
    int dataCount = 0;

    // Ask the user if they want to use the default file or provide their own
    char choice;
    printf("Do you want to use the default CSV file (Temperatures.csv)? (y/n): ");
    scanf(" %c", &choice);

    if (choice == 'y' || choice == 'Y') {
        strcpy(filename, DEFAULT_FILENAME);
    } else {
        printf("Enter the CSV file name: ");
        scanf("%s", filename);
    }

    // Open the CSV file
    file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    // Read the header line (skip it)
    fgets(line, sizeof(line), file);

    // Read the data lines
    while (fgets(line, sizeof(line), file)) {
        char *token;
        token = strtok(line, ",");
        if (token != NULL) {
            data[dataCount].temperature = atof(token);
            token = strtok(NULL, ",");
            if (token != NULL) {
                strcpy(data[dataCount].room, token);
                // Remove newline character and trim whitespace
                data[dataCount].room[strcspn(data[dataCount].room, "\n")] = 0;
                trimWhitespace(data[dataCount].room);

                // Check if the room is already in the rooms list
                int found = 0;
                for (int i = 0; i < roomCount; i++) {
                    if (strcmp(rooms[i], data[dataCount].room) == 0) {
                        found = 1;
                        break;
                    }
                }
                if (!found) {
                    strcpy(rooms[roomCount], data[dataCount].room);
                    roomCount++;
                }

                dataCount++;
            }
        }
    }

    fclose(file);

    // Debugging: Print all rooms found in the CSV file
    printf("Rooms found in the CSV file:\n");
    for (int i = 0; i < roomCount; i++) {
        printf("- %s\n", rooms[i]);
    }

    // Ask the user to select a room
    char selectedRoom[MAX_LINE_LENGTH];
    printf("Select a room: ");
    scanf(" %[^\n]", selectedRoom); // Read the entire line, including spaces
    trimWhitespace(selectedRoom);   // Trim whitespace from the user input

    // Check if the selected room exists
    int roomExists = 0;
    for (int i = 0; i < roomCount; i++) {
        if (strcmp(rooms[i], selectedRoom) == 0) {
            roomExists = 1;
            break;
        }
    }

    if (!roomExists) {
        printf("Error: Room '%s' does not exist.\n", selectedRoom);
        return 1;
    }

    // Print the temperatures and bar graph for the selected room
    printf("%s\n", selectedRoom);
    for (int i = 0; i < dataCount; i++) {
        if (strcmp(data[i].room, selectedRoom) == 0) {
            float temp = data[i].temperature;
            printf("%.1f ", temp);

            if (temp >= 0 && temp <= 30) {
                int dashes = (int)(temp * 2);
                for (int j = 0; j < dashes; j++) {
                    printf("-");
                }
            } else {
                printf("X");
            }
            printf("\n");
        }
    }

    return 0;
}
