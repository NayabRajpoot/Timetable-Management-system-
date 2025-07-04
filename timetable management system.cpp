// Timetable Management System 

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdio>



using namespace std;

// Function Prototypes
bool login(string role);
void adminPanel();
void userPanel();

// Admin Features
void addTeacher();
void removeTeacher();
void updateTeacher();
void viewTeachers();
void addClass();
void deleteClass();
void updateClass();
void viewClasses();
void addSchedule();
void backupData();

// User Features
void viewTimetable();
void viewSchedule();
void searchSubject();
void showSubjects();
void requestChange();
void printTimetable();
void exportTimetable();
void sendFeedback();

int main() {
    int choice;
    while (true) {
        cout << "\n===== TIMETABLE MANAGEMENT SYSTEM =====\n";
        cout << "1. Admin Login\n2. User Login\n3. Exit\nChoice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                if (login("admin")) adminPanel();
                break;
            case 2:
                if (login("user")) userPanel();
                break;
            case 3:
                cout << "Exiting...\n";
                return 0;
            default:
                cout << "Invalid choice.\n";
        }
    }
}

bool login(string role) {
    string name, email, password;
    string storedName, storedEmail, storedPassword;
    string filename;

    cin.ignore(); // Clear buffer
    cout << "\n--- " << role << " Login ---\n";
    cout << "Enter Name: "; getline(cin, name);
    cout << "Enter Email: "; getline(cin, email);
    cout << "Enter Password: "; getline(cin, password);

    filename = (role == "admin") ? "admin_login.txt" : "user_login.txt";
    ifstream file(filename.c_str());


    while (file >> ws && getline(file, storedName) && getline(file, storedEmail) && getline(file, storedPassword)) {
        if (name == storedName && email == storedEmail && password == storedPassword) {
            cout << "Login successful!\n";
            return true;
        }
    }

    cout << "Login failed. Check credentials.\n";
    return false;
}



void adminPanel() {
    int ch;
    do {
        cout << "\n--- Admin Panel ---\n";
        cout << "1. Add Teacher\n2. Remove Teacher\n3. Update Teacher\n4. View Teachers\n";
        cout << "5. Add Class\n6. Delete Class\n7. Update Class\n8. View Classes\n";
        cout << "9. Add Schedule\n10. Backup All Data\n0. Back\nChoice: ";
        cin >> ch;

        switch (ch) {
        	   case 1: 
                do {
                    addTeacher();
                    cout << "Add another teacher? (y/n): ";
                    char again;
                    cin >> again;
                    if (again != 'y' && again != 'Y') break;
                } while (true);
                break;
            case 2: removeTeacher(); break;
            case 3: updateTeacher(); break;
            case 4: viewTeachers(); break;
              case 5: 
                do {
                    addClass();
                    cout << "Add another class? (y/n): ";
                    char again;
                    cin >> again;
                    if (again != 'y' && again != 'Y') break;
                } while (true);
                break;
            case 6: deleteClass(); break;
            case 7: updateClass(); break;
            case 8: viewClasses(); break;
			 case 9: 
                do {
                    addSchedule();
                    cout << "Add another Schedule? (y/n): ";
                    char again;
                    cin >> again;
                    if (again != 'y' && again != 'Y') break;
                } while (true);
                break;
            
            case 10: backupData(); break;
            case 0: break;
            default: cout << "Invalid choice.\n";
        }
    } while (ch != 0);
}

void userPanel() {
    int ch;
    do {
        cout << "\n--- User Panel ---\n";
        cout << "1. View Timetable\n2. View Schedule\n3. Search Subject\n4. Show Subjects\n";
        cout << "5. Request Time Change\n6. View Classes\n7. View Teachers\n8. Print Timetable\n";
        cout << "9. Export Timetable\n10. Send Feedback\n0. Back\nChoice: ";
        cin >> ch;

        switch (ch) {
            case 1: viewTimetable(); break;
            case 2: viewSchedule(); break;
            case 3: searchSubject(); break;
            case 4: showSubjects(); break;
            case 5: requestChange(); break;
            case 6: viewClasses(); break;
            case 7: viewTeachers(); break;
            case 8: printTimetable(); break;
            case 9: exportTimetable(); break;
            case 10: sendFeedback(); break;
            case 0: break;
            default: cout << "Invalid choice.\n";
        }
    } while (ch != 0);
}

// Admin Functions
void addTeacher() {
    ofstream file("teachers.txt", ios::app);
    string name, subject;
    cin.ignore();
    cout << "Enter Teacher Name: "; getline(cin, name);
    cout << "Enter Subject: "; getline(cin, subject);
    file << name << "," << subject << endl;
    file.close();
    cout << "Teacher added successfully.\n";
}

void removeTeacher() {
    string name, line;
    cin.ignore();
    cout << "Enter Teacher Name to Remove: "; getline(cin, name);
    ifstream in("teachers.txt");
    ofstream out("temp.txt");
    bool found = false;
    while (getline(in, line)) {
        if (line.find(name) == string::npos) {
            out << line << endl;
        } else {
            found = true;
        }
    }
    in.close(); out.close();
    remove("teachers.txt"); rename("temp.txt", "teachers.txt");
    if (found) cout << "Teacher removed.\n";
    else cout << "Teacher not found.\n";
}

