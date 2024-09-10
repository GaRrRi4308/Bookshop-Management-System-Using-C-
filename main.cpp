/**
 * @file main.cpp
 * @brief Код C++ для управління книжковим магазином
 * @details Містить класи для роботи з різними елементами. Реалізовано меню для взаємодії, включає підключення до бази даних MySQL
 * @author Роман Курилюк
 * @version 2.0.0
 * @date 21.08.2024
 */
#include <iostream> // вивід даних з консолі
#include <conio.h> // фукції для роботи з консоллю
#include <mysql.h> // робота з MySQL
#include <sstream> // потоки рядків

#include "config.h" // вхід в БД

using namespace std; // скорочення для потоків

MYSQL* conn; // для взаємодії з БД
stringstream stmt; // для формування запитів
string query; // для формування запитів
const char* q; // для зберігання запиту в С-стилі
MYSQL_RES* res_set; // зберігання запиту
MYSQL_ROW row; // робота з окремими рядками результату запиту

/**
 * @class books
 * @brief Клас для упавління книгами в базі даних
 * @details Цей клас містить методи для додавання, оновлення цін, пошуку, оновлення і відображення книжок
 */
class books
{
    int id_ = 0; ///< Іденитифікатор книги
    string name_; ///< Назва книги
    string auth_; ///< Автор книги
    int price_ = 0; ///< Ціна книги
    int qty_ = 0; ///< Кількість книг

public:
    void add();
    void update_price();
    void search();
    static void update();
    static void display();
};

/**
 * @class suppliers
 * @brief Клас для упавління постачальниками в базі даних
 * @details Цей клас містить деталі про постачальників в системі
 * @warning Не завершено
 */
class suppliers
{
    int id_ = 0; ///< Ідентифікатор постачальника
    string name_; ///< Ім'я постачальника
    long int phn_ = 0; ///< Номер телефону постачальника
    string addr_line1_; ///< Перша лінія адреси постачальника
    string addr_line2_; ///< Друга лінія адреси постачальника
    string addr_city_; ///< Місто постачальника
    string addr_state_; ///< Область постачальника

public:
    void add_sup();
    void remove_supplier();
};

/**
 * @brief Додає новий запис про книгу в базу даних
 * @details Функція запитує в користувача назву книги, ім'я автра, ціну та кількість книг, отримує цю інформацію та зберігає у базу даних. Під час виконання цієї операції використовується MySQL. Функція також виводить повідомлення про вдале або невдале виконання дії
 * @return None
 */
void books::add()
{
    // Зчитує дані про книгу з консолі
    cout << "Enter the name of the book :";
    cin >> name_;
    cout << "Enter the name of the author :";
    cin >> auth_;
    cout << "Enter the Price :";
    cin >> price_;
    cout << "Enter the Qty Recived :";
    cin >> qty_;

    MYSQL_STMT* mysql_stmt = mysql_stmt_init(conn); //ініціалізація оператора MySQL

    // Перевірка на дійсність
    if (!mysql_stmt)
    {
        cout << "Could not initialize statement handler\n";
        return;
    }

    // Перевірка на готовнісь запиту до виконання
    if (const auto str = "INSERT INTO Books (name, auth, price, qty) VALUES (?, ?, ?, ?)"; mysql_stmt_prepare(
        mysql_stmt, str, strlen(str)))
    {
        cout << "Could not prepare statement\n" << mysql_stmt_error(mysql_stmt) << "\n";
        return;
    }

    MYSQL_BIND bind[4] = {}; //ініціалізація масиву

    // Прив'язка змінних до запиту
    bind[0].buffer_type = MYSQL_TYPE_STRING;
    bind[0].buffer = const_cast<char*>(name_.c_str());
    bind[0].buffer_length = name_.length();

    bind[1].buffer_type = MYSQL_TYPE_STRING;
    bind[1].buffer = const_cast<char*>(auth_.c_str());
    bind[1].buffer_length = auth_.length();

    bind[2].buffer_type = MYSQL_TYPE_LONG;
    bind[2].buffer = reinterpret_cast<char*>(&price_);
    bind[2].buffer_length = sizeof(price_);

    bind[3].buffer_type = MYSQL_TYPE_LONG;
    bind[3].buffer = reinterpret_cast<char*>(&qty_);
    bind[3].buffer_length = sizeof(qty_);

    // Перевірка прив'язки
    if (mysql_stmt_bind_param(mysql_stmt, bind))
    {
        cout << "Could not bind parameters\n";
        return;
    }

    // Перевірка, чи виконався запит
    if (mysql_stmt_execute(mysql_stmt))
    {
        cout << "Could not execute prepared statement\n" << mysql_stmt_error(mysql_stmt) << "\n";
        return;
    }

    cout << "Book record inserted successfully\n";

    mysql_stmt_close(mysql_stmt); //закриття стейтменту
}

