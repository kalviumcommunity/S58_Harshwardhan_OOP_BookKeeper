#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Book class representing a book in the library
class Book {
private:
    string title;
    string author;
    string ISBN;
    bool isAvailable;

public:
    // Constructor to initialize a book
    Book(string t, string a, string isbn)
        : title(t), author(a), ISBN(isbn), isAvailable(true) {}

    // Method to get book details
    void getDetails() const {
        cout << "Title: " << title << endl;
        cout << "Author: " << author << endl;
        cout << "ISBN: " << ISBN << endl;
        cout << "Available: " << (isAvailable ? "Yes" : "No") << endl;
    }

    // Method to check availability of the book
    bool checkAvailability() const {
        return this->isAvailable;
    }

    // Method to get the book's ISBN
    string getISBN() const {
        return this->ISBN;
    }

    // Method to set availability status
    void setAvailability(bool status) {
        this->isAvailable = status;
    }

    // Method to get the title
    string getTitle() const {
        return this->title;
    }

    // Method to get the author
    string getAuthor() const {
        return this->author;
    }
};

// Library class representing a collection of books
class Library {
private:
    vector<Book> books;  // Array (vector) of objects

public:
    // Method to add a book to the library
    void addBook(const Book& book) {
        books.push_back(book);
        cout << "Book added successfully." << endl;
    }

    // Method to remove a book from the library by ISBN
    void removeBook(string isbn) {
        for (auto it = books.begin(); it != books.end(); ++it) {
            if (it->getISBN() == isbn) {
                books.erase(it);
                cout << "Book removed successfully." << endl;
                return;
            }
        }
        cout << "Book not found." << endl;
    }

    // Method to search for a book by title
    void searchBookByTitle(string title) const {
        for (const auto& book : books) {
            if (book.getTitle() == title) {
                book.getDetails();
                return;
            }
        }
        cout << "Book not found." << endl;
    }

    // Method to search for a book by author
    void searchBookByAuthor(string author) const {
        for (const auto& book : books) {
            if (book.getAuthor() == author) {
                book.getDetails();
                return;
            }
        }
        cout << "Book not found." << endl;
    }

    // Method to list all books in the library
    void listBooks() const {
        if (books.empty()) {
            cout << "No books in the library." << endl;
            return;
        }

        for (const auto& book : books) {
            book.getDetails();
            cout << "-------------------" << endl;
        }
    }
};

// Main code under in main
int main() {
    Library library;
    int choice;

    do {
        cout << "\nLibrary Management System\n";
        cout << "1. Add Book\n";
        cout << "2. Remove Book\n";
        cout << "3. Search Book by Title\n";
        cout << "4. Search Book by Author\n";
        cout << "5. List All Books\n";
        cout << "6. Exit\n";
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

                Book newBook(title, author, isbn);
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
                cout << "Exiting the system..." << endl;
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    } while (choice != 6);

    return 0;
}