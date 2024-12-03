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

    virtual ~Item() = default; // Virtual destructor
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

    virtual ~Borrowable() = default; // Virtual destructor
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

// Library class
class Library {
private:
    vector<Item*> items; // Changed from Book* to Item*
    static int searchCount; // Static variable to keep track of searches

public:
    void addItem(Item* item) { // Changed from addBook to addItem
        items.push_back(item);
        cout << "Item added successfully." << endl;
    }

    void removeItem(string isbn) { // Changed from removeBook to removeItem
        for (auto it = items.begin(); it != items.end(); ++it) {
            Book* book = dynamic_cast<Book*>(*it);
            if (book && book->getISBN() == isbn) {
                delete *it; // Deleting the item
                items.erase(it);
                Book::totalBooks--; // Decrease the total books counter
                cout << "Item removed successfully." << endl;
                return;
            }
        }
        cout << "Item not found." << endl;
    }

    void listItems() const { // Changed from listBooks to listItems
        if (items.empty()) {
            cout << "No items in the library." << endl;
            return;
        }

        cout << "Listing all items in the library:\n";
        for (const auto& item : items) {
            item->getDetails();
            cout << "---------------------------------" << endl;
        }
    }

    const vector<Item*>& getItems() const { // Changed from getBooks to getItems
        return items;
    }

    static int getTotalSearches() {
        return searchCount;
    }

    static void incrementSearchCount() {
        searchCount++;
    }

    ~Library() {
        for (auto item : items) {
            delete item;
        }
    }
};

int Library::searchCount = 0; // Initialize static variable

// LibrarySearch class
class LibrarySearch {
public:
    static void searchItemByTitle(const Library& library, const string& title) { // Changed from searchBookByTitle to searchItemByTitle
        bool found = false;
        for (const auto& item : library.getItems()) {
            if (item->getTitle() == title) {
                item->getDetails();
                found = true;
            }
        }
        if (!found) {
            cout << "No items found with title: " << title << endl;
        } else {
            Library::incrementSearchCount();
        }
    }

    static void searchItemByAuthor(const Library& library, const string& author) { // Changed from searchBookByAuthor to searchItemByAuthor
        bool found = false;
        for (const auto& item : library.getItems()) {
            if (item->getAuthor() == author) {
                item->getDetails();
                found = true;
            }
        }
        if (!found) {
            cout << "No items found by author: " << author << endl;
        } else {
            Library::incrementSearchCount();
        }
    }
};

// Main code
int main() {
    Library library;
    int choice;

    for (;;) {
        cout << "\nLibrary Management System\n";
        cout << "1. Add Item\n"; // Changed from Add Book to Add Item
        cout << "2. Remove Item\n"; // Changed from Remove Book to Remove Item
        cout << "3. Search Item by Title\n"; // Changed from Search Book by Title to Search Item by Title
        cout << "4. Search Item by Author\n"; // Changed from Search Book by Author to Search Item by Author
        cout << "5. List All Items\n"; // Changed from List All Books to List All Items
        cout << "6. Show Total Books and Searches\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // Ignore newline character after reading choice

        switch (choice) {
            case 1: {
                string title, author, isbn;
                cout << "Enter item title: "; // Changed from book to item
                getline(cin, title);
                cout << "Enter item author: "; // Changed from book to item
                getline(cin, author);
                cout << "Enter item ISBN: "; // Changed from book to item
                getline(cin, isbn);
                Item* newItem = new BorrowableBook(title, author, isbn); // Using BorrowableBook
                library.addItem(newItem); // Changed from addBook to addItem
                break;
            }
            case 2: {
                string isbn;
                cout << "Enter ISBN of the item to remove: "; // Changed from book to item
                getline(cin, isbn);
                library.removeItem(isbn); // Changed from removeBook to removeItem
                break;
            }
            case 3: {
                string title;
                cout << "Enter title of the item to search: "; // Changed from book to item
                getline(cin, title);
                LibrarySearch::searchItemByTitle(library, title); // Changed from searchBookByTitle to searchItemByTitle
                break;
            }
            case 4: {
                string author;
                cout << "Enter author of the item to search: "; // Changed from book to item
                getline(cin, author);
                LibrarySearch::searchItemByAuthor(library, author); // Changed from searchBookByAuthor to searchItemByAuthor
                break;
            }
            case 5:
                library.listItems(); // Changed from listBooks to listItems
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