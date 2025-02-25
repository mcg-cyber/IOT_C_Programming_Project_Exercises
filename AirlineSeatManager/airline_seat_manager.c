#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ROWS 26
#define SEATS_PER_ROW 6
#define FILENAME "reservations.csv"

typedef struct {
    char first_name[50];
    char last_name[50];
    int row;
    char seat;
} Reservation;

// Function prototypes
void reserveSeat();
void printSeatMap();
void printPassengerList();
int isSeatTaken(int row, char seat);
void saveReservation(Reservation res);
void loadReservations(Reservation reservations[], int *count);
int compareReservations(const void *a, const void *b);

int main() {
    int choice;

    while (1) {
        printf("\nAirplane Seat Reservation System\n");
        printf("1. Reserve a seat\n");
        printf("2. Print seat map\n");
        printf("3. Print passenger list\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                reserveSeat();
                break;
            case 2:
                printSeatMap();
                break;
            case 3:
                printPassengerList();
                break;
            case 4:
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

void reserveSeat() {
    Reservation res;
    printf("Enter first name: ");
    scanf("%s", res.first_name);
    printf("Enter last name: ");
    scanf("%s", res.last_name);
    printf("Enter row number (1-26): ");
    scanf("%d", &res.row);
    printf("Enter seat (A-F): ");
    scanf(" %c", &res.seat);

    if (res.row < 1 || res.row > ROWS || res.seat < 'A' || res.seat > 'F') {
        printf("Invalid row or seat. Please try again.\n");
        return;
    }

    if (isSeatTaken(res.row, res.seat)) {
        printf("Seat %d%c is already taken.\n", res.row, res.seat);
        return;
    }

    saveReservation(res);
    printf("Reservation successful!\n");
}

void printSeatMap() {
    Reservation reservations[ROWS * SEATS_PER_ROW];
    int count = 0;
    loadReservations(reservations, &count);

    printf("\nSeat Map:\n");
    for (int row = 1; row <= ROWS; row++) {
        printf("%2d ", row);
        for (char seat = 'A'; seat <= 'F'; seat++) {
            int isTaken = 0;
            for (int i = 0; i < count; i++) {
                if (reservations[i].row == row && reservations[i].seat == seat) {
                    isTaken = 1;
                    break;
                }
            }
            if (seat == 'C' || seat == 'D') {
                printf("   "); // Aisle spacing
            }
            printf("%c", isTaken ? 'x' : seat);
        }
        printf("\n");
    }
}

void printPassengerList() {
    Reservation reservations[ROWS * SEATS_PER_ROW];
    int count = 0;
    loadReservations(reservations, &count);

    qsort(reservations, count, sizeof(Reservation), compareReservations);

    printf("\nPassenger List (Sorted by Last Name and First Name):\n");
    for (int i = 0; i < count; i++) {
        printf("%s %s - Row %d, Seat %c\n", reservations[i].first_name, reservations[i].last_name, reservations[i].row, reservations[i].seat);
    }
}

int isSeatTaken(int row, char seat) {
    Reservation reservations[ROWS * SEATS_PER_ROW];
    int count = 0;
    loadReservations(reservations, &count);

    for (int i = 0; i < count; i++) {
        if (reservations[i].row == row && reservations[i].seat == seat) {
            return 1;
        }
    }
    return 0;
}

void saveReservation(Reservation res) {
    FILE *file = fopen(FILENAME, "a");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }
    fprintf(file, "%s,%s,%d,%c\n", res.first_name, res.last_name, res.row, res.seat);
    fclose(file);
}

void loadReservations(Reservation reservations[], int *count) {
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL) {
        *count = 0;
        return;
    }

    *count = 0;
    while (fscanf(file, "%[^,],%[^,],%d,%c\n", reservations[*count].first_name, reservations[*count].last_name, &reservations[*count].row, &reservations[*count].seat) != EOF) {
        (*count)++;
    }
    fclose(file);
}

int compareReservations(const void *a, const void *b) {
    Reservation *res1 = (Reservation *)a;
    Reservation *res2 = (Reservation *)b;
    int cmp = strcmp(res1->last_name, res2->last_name);
    if (cmp == 0) {
        return strcmp(res1->first_name, res2->first_name);
    }
    return cmp;
}
