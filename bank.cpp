#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include <iostream>
#include <stack>
#include <math.h>
#include <iomanip>

using namespace std;

class Account {
    public:
        int account_id;
        string account_name;
        string bank_name;
        int account_number;
        string username;
        int balance;
};

bool is_empty_file(std::ifstream& pFile)
{
    return pFile.peek() == std::ifstream::traits_type::eof();
}

int get_latest_id() {
    ifstream account_file("account.txt", ios::in);
    Account account;
    stack<int> accountIds;

    if (is_empty_file(account_file)) {
        return 0;
    }

    while (account_file >> account.account_id >> account.account_name >> account.bank_name >> account.account_number >> account.username >> account.balance) {
        accountIds.push(account.account_id);
    }
    return accountIds.top();
}

bool account_number_exists(int account_number) {
    ifstream accountfile("account.txt", ios::in);
    Account account;
    while (accountfile >> account.account_id >> account.account_name >> account.bank_name >> account.account_number >> account.username >> account.balance) {
        if (account.account_number == account_number) {
            return true;
        }
    }
    return false;
}

int generate_account_number() {
    
    start:
        int number = rand() % 9000000 + 1000000;
    if (account_number_exists(number)) {
        goto start;
    }
    return number;
}

void save_account() {
    Account account;
    ofstream account_file("account.txt", ios::out | ios::app);
    cout << "Enter account name: ";
    cin >> account.account_name;
    cout << "Enter bank name: ";
    cin >> account.bank_name;
    cout << "Enter username: ";
    cin >> account.username;
    account.account_id = get_latest_id() + 1;
    account.account_number = generate_account_number();
    account.balance = 0;
    account_file << account.account_id << " " << account.account_name << " " << account.bank_name << " " << account.account_number << " " << account.username << " " << account.balance << endl;

    cout << "Account created successfully!" << endl;
    cout << "Account ID: " << account.account_id << endl;
    cout << "Account Number: " << account.account_number << endl;
    cout << "Balance: " << account.balance << endl;
    account_file.close();
}

void read_account() {
    ifstream account_file("account.txt", ios::in);
    Account account;
    while (account_file >> account.account_id >> account.account_name >> account.bank_name >> account.account_number >> account.username >> account.balance) {
        cout << account.account_id << " " << account.account_name << " " << account.bank_name << " " << account.account_number << " " << account.username << " " << account.balance << endl;
    }
}


