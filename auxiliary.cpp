#include "auxiliary.h"

int getInt(int lower, int upper) // Inclusive
{
    int choice;
    while (!(cin >> choice) || choice < lower || choice > upper) {
        cout << "Invalid Input: ";
        cin.clear();
        cin.ignore(1000000, '\n');
    }
    cin.ignore(1000000, '\n');
    return choice;
}

float getFloat(int lower, int upper) // Inclusive
{
    string temp;
    bool done = false;
    float result;

    while (!done)
    {
        getline(cin, temp);

        try
        {
            result = stof(temp);
        }
        catch(invalid_argument &e)
        {
            cout << "Invalid Input: ";
            continue;
        }

        if (result < lower || result > upper)
            cout << "Invalid Input: ";
        else done = true;
    }

    return result;
}

bool getYesNo()
{
    char choice;
    while(!(cin >> choice) || (toupper(choice) != 'Y' && toupper(choice) != 'N')){
        cout << "Invalid Input! Try again... ";
        cin.clear();
        cin.ignore(1000000, '\n');
    }
    cin.ignore(1000000, '\n');
    return (toupper(choice) == 'Y');  
}

void setColor(int color) {SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);}

void cursorPos(int x, int y)
{
    COORD c;
    c.X = x;
    c.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
