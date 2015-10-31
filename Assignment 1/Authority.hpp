//
//  Authority.hpp
//  Assignment 1
//
//  Created by Logan Kember on 2015-09-24.
//  Copyright © 2015 Logan Kember. All rights reserved.
//

#ifndef Authority_hpp
#define Authority_hpp
#include <string>
#include "account.hpp"
//////////////////////////////////////////////////////////
////////                CLASS                  ///////////
//////////////////////////////////////////////////////////
class person {
private:
    int login;
    int password;
    
public:
    bool changePassword();              //A method to change the password
    account chequing;                   //One Chequing account and one Savings account per person
    account savings;
    person(string, string, int, int, int);    ///////////CONSTRUCTOR/////////
    string firstName;                   //Customers first name
    string lastName;                    //Customers last name
    int getAuthority();
    bool checkPassword(int);
    person();
    bool deleteAccount();
    int authorityType=-1;               //0=client, 1=manager, 2=maintenance. It is set to -1 for checking an accounts validity in BankSystem.hpp
    int getLogin();
};


//////////////////////////////////////////////////////////
////////             CONSTRUCTORS                /////////
//////////////////////////////////////////////////////////

person::person(string fName, string lName, int login, int password, int authority) {
    this->firstName=fName;
    this->lastName=lName;
    this->login=login;
    this->password=password;
    this->authorityType=authority;
}

person::person() {
    authorityType=-1;
};



//////////////////////////////////////////////////////////
////////                 METHODS                 /////////
//////////////////////////////////////////////////////////


int person::getAuthority() {
    return authorityType;
};

bool person::checkPassword(int i) {
    if (i == this->password) {
        return true;
    }
    else
        return false;
};


bool person::changePassword() {
    int checkPassword;
    int newPassword;
    bool check = false;
    
    while (check) {
        cout<<"\n\nEnter your current password or 0 to exit: ";
        cin >> checkPassword;
        if (checkPassword==0) {
            return false;
        }
        if (checkPassword==this->password) {
            cout<<"\nEnter your new password: ";
            cin>>newPassword;
            cout<<"\nEnter your new password again: ";
            cin>>checkPassword;
            if (newPassword == checkPassword) {
                this->password=newPassword;
                check = true;
            }
        }
        else {
            cout<<"\nIncorrect Password. Try again.";
        }
    }
    return check;
};

int person::getLogin() {
    return this->login;
};

bool person::deleteAccount() {
    if (this->chequing.deactivate()&&this->savings.deactivate()) {
        this->authorityType=-1;
        return true;
    }
    return false;
}


#endif /* Authority_hpp */
