#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Base class Item
class Item {
protected:
    string title;
    string author;

public:
    Item(string t, string a) : title(t), author(a) {}

    virtual void getDetails() const = 0; // Pure virtual function

    string getTitle() const {
        return title;
    }

    string getAuthor() const {
        return author;
    }
};

// Base class Borrowable
class Borrowable {
protected:
    bool isAvailable;

public:
    Borrowable() : isAvailable(true) {}

    bool checkAvailability() const {
        return isAvailable;
    }

    void setAvailability(bool status) {
        isAvailable = status;
    }
};

// Derived class Book using single inheritance from Item
class Book : public Item {
private:
    string ISBN;

public:
    static int totalBooks; // Static variable to keep track of total books added

    // Default constructor
    Book() : Item("", ""), ISBN("") {
        totalBooks++;
    }

    // Parameterized constructor
    Book(string t, string a, string isbn)
        : Item(t, a), ISBN(isbn) {
        totalBooks++;
    }

    // Copy constructor
    Book(const Book& other)
        : Item(other.title, other.author), ISBN(other.ISBN) {
        totalBooks++;
    }

    // Destructor
    ~Book() {
        totalBooks--;
    }

    string getISBN() const {
        return ISBN;
    }

    void getDetails() const override {
        cout << "Title: " << title << endl;
        cout << "Author: " << author << endl;
        cout << "ISBN: " << ISBN << endl;
    }
};

int Book::totalBooks = 0; // Initialize static variable

// Derived class BorrowableBook using multiple inheritance from Book and Borrowable
class BorrowableBook : public Book, public Borrowable {
public:
    BorrowableBook(string t, string a, string isbn)
        : Book(t, a, isbn), Borrowable() {}

    void getDetails() const override {
        Book::getDetails();
        cout << "Available: " << (isAvailable ? "Yes" : "No") << endl;
    }
};

class Library {
private:
    vector<Book*> books;
    static int searchCount; // Static variable to keep track of searches

public:
    void addBook(Book* book) {
        books.push_back(book);
        cout << "Book added successfully." << endl;
    }

    void removeBook(string isbn) {
        for (auto it = books.begin(); it != books.end(); ++it) {
            if ((*it)->getISBN() == isbn) {
                delete *it; // Deleting the book
                books.erase(it);
                cout << "Book removed successfully." << endl;
                return;
            }
        }
        cout << "Book not found." << endl;
    }

    void searchBookByTitle(string title) const {
        for (const auto& book : books) {
            if (book->getTitle() == title) {
                book->getDetails();
                Library::searchCount++; // Increment search count
                return;
            }
        }
        cout << "Book not found." << endl;
    }

    void searchBookByAuthor(string author) const {
        for (const auto& book : books) {
            if (book->getAuthor() == author) {
                book->getDetails();
                Library::searchCount++; // Increment search count
                return;
            }
        }
        cout << "Book not found." << endl;
    }

    void listBooks() const {
        if (books.empty()) {
            cout << "No books in the library." << endl;
            return;
        }

        for (const auto& book : books) {
            book->getDetails();
            cout << "-------------------" << endl;
        }
    }

    static int getTotalSearches() {
        return searchCount;
    }

    ~Library() {
        for (auto book : books) {
            delete book;
        }
    }
};

int Library::searchCount = 0; // Initialize static variable

// Main code
int main() {
    Library library;
    int choice;
    for (;;) {
        cout << "\nLibrary Management System\n";
        cout << "1. Add Book\n";
        cout << "2. Remove Book\n";
        cout << "3. Search Book by Title\n";
        cout << "4. Search Book by Author\n";
        cout << "5. List All Books\n";
        cout << "6. Show Total Books and Searches\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();
        switch (choice) {
            case 1: {
                string title, author, isbn;
                cout << "Enter book title: ";
                getline(cin, title);
                cout << "Enter book author: ";
                getline(cin, author);
                cout << "Enter book ISBN: ";
                getline(cin, isbn);
                Book* newBook = new BorrowableBook(title, author, isbn); // Using BorrowableBook
                library.addBook(newBook);
                break;
            }
            case 2: {
                string isbn;
                cout << "Enter ISBN of the book to remove: ";
                getline(cin, isbn);
                library.removeBook(isbn);
                break;
            }
            case 3: {
                string title;
                cout << "Enter title of the book to search: ";
                getline(cin, title);
                library.searchBookByTitle(title);
                break;
            }
            case 4: {
                string author;
                cout << "Enter author of the book to search: ";
                getline(cin, author);
                library.searchBookByAuthor(author);
                break;
            }
            case 5:
                library.listBooks();
                break;
            case 6:
                cout << "Total Books in Library: " << Book::totalBooks << endl;
                cout << "Total Searches Conducted: " << Library::getTotalSearches() << endl;
                break;
            case 7:
                cout << "Exiting the system..." << endl;
                return 0;
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    }
    return 0;
}