void updateTeacher() {
    string name, newName, newSubject, line;
    cin.ignore();
    cout << "Enter Teacher Name to Update: "; getline(cin, name);
    cout << "Enter New Name: "; getline(cin, newName);
    cout << "Enter New Subject: "; getline(cin, newSubject);
    ifstream in("teachers.txt");
    ofstream out("temp.txt");
    while (getline(in, line)) {
        if (line.find(name) != string::npos) {
            out << newName << "," << newSubject << endl;
        } else {
            out << line << endl;
        }
    }
    in.close(); out.close();
    remove("teachers.txt"); rename("temp.txt", "teachers.txt");
    cout << "Teacher updated.\n";
}

void viewTeachers() {
    ifstream file("teachers.txt");
    string line;
    cout << "\n--- Teachers ---\n";
    while (getline(file, line)) cout << line << endl;
    file.close();
}

void addClass() {
    ofstream file("classes.txt", ios::app);
    string className;
    cin.ignore();
    cout << "Enter Class Name: "; getline(cin, className);
    file << className << endl;
    file.close();
    cout << "Class added successfully.\n";
}

void deleteClass() {
    string className, line;
    cin.ignore();
    cout << "Enter Class Name to Delete: "; getline(cin, className);
    ifstream in("classes.txt");
    ofstream out("temp.txt");
    while (getline(in, line)) {
        if (line != className) out << line << endl;
    }
    in.close(); out.close();
    remove("classes.txt"); rename("temp.txt", "classes.txt");
    cout << "Class deleted.\n";
}

void updateClass() {
    string oldName, newName, line;
    cin.ignore();
    cout << "Enter Class Name to Update: "; getline(cin, oldName);
    cout << "Enter New Name: "; getline(cin, newName);
    ifstream in("classes.txt");
    ofstream out("temp.txt");
    while (getline(in, line)) {
        if (line == oldName) out << newName << endl;
        else out << line << endl;
    }
    in.close(); out.close();
    remove("classes.txt"); rename("temp.txt", "classes.txt");
    cout << "Class updated.\n";
}

void viewClasses() {
    ifstream file("classes.txt");
    string line;
    cout << "\n--- Classes ---\n";
    while (getline(file, line)) cout << line << endl;
    file.close();
}

void addSchedule() {
    ofstream file("schedule.txt", ios::app);
    string className, day, time, subject, teacher;
    cin.ignore();
    cout << "Class: "; getline(cin, className);
    cout << "Day: "; getline(cin, day);
    cout << "Time: "; getline(cin, time);
    cout << "Subject: "; getline(cin, subject);
    cout << "Teacher: "; getline(cin, teacher);
    file << className << "," << day << "," << time << "," << subject << "," << teacher << endl;
    file.close();
    cout << "Schedule added.\n";
}

void backupData() {
    ofstream backup("backup.txt");
    const char* files[] = {"teachers.txt", "classes.txt", "schedule.txt", "feedback.txt"};
    for (int i = 0; i < 4; i++) {
        ifstream in(files[i]);
        string line;
        backup << "[" << files[i] << "]\n";
        while (getline(in, line)) backup << line << endl;
        backup << endl;
        in.close();
    }
    backup.close();
    cout << "Backup completed.\n";
}

// User Functions
void viewTimetable() { viewSchedule(); }
void viewSchedule() {
    ifstream file("schedule.txt");
    string line;
    cout << "\n--- Timetable ---\n";
    while (getline(file, line)) cout << line << endl;
    file.close();
}

void searchSubject() {
    string subject;
    cin.ignore();
    cout << "Enter Subject to Search: "; getline(cin, subject);
    ifstream file("schedule.txt");
    string line; bool found = false;
    while (getline(file, line)) {
        if (line.find(subject) != string::npos) {
            cout << line << endl; found = true;
        }
    }
    file.close();
    if (!found) cout << "Subject not found.\n";
}

void showSubjects() {
    ifstream file("teachers.txt");
    string line;
    cout << "\n--- Subjects ---\n";
    while (getline(file, line)) {
        int pos = line.find(",");
        if (pos != string::npos)
            cout << line.substr(pos + 1) << endl;
    }
    file.close();
}

void requestChange() {
    ofstream file("requests.txt", ios::app);
    string request;
    cin.ignore();
    cout << "Enter Change Request: "; getline(cin, request);
    file << request << endl;
    file.close();
    cout << "Request submitted.\n";
}

void printTimetable() {
    viewSchedule();
}

void exportTimetable() {
    ifstream in("schedule.txt");
    ofstream out("exported_timetable.txt");
    string line;
    while (getline(in, line)) out << line << endl;
    in.close(); out.close();
    cout << "Timetable exported to 'exported_timetable.txt'.\n";
}

void sendFeedback() {
    ofstream file("feedback.txt", ios::app);
    string feedback;
    cin.ignore();
    cout << "Enter Feedback: "; getline(cin, feedback);
    file << feedback << endl;
    file.close();
    cout << "Thank you for your feedback!\n";
}