/**
 * @brief Оновлення ціни книги
 * @details Здійснює пощук книги по ідентфікатору та виконує оновлення ціни в базі даних
 * @return None
 */
void books::update_price()
{
    cout << "Enter the id of the book for update in price : ";
    cin >> id_;

    // Формування запиту
    stmt.str("");
    stmt << "Select name, price from Books where id = " << id_ << ";";
    query = stmt.str();
    q = query.c_str();

    // Виконання запиту та вивід помилки
    if (mysql_query(conn, q))
    {
        cout << "Query Error!" << endl;
        return;
    }

    MYSQL_RES* res_set = mysql_store_result(conn); //збережання результатів запиту

    // Оновлення ціни в БД
    if (MYSQL_ROW row; (row = mysql_fetch_row(res_set)) != nullptr)
    {
        char choice;

        cout << "The name of the book is : " << row[0] << endl;
        cout << "The current price of the book is : " << row[1] << endl;
        cout << "Do you want to upgrade the price [y/n] : ";
        cin >> choice;

        // Оновлення ціни при згоді
        if (tolower(choice) == 'y')
        {
            cout << "Enter the new price : ";
            cin >> price_;

            // Оновлення в БД за заданим іденифікатором
            stmt.str("");
            stmt << "Update Books set price = " << price_ << " where id = " << id_ << ";";
            query = stmt.str();
            q = query.c_str();

            //Повідомлення про виконання
            if (mysql_query(conn, q))
            {
                cout << endl << endl << "Query Error!" << endl << "Contact technical team" << endl << endl << endl;
            }
            else
            {
                cout << endl << endl << "Book price updated successfully" << endl << endl << endl;
            }
        }
        else
        {
            cout << "No changes made!";
        }
    }
    else
    {
        cout << "No book found!";
    }
}

/**
 * @brief Функція пошуку каниги за іденифікатором
 * @details Формує запит та виводить дані, якщо книга існує
 * @return None
 */
void books::search()
{
    cout << "Enter book id for details : ";
    cin >> id_;

    // Формування запиту
    stmt.str("");
    stmt << "Select * from Books where id = " << id_ << ";";
    query = stmt.str();
    q = query.c_str();

    // Перевірка на помилки під час виконання запиту
    if (mysql_query(conn, q))
    {
        cout << "Query Error!" << endl;
        return;
    }

    MYSQL_RES* res_set = mysql_store_result(conn); //збереження результату запиту

    // Виведення інформації
    if (MYSQL_ROW row; (row = mysql_fetch_row(res_set)) != nullptr)
    {
        cout << "The Details of Book Id " << row[0] << endl;
        cout << "The Name of the book is : " << row[1] << endl;
        cout << "The Author of " << row[1] << " is " << row[2] << endl;
        cout << "The Price ofthe book is : " << row[3] << endl;
        cout << "The inventory count is " << row[4] << endl;
    }
    else
    {
        cout << "No record Found" << endl;
    }
}

/**
 * @brief Оновлення книг в БД
 * @details Оновлює статус книг в базі даних знідно з отриманими замовленнями
 * @return None
 */
void books::update()
{
    int b_id[100], qty[100], i = 0;

    // Формування запиту
    stmt.str("");
    stmt << "Select book_id,qty from Purchases where received = 'T' and inv IS NULL;";
    query = stmt.str();
    q = query.c_str();

    // Виконання запиту і виведення помилки
    if (mysql_query(conn, q))
    {
        cout << "Failed to execute query: " << mysql_error(conn) << endl;
        return;
    }

    res_set = mysql_store_result(conn); //Отримання результату запиту

    // Перевірка збереження резельтату
    if (res_set == nullptr)
    {
        cout << "Failed to store result: " << mysql_error(conn) << endl;
        return;
    }

    // Оновлення статусу для всіх отиманих покупок
    stmt.str("");
    stmt << "Update Purchases set inv = 1 where received = 'T' and inv IS NULL;";
    query = stmt.str();
    q = query.c_str();

    // Перевірка виканання запиту
    if (mysql_query(conn, q))
    {
        cout << "Failed to execute query: " << mysql_error(conn) << endl;
        return;
    }

    // Перетворення рядка результату в числа
    char* p_end;
    while ((row = mysql_fetch_row(res_set)) != nullptr)
    {
        b_id[i] = strtol(row[0], &p_end, 10);
        qty[i] = strtol(row[1], &p_end, 10);
        i++;
    }

    // Оновлення кількості книг в БД
    const int max = i;
    for (i = 0; i <= max; i++)
    {
        stmt.str("");
        stmt << "update Books set qty = " << qty[i] << " where id = " << b_id[i] << ";";
        query = stmt.str();
        q = query.c_str();

        if (mysql_query(conn, q))
        {
            cout << "Failed to execute query: " << mysql_error(conn) << endl;
            return;
        }
    }

    cout << "The orders recieved have been updated.";
}

