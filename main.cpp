#include <iostream>
#include <fstream>
#include <chrono>
#include <ctime>

using namespace std;

#define SIZE 100

// Get current date and time
string getCurrentTime() {
    auto now = chrono::system_clock::now();
    time_t currentTime = chrono::system_clock::to_time_t(now);
    return string(ctime(&currentTime));
}

// Structure to store employee login info
struct EmployeeLog {
    string name;
    string time;
};

class Queue {
private:
    EmployeeLog logs[SIZE];
    int front, rear;

public:
    Queue() {
        front = 0;
        rear = -1;
    }

    bool isFull() {
        return rear == SIZE - 1;
    }

    bool isEmpty() {
        return rear < front;
    }

    // Employee login
    void enqueue(string name) {
        if (isFull()) {
            cout << "Employee limit reached!" << endl;
            return;
        }

        rear++;
        logs[rear].name = name;
        logs[rear].time = getCurrentTime();

        ofstream file("log.txt", ios::app);
        file << "Employee: " << name << " | Login Time: " << logs[rear].time;
        file.close();

        cout << "======================================================================================" << endl;
        cout << "Hello, " << name << "!" << endl;
        cout << "Welcome to BlackArch Office. You may now enter." << endl;
        cout << "Logged in at: " << logs[rear].time;
        cout << "======================================================================================" << endl;
    }

    // display login records.
    bool displayLogs() {
        ifstream file("log.txt");
        string line;
        bool hasRecord = false;

        if (!file.is_open()) {
            cout << "Log in record is empty" << endl;
            return false;
        }

        while (getline(file, line)) {
            if (!line.empty()) {
                if (!hasRecord) {
                    cout << "======================================================================================" << endl;
                    cout << "EMPLOYEE LOGIN RECORDS" << endl;
                    cout << " " << endl;
                }
                cout << line << endl;
                hasRecord = true;
            }
        }

        file.close();

        if (!hasRecord) {
            cout << "======================================================================================" << endl;
            cout << "Log in record is empty" << endl;
            return false;
        }

        cout << "======================================================================================" << endl;
        return true;
    }

    // Reset log inn record
    void resetLogs() {
        rear = -1;
        ofstream file("log.txt", ios::trunc);
        file.close();
    }
};

int main() {
    Queue q;
    int choice;
    string employeeName;
    string adminName;
    string passkey;
    string user;
    string resetChoice;

    while (true) {
        cout << "Welcome to BlackArch Office" << endl;
        cout << "Founder: Gideon Bonilla" << endl << endl;
        cout << "Do you want to continue? (Yes/No): ";
        cin >> user;

        if (user == "No" || user == "no") {
            cout << "======================================================================================" << endl;
            cout << "Program terminated." << endl;
            break;
        }

        while (true) {
            cout << "======================================================================================" << endl;
            cout << "1. Log In | 2. View Logged In Employees (Admin) | 3. Exit" << endl;
            cout << "Select: ";
            cin >> choice;

            if (choice == 1) {
                cout << "Enter your name: ";
                cin.ignore();
                getline(cin, employeeName);
                q.enqueue(employeeName);
            }
            else if (choice == 2) {
                cout << "Enter admin name: ";
                cin.ignore();
                getline(cin, adminName);
                cout << "Enter passkey: ";
                getline(cin, passkey);

                if (adminName == "Gideon Bonilla" && passkey == "082006") {

                    bool hasLogs = q.displayLogs();

                    if (hasLogs) {
                        cout << "Do you want to reset it sir? (Yes/No): ";
                        cin >> resetChoice;

                        if (resetChoice == "Yes" || resetChoice == "yes") {
                            q.resetLogs();
                        }
                        cout << "======================================================================================" << endl;
                        cout << "Okay sir, thank you for your response." << endl;
                    }

                } else {
                    cout << "======================================================================================" << endl;
                    cout << "Sorry, you don't have access on this feature. Please select another." << endl;
                }
            }
            else if (choice == 3) {
                cout << "======================================================================================" << endl;
                cout << "Returning to main menu..." << endl;
                cout << "======================================================================================" << endl;
                break;
            }
            else {
                cout << "Invalid choice. Try again." << endl;
            }
        }
    }

    return 0;
}
