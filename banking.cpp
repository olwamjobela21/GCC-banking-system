// GCC BANK - Simple command line banking system
// Uses: functions, if/else, loops and arrays

#include <iostream>
#include <string>
using namespace std;

const int NUM_USERS = 3;

// Arrays that store the details of 3 users.
// Position 0 in every array belongs to user 1, position 1 to user 2, etc.
string names[NUM_USERS]        = {"Thabo", "Lerato", "Sipho"};
int    accountNumbers[NUM_USERS] = {1001, 1002, 1003};
int    pins[NUM_USERS]         = {1111, 2222, 3333};
double balances[NUM_USERS]     = {1000.00, 2500.00, 500.00};

// Shows the menu
void displayMenu() {
    cout << "\n===== GCC BANK =====" << endl;
    cout << "1. Deposit" << endl;
    cout << "2. Withdraw" << endl;
    cout << "3. Send Cash" << endl;
    cout << "4. Check Balance" << endl;
    cout << "5. Exit" << endl;
    cout << "Enter choice: ";
}

// Looks for an account number. Returns its position, or -1 if not found.
int findAccount(int accNumber) {
    for (int i = 0; i < NUM_USERS; i++) {
        if (accountNumbers[i] == accNumber) {
            return i;
        }
    }
    return -1;
}

// Adds money to the logged-in user's account
void deposit(int user) {
    double amount;
    cout << "Enter amount to deposit: R";
    cin >> amount;

    if (amount > 0) {
        balances[user] += amount;
        cout << "Deposit successful. New balance: R" << balances[user] << endl;
    } else {
        cout << "Error: amount must be more than 0." << endl;
    }
}

// Removes money from the logged-in user's account
void withdraw(int user) {
    double amount;
    cout << "Enter amount to withdraw: R";
    cin >> amount;

    if (amount <= 0) {
        cout << "Error: amount must be more than 0." << endl;
    } else if (amount > balances[user]) {
        cout << "Error: not enough money. Your balance is R" << balances[user] << endl;
    } else {
        balances[user] -= amount;
        cout << "Withdrawal successful. New balance: R" << balances[user] << endl;
    }
}

// Sends money to another account
void sendCash(int user) {
    int accNumber;
    double amount;

    cout << "Enter the account number to send to: ";
    cin >> accNumber;

    int receiver = findAccount(accNumber);

    if (receiver == -1) {
        cout << "Error: that account does not exist." << endl;
    } else if (receiver == user) {
        cout << "Error: you cannot send money to yourself." << endl;
    } else {
        cout << "Enter amount to send: R";
        cin >> amount;

        if (amount <= 0) {
            cout << "Error: amount must be more than 0." << endl;
        } else if (amount > balances[user]) {
            cout << "Error: not enough money. Your balance is R" << balances[user] << endl;
        } else {
            balances[user] -= amount;
            balances[receiver] += amount;
            cout << "R" << amount << " sent to " << names[receiver] << "." << endl;
            cout << "Your new balance: R" << balances[user] << endl;
        }
    }
}

// Shows the balance
void checkBalance(int user) {
    cout << "Your balance is: R" << balances[user] << endl;
}

// Asks for account number and PIN. Returns the user's position, or -1 if wrong.
int login() {
    int accNumber, pin;

    cout << "Enter your account number: ";
    cin >> accNumber;
    cout << "Enter your PIN: ";
    cin >> pin;

    int user = findAccount(accNumber);

    if (user != -1 && pins[user] == pin) {
        cout << "\nWelcome, " << names[user] << "!" << endl;
        return user;
    }

    cout << "Error: wrong account number or PIN." << endl;
    return -1;
}

int main() {
    cout << "Welcome to GCC Bank" << endl;

    // Keep asking until login works
    int user = -1;
    while (user == -1) {
        user = login();
    }

    int choice = 0;

    // The menu repeats until the user chooses 5 (Exit)
    while (choice != 5) {
        displayMenu();
        cin >> choice;

        // If the user typed letters instead of a number
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            choice = 0;
        }

        switch (choice) {
            case 1: deposit(user); break;
            case 2: withdraw(user); break;
            case 3: sendCash(user); break;
            case 4: checkBalance(user); break;
            case 5: cout << "Thank you for banking with GCC Bank. Goodbye!" << endl; break;
            default: cout << "Invalid choice. Please enter a number from 1 to 5." << endl;
        }
    }

    return 0;
}
