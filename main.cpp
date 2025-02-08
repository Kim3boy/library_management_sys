#include "library.h"
#include <iostream>
#include <string>

int main() {
    Library library;
    int choice;
    std::string title, author, ISBN, userID, userName;

    while (true) {
        displayMenu();
        std::cin >> choice;
        std::cin.ignore(); // Ignore the newline character left in the buffer

        switch (choice) {
            case 1: // Add Book
                std::cout << "Enter book title: ";
                std::getline(std::cin, title);
                std::cout << "Enter book author: ";
                std::getline(std::cin, author);
                std::cout << "Enter book ISBN: ";
                std::getline(std::cin, ISBN);
                library.addBook(new Book(title, author, ISBN));
                break;

            case 2: // Add User
                std::cout << "Enter user name: ";
                std::getline(std::cin, userName);
                std::cout << "Enter user ID: ";
                std::getline(std::cin, userID);
                library.addUser(new User(userName, userID));
                break;

            case 3: // Borrow Book
                std::cout << "Enter user ID: ";
                std::getline(std::cin, userID);
                std::cout << "Enter book title: ";
                std::getline(std::cin, title);

                {
                    User* user = library.searchUserByID(userID);
                    Book* book = library.searchBookByTitle(title);

                    if (user && book) {
                        user->borrowBook(book);
                    } else {
                        std::cout << "User or book not found." << std::endl;
                    }
                }
                break;

            case 4: // Return Book
                std::cout << "Enter user ID: ";
                std::getline(std::cin, userID);
                std::cout << "Enter book title: ";
                std::getline(std::cin, title);

                {
                    User* user = library.searchUserByID(userID);
                    Book* book = library.searchBookByTitle(title);

                    if (user && book) {
                        user->returnBook(book);
                    } else {
                        std::cout << "User or book not found." << std::endl;
                    }
                }
                break;

            case 5: // Display All Books
                library.displayAllBooks();
                break;

            case 6: // Display All Users
                library.displayAllUsers();
                break;

            case 7: // Exit
                std::cout << "Exiting the program. Goodbye!" << std::endl;
                return 0;

            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
                break;
        }
    }

    return 0;
}