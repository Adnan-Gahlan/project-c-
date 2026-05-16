#ifndef STUDENTS_H
#define STUDENTS_H

#include <iostream>
#include <fstream>
#include <cstring>
#include "files.h"

using namespace std;

struct Student
{
    int id;
    char name[50];
    char grade[10];
    float average;
};

void addStudent()
{
    Student s;
    cout << "Enter Student ID: ";
    cin >> s.id;

    cin.ignore();
    cout << "Enter Student Name: ";
    cin.getline(s.name, 50);

    cout << "Enter Grade/Class: ";
    cin >> s.grade;

    cout << "Enter Average Score: ";
    cin >> s.average;

    ofstream file("students.txt", ios::binary | ios::app);
    file.write((char*)&s, sizeof(s));
    file.close();

    cout << "Student added successfully.\n";
}

void viewAllStudents()
{
    ifstream file("students.txt", ios::binary);
    Student s;

    cout << "\n--- Students List ---\n";
    while (file.read((char*)&s, sizeof(s)))
    {
        cout << "ID: " << s.id
             << " | Name: " << s.name
             << " | Grade: " << s.grade
             << " | Average: " << s.average << endl;
    }
    file.close();
}

void viewStudentByID()
{
    int id;
    cout << "Enter Student ID: ";
    cin >> id;

    ifstream file("students.txt", ios::binary);
    Student s;

    while (file.read((char*)&s, sizeof(s)))
    {
        if (s.id == id)
        {
            cout << "\nStudent Found:\n";
            cout << "Name: " << s.name << endl;
            cout << "Grade: " << s.grade << endl;
            cout << "Average: " << s.average << endl;
            file.close();
            return;
        }
    }

    file.close();
    cout << "Student not found.\n";
}

void deleteStudent()
{
    int id;
    cout << "Enter Student ID to delete: ";
    cin >> id;

    ifstream in("students.txt", ios::binary);
    ofstream out("temp.txt", ios::binary);

    Student s;
    bool found = false;

    while (in.read((char*)&s, sizeof(s)))
    {
        if (s.id != id)
            out.write((char*)&s, sizeof(s));
        else
            found = true;
    }

    in.close();
    out.close();

    remove("students.txt");
    rename("temp.txt", "students.txt");

    if (found)
        cout << "Student deleted successfully.\n";
    else
        cout << "Student not found.\n";
}
void updateStudent()
{
    int id;
    cout << "Enter Student ID to update: ";
    cin >> id;

    fstream file("students.txt", ios::binary | ios::in | ios::out);
    Student s;

    while (file.read((char*)&s, sizeof(s)))
    {
        if (s.id == id)
        {
            cin.ignore();
            cout << "Enter New Name: ";
            cin.getline(s.name, 50);

            cout << "Enter New Grade: ";
            cin >> s.grade;

            cout << "Enter New Average: ";
            cin >> s.average;

            file.seekp(-sizeof(s), ios::cur);
            file.write((char*)&s, sizeof(s));
            file.close();

            cout << "Student updated successfully.\n";
            return;
        }
    }

    file.close();
    cout << "Student not found.\n";
}

void searchStudent()
{
    viewStudentByID();
}

void academicReport()
{
    ifstream file("students.txt", ios::binary);
    Student s;

    int countA = 0, countB = 0, countC = 0, countD = 0;

    cout << "\n--- Academic Report ---\n";

    while (file.read((char*)&s, sizeof(s)))
    {
        cout << "Name: " << s.name
             << " | Grade: " << s.grade
             << " | Average: " << s.average << endl;

        if (s.average >= 90) countA++;
        else if (s.average >= 80) countB++;
        else if (s.average >= 70) countC++;
        else countD++;
    }

    cout << "\nGrade Statistics:\n";
    cout << "A: " << countA << endl;
    cout << "B: " << countB << endl;
    cout << "C: " << countC << endl;
    cout << "D: " << countD << endl;

    file.close();
}

#endif
