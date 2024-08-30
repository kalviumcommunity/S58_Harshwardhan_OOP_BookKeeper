#include <iostream>
#include <vector>
#include <string>

using namespace std;

// class named Book
class Book {
private:
    string title;
    string author;
    string ISBN;
    bool isAvailable;

public:
    // initializing a book using constructor
    Book(string t, string a, string isbn)
        : title(t), author(a), ISBN(isbn), isAvailable(true) {}

    //get book Method
    void getDetails() const {
        cout << "Title: " << title << endl;
        cout << "Author: " << author << endl;
        cout << "ISBN: " << ISBN << endl;
        cout << "Available: " << (isAvailable ? "Yes" : "No") << endl;
    }

    //check availability of the book method
    bool checkAvailability() const {
        return isAvailable;
    }

    //get book's ISBN method
    string getISBN() const {
        return ISBN;
    }

    //set availability status method
    void setAvailability(bool status) {
        isAvailable = status;
    }

    //get title method
    string getTitle() const {
        return title;
    }

    //get author method
    string getAuthor() const {
        return author;
    }
};

// Library class
class Library {
private:
    vector<Book> books;

public:
    //add book method
    void addBook(const Book& book) {
        books.push_back(book);
        cout << "Book added successfully." << endl;
    }

    //remove book method
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

    //search book method(using title)
    void searchBookByTitle(string title) const {
        for (const auto& book : books) {
            if (book.getTitle() == title) {
                book.getDetails();
                return;
            }
        }
        cout << "Book not found." << endl;
    }

    //search book method(using author)
    void searchBookByAuthor(string author) const {
        for (const auto& book : books) {
            if (book.getAuthor() == author) {
                book.getDetails();
                return;
            }
        }
        cout << "Book not found." << endl;
    }

    //list all books method
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