// FARM WORKER MANAGEMENT SYSTEM.....

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

// Struct to Represent a Worker
struct Worker {
    int id;
    string name;
    string role;
    string task;
    string date;
    long long mobile_num;
    int hours_worked;
    int hourly_wage;
    int total_wage;

    Worker* next;
};

// Function to validate the date format and value
bool isValidDate(const string& date) {
    int day, month, year;
    char delimiter1, delimiter2;

    // Check if the date is in the format DD/MM/YYYY
    stringstream ss(date);
    ss >> day >> delimiter1 >> month >> delimiter2 >> year;

    if (delimiter1 != '/' || delimiter2 != '/' || ss.fail() || !ss.eof()) {
        return false; // Invalid format
    }

    // Check for valid month and year
    if (month < 1 || month > 12 || year < 1900 || year > 2100) {
        return false; // Invalid month or year
    }

    // Check for valid day based on month
    if (day < 1 || day > 31) {
        return false; // Invalid day
    }

    // Check for months with 30 days
    if (month == 4 || month == 6 || month == 9 || month == 11) {
        if (day > 30) {
            return false; // Invalid day for month with 30 days
        }
    }

    // Check for February and leap years
    if (month == 2) {
        bool isLeap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
        if ((isLeap && day > 29) || (!isLeap && day > 28)) {
            return false; // Invalid day for February
        }
    }

    return true; // Valid date
}

// Function to validate mobile number
bool isValidMobileNumber(const string& mobile) {
    if (mobile.length() != 10) {
        return false; // Must be exactly 10 digits
    }
    if (mobile[0] < '6' || mobile[0] > '9') {
        return false; // First digit must be between 6 and 9
    }
    for (char c : mobile) {
        if (!isdigit(c)) {
            return false; // All characters must be digits
        }
    }
    return true; // Valid mobile number
}

// Add a New Worker to the System
void Add_Worker(Worker*& head) {
    static int lastAssignedId = 0; // Static variable to keep track of the last assigned ID
    Worker* newWorker = new Worker();

    newWorker->id = ++lastAssignedId; // Auto-generate the Worker ID
    cout << "Generated Worker ID: " << newWorker->id << endl; // Display the generated ID
    cout << "Enter Worker Name: ";
    cin >> newWorker->name;
    cout << "Enter Worker Role: ";
    cin >> newWorker->role;
    cout << "Enter Worker Hourly Wage: Rs.";
    cin >> newWorker->hourly_wage;

    string mobile;
    while (true) {
        cout << "Enter Worker Mobile Number (10 digits): ";
        cin >> mobile;
        if (isValidMobileNumber(mobile)) {
            newWorker->mobile_num = stoll(mobile); // Convert string to long long
            break; // Exit loop if valid
        } else {
            cout << "Invalid mobile number. Please enter a valid 10-digit number." << endl;
        }
    }
    
    newWorker->hours_worked = 0;
    newWorker->total_wage = 0;
    newWorker->task = "Nothing";
    newWorker->next = nullptr;

    if (head == nullptr) {
        head = newWorker;
    } else {
        Worker* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newWorker;
    }
    cout << "Worker Added Successfully....." << endl;
    cout << endl;
}

// Assign Task to the Worker
void Assign_Task(Worker* head) {
    int id;
    cout << "Enter Worker ID for the Assign Task: ";
    cin >> id;

    Worker* temp = head;

    while (temp != nullptr) {
        if (temp->id == id) {
            string taskDate;
            cout << "Enter The Task: ";
            cin >> temp->task;

            // Loop until a valid date is entered
            while (true) {
                cout << "Enter Task Assign Date (DD/MM/YYYY): ";
                cin >> taskDate;

                if (isValidDate(taskDate)) {
                    temp->date = taskDate;
                    break; // Exit the loop if the date is valid
                } else {
                    cout << "Invalid date format. Please enter a valid date (DD/MM/YYYY)." << endl;
                }
            }

            cout << endl;
            cout << temp->task << " : Task Assigned Successfully to: " << temp->name << endl;
            cout << endl;
            return;
        }
        temp = temp->next;
    }
    cout << "Worker Not Found." << endl;
}

