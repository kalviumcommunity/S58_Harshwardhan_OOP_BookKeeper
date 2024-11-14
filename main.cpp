#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Book {
private:
    string title;
    string author;
    string ISBN;
    bool isAvailable;

public:
    static int totalBooks; // Static variable to keep track of total books added

    Book(string t, string a, string isbn)
        : title(t), author(a), ISBN(isbn), isAvailable(true) {
        totalBooks++; // Increment totalBooks whenever a new book is created
    }

    // Destructor
    ~Book() {
        totalBooks--; // Decrement totalBooks when a book is destroyed
    }

    // Accessors (getters)
    string getTitle() const {
        return this->title;
    }

    string getAuthor() const {
        return this->author;
    }

    string getISBN() const {
        return this->ISBN;
    }

    bool checkAvailability() const {
        return this->isAvailable;
    }

    // Mutators (setters)
    void setTitle(const string& t) {
        this->title = t;
    }

    void setAuthor(const string& a) {
        this->author = a;
    }

    void setISBN(const string& isbn) {
        this->ISBN = isbn;
    }

    void setAvailability(bool status) {
        this->isAvailable = status;
    }

    void getDetails() const {
        cout << "Title: " << title << endl;
        cout << "Author: " << author << endl;
        cout << "ISBN: " << ISBN << endl;
        cout << "Available: " << (isAvailable ? "Yes" : "No") << endl;
    }
};

int Book::totalBooks = 0; // Initialize static variable

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

                Book* newBook = new Book(title, author, isbn); // Dynamic allocation
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