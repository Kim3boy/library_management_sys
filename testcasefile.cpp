#include <cassert>
#include <sstream>
#include <iostream>
#include "library.h" // with the original code is in library.h

// Utility function to capture cout output
class CoutRedirect {
    std::streambuf* old;
    std::stringstream stream;
public:
    CoutRedirect() : old(std::cout.rdbuf(stream.rdbuf())) {}
    ~CoutRedirect() { std::cout.rdbuf(old); }
    std::string str() const { return stream.str(); }
};

void testBookClass() {
    std::cout << "\nTesting Book Class..." << std::endl;
    
    // Test book creation and getters
    Book book("The Hobbit", "J.R.R. Tolkien", "978-0547928227");
    assert(book.getTitle() == "The Hobbit");
    assert(book.getAuthor() == "J.R.R. Tolkien");
    assert(book.getISBN() == "978-0547928227");
    assert(book.isBookAvailable() == true);
    
    // Test availability setting
    book.setAvailability(false);
    assert(book.isBookAvailable() == false);
    
    // Test display function
    CoutRedirect redirect;
    book.display();
    assert(redirect.str().find("The Hobbit") != std::string::npos);
    assert(redirect.str().find("J.R.R. Tolkien") != std::string::npos);
    
    std::cout << "Book Class Tests Passed!" << std::endl;
}

void testUserClass() {
    std::cout << "\nTesting User Class..." << std::endl;
    
    User user("John Doe", "U001");
    Book* book1 = new Book("Book1", "Author1", "ISBN1");
    Book* book2 = new Book("Book2", "Author2", "ISBN2");
    
    // Test user creation and getters
    assert(user.getName() == "John Doe");
    assert(user.getUserID() == "U001");
    
    // Test borrowing books
    {
        CoutRedirect redirect;
        user.borrowBook(book1);
        assert(redirect.str().find("has borrowed") != std::string::npos);
        assert(!book1->isBookAvailable());
    }
    
    // Test borrowing unavailable book
    {
        CoutRedirect redirect;
        user.borrowBook(book1);
        assert(redirect.str().find("not available") != std::string::npos);
    }
    
    // Test returning books
    {
        CoutRedirect redirect;
        user.returnBook(book1);
        assert(redirect.str().find("has returned") != std::string::npos);
        assert(book1->isBookAvailable());
    }
    
    // Test returning non-borrowed book
    {
        CoutRedirect redirect;
        user.returnBook(book2);
        assert(redirect.str().find("was not borrowed") != std::string::npos);
    }
    
    // Clean up
    delete book1;
    delete book2;
    
    std::cout << "User Class Tests Passed!" << std::endl;
}

void testLibraryClass() {
    std::cout << "\nTesting Library Class..." << std::endl;
    
    Library library;
    Book* book = new Book("Test Book", "Test Author", "TEST-ISBN");
    User* user = new User("Test User", "TEST-ID");
    
    // Test adding book and user
    {
        CoutRedirect redirect;
        library.addBook(book);
        library.addUser(user);
        assert(redirect.str().find("Added book") != std::string::npos);
        assert(redirect.str().find("Added user") != std::string::npos);
    }
    
    // Test search functions
    assert(library.searchBookByTitle("Test Book") == book);
    assert(library.searchBookByTitle("Nonexistent Book") == nullptr);
    assert(library.searchUserByID("TEST-ID") == user);
    assert(library.searchUserByID("INVALID-ID") == nullptr);
    
    // Test display functions
    {
        CoutRedirect redirect;
        library.displayAllBooks();
        assert(redirect.str().find("Test Book") != std::string::npos);
        library.displayAllUsers();
        assert(redirect.str().find("Test User") != std::string::npos);
    }
    
    std::cout << "Library Class Tests Passed!" << std::endl;
}

void testFullWorkflow() {
    std::cout << "\nTesting Full Workflow..." << std::endl;
    
    Library library;
    
    // Add books and users
    Book* book1 = new Book("1984", "George Orwell", "978-0451524935");
    Book* book2 = new Book("Brave New World", "Aldous Huxley", "978-0060850524");
    User* user1 = new User("Alice Smith", "U001");
    User* user2 = new User("Bob Jones", "U002");
    
    library.addBook(book1);
    library.addBook(book2);
    library.addUser(user1);
    library.addUser(user2);
    
    // Test borrowing workflow
    user1->borrowBook(book1);
    assert(!book1->isBookAvailable());
    
    // Test that another user can't borrow the same book
    {
        CoutRedirect redirect;
        user2->borrowBook(book1);
        assert(redirect.str().find("not available") != std::string::npos);
    }
    
    // Test returning workflow
    user1->returnBook(book1);
    assert(book1->isBookAvailable());
    
    // Now user2 can borrow the book
    user2->borrowBook(book1);
    assert(!book1->isBookAvailable());
    
    std::cout << "Full Workflow Tests Passed!" << std::endl;
}

int main() {
    try {
        testBookClass();
        testUserClass();
        testLibraryClass();
        testFullWorkflow();
        
        std::cout << "\nAll tests passed successfully!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Test failed with exception: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}