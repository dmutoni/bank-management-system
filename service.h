#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include <iostream>
#include <stack>
#include <math.h>
#include <iomanip>
#include <vector>
#include <sstream>

using namespace std;

class Account
{
public:
    int account_id;
    string account_name;
    string bank_name;
    int account_number;
    string username;
    int balance;
};

bool is_empty_file(std::ifstream &pFile)
{
    return pFile.peek() == std::ifstream::traits_type::eof();
}

vector<Account> get_all_accounts()
{
    ifstream file("account.txt", ios::in);
    vector<Account> accounts;
    string line;
    while (getline(file, line))
    {
        stringstream ss(line);
        vector<string> fields;
        string field;
        while (getline(ss, field, ','))
        {
            fields.push_back(field);
        }
        Account account;
        account.account_id = stoi(fields[0]);
        account.account_name = fields[1];
        account.bank_name = fields[2];
        account.account_number = stoi(fields[3]);
        account.username = fields[4];
        account.balance = stoi(fields[5]);
        accounts.push_back(account);
    }
    file.close();
    return accounts;
}

int get_latest_id()
{
    vector<Account> accounts = get_all_accounts();
    return accounts.back().account_id;
}

bool account_number_exists(int account_number)
{
    vector<Account> accounts = get_all_accounts();
    for (int i = 0; i < accounts.size(); i++)
    {
        if (accounts[i].account_number == account_number)
        {
            return true;
        }
    }
    return false;
}

int generate_account_number()
{

start:
    int number = rand() % 9000000 + 1000000;
    if (account_number_exists(number))
    {
        goto start;
    }
    return number;
}

void save_account()
{
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
    account_file << account.account_id << "," << account.account_name << "," << account.bank_name << "," << account.account_number << "," << account.username << "," << account.balance << endl;

    cout << "Account created successfully!" << endl;
    cout << "Account ID: " << account.account_id << endl;
    cout << "Account Number: " << account.account_number << endl;
    cout << "Balance: " << account.balance << endl;
    account_file.close();
}

void print_accounts(vector<Account> accounts)
{
    for (int i = 0; i < accounts.size(); i++)
    {
        cout << accounts[i].account_id << " " << accounts[i].account_name << " " << accounts[i].bank_name << " " << accounts[i].account_number << " " << accounts[i].username << " " << accounts[i].balance << endl;
    }
}

void update_to_file_from_vector(vector<Account> accounts)
{
    ofstream temp_file("temp.txt", ios::out | ios::app);

    for (int i = 0; i < accounts.size(); i++)
    {
        Account account = accounts[i];
        temp_file << account.account_id << "," << account.account_name << "," << account.bank_name << "," << account.account_number << "," << account.username << "," << account.balance << endl;
    }
    remove("account.txt");
    rename("temp.txt", "account.txt");
    temp_file.close();
}

void update_account(int account_number)
{
    vector<Account> accounts = get_all_accounts();

    for (int i = 0; i < accounts.size(); i++)
    {
        Account account = accounts[i];
        if (account.account_number == account_number)
        {
            cout << "Enter updated account name: ";
            cin >> accounts[i].account_name;
            cout << "Enter updated bank name: ";
            cin >> accounts[i].bank_name;
            cout << "Enter updated account number: ";
            cin >> accounts[i].username;
        }
    }
    update_to_file_from_vector(accounts);
}

void delete_account(int account_number)
{
    vector<Account> accounts = get_all_accounts();

    for (int i = 0; i < accounts.size(); i++)
    {
        Account account = accounts[i];
        if (account.account_number == account_number)
        {
            accounts.erase(accounts.begin() + i);
        }
    }
    update_to_file_from_vector(accounts);
}

int increase_balance(int account_number, int amount)
{
    ofstream temp_file("temp.txt", ios::out | ios::app);
    ifstream account_file("account.txt", ios::in);
    Account account;

    int total_balance;

    while (account_file >> account.account_id >> account.account_name >> account.bank_name >> account.account_number >> account.username >> account.balance)
    {
        if (account.account_number == account_number)
        {
            total_balance = account.balance += amount;
        }
        temp_file << account.account_id << "," << account.account_name << "," << account.bank_name << "," << account.account_number << "," << account.username << "," << account.balance << endl;
    }
    remove("account.txt");
    rename("temp.txt", "account.txt");
    account_file.close();
    temp_file.close();
    return total_balance;
}

