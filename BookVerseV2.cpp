#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

// Constants
const int MAX_BOOKS = 100; // Fixed array size for books

// Book class
class Book {
private:
    string title, author, genre;
    int publicationYear;

public:
    Book(string t = "", string a = "", string g = "", int y = 0)
        : title(t), author(a), genre(g), publicationYear(y) {}

    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    string getGenre() const { return genre; }
    int getPublicationYear() const { return publicationYear; }

    void displayDetails() const {
        cout << setw(20) << left << "Title: " << title << endl;
        cout << setw(20) << left << "Author: " << author << endl;
        cout << setw(20) << left << "Genre: " << genre << endl;
        cout << setw(20) << left << "Publication Year: " << publicationYear << endl;
        cout << string(40, '-') << endl;
    }

    bool isEmpty() const { return title.empty(); }
};

class BookManager {
private:
    Book books[MAX_BOOKS]; // Fixed array of books
    int bookCount;         // Current number of books

public:
    BookManager() : bookCount(0) {}

    // Add a new book
    void addBook(const Book &book) {
        if (bookCount >= MAX_BOOKS) {
            cout << "\n[Error] Book collection is full! Cannot add more books.\n";
            return;
        }
        books[bookCount++] = book;
        cout << "\n[Success] Book added successfully!\n";
    }

    // Display all books
    void displayAllBooks() const {
        if (bookCount == 0) {
            cout << "\n[Notice] No books in your collection yet!\n";
            return;
        }
        cout << "\n=== Books in Your Collection ===\n";
        for (int i = 0; i < bookCount; ++i) {
            cout << "Book #" << i + 1 << ":\n";
            books[i].displayDetails();
        }
    }

    // Search for books by title (normal search)
    void searchBooksByTitle() const {
        string partialTitle;
        cout << "\nEnter partial title to search (or 0 to go back): ";
        getline(cin, partialTitle);

        if (partialTitle == "0") {
            cout << "\n[Notice] Returning to main menu.\n";
            return;
        }

        bool found = false;
        cout << "\n=== Search Results ===\n";
        for (int i = 0; i < bookCount; ++i) {
            if (books[i].getTitle().find(partialTitle) != string::npos) {
                books[i].displayDetails();
                found = true;
            }
        }

        if (!found) {
            cout << "[Notice] No book found containing: \"" << partialTitle << "\"\n";
        }
    }

    // Delete a book with confirmation
    void deleteBookWithConfirmation() {
        string partialTitle;
        cout << "\nEnter partial title of the book to delete (or 0 to go back): ";
        getline(cin, partialTitle);

        if (partialTitle == "0") {
            cout << "\n[Notice] Returning to main menu.\n";
            return;
        }

        int foundIndexes[MAX_BOOKS], foundCount = 0;
        for (int i = 0; i < bookCount; ++i) {
            if (books[i].getTitle().find(partialTitle) != string::npos) {
                foundIndexes[foundCount++] = i;
            }
        }

        if (foundCount == 0) {
            cout << "\n[Notice] No book found containing: \"" << partialTitle << "\"\n";
            return;
        }

        cout << "\n=== Matching Books ===\n";
        for (int i = 0; i < foundCount; ++i) {
            cout << i + 1 << ".\n";
            books[foundIndexes[i]].displayDetails();
        }

        int choice;
        cout << "\nEnter the number of the book you want to delete (or 0 to cancel): ";
        cin >> choice;
        cin.ignore();

        if (choice == 0) {
            cout << "\n[Notice] Deletion cancelled.\n";
            return;
        }

        if (choice < 1 || choice > foundCount) {
            cout << "\n[Error] Invalid choice! Please try again.\n";
            return;
        }

        const Book &bookToDelete = books[foundIndexes[choice - 1]];
        cout << "\nAre you sure you want to delete this book?\n";
        bookToDelete.displayDetails();

        char confirm;
        cout << "Enter 'Y' to confirm or 'N' to cancel: ";
        cin >> confirm;
        cin.ignore();

        if (toupper(confirm) == 'Y') {
            for (int i = foundIndexes[choice - 1]; i < bookCount - 1; ++i) {
                books[i] = books[i + 1];
            }
            bookCount--;
            cout << "\n[Success] Book deleted successfully!\n";
        } else {
            cout << "\n[Notice] Deletion cancelled.\n";
        }
    }
};

int main() {
    BookManager manager;
    int choice;

    do {
        cout << "\n=== Book Verse ===\n";
        cout << "1. Manage Books (Add/Delete)\n";
        cout << "2. Search by Title\n";
        cout << "3. Display All Books\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: {
                int subChoice;
                cout << "\n=== Manage Books ===";
                cout << "\n1. Add Book\n2. Delete Book\n0. Back to Main Menu\nEnter your choice: ";
                cin >> subChoice;
                cin.ignore();

                if (subChoice == 1) {
                    string title, author, genre;
                    int year;
                    cout << "\nEnter book details below:\n";
                    cout << "Title: ";
                    getline(cin, title);
                    cout << "Author: ";
                    getline(cin, author);
                    cout << "Genre: ";
                    getline(cin, genre);
                    cout << "Publication Year: ";
                    cin >> year;
                    cin.ignore();

                    manager.addBook(Book(title, author, genre, year));
                } else if (subChoice == 2) {
                    manager.deleteBookWithConfirmation();
                } else if (subChoice == 0) {
                    cout << "\n[Notice] Returning to main menu.\n";
                } else {
                    cout << "\n[Error] Invalid choice! Please try again.\n";
                }
                break;
            }
            case 2:
                manager.searchBooksByTitle();
                break;
            case 3:
                manager.displayAllBooks();
                break;
            case 4:
                cout << "\nExiting... Goodbye!\n";
                break;
            default:
                cout << "\n[Error] Invalid choice! Please try again.\n";
        }
    } while (choice != 4);

    return 0;
}
