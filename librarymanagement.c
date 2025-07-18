
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100
#define MAX_BOOKS 1000

// Structure for book
typedef struct {
    int id;
    char title[100];
    char author[100];
    int status; // 0 - available, 1 - borrowed
} Book;

// Structure for user
typedef struct {
    int id;
    char name[100];
    char email[100];
} User;

// Global variables
Book books[MAX_BOOKS];
User users[MAX];
int bookCount = 0;
int userCount = 0;

// Function prototypes
void addBook();
void addUser();
void displayBooks();
void displayUsers();
void borrowBook();
void returnBook();
void searchBook();
void searchUser();

int main() {
    int choice;
    while (1) {
        printf("Library Management System\n");
        printf("1. Add Book\n");
        printf("2. Add User\n");
        printf("3. Display Books\n");
        printf("4. Display Users\n");
        printf("5. Borrow Book\n");
        printf("6. Return Book\n");
        printf("7. Search Book\n");
        printf("8. Search User\n");
        printf("9. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addBook();
                break;
            case 2:
                addUser();
                break;
            case 3:
                displayBooks();
                break;
            case 4:
                displayUsers();
                break;
            case 5:
                borrowBook();
                break;
            case 6:
                returnBook();
                break;
            case 7:
                searchBook();
                break;
            case 8:
                searchUser();
                break;
            case 9:
                exit(0);
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

// Function to add book
void addBook() {
    if (bookCount < MAX_BOOKS) {
        printf("Enter book ID: ");
        scanf("%d", &books[bookCount].id);
        printf("Enter book title: ");
        scanf("%s", books[bookCount].title);
        printf("Enter book author: ");
        scanf("%s", books[bookCount].author);
        books[bookCount].status = 0; // 0 - available
        bookCount++;
        printf("Book added successfully.\n");
    } else {
        printf("Maximum number of books reached.\n");
    }
}

// Function to add user
void addUser() {
    if (userCount < MAX) {
        printf("Enter user ID: ");
        scanf("%d", &users[userCount].id);
        printf("Enter user name: ");
        scanf("%s", users[userCount].name);
        printf("Enter user email: ");
        scanf("%s", users[userCount].email);
        userCount++;
        printf("User added successfully.\n");
    } else {
        printf("Maximum number of users reached.\n");
    }
}

// Function to display books
void displayBooks() {
    if (bookCount == 0) {
        printf("No books available.\n");
    } else {
        printf("List of books:\n");
        for (int i = 0; i < bookCount; i++) {
            printf("ID: %d, Title: %s, Author: %s, Status: %s\n", books[i].id, books[i].title, books[i].author, books[i].status == 0 ? "Available" : "Borrowed");
        }
    }
}

// Function to display users
void displayUsers() {
    if (userCount == 0) {
        printf("No users available.\n");
    } else {
        printf("List of users:\n");
        for (int i = 0; i < userCount; i++) {
            printf("ID: %d, Name: %s, Email: %s\n", users[i].id, users[i].name, users[i].email);
        }
    }
}

// Function to borrow book
void borrowBook() {
    int bookId;
    printf("Enter book ID to borrow: ");
    scanf("%d", &bookId);

    for (int i = 0; i < bookCount; i++) {
        if (books[i].id == bookId && books[i].status == 0) {
            books[i].status = 1; // 1 - borrowed
            printf("Book borrowed successfully.\n");
            return;
        }
    }

    printf("Book not available or does not exist.\n");
}

// Function to return book
void returnBook() {
    int bookId;
    printf("Enter book ID to return: ");
    scanf("%d", &bookId);

    for (int i = 0; i < bookCount; i++) {
        if (books[i].id == bookId && books[i].status == 1) {
            books[i].status = 0; // 0 - available
            printf("Book returned successfully.\n");
            return;
        }
    }

    printf("Book does not exist or is not borrowed.\n");
}

// Function to search book
void searchBook() {
    char title[100];
    printf("Enter book title to search: ");
    scanf("%s", title);

    for (int i = 0; i < bookCount; i++) {
        if (strcmp(books[i].title, title) == 0) {
            printf("Book found: ID: %d, Title: %s, Author: %s, Status: %s\n", books[i].id, books[i].title, books[i].author, books[i].status == 0 ? "Available" : "Borrowed");
            return;
        }
    }

    printf("Book not found.\n");
}

// Function to search user
void searchUser() {
    int userId;
    printf("Enter user ID to search: ");
    scanf("%d", &userId);

    for (int i = 0; i < userCount; i++) {
        if (users[i].id == userId) {
            printf("User found: ID: %d, Name: %s, Email: %s\n", users[i].id, users[i].name, users[i].email);
            return;
        }
    }

    printf("User not found.\n");
}