int decrease_balance(int account_number, int amount)
{
    ofstream temp_file("temp.txt", ios::out | ios::app);
    ifstream account_file("account.txt", ios::in);
    Account account;

    int total_balance;

    while (account_file >> account.account_id >> account.account_name >> account.bank_name >> account.account_number >> account.username >> account.balance)
    {
        if (account.account_number == account_number)
        {
            total_balance = account.balance -= amount;
        }
        temp_file << account.account_id << "," << account.account_name << "," << account.bank_name << "," << account.account_number << "," << account.username << "," << account.balance << endl;
    }
    remove("account.txt");
    rename("temp.txt", "account.txt");
    account_file.close();
    temp_file.close();
    return total_balance;
}

int deposit()
{
    int account_number, amount;
    cout << "Enter account number : " << endl;
    cin >> account_number;

    if (!account_number_exists(account_number))
    {
        cout << "Sorry, your account is not found" << endl;
        deposit();
    }

    cout << "Enter amount to deposit : " << endl;
    cin >> amount;

    if (amount <= 0)
    {
        cout << "Amount must be greater than zero" << endl;
        deposit();
    }

    return increase_balance(account_number, amount);
}

bool isAmountAvailable(int account_number, int amount)
{
    ifstream account_file("account.txt", ios::in);
    Account account;
    while (account_file >> account.account_id >> account.account_name >> account.bank_name >> account.account_number >> account.username >> account.balance)
    {
        if (account.account_number == account_number)
        {
            if (account.balance >= amount)
            {
                return true;
            }
        }
    }
    account_file.close();
    return false;
}

int withdraw()
{
    int account_number, amount;
    cout << "Enter account number : " << endl;
    cin >> account_number;

    if (!account_number_exists(account_number))
    {
        cout << "Sorry, your account is not found" << endl;
        withdraw();
    }

    cout << "Enter amount to withdraw : " << endl;
    cin >> amount;

    if (amount <= 0)
    {
        cout << "Amount must be greater than zero" << endl;
        withdraw();
    }
    else if (amount > 200000)
    {
        cout << "Sorry, You are not allowed to withdraw this amount at once!" << endl;
        withdraw();
    }

    int total_balance = 0;

    ifstream account_file("account.txt", ios::in);
    ofstream temp_file("temp.txt", ios::out | ios::app);

    Account account;

    while (account_file >> account.account_id >> account.account_name >> account.bank_name >> account.account_number >> account.username >> account.balance)
    {
        if (account.account_number == account_number)
        {
            account.balance -= amount;
            if (amount > 10000 && amount < 50000)
                account.balance -= amount * 0.02;
            else if (amount <= 100000)
                account.balance -= amount * 0.03;
            total_balance = account.balance;
            temp_file << account.account_id << "," << account.account_name << "," << account.bank_name << "," << account.account_number << "," << account.username << "," << account.balance << endl;
        }
        else
        {
            temp_file << account.account_id << "," << account.account_name << "," << account.bank_name << "," << account.account_number << "," << account.username << "," << account.balance << endl;
        }
    }
    remove("account.txt");
    rename("temp.txt", "account.txt");
    account_file.close();
    temp_file.close();

    return total_balance;
}

void display()
{
    ifstream account_file("account.txt", ios::in);
    Account account;

    cout << "Account ID" << setw(5) << ","
         << "Account Name" << setw(5) << ","
         << "Bank Name" << setw(5) << ","
         << "Account Number" << setw(5) << ","
         << "Username" << setw(5) << ","
         << "Balance" << endl;

    while (account_file >> account.account_id >> account.account_name >> account.bank_name >> account.account_number >> account.username >> account.balance)
    {
        cout << account.account_id << setw(15) << "," << account.account_name << setw(15) << "," << account.bank_name << setw(10) << "," << account.account_number << setw(10) << "," << account.username << setw(10) << "," << account.balance << endl;
    }

    while (account_file >> account.account_id >> account.account_name >> account.bank_name >> account.account_number >> account.username >> account.balance)
    {
        cout << account.account_id << endl;
        cout << account.account_name << endl;
        cout << account.bank_name << endl;
        cout << account.account_number << endl;
        cout << account.username << endl;
        cout << account.balance << endl;
    }
    account_file.close();
}

int transfer_money(int senders_account, int receiver_account, int amount)
{
    int remaining_balance = decrease_balance(senders_account, amount);
    increase_balance(receiver_account, amount);
    return remaining_balance;
}

void sort_by_input(int balance)
{
    // read in file
    // as you read push account objects to a vector
    // perform bubble sort
}
