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
        cout << "9. Transfer money" << endl;
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
            case 9: {
                int senders_account, receiver_account, amount;
                cout << "Enter sender's account number: " << endl;
                cin >> senders_account;
                cout << "Enter receiver's account number: " << endl;
                cin >> receiver_account;
                cout << "Enter amount to transfer: " << endl;
                cin >> amount;
                int remaining_money = transfer_money(senders_account, receiver_account, amount);
                cout << "Successfully transfered money to " << receiver_account << endl;
                cout << "Your remaining balance is " << remaining_money << endl;
            }
                break;
            default:
                cout << "Invalid choice" << endl;
                break;
        }
    } while (choice == 1);
    return 0;
}


