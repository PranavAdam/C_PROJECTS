#include <stdio.h>
#include <string.h>

// Structure to store expense details
struct Expense {
    char date[11];    // Format: "dd-mm-yyyy"
    char category[20];
    float amount;
};

// Function for case-insensitive string comparison
int caseInsensitiveCompare(const char *s1, const char *s2) {
    while (*s1 && *s2) {
        char c1 = (*s1 >= 'A' && *s1 <= 'Z') ? *s1 + 32 : *s1;
        char c2 = (*s2 >= 'A' && *s2 <= 'Z') ? *s2 + 32 : *s2;
        if (c1 != c2) return 0;
        s1++; s2++;
    }
    return *s1 == '\0' && *s2 == '\0';
}

// Function to display the menu options
void displayMenu() {
    printf("\n---- Expense Tracker ----\n");
    printf("1. Add an Expense\n");
    printf("2. View All Expenses\n");
    printf("3. View Expenses by Category\n");
    printf("4. Modify an Expense\n");
    printf("5. Exit\n");
    printf("Choose an option: ");
}

void addExpense() {
    struct Expense newExpense;
    FILE *file = fopen("expenses.txt", "a");

    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    printf("Enter date (dd-mm-yyyy): ");
    scanf("%s", newExpense.date);

    printf("Enter category (e.g., Food, Travel): ");
    scanf("%s", newExpense.category);

    printf("Enter amount: ");
    scanf("%f", &newExpense.amount);

    fprintf(file, "%s %s %.2f\n", newExpense.date, newExpense.category, newExpense.amount);

    fclose(file);
    printf("Expense added successfully!\n");
}

void viewExpenses() {
    struct Expense expense;
    FILE *file = fopen("expenses.txt", "r");

    if (file == NULL) {
        printf("No expenses recorded yet.\n");
        return;
    }

    printf("\n---- All Expenses ----\n");
    printf("Date       | Category     | Amount\n");
    printf("-----------------------------------\n");

    while (fscanf(file, "%s %s %f", expense.date, expense.category, &expense.amount) != EOF) {
        printf("%-10s | %-12s | %.2f\n", expense.date, expense.category, expense.amount);
    }

    fclose(file);
}

void viewExpensesByCategory() {
    struct Expense expense;
    char category[20];
    FILE *file = fopen("expenses.txt", "r");

    if (file == NULL) {
        printf("No expenses recorded yet.\n");
        return;
    }

    printf("Enter category to filter by (e.g., Food, Travel): ");
    scanf("%s", category);

    printf("\n---- Expenses in Category: %s ----\n", category);
    printf("Date       | Amount\n");
    printf("-----------------------\n");

    while (fscanf(file, "%s %s %f", expense.date, expense.category, &expense.amount) != EOF) {
        if (caseInsensitiveCompare(expense.category, category)) {
            printf("%-10s | %.2f\n", expense.date, expense.amount);
        }
    }

    fclose(file);
}

void modifyExpenseByCategoryAndAmount() {
    struct Expense expenses[100];
    int count = 0, found = 0;
    char targetCategory[20];
    float targetAmount;

    FILE *file = fopen("expenses.txt", "r");
    if (file == NULL) {
        printf("No expenses recorded yet.\n");
        return;
    }

    // Load all expenses into memory
    while (fscanf(file, "%s %s %f", expenses[count].date, expenses[count].category, &expenses[count].amount) != EOF) {
        count++;
    }
    fclose(file);

    // Ask user for search criteria
    printf("Enter category to search: ");
    scanf("%s", targetCategory);
    printf("Enter amount to search: ");
    scanf("%f", &targetAmount);

    // Search for matching entry
    for (int i = 0; i < count; i++) {
        if (caseInsensitiveCompare(expenses[i].category, targetCategory) && expenses[i].amount == targetAmount) {
            found = 1;
            printf("Matching Expense Found:\n");
            printf("Date: %s | Category: %s | Amount: %.2f\n", expenses[i].date, expenses[i].category, expenses[i].amount);

            // Get new values from user
            printf("Enter new date (dd-mm-yyyy): ");
            scanf("%s", expenses[i].date);
            printf("Enter new category: ");
            scanf("%s", expenses[i].category);
            printf("Enter new amount: ");
            scanf("%f", &expenses[i].amount);

            break;
        }
    }

    if (!found) {
        printf("No matching expense found.\n");
        return;
    }

    // Rewrite file with updated data
    file = fopen("expenses.txt", "w");
    for (int i = 0; i < count; i++) {
        fprintf(file, "%s %s %.2f\n", expenses[i].date, expenses[i].category, expenses[i].amount);
    }
    fclose(file);

    printf("Expense modified successfully.\n");
}

// Main function
int main() {
    int choice;

    while (1) {
        displayMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addExpense();
                break;
            case 2:
                viewExpenses();
                break;
            case 3:
                viewExpensesByCategory();
                break;
            case 4:
                modifyExpenseByCategoryAndAmount();
                break;
            case 5:
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid option. Please try again.\n");
        }
    }

    return 0;
}