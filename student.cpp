#include <iostream>
#include <fstream>
#include <limits>
using namespace std;

struct Student {
    int id;
    string name;
};

Student s[100];
int count = 0;

// Load from file
void loadFromFile() {
    ifstream file("students.txt");
    while(file >> s[count].id) {
        file.ignore();
        getline(file, s[count].name);
        count++;
    }
    file.close();
}

// Save to file
void saveToFile() {
    ofstream file("students.txt");
    for(int i = 0; i < count; i++) {
        file << s[i].id << endl;
        file << s[i].name << endl;
    }
    file.close();
}

// Add student
void addStudent() {
    int newId;
    cout << "Enter ID: ";
    cin >> newId;

    // Prevent duplicate
    for(int i = 0; i < count; i++) {
        if(s[i].id == newId) {
            cout << "ID already exists!\n";
            return;
        }
    }

    s[count].id = newId;

    cout << "Enter Name: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, s[count].name);

    count++;
    saveToFile();
    cout << "Student added!\n";
}

// View students
void viewStudents() {
    if(count == 0) {
        cout << "No students available.\n";
        return;
    }

    for(int i = 0; i < count; i++) {
        cout << "ID: " << s[i].id 
             << " | Name: " << s[i].name << endl;
    }
}

// Delete student
void deleteStudent() {
    int id;
    cout << "Enter ID to delete: ";
    cin >> id;

    for(int i = 0; i < count; i++) {
        if(s[i].id == id) {
            for(int j = i; j < count - 1; j++) {
                s[j] = s[j + 1];
            }
            count--;
            saveToFile();
            cout << "Student deleted!\n";
            return;
        }
    }

    cout << "Student not found!\n";
}

// Search student
void searchStudent() {
    int id;
    cout << "Enter ID to search: ";
    cin >> id;

    for(int i = 0; i < count; i++) {
        if(s[i].id == id) {
            cout << "Found: ID = " << s[i].id 
                 << " | Name = " << s[i].name << endl;
            return;
        }
    }

    cout << "Student not found!\n";
}

// Update student
void updateStudent() {
    int id;
    cout << "Enter ID to update: ";
    cin >> id;

    for(int i = 0; i < count; i++) {
        if(s[i].id == id) {
            cout << "Enter new name: ";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, s[i].name);

            saveToFile();
            cout << "Student updated!\n";
            return;
        }
    }

    cout << "Student not found!\n";
}

// 🔥 Sort students by ID
void sortStudents() {
    for(int i = 0; i < count - 1; i++) {
        for(int j = i + 1; j < count; j++) {
            if(s[i].id > s[j].id) {
                Student temp = s[i];
                s[i] = s[j];
                s[j] = temp;
            }
        }
    }
    cout << "Students sorted by ID!\n";
}

// Main function
int main() {
    loadFromFile();

    int choice;
    while(true) {
        cout << "\n1. Add\n2. View\n3. Delete\n4. Search\n5. Update\n6. Sort\n7. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if(choice == 1) addStudent();
        else if(choice == 2) viewStudents();
        else if(choice == 3) deleteStudent();
        else if(choice == 4) searchStudent();
        else if(choice == 5) updateStudent();
        else if(choice == 6) sortStudents();
        else if(choice == 7) break;
        else cout << "Invalid choice!\n";
    }

    return 0;
}