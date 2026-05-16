#ifndef USERS_H
#define USERS_H

#include <iostream>
#include <fstream>
#include <cstring>
#include "validation.h"
#include "files.h"

using namespace std;

struct User
{
    char username[30];
    char password[30];
    char fullName[50];
    char phone[10];
    char type[10];    
    bool active;
};
void createDefaultAdmin()
{
    ifstream check("users.txt", ios::binary);
    if (check.good())
    {
        check.close();
        return;
    }
    check.close();

    ofstream file("users.txt", ios::binary);
    User admin;

    strcpy(admin.username, "Adnan");
    strcpy(admin.password, "779004023");
    strcpy(admin.fullName, "System Administrator");
    strcpy(admin.phone, "777777777");
    strcpy(admin.type, "admin");
    admin.active = true;

    file.write((char*)&admin, sizeof(admin));
    file.close();
}

bool usernameExists(const char uname[])
{
    ifstream file("users.txt", ios::binary);
    User u;

    while (file.read((char*)&u, sizeof(u)))
    {
        if (strcmp(u.username, uname) == 0)
        {
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}

void addEmployee()
{
    User u;

    cout << "Enter Username (no spaces): ";
    cin >> u.username;

    if (!isValidUsername(u.username) || usernameExists(u.username))
    {
        cout << "Invalid or existing username!\n";
        return;
    }

    cin.ignore(); 

    cout << "Enter Full Name: ";
    cin.getline(u.fullName, 50);

    cout << "Enter Password: ";
    cin >> u.password;

    cout << "Enter Phone Number: ";
    cin >> u.phone;

    if (!isValidPhone(u.phone))
    {
        cout << "Invalid phone number!\n";
        return;
    }

    strcpy(u.type, "employee");
    u.active = true;

    ofstream file("users.txt", ios::binary | ios::app);
    file.write((char*)&u, sizeof(u));
    file.close();

    cout << "Employee added successfully.\n";
}
void displayUsers()
{
    ifstream file("users.txt", ios::binary);
    User u;

    cout << "\n--- Users List ---\n";
    while (file.read((char*)&u, sizeof(u)))
    {
        cout << "Username: " << u.username
             << " | Name: " << u.fullName
             << " | Type: " << u.type
             << " | Active: " << (u.active ? "Yes" : "No") << endl;
    }
    file.close();
}

void toggleUserStatus()
{
    char uname[30];
    cout << "Enter username: ";
    cin >> uname;

    fstream file("users.txt", ios::binary | ios::in | ios::out);
    User u;

    while (file.read((char*)&u, sizeof(u)))
    {
        if (strcmp(u.username, uname) == 0)
        {
            u.active = !u.active;
            file.seekp(-sizeof(u), ios::cur);
            file.write((char*)&u, sizeof(u));
            file.close();
            cout << "User status updated.\n";
            return;
        }
    }
    file.close();
    cout << "User not found.\n";
}

void removeUser()
{
    char uname[30];
    cout << "Enter username to remove: ";
    cin >> uname;

    ifstream in("users.txt", ios::binary);
    ofstream out("temp.txt", ios::binary);

    User u;
    bool found = false;

    while (in.read((char*)&u, sizeof(u)))
    {
        if (strcmp(u.username, uname) != 0)
            out.write((char*)&u, sizeof(u));
        else
            found = true;
    }

    in.close();
    out.close();

    remove("users.txt");
    rename("temp.txt", "users.txt");

    if (found)
        cout << "User removed successfully.\n";
    else
        cout << "User not found.\n";
}

void userStatistics()
{
    int total = countRecords("users.txt", sizeof(User));
    cout << "Total Users: " << total << endl;
}

#endif
