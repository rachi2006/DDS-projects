#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

struct Transaction {
    string date;       // Format: YYYY-MM-DD
    string type;       // Income / Expense
    double amount;
    string description;
};

vector<Transaction> transactions;

// Function to add a transaction
void addTransaction() {
    Transaction t;
    cout << "Enter date (YYYY-MM-DD): ";
    cin >> t.date;
    cout << "Enter type (Income/Expense): ";
    cin >> t.type;
    cout << "Enter amount: ";
    cin >> t.amount;
    cin.ignore();
    cout << "Enter description: ";
    getline(cin, t.description);
    transactions.push_back(t);
    cout << "Transaction added!\n";
}

// Show all transactions
void showTransactions() {
    cout << "\n--- All Transactions ---\n";
    cout << left << setw(12) << "Date" 
         << setw(10) << "Type" 
         << setw(10) << "Amount" 
         << "Description\n";
    cout << "---------------------------------------------\n";
    for (auto &t : transactions) {
        cout << setw(12) << t.date 
             << setw(10) << t.type 
             << setw(10) << t.amount 
             << t.description << "\n";
    }
}

// Save to file
void saveToFile() {
    ofstream file("finance.txt");
    for (auto &t : transactions) {
        file << t.date << "|" << t.type << "|" << t.amount << "|" << t.description << "\n";
    }
    file.close();
    cout << "Data saved to finance.txt\n";
}

// Load from file
void loadFromFile() {
    ifstream file("finance.txt");
    if (!file) {
        cout << "No saved data found.\n";
        return;
    }
    transactions.clear();
    Transaction t;
    string line;
    while (getline(file, line)) {
        size_t pos1 = line.find("|");
        size_t pos2 = line.find("|", pos1 + 1);
        size_t pos3 = line.find("|", pos2 + 1);

        t.date = line.substr(0, pos1);
        t.type = line.substr(pos1 + 1, pos2 - pos1 - 1);
        t.amount = stod(line.substr(pos2 + 1, pos3 - pos2 - 1));
        t.description = line.substr(pos3 + 1);

        transactions.push_back(t);
    }
    file.close();
    cout << "Data loaded from finance.txt\n";
}

// Sort by amount
void sortByAmount() {
    sort(transactions.begin(), transactions.end(), [](Transaction &a, Transaction &b) {
        return a.amount < b.amount;
    });
    cout << "Transactions sorted by amount.\n";
}

// Filter expenses > 100
void filterExpenses() {
    cout << "\n--- Expenses > 100 ---\n";
    for (auto &t : transactions) {
        if (t.type == "Expense" && t.amount > 100) {
            cout << t.date << " | " << t.amount << " | " << t.description << "\n";
        }
    }
}

// ASCII Bar Chart of expenses per month
void showBarChart() {
    cout << "\n--- Monthly Expense Chart ---\n";
    int monthly[12] = {0};
    for (auto &t : transactions) {
        if (t.type == "Expense") {
            int month = stoi(t.date.substr(5, 2)); // extract month
            monthly[month - 1] += t.amount;
        }
    }
    for (int i = 0; i < 12; i++) {
        cout << setw(3) << i + 1 << " | ";
        int bars = monthly[i] / 10; // each '*' = 10 units
        for (int j = 0; j < bars; j++) cout << "*";
        cout << " (" << monthly[i] << ")\n";
    }
}

int main() {
    int choice;
    loadFromFile(); // load data if available

    do {
        cout << "\n=== Personal Finance Tracker ===\n";
        cout << "1. Add Transaction\n";
        cout << "2. Show Transactions\n";
        cout << "3. Save Data\n";
        cout << "4. Sort by Amount\n";
        cout << "5. Filter Expenses > 100\n";
        cout << "6. Show Monthly Expense Chart\n";
        cout << "7. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch(choice) {
            case 1: addTransaction(); break;
            case 2: showTransactions(); break;
            case 3: saveToFile(); break;
            case 4: sortByAmount(); break;
            case 5: filterExpenses(); break;
            case 6: showBarChart(); break;
            case 7: cout << "Exiting...\n"; saveToFile(); break;
            default: cout << "Invalid choice!\n";
        }
    } while(choice != 7);

    return 0;
}
