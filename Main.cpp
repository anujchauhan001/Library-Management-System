#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

class Book {
private:
    string title;
    string author;
    string ISBN;
    bool isIssued;

public:
    Book(string t, string a, string i) : title(t), author(a), ISBN(i), isIssued(false) {}

    string getTitle() { return title; }
    string getAuthor() { return author; }
    string getISBN() { return ISBN; }
    bool getIsIssued() { return isIssued; }

    void issueBook() { isIssued = true; }
    void returnBook() { isIssued = false; }

    void displayBookInfo() {
        cout << "Title: " << title << "\nAuthor: " << author << "\nISBN: " << ISBN << "\nIssued: " << (isIssued ? "Yes" : "No") << endl;
    }
};

class Member {
private:
    string name;
    string memberId;
    vector<string> issuedBooks;

public:
    Member(string n, string id) : name(n), memberId(id) {}

    string getName() { return name; }
    string getMemberId() { return memberId; }

    void issueBook(string ISBN) {
        issuedBooks.push_back(ISBN);
    }

    void returnBook(string ISBN) {
        for (auto it = issuedBooks.begin(); it != issuedBooks.end(); ++it) {
            if (*it == ISBN) {
                issuedBooks.erase(it);
                break;
            }
        }
    }

    void displayMemberInfo() {
        cout << "Name: " << name << "\nMember ID: " << memberId << "\nIssued Books: ";
        for (string isbn : issuedBooks) {
            cout << isbn << " ";
        }
        cout << endl;
    }
};

class Library {
private:
    vector<Book> books;
    vector<Member> members;

public:
    void addBook(Book book) {
        books.push_back(book);
    }

    void addMember(Member member) {
        members.push_back(member);
    }

    void issueBook(string isbn, string memberId) {
        for (auto &book : books) {
            if (book.getISBN() == isbn && !book.getIsIssued()) {
                for (auto &member : members) {
                    if (member.getMemberId() == memberId) {
                        book.issueBook();
                        member.issueBook(isbn);
                        cout << "Book issued successfully!" << endl;
                        return;
                    }
                }
            }
        }
        cout << "Book issuance failed!" << endl;
    }

    void returnBook(string isbn, string memberId) {
        for (auto &book : books) {
            if (book.getISBN() == isbn && book.getIsIssued()) {
                for (auto &member : members) {
                    if (member.getMemberId() == memberId) {
                        book.returnBook();
                        member.returnBook(isbn);
                        cout << "Book returned successfully!" << endl;
                        return;
                    }
                }
            }
        }
        cout << "Book return failed!" << endl;
    }

    void displayBooks() {
        for (auto &book : books) {
            book.displayBookInfo();
            cout << "------------------" << endl;
        }
    }

    void displayMembers() {
        for (auto &member : members) {
            member.displayMemberInfo();
            cout << "------------------" << endl;
        }
    }
};

int main() {
    Library lib;
    lib.addBook(Book("C++ Programming", "Bjarne Stroustrup", "12345"));
    lib.addBook(Book("Effective Modern C++", "Scott Meyers", "67890"));

    lib.addMember(Member("John Doe", "M001"));
    lib.addMember(Member("Jane Smith", "M002"));

    lib.displayBooks();
    lib.displayMembers();

    lib.issueBook("12345", "M001");
    lib.displayBooks();
    lib.displayMembers();

    lib.returnBook("12345", "M001");
    lib.displayBooks();
    lib.displayMembers();

    return 0;
}