// Update the Hours Worked by a Worker and Check their Wage
void Update_Hours(Worker* head) {
    int id, hours;

    cout << "Enter Worker ID for Update Hours: ";
    cin >> id;

    Worker* temp = head;

    while (temp != nullptr) {
        if (temp->id == id) {
            if (temp->task == "Nothing") {
                cout << "No Task Assigned. Please Assign the Task First....";
                return;
            }
            cout << "Enter How Many Hours They Worked: ";
            cin >> hours;
            temp->hours_worked += hours;
            temp->total_wage = temp->hours_worked * temp->hourly_wage;
            cout << "Hours Updated and Total Wage of Worker is: " << temp->total_wage << endl;
            cout << "Worker ID: " << temp->id << ", Name: " << temp->name << ", Hours Worked: " << temp->hours_worked << ", Total Wage: " << temp->total_wage << endl;
            cout << endl;
            return;
        }
        temp = temp->next;
    }
    cout << "Worker Not Found." << endl;
    cout << endl;
}

// Edit Worker Details
void Edit_Worker_Details(Worker* head) {
    int id;
    string newName;
    string newRole;
    int newWage;
    long long newMobile;

    cout << "Enter Worker ID to Edit Details: ";
    cin >> id;
    cout << endl;

    Worker* temp = head;

    while (temp != nullptr) {
        if (temp->id == id) {
            cout << "Editing Details for Worker ID: " << temp->id << endl;
            cout << endl;

            // Edit Name
            cout << "Current Name: " << temp->name << endl;
            cout << "Enter New Name Or Enter '0' to Keep With Current Name: ";
            cin >> newName;
            if (newName != "0") {
                temp->name = newName;
            }
            cout << endl;

            // Edit Role
            cout << "Current Role: " << temp->role << endl;
            cout << "Enter New Role Or Enter '0' to Keep With Current Role: ";
            cin >> newRole;
            if (newRole != "0") {
                temp->role = newRole;
            }
            cout << endl;

            // Edit Hourly Wage
            cout << "Current Hourly Wage: " << temp->hourly_wage << endl;
            cout << "Enter New Hourly Wage Or Enter -1 to Keep With Current Hourly Wage: ";
            cin >> newWage;
            if (newWage != -1) {
                temp->hourly_wage = newWage;
                // Recalculate total wage
                temp->total_wage = temp->hours_worked * temp->hourly_wage;
            }
            cout << endl;

            // Edit Mobile Number
            cout << "Current Mobile Number: " << temp->mobile_num << endl;
            cout << "Enter New Mobile Number Or Enter -1 to Keep With Current Mobile Number: ";
            cin >> newMobile;
            if (newMobile != -1) {
                temp->mobile_num = newMobile;
            }
            cout << endl;

            cout << "Worker Details Updated Successfully....." << endl;
            cout << endl;
            return;
        }
        temp = temp->next;
    }
    cout << "Worker Not Found." << endl;
    cout << endl;
}

// Display All Workers in the System
// Display All Workers in the System
void Display_Workers(Worker* head) {
    if (head == nullptr) {
        cout << "No Workers in The System." << endl;
        return;
    }

    // Print the header
    cout << left << setw(5) << "ID" 
         << left << setw(15) << "Name" 
         << left << setw(15) << "Role" 
         << left << setw(20) << "Task" 
         << left << setw(15) << "Hours Worked" 
         << left << setw(15) << "Total Wage" 
         << left << setw(15) << "Mobile Number" 
         << left << setw(20) << "Task Assign Date" << endl;

    cout << string(120, '-') << endl; // Separator line

    Worker* temp = head;
    while (temp != nullptr) {
        cout << left << setw(5) << temp->id 
             << left << setw(15) << temp->name 
             << left << setw(15) << temp->role 
             << left << setw(25) << temp->task 
             << left << setw(12) << temp->hours_worked 
             << left << setw(13) << temp->total_wage 
             << left << setw(15) << temp->mobile_num 
             << left << setw(20) << temp->date << endl;
        temp = temp->next;
    }
    cout << endl;
}

