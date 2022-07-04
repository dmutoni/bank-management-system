#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include <iostream>
#include <stack>
#include <math.h>
#include <iomanip>
#include "./service.h"

using namespace std;

int main()
{
    int choice;
    do
    {
        cout << "1. Save account" << endl;
        cout << "2. Read account" << endl;
        cout << "3. Update account" << endl;
        cout << "4. Delete account" << endl;
        cout << "5. Exit" << endl;
        cout << "6. Deposit" << endl;
        cout << "7. Withdraw" << endl;
        cout << "8. Display" << endl;
        cout << "9. Transfer money" << endl;
        cout << "10. Sort money" << endl;

        cin >> choice;
        switch (choice)
        {
        case 1:
            save_account();
            break;
        case 2:
        {
            vector<Account> accounts = get_all_accounts();
            print_accounts(accounts);
        }
        break;
        case 3:
        {
            int account_number;
        account:
            cout << "Enter account number : ";
            cin >> account_number;
            if (!account_number_exists(account_number))
                goto account;
            update_account(account_number);
        }
        break;
        case 4:
        {
            int account_number;
        update_account:
            cout << "Enter account number : ";
            cin >> account_number;
            if (!account_number_exists(account_number))
                goto update_account;
            delete_account(account_number);
        }
        break;
        case 5:
            return 0;
            break;
        case 6:
        {
            int total_balance = deposit();
            cout << "Your new balance: " << total_balance << endl;
            break;
        }
        case 7:
        {
            int total_balance = withdraw();
            cout << "Your new balance: " << total_balance << endl;
            break;
        }
        case 8:
            display();
            break;
        case 9:
        {
            int senders_account, receiver_account, amount;
        sender:
            cout << "Enter sender's account number: " << endl;
            cin >> senders_account;
            if (!account_number_exists(senders_account))
            {
                cout << "Sorry, this sender's account does not exist";
                goto sender;
            }
        receiver:
            cout << "Enter receiver's account number: " << endl;
            cin >> receiver_account;
            if (!account_number_exists(receiver_account))
            {
                cout << "Sorry, this receiver's account does not exist" << endl;
                goto receiver;
            }
        amount:
            cout << "Enter amount to transfer: " << endl;
            cin >> amount;
            if (!isAmountAvailable(senders_account, amount))
            {
                cout << "Sorry, this amount is not available on your account" << endl;
                goto amount;
            }
            int remaining_money = transfer_money(senders_account, receiver_account, amount);
            cout << "Successfully transfered money to " << receiver_account << endl;
            cout << "Your remaining balance is " << remaining_money << endl;
        }
        break;
        case 10:
            sorting_accounts_by_input();
            break;
        default:
            cout << "Invalid choice" << endl;
            break;
        }
    } while (choice == 1);
    return 0;
}
