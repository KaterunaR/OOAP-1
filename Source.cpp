#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Book {
private:
    string title;   
    string author;  

public:
    Book(const string& t, const string& a) : title(t), author(a) {}

    string getTitle() const {
        return title;
    }

    string getAuthor() const {
        return author;
    }

    void displayBookInfo() const {
        cout << "�����: " << title << ", �����: " << author << endl;
    }
};


class BookCollection {
private:
    vector<Book> books; 

public:
    void addBook(const Book& book) {
        books.push_back(book);
    }

    void removeBook(const string& title) {
        for (auto it = books.begin(); it != books.end(); ++it) {
            if (it->getTitle() == title) {
                books.erase(it);
                cout << "����� ��������: " << title << endl;
                return;
            }
        }
        cout << "����� � ������ " << title << " �� ��������." << endl;
    }

    Book* findBookByAuthor(const string& author) {
        for (auto& book : books) {
            if (book.getAuthor() == author) {
                return &book;
            }
        }
        return nullptr;
    }

    void displayAllBooks() const {
        for (const auto& book : books) {
            book.displayBookInfo();
        }
    }
};


class BookCollectionProxy {
private:
    BookCollection* realCollection; // �������� �� �������� �������� ����

public:
    BookCollectionProxy(BookCollection* collection) : realCollection(collection) {}


    void addBook(const Book& book) {
        cout << "����� ���� ������ (Proxy)" << endl;
        realCollection->addBook(book);
    }


    void removeBook(const string& title) {
        cout << "����� ���� �������� (Proxy)" << endl;
        realCollection->removeBook(title);
    }


    Book* findBookByAuthor(const string& author) {
        cout << "��������� ������ (Proxy)" << endl;
        return realCollection->findBookByAuthor(author);
    }


    void displayAllBooks() const {
        cout << "�� ����� (Proxy)" << endl;
        realCollection->displayAllBooks();
    }
};


int main() {
    setlocale(LC_ALL, "Ukr");

    // ��������� ��'��� ������� �������� ����
    BookCollection realCollection;

    // ��������� ��'��� Proxy ��� ������� �� ������� ��������
    BookCollectionProxy proxy(&realCollection);


    proxy.addBook(Book("������", "����� ��������"));
    proxy.addBook(Book("���� ������", "����� ������"));
    proxy.addBook(Book("��������� ��'�", "���� �����-���������"));

    proxy.displayAllBooks();


    cout << "\n������ ����� �� ������� '����� ������':" << endl;
    Book* foundBook = proxy.findBookByAuthor("����� ������");
    if (foundBook) {
        foundBook->displayBookInfo();
    }
    else {
        cout << "����� �� ��������." << endl;
    }

    proxy.removeBook("������");

    proxy.displayAllBooks();

    return 0;
}