#include <iostream> 
#include <fstream> 
#include <string> 
#include <cstdlib> 
using namespace std; 
 
 
class Student { 
private: 
  int rollNo; 
  string name; 
  string division; 
  string address; 
 

public: 
  void inputData() { 
      cout << "\nEnter Roll Number: "; 
      cin >> rollNo; 
      cin.ignore(); 
      cout << "Enter Name: "; 
      getline(cin, name); 
      cout << "Enter Division: "; 
      getline(cin, division); 
      cout << "Enter Address: "; 
      getline(cin, address); 
  } 
 
 
  void displayData() { 
      cout << "\nStudent Details:" << endl; 
      cout << "Roll Number: " << rollNo << endl; 
      cout << "Name: " << name << endl; 
      cout << "Division: " << division << endl; 
      cout << "Address: " << address << endl; 
  } 
 
 
  int getRollNo() { return rollNo; } 
  string getName() { return name; } 
  string getDivision() { return division; } 
  string getAddress() { return address; } 
}; 
 
 
class FileHandler { 
private: 
  const string filename = "students.txt"; 
 
 
public: 
  void addStudent() { 
      Student s; 
      s.inputData(); 
     
      ifstream inFile(filename); 
      ofstream tempFile("temp.txt"); 
      bool exists = false; 
     
      if (inFile.is_open()) { 
          string line; 
          while (getline(inFile, line)) { 
              if (line == to_string(s.getRollNo())) { 
                  exists = true; 
                  tempFile << s.getRollNo() << endl; 
                  tempFile << s.getName() << endl; 
                  tempFile << s.getDivision() << endl; 
                  tempFile << s.getAddress() << endl; 
                  tempFile << "END_RECORD" << endl; 
                  for (int i = 0; i < 4; i++) { 
                      getline(inFile, line); 
                  } 
              } else { 
                  tempFile << line << endl; 
              } 
          } 
          inFile.close(); 
      } 
     
      if (!exists) { 
          tempFile << s.getRollNo() << endl; 
          tempFile << s.getName() << endl; 
          tempFile << s.getDivision() << endl; 
          tempFile << s.getAddress() << endl; 
          tempFile << "END_RECORD" << endl; 
      } 
     
      tempFile.close(); 
      remove(filename.c_str()); 
      rename("temp.txt", filename.c_str()); 
     
      cout << "Student record " << (exists ? "updated" : "added") << " successfully!" << endl; 
  } 
 
 
  void deleteStudent(int roll) { 
      ifstream inFile(filename); 
      ofstream tempFile("temp.txt"); 
      bool found = false; 
      string line; 
     
      if (!inFile || !tempFile) { 
          cout << "Error opening files!" << endl; 
          return; 
      } 
     
      while (getline(inFile, line)) { 
          if (line == to_string(roll)) { 
              found = true; 
              for (int i = 0; i < 4; i++) { 
                  getline(inFile, line); 
              } 
          } else { 
              tempFile << line << endl; 
          } 
      } 
     
      inFile.close(); 
      tempFile.close(); 
      remove(filename.c_str()); 
      rename("temp.txt", filename.c_str()); 
     
      if (found) 
          cout << "Student record deleted successfully!" << endl; 
      else 
          cout << "Student record not found!" << endl; 
  } 
 
 
  void displayStudent(int roll) { 
      ifstream inFile(filename); 
      string line; 
      bool found = false; 
 
 
      if (!inFile) { 
          cout << "Error opening file!" << endl; 
          return; 
      } 
 
 
      while (getline(inFile, line)) { 
          if (line == to_string(roll)) { 
              found = true; 
              Student s; 
              cout << "\nStudent Details:" << endl; 
              cout << "Roll Number: " << line << endl; 
             
              getline(inFile, line); 
              cout << "Name: " << line << endl; 
             
              getline(inFile, line); 
              cout << "Division: " << line << endl; 
             
              getline(inFile, line); 
              cout << "Address: " << line << endl; 
             
              getline(inFile, line); 
              break; 
          } 
          while (getline(inFile, line) && line != "END_RECORD"); 
      } 
     
      inFile.close(); 
      if (!found) 
          cout << "Student with roll number " << roll << " not found!" << 
endl; 
  } 
 
 
  void displayAllStudents() { 
   ifstream inFile(filename); 
   string line; 
   bool recordsFound = false; 
 
   if (!inFile) { 
       cout << "Error opening file or no records exist!" << endl; 
       return; 
   } 
   cout << "\n=== All Student Records ===" << endl; 
   while (getline(inFile, line)) { 
       try { 
           stoi(line); 
           recordsFound = true; 
           cout << "\nStudent Details:" << endl; 
           cout << "Roll Number: " << line << endl; 
 
           getline(inFile, line); 
           cout << "Name: " << line << endl; 
 
           getline(inFile, line); 
           cout << "Division: " << line << endl; 
 
           getline(inFile, line); 
           cout << "Address: " << line << endl; 
 
           getline(inFile, line); 
           cout << "-------------------" << endl; 
       } catch (const invalid_argument&) { 
           continue; 
       } 
   } 
 
   inFile.close(); 
   if (!recordsFound) { 
       cout << "No student records found in the file!" << endl; 
   } 
} 
}; 
 
int main() { 
   FileHandler fh; 
   int choice, roll; 
   while (true) { 
       cout << "\nStudent Information System" << endl; 
       cout << "1. Add Student" << endl; 
       cout << "2. Delete Student" << endl; 
       cout << "3. Search Student" << endl; 
       cout << "4. Display All Students" << endl; 
       cout << "5. Exit" << endl;                
       cout << "Enter your choice: "; 
       cin >> choice; 
       switch (choice) { 
           case 1: 
               fh.addStudent(); 
               break; 
           case 2: 
               cout << "Enter roll number to delete: "; 
               cin >> roll; 
               fh.deleteStudent(roll); 
               break; 
           case 3: 
               cout << "Enter roll number to search: "; 
               cin >> roll; 
               fh.displayStudent(roll); 
               break; 
           case 4:                      
               fh.displayAllStudents(); 
               break; 
case 5:                                
cout << "Exiting program..." << endl; 
return 0; 
default: 
cout << "Invalid choice! Please try again." << endl; 
} 
} 
return 0; 
} 
