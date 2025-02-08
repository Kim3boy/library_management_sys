 #include <cassert>
#include <sstream>
#include "library.h"

// Utility function to capture cout output
class CoutRedirect {
    std::streambuf* old;
    std::stringstream stream;
public:
    CoutRedirect() : old(std::cout.rdbuf(stream.rdbuf())) {}
    ~CoutRedirect() { std::cout.rdbuf(old); }
    std::string str() const { return stream.str(); }
};

void testNullPointerHandling() {
    std::cout << "\nTesting Null Pointer Handling..." << std::endl;
    
    Library library;
    
    // Test adding null book
    {
        CoutRedirect redirect;
        library.addBook(nullptr);
        assert(redirect.str().empty()); // Should not add or print anything
    }
    
    // Test adding null user
    {
        CoutRedirect redirect;
        library.addUser(nullptr);
        assert(redirect.str().empty()); // Should not add or print anything
    }
    
    std::cout << "Null Pointer Handling Tests Passed!" << std::endl;
}

void testEmptyInputs() {
    std::cout << "\nTesting Empty Inputs..." << std::endl;
    
    // Test book with empty fields
    Book emptyBook("", "", "");
    assert(emptyBook.getTitle().empty());
    assert(emptyBook.getAuthor().empty());
    assert(emptyBook.getISBN().empty());
    
    // Test user with empty fields
    User emptyUser("", "");
    assert(emptyUser.getName().empty());
    assert(emptyUser.getUserID().empty());
    
    // Test searching with empty strings
    Library library;
    assert(library.searchBookByTitle("") == nullptr);
    assert(library.searchUserByID("") == nullptr);
    
    std::cout << "Empty Inputs Tests Passed!" << std::endl;
}

void testInvalidBookOperations() {
    std::cout << "\nTesting Invalid Book Operations..." << std::endl;
    
    Library library;
    User user("Test User", "TEST-ID");
    
    // Try to borrow non-existent book
    {
        CoutRedirect redirect;
        user.borrowBook(nullptr);
        assert(redirect.str().find("not available") != std::string::npos);
    }
    
    // Try to return non-existent book
    {
        CoutRedirect redirect;
        user.returnBook(nullptr);
        assert(redirect.str().find("not borrowed") != std::string::npos);
    }
    
    // Try to borrow same book twice
    Book* book = new Book("Test Book", "Test Author", "TEST-ISBN");
    library.addBook(book);
    
    {
        CoutRedirect redirect;
        user.borrowBook(book);
        user.borrowBook(book); // Try to borrow again
        assert(redirect.str().find("not available") != std::string::npos);
    }
    
    delete book;
    std::cout << "Invalid Book Operations Tests Passed!" << std::endl;
}

void testDuplicateEntries() {
    std::cout << "\nTesting Duplicate Entries..." << std::endl;
    
    Library library;
    
    // Add books with same title but different ISBN
    Book* book1 = new Book("Same Title", "Author 1", "ISBN-1");
    Book* book2 = new Book("Same Title", "Author 2", "ISBN-2");
    
    library.addBook(book1);
    library.addBook(book2);
    
    // Search should return the first book with matching title
    assert(library.searchBookByTitle("Same Title") == book1);
    
    // Add users with same name but different IDs
    User* user1 = new User("Same Name", "ID-1");
    User* user2 = new User("Same Name", "ID-2");
    
    library.addUser(user1);
    library.addUser(user2);
    
    // Search should return correct user based on ID
    assert(library.searchUserByID("ID-1") == user1);
    assert(library.searchUserByID("ID-2") == user2);
    
    delete book1;
    delete book2;
    std::cout << "Duplicate Entries Tests Passed!" << std::endl;
}

void testBoundaryConditions() {
    std::cout << "\nTesting Boundary Conditions..." << std::endl;
    
    Library library;
    
    // Test with very long strings
    std::string longString(1000, 'a'); // String with 1000 'a' characters
    
    Book* longBook = new Book(longString, longString, longString);
    User* longUser = new User(longString, longString);
    
    library.addBook(longBook);
    library.addUser(longUser);
    
    assert(library.searchBookByTitle(longString) == longBook);
    assert(library.searchUserByID(longString) == longUser);
    
    // Test special characters in strings
    Book* specialBook = new Book("Book!@#$%", "Author&*()", "ISBN<>?");
    User* specialUser = new User("User!@#$%", "ID&*()");
    
    library.addBook(specialBook);
    library.addUser(specialUser);
    
    assert(library.searchBookByTitle("Book!@#$%") == specialBook);
    assert(library.searchUserByID("ID&*()") == specialUser);
    
    delete longBook;
    delete specialBook;
    std::cout << "Boundary Conditions Tests Passed!" << std::endl;
}

void testConcurrentOperations() {
    std::cout << "\nTesting Concurrent Operations..." << std::endl;
    
    Library library;
    Book* book = new Book("Popular Book", "Author", "ISBN");
    library.addBook(book);
    
    User* user1 = new User("User 1", "ID1");
    User* user2 = new User("User 2", "ID2");
    library.addUser(user1);
    library.addUser(user2);
    
    // User 1 borrows the book
    user1->borrowBook(book);
    
    // User 2 tries to borrow the same book
    {
        CoutRedirect redirect;
        user2->borrowBook(book);
        assert(redirect.str().find("not available") != std::string::npos);
    }
    
    // User 2 tries to return a book they never borrowed
    {
        CoutRedirect redirect;
        user2->returnBook(book);
        assert(redirect.str().find("not borrowed") != std::string::npos);
    }
    
    delete book;
    std::cout << "Concurrent Operations Tests Passed!" << std::endl;
}

int main() {
    try {
        testNullPointerHandling();
        testEmptyInputs();
        testInvalidBookOperations();
        testDuplicateEntries();
        testBoundaryConditions();
        testConcurrentOperations();
        
        std::cout << "\nAll negative tests passed successfully!" << std::endl;
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Test failed with exception: " << e.what() << std::endl;
        return 1;
    }
}