#include "menu.h"
#include "bakery.h"

int main()
{
    Bakery bakery;
    int option;
    
    do {
        system("cls");
        setColor(12);
        cout << "<<Welcome to The Bakery>>\n";
        setColor(7);
        cout << "[1] Client\n[2] Manager\n[3] Employee\n[4] Leave\nChoose an option: ";
        option = getInt(1, 4);
        switch(option) {
        case 1:
            clients(bakery);
            break;
        case 2:
            manager(bakery);
            break;
        case 3:
            loginEmployee(bakery);
            break;
        case 4:
            cout << "Leaving... Bye";
            Sleep(3000);
            break;
        }
    } while (option != 4);
}