
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

// Store transactions in a contiguous array
struct Transaction {
    int transactionID;
    int customerID;
    double amount;
    int suspicious;
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

    int suspiciousCount = 0;

    // Set up the high-resolution timer
    LARGE_INTEGER frequency, start, end;
    QueryPerformanceFrequency(&frequency);

    // Start timing
    QueryPerformanceCounter(&start);

    // Allocate memory for all transactions at once
    struct Transaction *transactions =
        malloc((size_t)numberOfTransactions *
               sizeof(struct Transaction));

    if (transactions == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    // Generate transactions in an array
    for (int i = 0; i < numberOfTransactions; i++) {
        transactions[i].transactionID = i + 1;
        transactions[i].customerID = 100 + (i % 1000);
        transactions[i].amount =
            (double)((i * 37LL) % 10000);
        transactions[i].suspicious = 0;
    }

    // Check each transaction for suspicious activity
    for (int i = 0; i < numberOfTransactions; i++) {
        if (transactions[i].amount > 5000.00) {
            transactions[i].suspicious = 1;
            suspiciousCount++;
        }
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

    // Free allocated memory
    free(transactions);

    return 0;
}
