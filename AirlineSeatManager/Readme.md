### Explanation of the Program:
## Reservation Structure:

## Stores passenger details (first name, last name, row, and seat).

##  Main Menu:

* Provides options to reserve a seat, print the seat map, print the passenger list, or exit.

## Reserve a Seat:

*** Prompts the user for passenger details and checks if the seat is already taken.

* If the seat is available, it saves the reservation to the CSV file.

## Print Seat Map:

## Reads all reservations from the CSV file and displays the seat map.

## Reserved seats are marked with x, and free seats are displayed with their respective letters.

* Print Passenger List:

* Reads all reservations, sorts them by last name and first name, and prints the list.

## File Handling:

* Reservations are stored in a CSV file (reservations.csv).

* The program appends new reservations to the file and reads all reservations when needed.

## Sorting:

* The qsort function is used to sort the passenger list by last name and first name.

## Example Output:
* Seat Map:

* 1 ABx DEF
* 2 ABC DEF
* 3 xxC xxF
*** ...
* 26 ABC DEF
* Passenger List:
* C
* John Doe - Row 1, Seat B
* Jane Smith - Row 3, Seat C
***...
* This program provides a simple yet effective way to manage airplane seat reservations. You can extend it further by adding features like canceling reservations or handling edge cases.


