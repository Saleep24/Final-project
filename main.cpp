#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

// Forward declaration
class User;

// Class for Book
class Book {
public:
    string title; // Made public
    string author;
    bool available;
    int borrowCount;

    Book(string _title, string _author) : title(_title), author(_author), available(true), borrowCount(0) {}

    void displayDetails() {
        cout << "Title: " << title << endl;
        cout << "Author: " << author << endl;
        cout << "Availability: " << (available ? "Available" : "Not Available") << endl;
        cout << "Times Borrowed: " << borrowCount << endl;
    }

    void borrowBook(const User& user) {
        if (available) {
            available = false;
            borrowCount++;
            cout << "Book \"" << title << "\" successfully borrowed by user with ID: " << user.getID() << endl;
        } else {
            cout << "Sorry, the book is not available for borrowing." << endl;
        }
    }

    void renewBook() {
        if (!available) {
            cout << "You have successfully renewed the book." << endl;
        } else {
            cout << "Sorry, the book is not currently borrowed." << endl;
        }
    }

    bool isAvailable() {
        return available;
    }

    void makeAvailable() {
        available = true;
    }
};

// Class for User
class User {
private:
    string id;

public:
    User(string _id) : id(_id) {}

    string getID() const {
        return id;
    }
};

// Class for Library
class Library {
private:
    vector<Book> books;
    string adminPassword;
    map<string, User> users;

public:
    Library(string _adminPassword) : adminPassword(_adminPassword) {}

    void addUser(string id) {
        users[id] = User(id);
        cout << "User with ID: " << id << " added successfully." << endl;
    }

    void addBook(string title, string author, string password) {
        if (password != adminPassword) {
            cout << "Sorry, you don't have permission to add books." << endl;
            return;
        }
        books.push_back(Book(title, author));
        cout << "Book added successfully." << endl;
        displayBooks();
    }

    void displayBooks() {
        cout << "\nAvailable Books:" << endl;
        for (const auto& book : books) {
            if (book.isAvailable()) {
                cout << "Title: " << book.title << ", Author: " << book.author << endl;
            }
        }
    }

    void searchBook(string title) {
        bool found = false;
        for (const auto& book : books) {
            if (book.isAvailable() && book.title == title) {
                book.displayDetails();
                found = true;
                break;
            }
        }
        if (!found) {
            cout << "Book not found or not available." << endl;
        }
    }

    void borrowBook(string title, const User& user) {
        for (auto& book : books) {
            if (book.title == title) {
                book.borrowBook(user);
                return;
            }
        }
        cout << "Book not found." << endl;
    }

    void renewBook(string title) {
        for (auto& book : books) {
            if (!book.isAvailable() && book.title == title) {
                book.renewBook();
                return;
            }
        }
        cout << "Book not found or not currently borrowed." << endl;
    }
};

int main() {
    Library library("admin123");

    // Adding some initial books
    library.addBook("The Great Gatsby", "F. Scott Fitzgerald", "admin123");
    library.addBook("To Kill a Mockingbird", "Harper Lee", "admin123");
    library.addBook("1984", "George Orwell", "admin123");

    // Adding some initial users
    library.addUser("user1");
    library.addUser("user2");
    library.addUser("user3");

    int choice;
    string title, password, userId;

    do {
        cout << "\nLibrary Management System\n";
        cout << "1. Search Book\n";
        cout << "2. Borrow Book\n";
        cout << "3. Renew Book\n";
        cout << "4. Add Book (Admin Only)\n";
        cout << "5. Add User\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter book title: ";
                cin.ignore();
                getline(cin, title);
                library.searchBook(title);
                break;
            case 2:
                cout << "Enter user ID: ";
                cin >> userId;
                cout << "Enter book title: ";
                cin.ignore();
                getline(cin, title);
                library.borrowBook(title, library.users[userId]);
                break;
            case 3:
                cout << "Enter book title: ";
                cin.ignore();
                getline(cin, title);
                library.renewBook(title);
                break;
            case 4:
                cout << "Enter admin password: ";
                cin >> password;
                cout << "Enter book title: ";
                cin.ignore();
                getline(cin, title);
                library.addBook(title, "Unknown", password);
                break;
            case 5:
                cout << "Enter user ID to add: ";
                cin >> userId;
                library.addUser(userId);
                break;
            case 6:
                cout << "Exiting program. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 6);

    return 0;
}
