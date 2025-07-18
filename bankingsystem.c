
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

// Structure for account
typedef struct {
    int accountNumber;
    char accountHolderName[100];
    float balance;
} Account;

// Global variables
Account accounts[MAX];
int accountCount = 0;

// Function prototypes
void createAccount();
void deposit();
void withdraw();
void displayAccounts();
void searchAccount();
void deleteAccount();

int main() {
    int choice;
    while (1) {
        printf("Bank Management System\n");
        printf("1. Create Account\n");
        printf("2. Deposit\n");
        printf("3. Withdraw\n");
        printf("4. Display Accounts\n");
        printf("5. Search Account\n");
        printf("6. Delete Account\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                createAccount();
                break;
            case 2:
                deposit();
                break;
            case 3:
                withdraw();
                break;
            case 4:
                displayAccounts();
                break;
            case 5:
                searchAccount();
                break;
            case 6:
                deleteAccount();
                break;
            case 7:
                exit(0);
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

// Function to create account
void createAccount() {
    if (accountCount < MAX) {
        printf("Enter account number: ");
        scanf("%d", &accounts[accountCount].accountNumber);
        printf("Enter account holder name: ");
        scanf("%s", accounts[accountCount].accountHolderName);
        accounts[accountCount].balance = 0;
        accountCount++;
        printf("Account created successfully.\n");
    } else {
        printf("Maximum number of accounts reached.\n");
    }
}

// Function to deposit
void deposit() {
    int accountNumber;
    float amount;
    printf("Enter account number: ");
    scanf("%d", &accountNumber);

    for (int i = 0; i < accountCount; i++) {
        if (accounts[i].accountNumber == accountNumber) {
            printf("Enter amount to deposit: ");
            scanf("%f", &amount);
            accounts[i].balance += amount;
            printf("Deposit successful. New balance: %.2f\n", accounts[i].balance);
            return;
        }
    }

    printf("Account not found.\n");
}

// Function to withdraw
void withdraw() {
    int accountNumber;
    float amount;
    printf("Enter account number: ");
    scanf("%d", &accountNumber);

    for (int i = 0; i < accountCount; i++) {
        if (accounts[i].accountNumber == accountNumber) {
            printf("Enter amount to withdraw: ");
            scanf("%f", &amount);

            if (amount > accounts[i].balance) {
                printf("Insufficient balance.\n");
            } else {
                accounts[i].balance -= amount;
                printf("Withdrawal successful. New balance: %.2f\n", accounts[i].balance);
            }
            return;
        }
    }

    printf("Account not found.\n");
}

// Function to display accounts
void displayAccounts() {
    if (accountCount == 0) {
        printf("No accounts available.\n");
    } else {
        printf("List of accounts:\n");
        for (int i = 0; i < accountCount; i++) {
            printf("Account Number: %d, Account Holder Name: %s, Balance: %.2f\n", accounts[i].accountNumber, accounts[i].accountHolderName, accounts[i].balance);
        }
    }
}

// Function to search account
void searchAccount() {
    int accountNumber;
    printf("Enter account number: ");
    scanf("%d", &accountNumber);

    for (int i = 0; i < accountCount; i++) {
        if (accounts[i].accountNumber == accountNumber) {
            printf("Account found: Account Number: %d, Account Holder Name: %s, Balance: %.2f\n", accounts[i].accountNumber, accounts[i].accountHolderName, accounts[i].balance);
            return;
        }
    }

    printf("Account not found.\n");
}

// Function to delete account
void deleteAccount() {
    int accountNumber;
    printf("Enter account number: ");
    scanf("%d", &accountNumber);

    for (int i = 0; i < accountCount; i++) {
        if (accounts[i].accountNumber == accountNumber) {
            // Shift accounts to fill the gap
            for (int j = i; j < accountCount - 1; j++) {
                accounts[j] = accounts[j + 1];
            }
            accountCount--;
            printf("Account deleted successfully.\n");
            return;
        }
    }

    printf("Account not found.\n");
}
