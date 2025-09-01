#include <iostream>
#include <queue>
#include <string>
using namespace std;

// Structure for a patient
struct Patient {
    string name;
    int severity;   // higher = more critical
    bool emergency; // true = emergency
};

// Comparator for priority queue
struct Compare {
    bool operator()(const Patient &a, const Patient &b) {
        return a.severity < b.severity; // higher severity first
    }
};

priority_queue<Patient, vector<Patient>, Compare> emergencyQueue;
queue<Patient> regularQueue;

void addPatient() {
    Patient p;
    int type;
    cout << "Enter patient name: ";
    cin >> p.name;
    cout << "1. Emergency  2. Regular: ";
    cin >> type;

    if(type == 1) {
        p.emergency = true;
        cout << "Enter severity (1-10): ";
        cin >> p.severity;
        emergencyQueue.push(p);
    } else {
        p.emergency = false;
        p.severity = 0;
        regularQueue.push(p);
    }
    cout << "Patient added successfully!\n";
}

void servePatient() {
    if(!emergencyQueue.empty()) {
        Patient p = emergencyQueue.top();
        emergencyQueue.pop();
        cout << "Serving EMERGENCY patient: " << p.name 
             << " (severity " << p.severity << ")\n";
    }
    else if(!regularQueue.empty()) {
        Patient p = regularQueue.front();
        regularQueue.pop();
        cout << "Serving REGULAR patient: " << p.name << "\n";
    }
    else {
        cout << "No patients in queue.\n";
    }
}

void showQueueStatus() {
    cout << "\n--- Queue Status ---\n";
    cout << "Emergency patients: " << emergencyQueue.size() << endl;
    cout << "Regular patients: " << regularQueue.size() << endl;

    int total = emergencyQueue.size() + regularQueue.size();
    cout << "Estimated wait time: " << total * 10 << " minutes\n";
}

int main() {
    int choice;
    do {
        cout << "\n=== Hospital Patient Queue ===\n";
        cout << "1. Add Patient\n";
        cout << "2. Serve Next Patient\n";
        cout << "3. Show Queue Status\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch(choice) {
            case 1: addPatient(); break;
            case 2: servePatient(); break;
            case 3: showQueueStatus(); break;
            case 4: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice!\n";
        }
    } while(choice != 4);

    return 0;
}
