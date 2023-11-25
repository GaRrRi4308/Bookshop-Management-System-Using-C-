
// HEADER FILES

#include <iostream>
#include <conio.h>
#include <mysql.h>
#include <sstream>

#define PASSWORD 4308
#define HOST "sql11.freemysqlhosting.net"
#define USER "sql11664456"
#define PASS "vpaTmIRPm1"
#define DATABASE "sql11664456"
#define PORT 3306

using namespace std;

// GLOBAL VARIABLES

MYSQL *conn;

// CLASSES MADE

class books {
    int id;
    string name;
    string auth;
    int price;
    int qty;
public:
    void add();
};

// MEMBER FUNCTIONS

//class books
void books::add() {
    cout << "Enter the name of the book: ";
    cin >> name;
    cout << "Enter the name of the author: ";
    cin >> auth;
    cout << "Enter the Price: ";
    cin >> price;
    cout << "Enter the Qty Received: ";
    cin >> qty;

    // Використання підготовленого запиту для безпечного додавання даних
    MYSQL_STMT *stmt;
    stmt = mysql_stmt_init(conn);
    if (!stmt) {
        cout << "Could not initialize statement handler\n";
        return;
    }

    const char *query = "INSERT INTO Books (name, auth, price, qty) VALUES (?, ?, ?, ?)";
    if (mysql_stmt_prepare(stmt, query, strlen(query))) {
        cout << "Could not prepare statement\n" << mysql_stmt_error(stmt) << "\n";;
        return;
    }

    MYSQL_BIND bind[4];
    memset(bind, 0, sizeof(bind));

    // Прив'язка параметрів
    bind[0].buffer_type = MYSQL_TYPE_STRING;
    bind[0].buffer = (char *) name.c_str();
    bind[0].buffer_length = name.length();

    bind[1].buffer_type = MYSQL_TYPE_STRING;
    bind[1].buffer = (char *) auth.c_str();
    bind[1].buffer_length = auth.length();

    bind[2].buffer_type = MYSQL_TYPE_LONG;
    bind[2].buffer = (char *) &price;
    bind[2].buffer_length = sizeof(price);

    bind[3].buffer_type = MYSQL_TYPE_LONG;
    bind[3].buffer = (char *) &qty;
    bind[3].buffer_length = sizeof(qty);

    if (mysql_stmt_bind_param(stmt, bind)) {
        cout << "Could not bind parameters\n";
        return;
    }

    // Виконання запиту
    if (mysql_stmt_execute(stmt)) {
        cout << "Could not execute prepared statement\n" << mysql_stmt_error(stmt) << "\n";;
        return;
    }

    cout << "Book record inserted successfully\n";

    mysql_stmt_close(stmt);
};
//class suppliers

//class purchased

//class employees

//class members

//class sales

// FUNCTIONS

void book_menu();

//main menu

void main_menu() {
    int c;
    cout << "*************************************************" << endl;
    cout << "         BOOKSHOP MANAGEMENT SYSTEM" << endl;
    cout << "*************************************************" << endl;
    cout << "   1. BOOKS" << endl;
    cout << "   2. SUPPLIERS" << endl;
    cout << "   3. PURCHASES" << endl;
    cout << "   4. EMPLOYEES" << endl;
    cout << "   5. MEMBERS" << endl;
    cout << "   6. SALES" << endl;
    cout << "   7. EXIT" << endl << endl << endl;
    cout << "Enter Your Choice : ";
    cin >> c;
    switch (c) {
        case 1:
            system("cls");
            book_menu();
            getch();
            break;
    }
}

//book menu

void book_menu() {
    int c;
    books b;

    cout << "*************************************************" << endl;
    cout << "                  BOOK MENU" << endl;
    cout << "*************************************************" << endl;
    cout << "   1. ADD" << endl;
    cout << "   2. UPDATE PRICE" << endl;
    cout << "   3. SEARCH" << endl;
    cout << "   4. UPDATE STATUS" << endl;
    cout << "   5. DISPLAY ALL" << endl;
    cout << "   6. RETURN TO MAIN MENU" << endl << endl << endl;
    cout << "Enter Your Choice : ";
    cin >> c;
    switch (c) {
        case 1:
            b.add();
    }
}

//sup menu

//purchase menu

//emp menu

//mem menu

//sal menu

//pass function

void pass() {
    int num = 0;
    cout << "Enter password :";
    for (int i = 0; i < 4; i++) {
        num = num * 10 + (getch() - 48);
        cout << "*";
    }
    if (num == PASSWORD) {
        cout << endl << endl << "Correct Password" << endl << endl;
        cout << "Press any key...";
        getch();
    } else {
        cout << endl << endl << "Incorrect Password" << endl << endl;
        cout << "Press any key..";
        getch();
        exit(1);
    }
}

// MAIN FUNCTION

int main() {
    pass();
    conn = mysql_init(nullptr);
    conn = mysql_real_connect(conn, HOST, USER, PASS, DATABASE, PORT, nullptr, 0);
    int choice;
    if (1) {
        while (true) {
            system("cls");
            main_menu();
        }

    }
}
