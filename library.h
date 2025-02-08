 #ifndef LIBRARY_H
#define LIBRARY_H

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
    Book(std::string title, std::string author, std::string ISBN);
    std::string getTitle() const;
    std::string getAuthor() const;
    std::string getISBN() const;
    bool isBookAvailable() const;
    void setAvailability(bool availability);
    void display() const;
};

class User {
private:
    std::string name;
    std::string userID;
    std::vector<Book*> borrowedBooks;

public:
    User(std::string name, std::string userID);
    std::string getName() const;
    std::string getUserID() const;
    void borrowBook(Book* book);
    void returnBook(Book* book);
    void display() const;
};

class Library {
private:
    std::vector<Book*> books;
    std::vector<User*> users;

public:
    void addBook(Book* book);
    void addUser(User* user);
    Book* searchBookByTitle(const std::string& title);
    User* searchUserByID(const std::string& userID);
    void displayAllBooks() const;
    void displayAllUsers() const;
};

void displayMenu();

#endif // LIBRARY_H