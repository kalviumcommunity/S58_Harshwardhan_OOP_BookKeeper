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
    Book(string t, string a, string isbn)
        : title(t), author(a), ISBN(isbn), isAvailable(true) {}

    // Destructor
    ~Book() {}

    void getDetails() const {
        cout << "Title: " << title << endl;
        cout << "Author: " << author << endl;
        cout << "ISBN: " << ISBN << endl;
        cout << "Available: " << (isAvailable ? "Yes" : "No") << endl;
    }

    bool checkAvailability() const {
        return this->isAvailable;
    }

    string getISBN() const {
        return this->ISBN;
    }

    void setAvailability(bool status) {
        this->isAvailable = status;
    }

    string getTitle() const {
        return this->title;
    }

    string getAuthor() const {
        return this->author;
    }
};

class Library {
private:
    vector<Book*> books;

public:
    void addBook(Book* book) {
        books.push_back(book);
        cout << "Book added successfully." << endl;
    }

    void removeBook(string isbn) {
        for (auto it = books.begin(); it != books.end(); ++it) {
            if ((*it)->getISBN() == isbn) {
                delete *it; //here
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
                return;
            }
        }
        cout << "Book not found." << endl;
    }

    void searchBookByAuthor(string author) const {
        for (const auto& book : books) {
            if (book->getAuthor() == author) {
                book->getDetails();
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

    ~Library() {
        for (auto book : books) {
            delete book;
        }
    }
};

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
                cout << "Exiting the system..." << endl;
                return 0;
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    }

    return 0;
}
