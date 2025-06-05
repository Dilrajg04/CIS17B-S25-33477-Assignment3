//
//  main.cpp
//  Assignment3
//
//  Created by Dilraj Grewal on 3/24/25.
//

#include <iostream>
#include <memory>
#include <stdexcept>

using namespace std;

// TODO: Define custom exception classes here
// - NegativeDepositException (for negative deposit attempts)
class NegativeDepositException : public runtime_error{
public:
    NegativeDepositException() : runtime_error("Error can't deposit a negative amount!"){}
};
// - OverdrawException (for withdrawing more than the balance)
class OverdrawException : public runtime_error {
public:
    OverdrawException() : runtime_error("Insufficient funds !") {}
};
// - InvalidAccountOperationException (for transactions on a closed account)
class InvalidAccountOperationException : public runtime_error{
public:
    InvalidAccountOperationException() : runtime_error("This account is closed!"){}

};

class BankAccount {
private:
    std::string accountNumber;
    double balance;
    bool isActive;

public:
    // Constructor to initialize account number, balance, and active status
    BankAccount(std::string accNum, double initialBalance) : accountNumber(accNum), balance(initialBalance), isActive(true) {}

    // Deposit method
    void deposit(double amount) {
        if(!isActive){
            throw InvalidAccountOperationException();
        }
        if(amount < 0) {
            throw NegativeDepositException();
        }
        balance += amount;
    }

    // Withdraw method
    void withdraw(double amount) {
        // TODO: Implement exception handling for overdrawing and closed accounts
        if (!isActive) {
            throw InvalidAccountOperationException();
        }
        if (amount > balance) {
            throw OverdrawException();
        }
        balance -= amount;
    }

    // Method to get current balance
    double getBalance() const {
        return balance;
    }

    // Method to close the account
    void closeAccount() {
        // TODO: Prevent further transactions when the account is closed
        isActive = false;
    }
    
};

void displayMenu(){
     cout << endl;
     cout << "Choose the following options: " << endl;
     cout << "1.Deposit money\n";
     cout << "2.Withdraw money\n";
     cout << "3.Check balance\n";
     cout << "4.Close account\n";
     cout << "5.Exit";
    cout << endl;
     cout << "Enter your choice: ";
}

int main() {
    double initialBalance;
    try {
        // TODO: Ask the user to enter an initial balance and create a BankAccount object using smart pointers
            cout << "Enter initial balance: ";
            cin >> initialBalance;
            auto account = std::make_unique<BankAccount>("123456", initialBalance);
        
        std::cout << "Bank Account Created: #" << "123456" << std::endl;

        while(true){
            displayMenu();
            int input;
            cin >> input;
            
            switch (input) {
                case 1:
                    //deposit money and return account balance
                    double damount;
                    cout << "\nEnter the deposit amount: ";
                    cin >> damount;
                    account -> deposit(damount);
                    cout << "Deposit Successful!" << endl;
                    cout << "Balance : " << account->getBalance() << endl;
                    break;
                
                case 2:
                    //withdraw money and return account balance
                    double wamount;
                    cout << "\nEnter the withdrawl amount: ";
                    cin >> wamount;
                    account -> withdraw(wamount);
                    cout << "Withdrawl Successful!" << endl;
                    cout << "Balance : " << account->getBalance() << endl;
                    break;
                    
                case 3:
                    //check account balance
                    cout << "\nCurrent Balance: " << account->getBalance() << endl;
                    break;
                
                case 4:
                    //confirms if users wants to close account or not.
                    int choice;
                    do {
                        cout << "Are you sure you want to close the account?" << endl;
                        cout << "1. Yes" << endl;
                        cout << "2. No" << endl;
                        cout << "Enter your choice: ";
                        cin >> choice;
                        //basic if else statements.
                        if (choice == 1) {
                            account->closeAccount();
                            cout << "Your account has been closed. Sorry to see you go :(" << endl;
                        } else if (choice == 2) {
                            cout << "Account closure canceled." << endl;
                        } else {
                            cout << "Invalid choice. Please enter 1 for Yes or 2 for No." << endl;
                        }
                    } while (choice != 1 && choice != 2);
                    break;
                
                case 5:
                    //quits the program
                    cout << "Thank you for banking with us\n" << endl;
                    break;
                    
                default:
                    break;
            }
            
        }
 
    }
    catch (const std::exception& e) {
        // TODO: Catch and handle exceptions properly
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
