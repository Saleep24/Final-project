#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm> // For find

using namespace std;

// Book structure
struct Book {
    string title;
    string author;
    int ISBN;
    bool available;
};

// Member structure
struct Member {
    string name;
    int memberID;
    vector<int> borrowedBooks; // Stores ISBNs of borrowed books
};

// Global vectors for storing books and members
vector<Book> books;
vector<Member> members;

// Function prototypes
void addBook();
void issueBook();
void returnBook();
void searchBooks();
void displayAllBooks();
void addMember();
void displayAllMembers();
void saveDataToFile();
void loadDataFromFile();

int main() {
    loadDataFromFile(); // Load data on startup

    int choice;

    do {
        cout << "\nLibrary Management System\n";
        cout << "1. Add Book\n";
        cout << "2. Issue Book\n";
        cout << "3. Return Book\n";
        cout << "4. Search Books\n";
        cout << "5. Display All Books\n";
        cout << "6. Add Member\n";
        cout << "7. Display All Members\n";
        cout << "8. Save Data\n"; // Option to save data
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addBook(); break;
            case 2: issueBook(); break;
            case 3: returnBook(); break;
            case 4: searchBooks(); break;
            case 5: displayAllBooks(); break;
            case 6: addMember(); break;
            case 7: displayAllMembers(); break;
            case 8: saveDataToFile(); break;
            case 0: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice!\n";
        }
    } while (choice != 0);

    saveDataToFile(); // Save data on exit
    return 0;
}

// Function definitions
void addBook() {
    Book book;
    cout << "Enter Book Title: ";
    cin.ignore(); // Clear input buffer
    getline(cin, book.title);
    cout << "Enter Author: ";
    getline(cin, book.author);
    cout << "Enter ISBN: ";
    cin >> book.ISBN;
    book.available = true;
    books.push_back(book);
    cout << "Book added successfully!\n";
}

void issueBook() {
    int ISBN, memberID;
    bool foundBook = false;

    cout << "Enter ISBN of the book to issue: ";
    cin >> ISBN;

    // Find the book by ISBN
    for (size_t i = 0; i < books.size(); ++i) {
        if (books[i].ISBN == ISBN && books[i].available) {
            foundBook = true;
            

            cout << "Enter Member ID: ";
            cin >> memberID;

            // Find the member by ID and add borrowed book ISBN
            for (size_t j = 0; j < members.size(); ++j) {
                if (members[j].memberID == memberID) {
                    members[j].borrowedBooks.push_back(ISBN);
                    books[i].available = false;  // Mark book as issued
                    cout << "Book issued successfully to " << members[j].name << endl;
                    return;
                }
            }
            cout << "Invalid Member ID!\n";
            books[i].available = true; // Revert availability change
            return;
        }
    }

    if (!foundBook) {
        cout << "Book not found or unavailable!\n";
    }
}

void returnBook() {
    int ISBN, memberID;
    bool foundBook = false;

    cout << "Enter ISBN of the book to return: ";
    cin >> ISBN;

    // Find the book by ISBN
    for (size_t i = 0; i < books.size(); ++i) {
        if (books[i].ISBN == ISBN) {
            foundBook = true;
            books[i].available = true;   // Mark book as available

            cout << "Enter Member ID: ";
            cin >> memberID;

            // Find the member by ID and remove borrowed book ISBN
            for (size_t j = 0; j < members.size(); ++j) {
                if (members[j].memberID == memberID) {
                    vector<int>::iterator it = find(members[j].borrowedBooks.begin(), members[j].borrowedBooks.end(), ISBN);
                    if (it != members[j].borrowedBooks.end()) {
                        members[j].borrowedBooks.erase(it);
                        cout << "Book returned successfully!\n";
                        return;
                    } else {
                        cout << "Member has not borrowed this book!\n";
                        return;
                    }
                }
            }
        }
    }

    if (!foundBook) {
        cout << "Book not found!\n";
    }
}

