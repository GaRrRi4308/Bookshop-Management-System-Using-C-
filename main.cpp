#include <iostream>
#include <conio.h>

#define PASSWORD 4308

using namespace std;

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

int main() {
    pass();
}