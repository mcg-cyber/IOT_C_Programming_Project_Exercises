#include <stdio.h>  // Standard I/O library
#include <stdlib.h> // Standard library for memory allocation, process control, conversions, etc.
#include <ctype.h>  // Character handling functions
#include <string.h> // String handling functions

#define MAX_LINE_LENGTH 256  // Maximum length for input lines
#define MAX_COURSES 100     // Maximum number of courses
#define MAX_STUDENTS 100    // Maximum number of students per course

typedef struct {  // Structure to store student information
    char name[MAX_LINE_LENGTH];  // Student's name
    int grade;                   // Student's grade
} Student;

typedef struct {  // Structure to store course information
    char title[MAX_LINE_LENGTH]; // Course title
    int credits;                 // Course credits
    Student students[MAX_STUDENTS]; // Array of students in the course
    int student_count;           // Number of students in the course
} Course;

void trim_whitespace(char *str) {  // Function to trim leading and trailing whitespace
    char *end;  // Pointer to the end of the string

    // Trim leading space by moving the pointer to the first non-space character
    while (isspace((unsigned char)*str)) str++;

    // Trim trailing space by setting the end pointer to the last non-space character
    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end)) end--;

    // Null terminate after the last non-space character to remove trailing spaces
    *(end + 1) = '\0';
}

int main() {  // Main function
    FILE *file = fopen("student_db.txt", "r");  // Open the file for reading
    if (!file) {  // Check if the file was opened successfully
        perror("Failed to open file");  // Print error message if file opening fails
        return EXIT_FAILURE;  // Exit the program with failure status
    }

    Course courses[MAX_COURSES];  // Array to store courses
    int course_count = 0;  // Counter for the number of courses
    char line[MAX_LINE_LENGTH];  // Buffer to store each line from the file
    Course *current_course = NULL;  // Pointer to the current course being processed

    while (fgets(line, sizeof(line), file)) {  // Read each line from the file
        trim_whitespace(line);  // Trim whitespace from the line

        if (line[0] == '\0') {
            continue; // Ignore empty lines
        }

        if (line[0] == '[') {
            // Parse course title
            char *end_bracket = strchr(line, ']');
            if (end_bracket) {
                *end_bracket = '\0';
                current_course = &courses[course_count++];
                strcpy(current_course->title, line + 1);
                current_course->credits = 0; // Default credits to 0 if not specified
                current_course->student_count = 0;
            }
        } else if (current_course) {
            // Parse student name and grade
            char *colon = strchr(line, ':');
            if (colon) {
                *colon = '\0';
                trim_whitespace(line); // Ensure student name is trimmed before storing
                Student *student = &current_course->students[current_course->student_count++];
                strcpy(student->name, line);
                student->grade = atoi(colon + 1);
            }
        } else {
            fprintf(stderr, "Error: Student found before any course title: %s\n", line);
        }
    }

    fclose(file);  // Close the file after reading

    char student_name[MAX_LINE_LENGTH];  // Buffer to store user input for student name
    while (1) {  // Loop to continuously ask for student names
        printf("Enter student's name (or 'stop' to exit): ");  // Prompt user for input
        fgets(student_name, sizeof(student_name), stdin);  // Read user input
        student_name[strcspn(student_name, "\n")] = '\0'; // Remove newline character
        trim_whitespace(student_name);  // Trim whitespace from user input

        if (strcmp(student_name, "stop") == 0) {
            break;  // Exit the loop if user enters "stop"
        }

        int total_grades = 0;
        int total_courses = 0;
        printf("Courses for %s:\n", student_name);
        for (int i = 0; i < course_count; i++) {
            for (int j = 0; j < courses[i].student_count; j++) {
                // Check if the student's full name or first name matches the input
                if (strcasecmp(courses[i].students[j].name, student_name) == 0 ||
                    strcasecmp(strtok(courses[i].students[j].name, " "), student_name) == 0) {
                    printf("  %s: %d\n", courses[i].title, courses[i].students[j].grade);
                    total_grades += courses[i].students[j].grade;
                    total_courses++;
                }
            }
        }

        if (total_courses > 0) {
            printf("Average grade: %.2f\n", (double)total_grades / total_courses);  // Calculate and print average grade
        } else {
            printf("No courses found for %s.\n", student_name);  // Inform user if no courses are found
        }
    }

    return EXIT_SUCCESS;  // Exit the program successfully
}
