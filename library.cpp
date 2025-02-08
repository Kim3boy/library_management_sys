#include "library.h"

// Book class implementations
Book::Book(std::string title, std::string author, std::string ISBN)
    : title(title), author(author), ISBN(ISBN), isAvailable(true) {}

std::string Book::getTitle() const { return title; }
std::string Book::getAuthor() const { return author; }
std::string Book::getISBN() const { return ISBN; }
bool Book::isBookAvailable() const { return isAvailable; }
void Book::setAvailability(bool availability) { isAvailable = availability; }

void Book::display() const {
    std::cout << "Title: " << title << ", Author: " << author
              << ", ISBN: " << ISBN << ", Available: " 
              << (isAvailable ? "Yes" : "No") << std::endl;
}

// User class implementations
User::User(std::string name, std::string userID)
    : name(name), userID(userID) {}

std::string User::getName() const { return name; }
std::string User::getUserID() const { return userID; }

void User::borrowBook(Book* book) {
    if (book && book->isBookAvailable()) {
        borrowedBooks.push_back(book);
        book->setAvailability(false);
        std::cout << name << " has borrowed the book: " << book->getTitle() << std::endl;
    } else {
        std::cout << "Book is not available for borrowing." << std::endl;
    }
}

void User::returnBook(Book* book) {
    auto it = std::find(borrowedBooks.begin(), borrowedBooks.end(), book);
    if (it != borrowedBooks.end()) {
        borrowedBooks.erase(it);
        book->setAvailability(true);
        std::cout << name << " has returned the book: " << book->getTitle() << std::endl;
    } else {
        std::cout << "This book was not borrowed by " << name << "." << std::endl;
    }
}

void User::display() const {
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

// Library class implementations
void Library::addBook(Book* book) {
    if (book) {
        books.push_back(book);
        std::cout << "Added book: " << book->getTitle() << std::endl;
    }
}

void Library::addUser(User* user) {
    if (user) {
        users.push_back(user);
        std::cout << "Added user: " << user->getName() << std::endl;
    }
}

Book* Library::searchBookByTitle(const std::string& title) {
    for (auto& book : books) {
        if (book->getTitle() == title) {
            return book;
        }
    }
    return nullptr;
}

User* Library::searchUserByID(const std::string& userID) {
    for (auto& user : users) {
        if (user->getUserID() == userID) {
            return user;
        }
    }
    return nullptr;
}

void Library::displayAllBooks() const {
    std::cout << "Books in the library:" << std::endl;
    for (const auto& book : books) {
        book->display();
    }
}

void Library::displayAllUsers() const {
    std::cout << "Users in the library:" << std::endl;
    for (const auto& user : users) {
        user->display();
    }
}

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