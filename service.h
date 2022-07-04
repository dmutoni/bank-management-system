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

int increase_balance (int account_number, int amount) {
    ofstream temp_file("temp.txt", ios::out | ios::app);
    ifstream account_file("account.txt", ios::in);
    Account account;

    int total_balance;

    while(account_file >> account.account_id >> account.account_name >> account.bank_name >> account.account_number >> account.username >> account.balance) {
        if (account.account_number == account_number) {
            total_balance = account.balance += amount;
        }
        temp_file << account.account_id << " " << account.account_name << " " << account.bank_name << " " << account.account_number << " " << account.username << " " << account.balance << endl;
    }
    remove("account.txt");
    rename("temp.txt", "account.txt");
    account_file.close();
    temp_file.close();
    return total_balance;
}

int decrease_balance (int account_number, int amount) {
    ofstream temp_file("temp.txt", ios::out | ios::app);
    ifstream account_file("account.txt", ios::in);
    Account account;

    int total_balance;

    while(account_file >> account.account_id >> account.account_name >> account.bank_name >> account.account_number >> account.username >> account.balance) {
        if (account.account_number == account_number) {
            total_balance = account.balance -= amount;
        }
        temp_file << account.account_id << " " << account.account_name << " " << account.bank_name << " " << account.account_number << " " << account.username << " " << account.balance << endl;
    }
    remove("account.txt");
    rename("temp.txt", "account.txt");
    account_file.close();
    temp_file.close();
    return total_balance;
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

    if (amount <= 0) {
        cout << "Amount must be greater than zero" << endl;
        deposit();    
    }
  
    return increase_balance(account_number, amount);
}

bool isAmountAvailable(int account_number, int amount) {
    ofstream temp_file("temp.txt", ios::out | ios::app);
    ifstream account_file("account.txt", ios::in);
    Account account;
    while (account_file >> account.account_id >> account.bank_name >> account.account_name >> account.username >> account.balance) {
        if (account.account_number == account_number && account.balance >= amount) {
            return true;
        } 
    }
    temp_file.close();
    account_file.close();
    return false;
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

    if (amount <= 0) {
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
            account.balance -= amount;
            if( amount > 10000  && amount < 50000 ) account.balance -= amount * 0.02;
            else if( amount <= 100000 ) account.balance -= amount * 0.03;
            total_balance = account.balance;
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

int transfer_money(int senders_account, int receiver_account, int amount) {
  // check if the sender's account number and receivers account number exists
  // if yes, check if the sender's account has that money
  // if yes, deposit on the receiver's account
    // if no, return -1
    if (!account_number_exists(senders_account)) {
        cout << "Sorry, this account does not exist";
        transfer_money(senders_account, receiver_account, amount);
    }
    if (!account_number_exists(receiver_account)) {
        cout << "Sorry, this account does not exist";
        transfer_money(senders_account, receiver_account, amount);
    }
    if(!isAmountAvailable(senders_account, amount)) {
        cout << "Sorry, this account does not exist";
        transfer_money(senders_account, receiver_account, amount);
    }
    int remaining_balance = decrease_balance(senders_account, amount);
    increase_balance(receiver_account, amount);
    return remaining_balance;
}