void update_account() {
    ifstream account_file("account.txt", ios::in);
    ofstream temp_file("temp.txt", ios::out | ios::app);

    Account account;

    int account_id;

    cout << "Enter account id: ";
    cin >> account_id;

    int count = 0;

    while(account_file >> account.account_id >> account.account_name >> account.bank_name >> account.account_number >> account.username >> account.balance) {
        if (account.account_id == account_id) {
            cout << "Update account name: ";
            cin >> account.account_name;
            cout << "Update bank name: ";
            cin >> account.bank_name;
            cout << "Update account number: ";
            cin >> account.account_number;
            cout << "Update username: ";
            cin >> account.username;
            temp_file << account.account_id << " " << account.account_name << " " << account.bank_name << " " << account.account_number << " " << account.username << " " << account.balance << endl;
            count ++;
        } else {
            temp_file << account.account_id << " " << account.account_name << " " << account.bank_name << " " << account.account_number << " " << account.username << " " << account.balance << endl;
        }
    }
    if (count == 0) {
        cout << "Sorry, account not found" << endl;
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
    
     while (account_file >> account.account_id >> account.account_name >> account.bank_name >> account.account_number >> account.username >> account.balance) {
        if (account.account_id != account_id) count ++;
        else {
            temp_file << account.account_id << " " << account.account_name << " " << account.bank_name << " " << account.account_number << " " << account.username << " " << account.balance << endl;
        }
     }
    remove("account.txt");
    rename("temp.txt", "account.txt");
    account_file.close();
    temp_file.close();
}

int deposit() {
    int account_number, amount;
    cout << "Enter account number : " << endl;
    cin >> account_number;

    if (!account_number_exists(account_number)) {
        cout << "Sorry, your account is not found" << endl;
        deposit();    
    }

    cout << "Enter amount to deposit : " << endl;
    cin >> amount;

    if (amount>=0) {
        cout << "Amount must be greater than zero" << endl;
        deposit();    
    }

    int total_balance = 0;
    
    ifstream account_file("account.txt", ios::in);
    ofstream temp_file("temp.txt", ios::out | ios::app);

    Account account;

    while (account_file >> account.account_id >> account.account_name >> account.bank_name >> account.account_number >> account.username >> account.balance) {
        if (account.account_number == account_number) {
            total_balance = account.balance += amount;
            temp_file << account.account_id << " " << account.account_name << " " << account.bank_name << " " << account.account_number << " " << account.username << " " << account.balance << endl;
        } else {
            temp_file << account.account_id << " " << account.account_name << " " << account.bank_name << " " << account.account_number << " " << account.username << " " << account.balance << endl;
        }
    }
    remove("account.txt");
    rename("temp.txt", "account.txt");
    account_file.close();
    temp_file.close();
    return total_balance;
}


int withdraw() {
    int account_number, amount;
    cout << "Enter account number : " << endl;
    cin >> account_number;

    if (!account_number_exists(account_number)) {
        cout << "Sorry, your account is not found" << endl;
        withdraw();    
    }

    cout << "Enter amount to withdraw : " << endl;
    cin >> amount;

    if (amount>=0) {
        cout << "Amount must be greater than zero" << endl;
        withdraw();    
    } else if( amount > 200000 ) {
    	cout<<"Sorry, You are not allowed to withdraw this amount at once!"<<endl;
    	withdraw();
    }


    int total_balance = 0;
    
    ifstream account_file("account.txt", ios::in);
    ofstream temp_file("temp.txt", ios::out | ios::app);

    Account account;

    while (account_file >> account.account_id >> account.account_name >> account.bank_name >> account.account_number >> account.username >> account.balance) {
        if (account.account_number == account_number) {
            total_balance = account.balance -= amount;
            temp_file << account.account_id << " " << account.account_name << " " << account.bank_name << " " << account.account_number << " " << account.username << " " << account.balance << endl;
        } else {
            temp_file << account.account_id << " " << account.account_name << " " << account.bank_name << " " << account.account_number << " " << account.username << " " << account.balance << endl;
        }
    }
    remove("account.txt");
    rename("temp.txt", "account.txt");
    account_file.close();
    temp_file.close();

    if( amount > 10000  && amount < 50000 ) total_balance -= total_balance * 0.02;
    else if( amount <= 100000 ) total_balance -= total_balance * 0.03;

    return total_balance;
}

void display() {
    ifstream account_file("account.txt", ios::in);
    Account account;

    cout << "Account ID" << setw(5) << " " << "Account Name" << setw(5) << " " << "Bank Name" << setw(5) << " " << "Account Number" << setw(5) << " "  << "Username" << setw(5) << " " << "Balance" << endl;



    while (account_file >> account.account_id >> account.account_name >> account.bank_name >> account.account_number >> account.username >> account.balance) {
        cout << account.account_id << setw(15) << " " << account.account_name << setw(15) << " " << account.bank_name << setw(10) << " " << account.account_number << setw(10) << " " << account.username << setw(10) << " " << account.balance << endl;
    }

    while (account_file >> account.account_id >> account.account_name >> account.bank_name >> account.account_number >> account.username >> account.balance) {
        cout << account.account_id << endl;
        cout << account.account_name << endl;
        cout << account.bank_name << endl;
        cout << account.account_number << endl;
        cout << account.username << endl;
        cout << account.balance << endl;
    }
    account_file.close();
}

int send_money() {
    int account_number, amount, account_number_receiver; 

    cout << "Enter account number : " << endl;
    cin >> account_number;

    if (!account_number_exists(account_number)) {
        cout << "Sorry, your account is not found" << endl;
        send_money();    
    }

    cout << "Enter account number receiver : " << endl;
    cin >> account_number_receiver;

    if (!account_number_exists(account_number_receiver)) {
        cout << "Sorry, your account is not found" << endl;
        send_money();    
    }
    

    cout << "Enter amount to send : " << endl;
    cin >> amount;

    if (amount>=0) {
        cout << "Amount must be greater than zero" << endl;
        send_money();    
    }

    int total_balance = 0;
    
    ifstream account_file("account.txt", ios::in);
    ofstream temp_file("temp.txt", ios::out | ios::app);

    Account account;
    while (account_file >> account.account_id >> account.account_name >> account.bank_name >> account.account_number >> account.username >> account.balance) {
        if (account.account_number == account_number_receiver) {
            total_balance = account.balance += amount;
            
            temp_file << account.account_id << " " << account.account_name << " " << account.bank_name << " " << account.account_number << " " << account.username << " " << account.balance << endl;
        } else {
            temp_file << account.account_id << " " << account.account_name << " " << account.bank_name << " " << account.account_number << " " << account.username << " " << account.balance << endl;
        }
    }


    remove("account.txt");
    rename("temp.txt", "account.txt");
    account_file.close();
    temp_file.close();
    return total_balance;
}

int main () {
    int choice;
    do {
        cout << "1. Save account" << endl;
        cout << "2. Read account" << endl;
        cout << "3. Update account" << endl;
        cout << "4. Delete account" << endl;
        cout << "5. Exit" << endl;
        cout << "6. Deposit" << endl;
        cout << "7. Withdraw" << endl;
        cout << "8. Display" << endl;
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
            case 5:
                return 0;
                break;
            case 6: {
                int total_balance = deposit();
                cout << "Total balance: " << total_balance << endl;
                break;
            }
            case 7: {
                int total_balance = withdraw();
                cout << "Total balance: " << total_balance << endl;
                break;
            }
            case 8: 
                display();
                break;
            default:
                cout << "Invalid choice" << endl;
                break;
        }
    } while (choice == 1);
    return 0;
}