void searchBooks() {
    string searchTerm;
    int choice;

    cout << "Search by:\n";
    cout << "1. Title\n";
    cout << "2. Author\n";
    cout << "3. ISBN\n";
    cout << "Enter your choice: ";
    cin >> choice;

    cin.ignore(); // Clear input buffer
    cout << "Enter search term: ";
    getline(cin, searchTerm);

    bool found = false;
    switch (choice) {
        case 1:
            for (size_t i = 0; i < books.size(); ++i) {
                if (books[i].title.find(searchTerm) != string::npos) {
                    cout << books[i].title << " - " << books[i].author << " (ISBN: " << books[i].ISBN << ")" << endl;
                    found = true;
                }
            }
            break;
        case 2: // Search by Author
            for (size_t i = 0; i < books.size(); ++i) {
                if (books[i].author.find(searchTerm) != string::npos) {
                    cout << "Title: " << books[i].title << endl;
                    cout << "Author: " << books[i].author << endl;
                    cout << "ISBN: " << books[i].ISBN << endl;
                    cout << "Available: " << (books[i].available ? "Yes" : "No") << endl;
                    cout << "-------\n";
                    found = true;
                }
            }
            break;
        case 3: // Search by ISBN
            int searchISBN;
            try {
                searchISBN = stoi(searchTerm);
            } catch (exception& e) {
                cout << "Invalid ISBN format!\n";
                break;
            }
            for (size_t i = 0; i < books.size(); ++i) {
                if (books[i].ISBN == searchISBN) {
                    cout << "Title: " << books[i].title << endl;
                    cout << "Author: " << books[i].author << endl;
                    cout << "ISBN: " << books[i].ISBN << endl;
                    cout << "Available: " << (books[i].available ? "Yes" : "No") << endl;
                    cout << "-------\n";
                    found = true;
                }
            }
            break;
        default:
            cout << "Invalid choice!\n";
    }

    if (!found) {
        cout << "No matching books found.\n";
    }
}

void displayAllBooks() {
    if (books.empty()) {
        cout << "No books in the library.\n";
        return;
    }

    cout << "\nAll Books:\n";
    for (size_t i = 0; i < books.size(); ++i) {
        cout << "Title: " << books[i].title << endl;
        cout << "Author: " << books[i].author << endl;
        cout << "ISBN: " << books[i].ISBN << endl;
        cout << "Available: " << (books[i].available ? "Yes" : "No") << endl;
        cout << "-------\n";
    }
}

void addMember() {
    Member member;
    cout << "Enter Member Name: ";
    cin.ignore();
    getline(cin, member.name);
    cout << "Enter Member ID: ";
    cin >> member.memberID;
    members.push_back(member);
    cout << "Member added successfully!\n";
}

void displayAllMembers() {
    if (members.empty()) {
        cout << "No members in the library.\n";
    } else {
        cout << "\nAll Members:\n";
        for (size_t i = 0; i < members.size(); ++i) {
            cout << "Name: " << members[i].name << endl;
            cout << "Member ID: " << members[i].memberID << endl;
            cout << "-------\n";
        }
    }
}

// Functions to save data to a file
void saveDataToFile() {
    ofstream file("library_data.txt");
    if (file.is_open()) {
        // Save Books
        for (size_t i = 0; i < books.size(); ++i) {
            file << books[i].title << "," << books[i].author << "," << books[i].ISBN << "," << books[i].available << endl;
        }
        // Save Members
        for (size_t i = 0; i < members.size(); ++i) {
            file << members[i].name << "," << members[i].memberID;
            for (size_t j = 0; j < members[i].borrowedBooks.size(); ++j) {
                file << "," << members[i].borrowedBooks[j];
            }
            file << endl;
        }
        file.close();
        cout << "Data saved successfully!\n";
    } else {
        cout << "Failed to open file!\n";
    }
}

// Function to load data from a file
void loadDataFromFile() {
    ifstream file("library_data.txt");
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            vector<string> data;
            string token;
            size_t pos = 0;

            // Split the line (comma-separated data) into tokens
            while ((pos = line.find(",")) != string::npos) {
                token = line.substr(0, pos);
                data.push_back(token);
                line.erase(0, pos + 1);
            }
            data.push_back(line); // Add the last token

            // Process the tokens based on whether it's book or member data
            if (data.size() == 4) { // Book data
                Book book;
                book.title = data[0];
                book.author = data[1];
                book.ISBN = stoi(data[2]); // Convert ISBN string to int
                book.available = (data[3] == "true") ? true : false;
                books.push_back(book);      
            } else { // Member data
                Member member;
                member.name = data[0];
                member.memberID = stoi(data[1]);

                for (size_t i = 2; i < data.size(); ++i) {
                    member.borrowedBooks.push_back(stoi(data[i]));
                }
                members.push_back(member);
            }
        }
        file.close();
    } else {
        cout << "Failed to open file!\n";
    }
}