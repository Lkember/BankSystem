//
//  Class.hpp
//  Assignment 1
//
//  Created by Logan Kember on 2015-09-24.
//  Copyright © 2015 Logan Kember. All rights reserved.
//

#ifndef account_hpp
#define account_hpp
#include<cmath>
#include<math.h>
#include<iostream>
#include<stdio.h>
#include<iomanip>
using namespace std;

class account {
private:
    int accountNum;                         //Account number
    double balance=0;                       //Balance of the account
    
public:
    int accountType=-1;                     //Account type (-1 uninitialized, 0 chequings, 1 savings)
    int activated;                          //0 = not activated, 1 = activated
    void activate();                        //Method to activate an account
    bool deactivate();                      //Method to deactivate an account
    void createAccount();                   //Method to get data from user
    void showAccount();                     //Method to show account information for user
    void modify();                          //Method to modify the user information data
    void deposit(double);                   //Method to deposit money into an account
    bool withdraw(int);                     //Method to withdraw money from an account
    int getAccountNumber() const;           //Method to return account number
    double getAccountBalance();             //Method to return account balance
    int getAccountType() const;             //Method which returns account type
    bool isActive();                        //Method which tells whether the account is active or not
};



void account::showAccount() {
    if (activated==1) {
        cout<<"\nAccount Number: "<<accountNum;
        cout<<"\nAccount Type: ";
        if (accountType==0)
            cout<<"Chequing";
        else
            cout<<"Savings";
        cout<<"\nAccount Balance: "<<fixed<<setprecision(2)<<balance<<"\n";
    }
}

void account::modify() {
    int option;
    cout<<"What information would you like to change?";
    cout<<"1. Name";
    cin>>option;
}

void account::deposit(double x) {
    if (isActive()) {
        
        balance += x;
        cout<<"\n\nYour new balance is $"<<fixed<<setprecision(2)<<balance<<"\n";
        sleep(1.5);
    }
    else {
        cout<<"\nThis account isn't activated yet.\n";
    }
}







bool account::withdraw(int x) {
    
    //If the account is a savings account
    if (accountType==1) {
        
        //If there is no money in the account, then let the user know there is no money.
        if (balance==0) {
            cout<<"\n\nNo funds available.\n\n";
            return false;
        }

        //Otherwise, continue with the transaction
        while (true) {
            if (x==0) { //If the user enters 0, then exit.
                return false;
            }
            
            if (x <= balance) {    //If there are enough funds, then withdraw the money
                balance -= x;
                cout<<"\n\nYour new balance is $"<<fixed<<setprecision(2)<<balance;
                return true;        //Return true
            
            }
            else {      //Otherwise, let the user know there is insufficient funds.
                cout<<"\nError. Insufficient funds.\n";
                cout<<"\nYou have $"<<fixed<<setprecision(2)<<balance<<" available to withdraw.\n";
                sleep(1.5);
                cout<<"\nEnter the amount you would like to withdraw, or 0 to exit.\n\n~:";
                cin>>x;
            }
        }
    }
    
    
    //If the account is a chequings
    else {
        //If there is no money in the account, then let the user know there is no money.
        if (balance==0) {
            cout<<"\n\nNo funds available.\n\n";
            return false;       //And return
        }
        
        //Otherwise, continue with the transaction
        while (true) {  //<--Used if the user inputs an amount not in his/her account.
            if (x==0) {             //If the user entered 0, then exit
                return false;
            }
            
            if (x <= balance) {     //If the user entered a valid number
                
                //If the balance after the withdraw is above $1000 then withdraw the amount.
                if ((balance-x)>=1000.00) {
                    balance -= x;
                    cout<<"\n\nYour new balance is $"<<fixed<<setprecision(2)<<balance<<"\n";
                    return true;        //And return
                }
                
                //Otherwise let the user know, that they have insufficient funds or their account will go below the threshold.
                else {
                    char input;
                    cout<<"\n\nIf you withdraw $"<<fixed<<setprecision(2)<<x<<", then your account will go below $1000 and you will be charged $2.00.";
                    sleep(1.5);
                    cout<<"\nWould you like to continue with the transaction?\n1. Yes\n2.No\n\n~:";
                    
                    while (true) {
                        cin>>input;
                        
                        switch (input) {
                            case '1': {         //If the user enters 1, then check if there's enough money in the account to take $2.00
                                if ((balance-x) > 2.00) {
                                    balance-=x;     //if so, take the amount the user wanted
                                    balance-=2;     //And take the $2.00 for being below the threshold.
                                    cout<<"\n\nThe amount was withdrawn, and you were charged $2.00.";
                                    sleep(1.5);
                                    cout<<"\n\nYour new balance is $"<<fixed<<setprecision(2)<<balance;
                                    sleep(1.5);
                                    return true;    //Return
                                }
                                
                                else {  //Otherwise we can't take $2.00, so the user can't take out that much money.
                                    cout<<"The maximum you can withdraw is: "<<fixed<<setprecision(2)<<balance-2.00<<"\n";
                                    sleep(1.5);
                                    cout<<"Would you like to take out that amount?\n1. Yes\n2. No, exit\n\n~:";
                                    while (true) {
                                        cin>>input;
                                        
                                        switch (input) {
                                            case '1':   //if the user enters 1, then set there account to 0. (Amount withdrawn + $2.00)
                                                balance=0;
                                                cout<<"\nYour account contains $0.00\n";
                                                sleep(1.5);
                                                return true;    //return
                                                
                                            case '2':
                                                return false;   //then exit
                                                
                                            default:    //Ask user for another input.
                                                cout<<"\nIncorrect input. Try again.\n";
                                        }
                                        
                                    }
                                }
                            }
                                
                            case '2': {
                                return false;   //Then exit
                            }
                                
                            default:    //Ask user for another input.
                                cout<<"\n\nIncorrect input. Try again.\n\n";
                                sleep(1);
                        }
                        
                    }
                    
                }
                
            }
            
            else {  //Otherwise the user doesn't have sufficient funds. Ask for another amount.
                cout<<"\nError. Insufficient funds.\n";
                cout<<"\nYou have $"<<fixed<<setprecision(2)<<balance<<" available, and $"<<fixed<<setprecision(2)<<balance-2.00<<" to withdraw.\n";
                sleep(1.5);
                    //Ask user for another amount.
                cout<<"\nEnter the amount you would like to withdraw, or 0 to exit.\n\n~:";
                cin>>x;
            }
        }
    }
}







int account::getAccountNumber() const {
    return accountNum;
}

double account::getAccountBalance() {
    return balance;
}


bool account::isActive() {
    if (activated==1)
        return true;
    else
        return false;
};

void account::activate() {
    accountNum=rand() % 9000 + 1000;    //Randomly generates an account number, when activated.
    activated=1;                        //Activates the account.
}

//Method to deactivate an account
bool account::deactivate() {
    if (balance == 0) {
        accountNum=0;
        activated=0;
        return true;
    }
    else {
        cout<<"\n\nFailed to deactivate. There is still $"<<fixed<<setprecision(2)<<balance<<" in your ";
        if (this->accountType==1) {
            cout<<"savings account.\n\n";
        }
        else {
            cout<<"chequings account.\n\n";
        }
        return false;
    }
}

#endif /*account_hpp*/