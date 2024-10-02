#include <iostream>
#include <vector>
#include <string>
using namespace std;

//Розробити програму, яка працює зі списком книг. Розробити власний клас
//колекцію, який містить усі необхідні методи (додавання, пошук, видалення).
//Пошук книги здійснювати за автором. Доступ до елементів колекції здійснити
//за допомогою шаблону Proxy (Заступник).

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
        cout << "Назва: " << title << ", Автор: " << author << endl;
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
                cout << "Книгу видалено: " << title << endl;
                return;
            }
        }
        cout << "Книга з назвою " << title << " не знайдена." << endl;
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
    BookCollection* realCollection; 

public:
    BookCollectionProxy(BookCollection* collection) : realCollection(collection) {}


    void addBook(const Book& book) {
        cout << "Книгу було додано (Proxy)" << endl;
        realCollection->addBook(book);
    }


    void removeBook(const string& title) {
        cout << "Книгу було видалтно (Proxy)" << endl;
        realCollection->removeBook(title);
    }


    Book* findBookByAuthor(const string& author) {
        cout << "Результат пошуку (Proxy)" << endl;
        return realCollection->findBookByAuthor(author);
    }


    void displayAllBooks() const {
        cout << "Всі книги (Proxy)" << endl;
        realCollection->displayAllBooks();
    }
};


int main() {
    setlocale(LC_ALL, "Ukr");

    //  об'єкт реальної колекції книг
    BookCollection realCollection;

    // об'єкт Proxy для доступу до реальної колекції
    BookCollectionProxy proxy(&realCollection);


    proxy.addBook(Book("Кобзар", "Тарас Шевченко"));
    proxy.addBook(Book("Гаррі Поттер", "Джоан Роулінг"));
    proxy.addBook(Book("Кайдашева сім'я", "Іван Нечуй-Левицький"));

    proxy.displayAllBooks();


    cout << "\nШукаємо книгу за автором 'Джоан Роулінг':" << endl;
    Book* foundBook = proxy.findBookByAuthor("Джоан Роулінг");
    if (foundBook) {
        foundBook->displayBookInfo();
    }
    else {
        cout << "Книгу не знайдено." << endl;
    }

    proxy.removeBook("Кобзар");

    proxy.displayAllBooks();

    return 0;
}