// Search for a Worker by ID, Name, or Role
void Search_Worker(Worker* head) {
    int choice;
    cout << "Search By: 1. ID  2. Name  3. Role" << endl;
    cout << endl;
    cout << "Enter your choice :- ";
    cin >> choice;

    if (choice == 1) {
        int id;
        cout << "Enter Worker ID :- ";
        cin >> id;
        cout << endl;
        Worker* temp = head;
        while (temp != nullptr) {
            if (temp->id == id) {
                cout << "Worker Found: ID :- " << temp->id << ", Role :- " << temp->role << ", Hourly Wage :- " << temp->hourly_wage << endl;
                return;
            }
            temp = temp->next;
        }
        cout << "Worker Not Found....." << endl;
    } else if (choice == 2) {
        string name;
        cout << "Enter Worker Name :- ";
        cin >> name;
        Worker* temp = head;
        while (temp != nullptr) {
            if (temp->name == name) {
                cout << "Worker Found: ID :- " << temp->id << ", Role :- " << temp->role << ", Hourly Wage :- " << temp->hourly_wage << endl;
                cout << endl;
                return;
            }
            temp = temp->next;
        }
        cout << "Worker Not Found....." << endl;
    } else if (choice == 3) {
        string role;
        cout << "Enter Worker Role :- ";
        cin >> role;
        Worker* temp = head;
        bool found = false;
        while (temp != nullptr) {
            if (temp->role == role) {
                cout << "Worker Found: ID :- " << temp->id << ", Name :- " << temp->name << ", Hourly Wage :- " << temp->hourly_wage << endl;
                found = true;
            }
            temp = temp->next;
        }
        if (!found) {
            cout << "No Workers Found with Role :- " << role << endl;
        }
    } else {
        cout << "Invalid Choice....." << endl;
    }
    cout << endl;
}

// Delete a Worker from the System
void Delete_Worker(Worker*& head) {
    int id;
    cout << "Enter Worker ID for Delete :- ";
    cin >> id;
    cout << endl;
    Worker* temp = head;
    Worker* prev = nullptr;

    while (temp != nullptr) {
        if (temp->id == id) {
            if (prev == nullptr) {
                head = temp->next; // Deleting the head
            } else {
                prev->next = temp->next; // Bypass the node to delete
            }
            delete temp; // Free memory
            cout << "Worker Deleted Successfully....." << endl;
            cout << endl;
            return;
        }
        prev = temp;
        temp = temp->next;
    }
    cout << "Worker Not Found....." << endl;
    cout << endl;
}

// Clear All Workers from the System
void Clear_Workers(Worker*& head) {
    Worker* temp;
    while (head != nullptr) {
        temp = head;
        head = head->next;
        delete temp; 
    }
    cout << "All Workers Cleared....." << endl;
    cout << endl;
}

// Main Function to Demonstrate the System
int main() {
    Worker* head = nullptr;
    int choice;

    do {
        cout << "|-:------------------------:Farm Worker Management System :----------------------------:-|" << endl;
        cout << "1. Add Worker :- " << endl;
        cout << "2. Assign Task :- " << endl;
        cout << "3. Update Hours :- " << endl;
        cout << "4. Edit Worker Details :- " << endl;
        cout << "5. Display Workers :- " << endl;
        cout << "6. Search Worker :- " << endl;
        cout << "7. Delete Worker :- " << endl;
        cout << "8. Clear All Workers :- " << endl;
        cout << "9. Exit :- " << endl;
        cout << endl;
        cout << "Enter your choice :- ";
        cin >> choice;

        switch (choice) {
            case 1:
                Add_Worker(head);
                break;
            case 2:
                Assign_Task(head);
                break;
            case 3:
                Update_Hours(head);
                break;
            case 4:
                Edit_Worker_Details(head);
                break;
            case 5:
                Display_Workers(head);
                break;
            case 6:
                Search_Worker(head);
                break;
            case 7:
                Delete_Worker(head);
                break;
            case 8:
                Clear_Workers(head);
                break;
            case 9:
                cout << "Exiting the System....." << endl;
                break;
            default:
                cout << "Invalid Choice. Please Try Again!" << endl;
        }
    } while (choice != 9);

    return 0;
}
