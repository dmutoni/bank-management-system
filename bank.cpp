#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include <iostream>

using namespace std;

class Account {
    public:
        int account_id;
        string account_name;
        string bank_name;
        int account_number;
        string username;
};

class Deposit{
    public:
        int deposit_id;
        int account_number;
        float amount;

};

void save_account() {
    ofstream account_file("account.txt", ios::out | ios::app);
    Account account;
    cout << "Enter account id: ";
    cin >> account.account_id;
    cout << "Enter account name: ";
    cin >> account.account_name;
    cout << "Enter bank name: ";
    cin >> account.bank_name;
    cout << "Enter account number: ";
    cin >> account.account_number;
    cout << "Enter username: ";
    cin >> account.username;
    account_file << account.account_id << " " << account.account_name << " " << account.bank_name << " " << account.account_number << " " << account.username << endl;
    account_file.close();
}
void read_account() {
    ifstream account_file("account.txt", ios::in);
    Account account;
    while (account_file >> account.account_id >> account.account_name >> account.bank_name >> account.account_number >> account.username) {
        cout << account.account_id << " " << account.account_name << " " << account.bank_name << " " << account.account_number << " " << account.username << endl;
    }
}

void update_account() {
    ifstream account_file("account.txt", ios::in);
    ofstream temp_file("temp.txt", ios::out | ios::app);

    Account account;

    int account_id;
    cout << "Enter account id: ";

    cin >> account_id;

    while(account_file >> account.account_id >> account.account_name >> account.bank_name >> account.account_number >> account.username) {
        if (account.account_id == account.account_id) {
            cout << "Update account name: ";
            cin >> account.account_name;
            cout << "Update bank name: ";
            cin >> account.bank_name;
            cout << "Update account number: ";
            cin >> account.account_number;
            cout << "Update username: ";
            cin >> account.username;
            temp_file << account.account_id << " " << account.account_name << " " << account.bank_name << " " << account.account_number << " " << account.username << endl;
        } else {
            temp_file << account.account_id << " " << account.account_name << " " << account.bank_name << " " << account.account_number << " " << account.username << endl;
        }
    }
    remove("account.txt");
    rename("temp.txt", "account.txt");

    account_file.close();
    temp_file.close();
}

void delete_account() {
    ifstream account_file("account.txt", ios::in);
    ofstream temp_file("temp.txt", ios::out | ios::app);

    Account account;

    int account_id;
    cout << "Enter account id: ";

    cin >> account_id;
    int count = 0;
    
     while (account_file >> account.account_id >> account.account_name >> account.bank_name >> account.account_number >> account.username) {
        if (account.account_id != account_id) count ++;
        else {
            temp_file << account.account_id << " " << account.account_name << " " << account.bank_name << " " << account.account_number << " " << account.username << endl;
        }
     }
    remove("account.txt");
    rename("temp.txt", "account.txt");
    account_file.close();
    temp_file.close();
}

int main () {
    int choice;
    do {
        cout << "1. Save account" << endl;
        cout << "2. Read account" << endl;
        cout << "3. Update account" << endl;
        cout << "4. Delete account" << endl;
        cin >> choice;
        switch (choice) {
            case 1:
                save_account();
                break;
            case 2:
                read_account();
                break;
            case 3:
                update_account();
                break;
            case 4:     
                delete_account();
                break;
            default:
                cout << "Invalid choice" << endl;
                break;
        }
    } while (choice == 1);
    return 0;
}


