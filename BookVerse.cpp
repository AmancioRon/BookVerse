#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
using namespace std;

// Book class
class Book {
private:
    string title, author;
    vector<string> genres;
    int publicationYear;

public:
    // Constructor
    Book(string t, string a, vector<string> g, int y) 
        : title(t), author(a), genres(g), publicationYear(y) {}

    // Getters
    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    vector<string> getGenres() const { return genres; }
    int getPublicationYear() const { return publicationYear; }

    // Display book details
    void displayDetails() const {
        cout << "Title: " << title << ", Author: " << author << ", Genres: ";
        for (size_t i = 0; i < genres.size(); ++i) {
            cout << genres[i];
            if (i != genres.size() - 1) cout << ", ";
        }
        cout << ", Year: " << publicationYear << endl;
    }
};

// BookManager class
class BookManager {
private:
    vector<Book> books;

public:
    // Add a new book
    void addBook(const Book &book) { books.push_back(book); }

    // Display all books
    void displayAllBooks() const {
        if (books.empty()) {
            cout << "No books in your collection yet!" << endl;
            return;
        }
        cout << "Books in your collection:" << endl;
        for (const auto &book : books) book.displayDetails();
    }

    // Fuzzy search by title
    void searchBooksByTitle(const string &partialTitle) const {
        bool found = false;
        for (const auto &book : books) {
            if (book.getTitle().find(partialTitle) != string::npos) {
                book.displayDetails();
                found = true;
            }
        }
        if (!found) cout << "No book found containing: " << partialTitle << endl;
    }

    // List books by genre
    void listBooksByGenre(const string &genre) const {
        bool found = false;
        for (const auto &book : books) {
            if (find(book.getGenres().begin(), book.getGenres().end(), genre) != book.getGenres().end()) {
                book.displayDetails();
                found = true;
            }
        }
        if (!found) cout << "No books found in the genre: " << genre << endl;
    }

    // Genre Analytics
    void displayGenreAnalytics() const {
        map<string, int> genreCount;
        for (const auto &book : books) {
            for (const auto &genre : book.getGenres()) {
                genreCount[genre]++;
            }
        }
        cout << "Genre Analytics:" << endl;
        for (const auto &pair : genreCount) {
            cout << pair.first << ": " << pair.second << " books" << endl;
        }
    }
};

// Main function
int main() {
    BookManager manager;
    int choice;

    do {
        cout << "\n--- Book Verse ---\n";
        cout << "1. Add Book\n2. Search by Title\n3. List Books by Genre\n4. Display All Books\n5. Genre Analytics\n6. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: {
                string title, author, genreInput;
                vector<string> genres;
                int year;

                cout << "Enter title: ";
                getline(cin, title);
                cout << "Enter author: ";
                getline(cin, author);

                cout << "Enter genres (comma-separated): ";
                getline(cin, genreInput);

                size_t pos = 0;
                while ((pos = genreInput.find(',')) != string::npos) {
                    genres.push_back(genreInput.substr(0, pos));
                    genreInput.erase(0, pos + 1);
                }
                genres.push_back(genreInput); // Add the last genre

                cout << "Enter publication year: ";
                cin >> year;

                manager.addBook(Book(title, author, genres, year));
                cout << "Book added successfully!" << endl;
                break;
            }
            case 2: {
                string title;
                cout << "Enter part of the title to search: ";
                getline(cin, title);
                manager.searchBooksByTitle(title);
                break;
            }
            case 3: {
                string genre;
                cout << "Enter genre: ";
                getline(cin, genre);
                manager.listBooksByGenre(genre);
                break;
            }
            case 4:
                manager.displayAllBooks();
                break;
            case 5:
                manager.displayGenreAnalytics();
                break;
            case 6:
                cout << "Exiting... Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice!" << endl;
        }
    } while (choice != 6);

    return 0;
}
