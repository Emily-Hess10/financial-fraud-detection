
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

// Each transaction is stored in a linked list node
struct Transaction {
    int transactionID;
    int customerID;
    double amount;
    int suspicious;
    struct Transaction *next;
};

int main(int argc, char *argv[]) {
    int numberOfTransactions = 1000;

    // Allow the user to choose the dataset size
    if (argc > 1) {
        numberOfTransactions = atoi(argv[1]);
    }

    if (numberOfTransactions <= 0) {
        printf("Please enter a positive number.\n");
        return 1;
    }

    struct Transaction *head = NULL;
    struct Transaction *tail = NULL;
    int suspiciousCount = 0;

    // Set up the high-resolution timer
    LARGE_INTEGER frequency, start, end;
    QueryPerformanceFrequency(&frequency);

    // Start timing
    QueryPerformanceCounter(&start);

    // Generate transactions using a linked list
    for (int i = 0; i < numberOfTransactions; i++) {
        struct Transaction *newTransaction =
            malloc(sizeof(struct Transaction));

        if (newTransaction == NULL) {
            printf("Memory allocation failed.\n");

            // Free previously allocated transactions
            while (head != NULL) {
                struct Transaction *temp = head;
                head = head->next;
                free(temp);
            }

            return 1;
        }

        newTransaction->transactionID = i + 1;
        newTransaction->customerID = 100 + (i % 1000);
        newTransaction->amount =
            (double)((i * 37LL) % 10000);
        newTransaction->suspicious = 0;
        newTransaction->next = NULL;

        if (head == NULL) {
            head = newTransaction;
        } else {
            tail->next = newTransaction;
        }

        tail = newTransaction;
    }

    // Check each transaction for suspicious activity
    struct Transaction *current = head;

    while (current != NULL) {
        if (current->amount > 5000.00) {
            current->suspicious = 1;
            suspiciousCount++;
        }

        current = current->next;
    }

    // Stop timing
    QueryPerformanceCounter(&end);

    // Calculate execution time in seconds
    double executionTime =
        (double)(end.QuadPart - start.QuadPart) /
        (double)frequency.QuadPart;

    printf("Total Transactions: %d\n",
           numberOfTransactions);

    printf("Suspicious Transactions: %d\n",
           suspiciousCount);

    printf("Execution Time: %.9f seconds\n",
           executionTime);

    // Free all allocated memory
    current = head;

    while (current != NULL) {
        struct Transaction *temp = current;
        current = current->next;
        free(temp);
    }

    return 0;
}

