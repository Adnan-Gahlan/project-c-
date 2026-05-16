#include <iostream>
#include <cstring>
#include "users.h"
#include "students.h"

using namespace std;
bool login(char userType[], char loggedUser[])
{
    User u;
    char uname[30], pass[30];

    ifstream file("users.txt", ios::binary);

    cout << "Username: ";
    cin >> uname;

    cout << "Password: ";
    cin >> pass;

    while (file.read((char*)&u, sizeof(u)))
    {
        if (strcmp(u.username, uname) == 0 &&
            strcmp(u.password, pass) == 0 &&
            u.active)
        {
            strcpy(userType, u.type);
            strcpy(loggedUser, u.username);
            file.close();
            return true;
        }
    }

    file.close();
    return false;
}

void adminMenu()
{
    int choice;
    do
    {
        cout << "\n--- Admin Menu ---\n";
        cout << "1. Add Employee\n";
        cout << "2. Remove User\n";
        cout << "3. Activate / Deactivate User\n";
        cout << "4. Display Users\n";
        cout << "5. User Statistics\n";
        cout << "0. Logout\n";
        cout << "Choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1: addEmployee(); break;
        case 2: removeUser(); break;
        case 3: toggleUserStatus(); break;
        case 4: displayUsers(); break;
        case 5: userStatistics(); break;
        case 0: cout << "Logging out...\n"; break;
        default: cout << "Invalid choice!\n";
        }
    } while (choice != 0);
}

void employeeMenu()
{
    int choice;
    do
    {
        cout << "\n--- Employee Menu ---\n";
        cout << "1. Add Student\n";
        cout << "2. Delete Student\n";
        cout << "3. Update Student\n";
        cout << "4. View Student by ID\n";
        cout << "5. View All Students\n";
        cout << "6. Search Student by ID\n";
        cout << "7. Academic Report\n";
        cout << "0. Logout\n";
        cout << "Choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1: addStudent(); break;
        case 2: deleteStudent(); break;
        case 3: updateStudent(); break;
        case 4: viewStudentByID(); break;
        case 5: viewAllStudents(); break;
        case 6: searchStudent(); break;
        case 7: academicReport(); break;
        case 0: cout << "Logging out...\n"; break;
        default: cout << "Invalid choice!\n";
        }
    } while (choice != 0);
}

int main()
{
    createDefaultAdmin();

    char userType[10];
    char loggedUser[30];

    cout << "=== School Management System ===\n";

    if (!login(userType, loggedUser))
    {
        cout << "Invalid login or inactive account!\n";
        return 0;
    }

    cout << "Welcome " << loggedUser << endl;

    if (strcmp(userType, "admin") == 0)
        adminMenu();
    else
        employeeMenu();

    return 0;
}
