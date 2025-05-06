#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <cstring>

using namespace std;

struct Student
{
    int id;
    char name[50];
    float grade;
    bool isActive;
};

const string FILENAME = "students.dat";
const int RECORD_SIZE = sizeof(Student);

Student createRecord(int id, const string &name, float grade)
{
    Student student;
    student.id = id;
    strcpy(student.name, name.c_str());
    student.grade = grade;
    student.isActive = true;
    return student;
}

void insertRecord(int id, const string &name, float grade)
{
    fstream file(FILENAME, ios::in | ios::out | ios::binary);

    if (!file.is_open())
    {
        file.open(FILENAME, ios::out | ios::binary);
        file.close();
        file.open(FILENAME, ios::in | ios::out | ios::binary);
        if (!file.is_open())
        {
            cout << "Error: Cannot open file!" << endl;
            return;
        }
    }


    Student student = createRecord(id, name, grade);

    streampos position = id * RECORD_SIZE;

    Student temp;
    file.seekg(position);
    file.read((char *)&temp, RECORD_SIZE);
    bool positionExists = file.good();

    if (positionExists && temp.isActive)
    {
        cout << "Error: Record with ID " << id << " already exists!" << endl;
    }
    else
    {
        file.clear();
        file.seekp(position);
        file.write((char *)&student, RECORD_SIZE);
        cout << "Record inserted successfully!" << endl;
    }

    file.close();
}

void deleteRecord(int id)
{
    fstream file(FILENAME, ios::in | ios::out | ios::binary);

    if (!file.is_open())
    {
        cout << "Error: File does not exist!" << endl;
        return;
    }

    streampos position = id * RECORD_SIZE;

    Student student;
    file.seekg(position);
    file.read((char *)&student, RECORD_SIZE);
    if (!file.good())
    {
        cout << "Error: Record with ID " << id << " does not exist!" << endl;
    }
    else if (!student.isActive)
    {
        cout << "Error: Record with ID " << id << " is already deleted!" << endl;
    }
    else
    {
        student.isActive = false;
        file.clear();
        file.seekp(position);
        file.write((char *)&student, RECORD_SIZE);
        cout << "Record deleted successfully!" << endl;
    }

    file.close();
}

void displayRecord(int id)
{
    fstream file(FILENAME, ios::in | ios::binary);

    if (!file.is_open())
    {
        cout << "Error: File does not exist!" << endl;
        return;
    }

    Student student;
    streampos position = id * RECORD_SIZE;
    file.seekg(position);

    file.read((char *)&student, RECORD_SIZE);
    if (file.good() && student.isActive)
    {
        cout << "ID: " << student.id << endl;
        cout << "Name: " << student.name << endl;
        cout << "Grade: " << student.grade << endl;
    }
    else
    {
        cout << "Record with ID " << id << " not found or deleted!" << endl;
    }

    file.close();
}

void displayAllRecords()
{
    fstream file(FILENAME, ios::in | ios::binary);

    if (!file.is_open())
    {
        cout << "Error: File does not exist!" << endl;
        return;
    }

    bool foundRecords = false;
    Student student;
    int id = 0;

    cout << "\n=== All Active Student Records ===\n";
    cout << setw(5) << "ID" << setw(30) << "Name" << setw(10) << "Grade" << endl;
    cout << string(45, '-') << endl;

    file.seekg(0, ios::beg);
    while (file.read((char *)&student, RECORD_SIZE))
    {
        if (student.isActive)
        {
            foundRecords = true;
            cout << setw(5) << student.id
                 << setw(30) << student.name
                 << setw(10) << fixed << setprecision(2) << student.grade
                 << endl;
        }
        id += 1;
    }

    if (!foundRecords)
    {
        cout << "No active records found!" << endl;
    }

    file.close();
}

int main()
{
    int choice, id;
    string name;
    float grade;

    do
    {
        system("clear");
        cout << "\n=== Student Record Management System ===\n";
        cout << "1. Insert Record\n";
        cout << "2. Display Record\n";
        cout << "3. Delete Record\n";
        cout << "4. Display All Records\n";
        cout << "5. Exit\n";
        cout << "Enter your choice (1-5): ";

        if (!(cin >> choice))
        {
            cin.clear();
            cin.ignore(10000, '\n');
            choice = -1;
        }
        else
        {
            cin.ignore();
        }

        switch (choice)
        {
        case 1:
            cout << "\nEnter ID: ";
            if (!(cin >> id))
            {
                cout << "Error: Invalid ID!\n";
                cin.clear();
                cin.ignore(10000, '\n');
                break;
            }
            cin.ignore();
            cout << "Enter Name: ";
            getline(cin, name);
            cout << "Enter Grade: ";
            if (!(cin >> grade))
            {
                cout << "Error: Invalid grade!\n";
                cin.clear();
                cin.ignore(10000, '\n');
                break;
            }
            insertRecord(id, name, grade);
            break;

        case 2:
            cout << "\nEnter ID to display: ";
            if (!(cin >> id))
            {
                cout << "Error: Invalid ID!\n";
                cin.clear();
                cin.ignore(10000, '\n');
                break;
            }
            cout << "\n";
            displayRecord(id);
            break;

        case 3:
            cout << "\nEnter ID to delete: ";
            if (!(cin >> id))
            {
                cout << "Error: Invalid ID!\n";
                cin.clear();
                cin.ignore(10000, '\n');
                break;
            }
            cout << "\n";
            deleteRecord(id);
            break;

        case 4:
            cout << "\n";
            displayAllRecords();
            break;

        case 5:
            cout << "\nExiting program...\n";
            break;

        default:
            cout << "\nInvalid choice! Please try again.\n";
        }

        if (choice != 5)
        {
            cout << "\nPress Enter to continue...";
            cin.ignore(10000, '\n');
            cin.get();
        }
    } while (choice != 5);

    return 0;
}
