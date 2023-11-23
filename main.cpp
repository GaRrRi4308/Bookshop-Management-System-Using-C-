
// HEADER FILES

#include <iostream>
#include <conio.h>
#include <mysql.h>

#define PASSWORD 4308
#define HOST "sql11.freemysqlhosting.net"
#define USER "root"
#define PASS "4308"
#define DATABASE "Management"
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

    void update_prise();

    void search();

    void update();

    void display();
};

// MEMBER FUNCTIONS

//class books

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
