#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

class Book {
private:
    std::string title;
    std::string author;
    std::string ISBN;
    bool isAvailable;

public:
    Book(std::string title, std::string author, std::string ISBN)
        : title(title), author(author), ISBN(ISBN), isAvailable(true) {}

    std::string getTitle() const { return title; }
    std::string getAuthor() const { return author; }
    std::string getISBN() const { return ISBN; }
    bool isBookAvailable() const { return isAvailable; }
    void setAvailability(bool availability) { isAvailable = availability; }

    void display() const {
        std::cout << "Title: " << title << ", Author: " << author
                  << ", ISBN: " << ISBN << ", Available: " 
                  << (isAvailable ? "Yes" : "No") << std::endl;
    }
};

class User {
private:
    std::string name;
    std::string userID;
    std::vector<Book*> borrowedBooks;

public:
    User(std::string name, std::string userID)
        : name(name), userID(userID) {}

    std::string getName() const { return name; }
    std::string getUserID() const { return userID; }

    void borrowBook(Book* book) {
        if (book && book->isBookAvailable()) {
            borrowedBooks.push_back(book);
            book->setAvailability(false);
            std::cout << name << " has borrowed the book: " << book->getTitle() << std::endl;
        } else {
            std::cout << "Book is not available for borrowing." << std::endl;
        }
    }

    void returnBook(Book* book) {
        auto it = std::find(borrowedBooks.begin(), borrowedBooks.end(), book);
        if (it != borrowedBooks.end()) {
            borrowedBooks.erase(it);
            book->setAvailability(true);
            std::cout << name << " has returned the book: " << book->getTitle() << std::endl;
        } else {
            std::cout << "This book was not borrowed by " << name << "." << std::endl;
        }
    }

    void display() const {
        std::cout << "User: " << name << " (ID: " << userID << ")" << std::endl;
        if (borrowedBooks.empty()) {
            std::cout << "No books borrowed." << std::endl;
        } else {
            std::cout << "Borrowed Books:" << std::endl;
            for (const auto& book : borrowedBooks) {
                std::cout << "- " << book->getTitle() << " by " << book->getAuthor() << std::endl;
            }
        }
    }
};

class Library {
private:
    std::vector<Book*> books;
    std::vector<User*> users;

public:
    void addBook(Book* book) {
        if (book) {
            books.push_back(book);
            std::cout << "Added book: " << book->getTitle() << std::endl;
        }
    }

    void addUser(User* user) {
        if (user) {
            users.push_back(user);
            std::cout << "Added user: " << user->getName() << std::endl;
        }
    }

    Book* searchBookByTitle(const std::string& title) {
        for (auto& book : books) {
            if (book->getTitle() == title) {
                return book;
            }
        }
        return nullptr;
    }

    User* searchUserByID(const std::string& userID) {
        for (auto& user : users) {
            if (user->getUserID() == userID) {
                return user;
            }
        }
        return nullptr;
    }

    void displayAllBooks() const {
        std::cout << "Books in the library:" << std::endl;
        for (const auto& book : books) {
            book->display();
        }
    }

    void displayAllUsers() const {
        std::cout << "Users in the library:" << std::endl;
        for (const auto& user : users) {
            user->display();
        }
    }
};

void displayMenu() {
    std::cout << "\nLibrary Management System\n";
    std::cout << "1. Add Book\n";
    std::cout << "2. Add User\n";
    std::cout << "3. Borrow Book\n";
    std::cout << "4. Return Book\n";
    std::cout << "5. Display All Books\n";
    std::cout << "6. Display All Users\n";
    std::cout << "7. Exit\n";
    std::cout << "Enter your choice: ";
}

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