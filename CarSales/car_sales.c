#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_CARS 1000
#define DATE_FORMAT "%Y-%m-%d"
#define FILENAME "car_sales.csv"

typedef struct {
  char make[50];
  char model[50];
  int mileage;
  char purchase_date[11]; // YYYY-MM-DD
  double purchase_price;
  char selling_date[11]; // YYYY-MM-DD
  double selling_price;
} Car;

Car cars[MAX_CARS];
int car_count = 0;

// Function to calculate the difference in days between two dates
int date_diff(const char *start_date, const char *end_date) {
  struct tm start = {0}, end = {0};
  strptime(start_date, DATE_FORMAT, &start);
  strptime(end_date, DATE_FORMAT, &end);
  time_t start_time = mktime(&start);
  time_t end_time = mktime(&end);
  return (int)(difftime(end_time, start_time) / (60 * 60 * 24));
}

// Function to load cars from the CSV file
void load_cars() {
  FILE *file = fopen(FILENAME, "r");
  if (!file) {
    printf("No existing data file found. A new one will be created.\n");
    return;
  }

  char line[256];
  while (fgets(line, sizeof(line), file)) {
    if (sscanf(line, "%49[^,],%49[^,],%d,%10[^,],%lf,%10[^,],%lf", cars[car_count].make,
               cars[car_count].model, &cars[car_count].mileage,
               cars[car_count].purchase_date, &cars[car_count].purchase_price,
               cars[car_count].selling_date, &cars[car_count].selling_price) == 7) {
        car_count++;
    }
  }
  fclose(file);
}

// Function to save cars to the CSV file
void save_cars() {
  FILE *file = fopen(FILENAME, "w");
  if (!file) {
    printf("Error opening file for writing.\n");
    return;
  }

  for (int i = 0; i < car_count; i++) {
    fprintf(file, "%s,%s,%d,%s,%.2f,%s,%.2f\n", cars[i].make, cars[i].model,
            cars[i].mileage, cars[i].purchase_date, cars[i].purchase_price,
            cars[i].selling_date, cars[i].selling_price);
  }
  fclose(file);
}

// Function to add a new car
void add_car() {
  if (car_count >= MAX_CARS) {
    printf("Cannot add more cars. Storage full.\n");
    return;
  }

  Car new_car;
  printf("Enter make: ");
  scanf("%s", new_car.make);
  printf("Enter model: ");
  scanf("%s", new_car.model);
  printf("Enter mileage: ");
  scanf("%d", &new_car.mileage);
  printf("Enter purchase date (YYYY-MM-DD): ");
  scanf("%s", new_car.purchase_date);
  printf("Enter purchase price: ");
  scanf("%lf", &new_car.purchase_price);
  printf("Enter selling date (YYYY-MM-DD): ");
  scanf("%s", new_car.selling_date);
  printf("Enter selling price: ");
  scanf("%lf", &new_car.selling_price);

  cars[car_count++] = new_car;
  save_cars();
  printf("Car added successfully.\n");
}

// Function to compare cars by profit (descending)
int compare_by_profit(const void *a, const void *b) {
  Car *car_a = (Car *)a;
  Car *car_b = (Car *)b;
  double profit_a = car_a->selling_price - car_a->purchase_price;
  double profit_b = car_b->selling_price - car_b->purchase_price;
  return (profit_b > profit_a) ? 1 : -1;
}

// Function to print the profit report
void print_profit_report() {
  double total_profit = 0;
  for (int i = 0; i < car_count; i++) {
    total_profit += cars[i].selling_price - cars[i].purchase_price;
  }
  qsort(cars, car_count, sizeof(Car), compare_by_profit);

  printf("\nProfit Report:\n");
  printf("Make\tModel\tProfit\n");
  for (int i = 0; i < car_count; i++) {
    double profit = cars[i].selling_price - cars[i].purchase_price;
    printf("%s\t%s\t$%.2f\n", cars[i].make, cars[i].model, profit);
  }
  printf("Total Profit: $%.2f\n", total_profit);
}

// Function to compare cars by sell time (ascending)
int compare_by_sell_time(const void *a, const void *b) {
  Car *car_a = (Car *)a;
  Car *car_b = (Car *)b;
  int days_a = date_diff(car_a->purchase_date, car_a->selling_date);
  int days_b = date_diff(car_b->purchase_date, car_b->selling_date);
  return days_a - days_b;
}

// Function to print the sell time report
void print_sell_time_report() {
  double total_profit = 0;
  for (int i = 0; i < car_count; i++) {
    total_profit += cars[i].selling_price - cars[i].purchase_price;
  }
  qsort(cars, car_count, sizeof(Car), compare_by_sell_time);

  printf("\nSell Time Report:\n");
  printf("Total Profit: $%.2f\n", total_profit);
  printf("Make\tModel\tSell Time (Days)\n");
  for (int i = 0; i < car_count; i++) {
    int days = date_diff(cars[i].purchase_date, cars[i].selling_date);
    printf("%s\t%s\t%d\n", cars[i].make, cars[i].model, days);
  }
}

// Main function
int main() {
  load_cars();

  int choice;
  do {
    printf("\nCar Sales Manager\n");
    printf("1. Add a car\n");
    printf("2. Print profit report\n");
    printf("3. Print sell time report\n");
    printf("4. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
    case 1:
      add_car();
      break;
    case 2:
      print_profit_report();
      break;
    case 3:
      print_sell_time_report();
      break;
    case 4:
      printf("Exiting...\n");
      break;
    default:
      printf("Invalid choice. Please try again.\n");
    }

  } while (choice != 4);

  return 0;
}