/**
* @brief Відображає інформацію про всі книги
* @details Функція виконує SQL запит до бази даних для отримання усіх записів з таблиці Books. Інформація включає назву книги, автора, ціну та кількість.
* @return None
*/
void books::display()
{
    int i = 0;

    // Виконання SQL запиту до БД для отримання всіх записів з таблиці "Books"
    query = "Select * from Books;";
    q = query.c_str();
    mysql_query(conn, q);
    res_set = mysql_store_result(conn);

    // Виводить інформацію про кожну книгу з бази даних
    while ((row = mysql_fetch_row(res_set)) != nullptr)
    {
        cout << endl;
        cout << "Name for book " << ++i << " : " << row[1] << endl;
        cout << "Name of Author : " << row[2] << endl;
        cout << "Price : " << row[3] << endl;
        cout << "Quantity : " << row[4] << endl;
    }
}

/**
 * @brief Додає дані про нового постачальника.
 *
 * @details Функція зчитує з консолі інформацію про нового постачальника, включаючи ім'я,
 * номер телефону і адресу. Після цього дані зберігаються в БД MySQL. Функція повідомляє
 * про успішність/неуспішність виконання.
 *
 * @return Нічого не повертає.
 */
void suppliers::add_sup()
{
    // Введення даних про постачальника
    cout << "Enter the Supplier Name : ";
    cin >> name_;
    cout << "Enter Phone no. : ";
    cin >> phn_;
    cout << "Enter the address (in 3 lines) : ";
    cin >> addr_line1_;
    cin >> addr_line2_;
    cin >> addr_city_;
    cout << "Enter State : ";
    cin >> addr_state_;

    MYSQL_STMT* mysql_stmt = mysql_stmt_init(conn); //ініціалізація оператора MySQL

    // Перевірка на дійсність
    if (!mysql_stmt)
    {
        cout << "Could not initialize statement handler\n";
        return;
    }

    // Перевірка на готовнісь запиту до виконання
    if (const auto str =
            "INSERT INTO Suppliers (name, phn, addr_line1, addr_line2, addr_city, addr_state) VALUES (?, ?, ?, ?, ?, ?)"
        ;
        mysql_stmt_prepare(
            mysql_stmt, str, strlen(str)))
    {
        cout << "Could not prepare statement\n" << mysql_stmt_error(mysql_stmt) << "\n";
        return;
    }

    MYSQL_BIND bind[6] = {}; //ініціалізація масиву

    // Прив'язка змінних до запиту
    bind[0].buffer_type = MYSQL_TYPE_STRING;
    bind[0].buffer = const_cast<char*>(name_.c_str());
    bind[0].buffer_length = name_.length();

    bind[1].buffer_type = MYSQL_TYPE_LONG;
    bind[1].buffer = reinterpret_cast<char*>(&phn_);
    bind[1].buffer_length = sizeof(phn_);

    bind[2].buffer_type = MYSQL_TYPE_STRING;
    bind[2].buffer = const_cast<char*>(addr_line1_.c_str());
    bind[2].buffer_length = addr_line1_.length();

    bind[3].buffer_type = MYSQL_TYPE_STRING;
    bind[3].buffer = const_cast<char*>(addr_line2_.c_str());
    bind[3].buffer_length = addr_line2_.length();

    bind[4].buffer_type = MYSQL_TYPE_STRING;
    bind[4].buffer = const_cast<char*>(addr_city_.c_str());
    bind[4].buffer_length = addr_city_.length();

    bind[5].buffer_type = MYSQL_TYPE_STRING;
    bind[5].buffer = const_cast<char*>(addr_state_.c_str());
    bind[5].buffer_length = addr_state_.length();

    // Перевірка прив'язки
    if (mysql_stmt_bind_param(mysql_stmt, bind))
    {
        cout << "Could not bind parameters\n";
        return;
    }

    // Перевірка, чи виконався запит
    if (mysql_stmt_execute(mysql_stmt))
    {
        cout << "Could not execute prepared statement\n" << mysql_stmt_error(mysql_stmt) << "\n";
        return;
    }

    cout << "Suppliers record inserted successfully\n";

    mysql_stmt_close(mysql_stmt); //закриття стейтменту
}

/**
* @brief Вилучає постачальника з бази даних.
* @details Цей метод дозволяє вилучити постачальника з бази даних, виконавши відповідний SQL-запит до бази даних.
* @return None
*/
void suppliers::remove_supplier()
{
    //Запит на введення ідентифікаційного номера постачальника для його видалення
    cout << "Enter the supplier id to remove the supplier : ";
    cin >> id_;

    //Виконання запиту на видалення постачальника з бази даних за його ідентифікатором
    stmt.str("");
    stmt << "Delete from Suppliers where id = " << id_ << ";";
    query = stmt.str();
    q = query.c_str();
    mysql_query(conn, q);

    cout << "Supplier removed";
}


void book_menu();
void sup_menu();

/**
 * @brief Головне меню системи
 * @details Функція відображує головне меню системи та дозволяє користувачу вибирати різні опції (книги, постачальники, закупівлі, працівники, члени, продажі та вихід).
 * @return None
 * @warning Не завершено
 */
void main_menu()
{
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

    switch (c)
    {
    case 1:
        system("cls");
        book_menu();
        getch();
        break;
    case 2:
        system("cls");
        sup_menu();
        getch();
        break;
    case 3:
        system("cls");
    //TODO: pur_menu();
        getch();
        break;
    case 4:
        system("cls");
    //TODO: emp_menu();
        getch();
        break;
    case 5:
        system("cls");
    //TODO: mem_menu();
        getch();
        break;
    case 6:
        system("cls");
    //TODO: sal_menu();
        getch();
        break;
    case 7:
        exit(1);
    default:
        system("cls");
        cout << "Wrong input" << endl;
        getch();
        break;
    }
}

/**
 * @brief Відображення меню книжкового складу
 * @details Функція відображає меню книжкового складу з різними опціями, такими як "Додати", "Оновити ціну", "Пошук", "Оновити статус", "Показати все" та "Повернутися до головного меню". Вона також обробляє вибір користувача та виконує відповідні дії.
 * @return  None
 */
void book_menu()
{
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

    switch (c)
    {
    case 1:
        b.add();
        break;
    case 2:
        b.update_price();
        break;
    case 3:
        b.search();
        break;
    case 4:
        books::update();
        break;
    case 5:
        books::display();
        break;
    case 6:
        return;
    default:
        cout << "Wrong Input" << endl;
        break;
    }
}

/**
* @brief Меню постачальників
* @details Функція, що виводить меню дій з постачальниками, зчитує введене користувачем значення та виконує відповідну дію.
* @return None
* @warning Не завершено
*/
void sup_menu()
{
    int c;
    suppliers s;

    cout << "*************************************************" << endl;
    cout << "                SUPPLIER MENU" << endl;
    cout << "*************************************************" << endl;
    cout << "   1. ADD" << endl;
    cout << "   2. REMOVE" << endl;
    cout << "   3. SEARCH" << endl;
    cout << "   4. RETURN TO MAIN MENU" << endl << endl << endl;
    cout << "Enter Your Choice : ";
    cin >> c;

    switch (c)
    {
    case 1:
        s.add_sup();
        break;
    case 2:
        s.remove_supplier();
        break;
    case 3:
        //TODO: s.search_id();
        break;
    case 4:
        return;
    default:
        cout << "Wrong input" << endl;
        break;
    }
}

/**
 * @brief Верифікація пароля.
 * @details Порівнює введений користувачем пароль з встановленим паролем. Вихід з програми, якщо пароль невірний.
 * @return None
 */
void pass()
{
    int num = 0;
    cout << "Enter password :";

    // Отримання та обробка вводу пароля, де кожен символ відображається як "*".
    for (int i = 0; i < 4; i++)
    {
        num = num * 10 + (getch() - 48);
        cout << "*";
    }

    // Якщо введений користувачем пароль відповідає правильному, виводиться повідомлення про успішний вхід
    if (num == PASSWORD)
    {
        cout << endl << endl << "Correct Password" << endl << endl;
        cout << "Press any key...";
        getch();
    }
    // Блок коду для виходу з програми, якщо введений пароль невірний
    else
    {
        cout << endl << endl << "Incorrect Password" << endl << endl;
        cout << "Press any key..";
        getch();
        exit(1);
    }
}

/**
 * @brief Вхідна точка програми.
 * @details Ця функція ініціалізує підключення до бази даних, потім обробляє вибір користувача в головному меню. Якщо підключення до бази даних не вдається, виводить повідомлення про помилку на екран.
 * @return None
 */
[[noreturn]] int main()
{
    pass();
    conn = mysql_init(nullptr);
    conn = mysql_real_connect(conn, HOST, USER, PASS, DATABASE, PORT, nullptr, 0);

    if (conn)
    {
        while (true)
        {
            system("cls");
            main_menu();
        }
    }

    system("cls");
    cout << "Error while connection to database." << endl << "Contant tech expert." << endl << "romakuriluk@gmail.com";

    return 0;
}
