
//  BankSystem.hpp
//  Assignment 1
//
//  Created by Logan Kember on 2015-09-24.
//  Copyright © 2015 Logan Kember. All rights reserved.

#ifndef BankSystem_hpp
#define BankSystem_hpp

//////////////////////////////////////////////////////
////////////////       CLASS       ///////////////////
//////////////////////////////////////////////////////

class BankSystem {
private:
//    int index=0;                    //Index, which keeps track of where the next account should be added.
    int findAccount(int);
    void summary();
    
public:
    person bankArray[20];           //Maximum 20 people on the bank system
    
    //////////METHODS////////
    void startup();
    void createAccount(int);
    void login();
    void managerMenu(int);
    void clientMenu(int);
    void maintenanceMenu(int);
    void makeChanges(person);
    bool isAccount(int);
    void initialize(string, string, int, int, int, string, string, int, int, int);              //Adds 1 manager account and 1 client account
};


//////////////////////////////////////////////////////
/////////             METHODS              ///////////
//////////////////////////////////////////////////////

void BankSystem::initialize(string fName, string lName, int login, int accPass, int accType,
                            string fName2, string lName2, int login2, int accPass2, int accType2) {
    
    for (int i=0; i<20; i++) {
        bankArray[i].authorityType=-1;          //Setting authority type to -1, to show it's not active
        bankArray[i].savings.activated=0;       //Deactivating each account
        bankArray[i].chequing.activated=0;
    }
    
    bankArray[0] = person(fName, lName, login, accPass, accType);
    bankArray[1] = person(fName2, lName2, login2, accPass2, accType2);
    bankArray[0].savings.activated=0;
    bankArray[0].chequing.activated=0;
    bankArray[1].savings.activated=0;
    bankArray[2].chequing.activated=0;
};


void BankSystem::startup() {
    char option;
    cout<<"\t\tWELCOME TO \n\tLOGAN'S BANK OF\n\t\t CANADA.\n\n\n1. Login\n\n2. Exit";
    while (true) {
        cout<<"\n\n~:";
        cin>>option;
        switch (option) {
            case '1':
                login();
                return;
            
            case '2':
                cout<<"Thanks for using LBC.\n";
                return;
                
            default:
                cout<<"\n\nInvalid input. Try again...";
        }
    }
    return;
};

/*Method to login to the bank system*/
void BankSystem::login() {
    int accNum;
    int accPwd;
    int currentUser;
    
    
    cout<<"\n\nEnter your account number: ";
    
    while (true) {
        cin>>accNum;
        
        if (isAccount(accNum)) {
            break;
        }
        else {
            cout<<"Couldn't find your account.\n\n";
            sleep(1.5);
            startup();
        }
        
    }
    
    currentUser=findAccount(accNum);
    
    
    if (bankArray[currentUser].getAuthority()!=-1) {
        cout<<"Enter your password: ";
        while (!(cin>>accPwd)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            cout<<"Invalid input. Try again.\n\n~:";
        }
        if (bankArray[currentUser].checkPassword(accPwd)) {
            cout<<"\nYou have successfully signed in.\n\n\nWelcome, to LBC's Banking System.\n\n\n";
            if (bankArray[currentUser].getAuthority()==1)
                managerMenu(currentUser);
            else
                clientMenu(currentUser);
        }
        else {
            cout<<"You entered an incorrect password. Please, enter your password: ";
            cin>>accPwd;
            if (bankArray[currentUser].checkPassword(accPwd)) {
                cout<<"\n\nYou have successfully signed in.\nWelcome to LBC's Banking System.";
                if (bankArray[currentUser].getAuthority()==1) {
                    managerMenu(currentUser);
                }
                else {
                    clientMenu(currentUser);
                }
            }
            else {
                cout<<"Failed to login to account.";
                login();
            }
        }
    }
    else {
        cout<<"We couldn't find your account. Check your account number and try again.\n\n";
        login();
    }
    
};



/*Once logged into the banking system, the main menu method is used to display options to the user*/
void BankSystem::managerMenu(int user) {
    char input;
    cout<<"\nMAIN MENU";
    
    cout<<"\n\n1. Add a new client";
    cout<<"\n\n2. Add Account to Client";
    cout<<"\n\n3. Deposit";
    cout<<"\n\n4. Withdraw";
    cout<<"\n\n5. Make a Direct Payment";
    cout<<"\n\n6. Balance Inquiry";
    cout<<"\n\n7. Modify an Existing Account";
    cout<<"\n\n8. Logout\n\n~:";

    
    while (true) {              //While loop used to check for valid input.
        
        cin>>input;             //Get user input
        
        switch (input) {
                
                
                //Case 1: Add a new client
            case '1': {
                createAccount(user);
                managerMenu(user);
                return;
            }

                
                //Case 2: Add account to a client
            case '2': {
                int acc=-1;
                
                int num;
                cout<<"\n\nEnter the clients login, who you're adding an account to or 0 to exit.\n\n~:";
                
                //While we haven't found an account, continue looping
                while (acc==-1) {
                    cin>>num;
                    
                    if (num==0) {   //If the user entered 0, then return to main menu
                        cout<<"\n\nReturning to Main Menu.\n\n";
                        managerMenu(user);
                        return;
                    }
                    
                    else {         //Otherwise, the user put in a login.
                        acc = findAccount(num);   //Find the index at which the user is located
                        if (acc==-1) {   //If the authority is -1, it didn't find the user.
                            cout<<"Client could not be found.\n";
                            sleep(1);
                            cout<<"\nPlease try again.\n";
                            sleep(1);
                            cout<<"\n~:";
                        }
                        
                    }
                }
                cout<<"\nYou've chosen: "<<bankArray[acc].firstName<<" "<<bankArray[acc].lastName<<"'s account\n";
                sleep(1.5);
                
                
                
                if ((!bankArray[acc].savings.isActive()==1) && (!bankArray[acc].chequing.isActive()==1)) {
                    cout<<"\nSelect which account you would like to setup:\n\n1. Savings\n\n2. Chequing\n\n3. Exit\n\n~:";
                    
                    while (true) {
                        cin>>input;
                        
                        switch (input) {
                            case '1':
                                bankArray[acc].savings.accountType=1;
                                bankArray[acc].savings.activate();
                                /////////////////////////////////HERE////////////////////////////////////////////////
                                cout<<"\nThe clients Savings account is now setup.\n";
                                sleep(1.5);
                                break;
                                
                            case '2':
                                cout<<"\nTo setup this account, you must meet the threshold of $1000.\n";
                                cout<<"Would the client like to deposit into his/her account?\n\n";
                                cout<<"1. Yes\n\n2. No\n\n~:";
                                
                                while (true) {
                                    cin>>input;
                                    
                                    switch (input) {
                                            
                                        case '1':
                                            while (true) {
                                                double depAmount;
                                                cout<<"\n\nEnter the amount the client would like to deposit.\n\n~:";
                                                cin>>depAmount;
                                                if (depAmount>=1000) {
                                                    cout<<"\n$"<<depAmount<<" will be deposited into the account.\n\n";
                                                    bankArray[acc].chequing.accountType=0;
                                                    bankArray[acc].chequing.activate();
                                                    bankArray[acc].chequing.deposit(depAmount);
                                                    break;
                                                }
                                                else {
                                                    cout<<"\nThe amount you entered is below the required threshold of $1000.\n\n";
                                                    sleep(1.5);
                                                }
                                            }
                                            break;
                                            
                                        case '2':
                                            cout<<"\n\nChequing account not setup.\n\n";
                                            break;
                                            
                                        default:
                                            cout<<"\n\nInvalid input. Try again.\n\n~:";
                                            
                                    }
                                    cout<<"\n\nReturning to Main Menu.\n\n";
                                    sleep(1.5);
                                    managerMenu(user);
                                    return;
                                }
                                
                                break;
                                
                            case '3':
                                cout<<"\nAccounts not setup.\n";
                                sleep(1.5);
                                break;
                                
                            default:
                                cout<<"\nInvalid input. Try again.\n\n~:";
                        }
                        
                        cout<<"\nReturning to Main Menu.\n\n";
                        sleep(1.5);
                        managerMenu(user);
                        return;
                    }
                }
                else if (!bankArray[acc].savings.isActive()) {
                    cout<<"\nSelect which account you would like to setup:\n\n1. Savings\n\n2. Exit\n\n~:";
                    
                    while (true) {
                        cin>>input;
                        
                        switch (input) {
                            case '1':
                                bankArray[acc].savings.accountType=1;
                                bankArray[acc].savings.activate();
                                cout<<"\nThe clients Savings account is now setup.\n";
                                break;
                            
                            case '2':
                                cout<<"\nAccounts not setup.\n";
                                break;
                                
                            default:
                                cout<<"\nInvalid input. Try again.\n\n~:";
                        }
                        cout<<"\nReturning to Main Menu.\n\n";
                        sleep(1.5);
                        managerMenu(user);
                        return;
                    }
                }
                else if (!bankArray[acc].chequing.isActive()) {
                    cout<<"\nSelect which account you would like to setup:\n\n1. Chequing\n\n2. Exit\n\n~:";
                    while (true) {
                        cin>>input;
                        
                        switch (input) {
                            case '1': {
                                cout<<"\nTo setup this account, you must meet the threshold of $1000.\n";
                                cout<<"Would the client like to deposit into his/her account?\n\n";
                                cout<<"1. Yes\n\n2. No\n\n~:";
                                while (true) {
                                    cin>>input;
                                    
                                    switch (input) {
                                        case '1': {
                                            while (true) {
                                                double depAmount;
                                                cout<<"\n\nEnter the amount the client would like to deposit.\n\n~:";
                                                cin>>depAmount;
                                                if (depAmount>=1000) {
                                                    cout<<"\n$"<<depAmount<<" will be deposited into the account.\n\n";
                                                    bankArray[acc].chequing.accountType=0;
                                                    bankArray[acc].chequing.activate();
                                                    bankArray[acc].chequing.deposit(depAmount);
                                                    break;
                                                }
                                                else {
                                                    cout<<"\nThe amount you entered is below the required threshold of $1000.\n\n";
                                                    sleep(1.5);
                                                }
                                            }
                                        }
                                            break;
                                            
                                        case '2':
                                            cout<<"\nAccount not setup.\n\n";
                                            break;
                                            
                                        default:
                                            cout<<"\nInvalid input. Try again.\n\n~:";
                                    }
                                    cout<<"Returning to Main Menu.";
                                    sleep(1.5);
                                    managerMenu(user);
                                    return;
                                }
                            }
                                break;
                                
                            case '2':
                                cout<<"\n\nChequing account not setup.\n\n";
                                break;
                                
                            default:
                                cout<<"\nInvalid input. Try again.\n\n~:";
                        }
                        cout<<"\nReturning to Main Menu.\n\n";
                        sleep(1.5);
                        managerMenu(user);
                        return;
                    }
                }
                else {
                    cout<<"Client already has a chequings and savings.\n\n";
                    sleep(1.5);
                    cout<<"Returning to Main Menu.\n\n";
                    sleep(1.5);
                    managerMenu(user);
                    return;
                }
                cout<<"\n\nReturning to Main Menu.\n\n";
                managerMenu(user);
                return;
            }
                break;
            
                
                
                
                
                
            //Case 3: If the user wants to deposit into an account
            case '3': {
                double depAmount;
                char account;
                bool cheq=false;        //cheq and sav are to check if the users chequing and savings accounts are activated.
                bool sav=false;
                
                cout<<"\n\n\nEnter the amount you would like to deposit, or 0 to exit.\n\n~:";
                cin>>depAmount;
                
                //Checks if the user wants to exit
                if (depAmount==0) {
                    managerMenu(user);  //If user wants to exit, then go back to the main menu
                    return;
                }
                
                
                else {  //Otherwise continue with the operation
                    //Check to see which accounts are active
                    if (bankArray[user].chequing.isActive()) {
                        cheq=true;
                    }
                    if (bankArray[user].savings.isActive()) {
                        sav=true;
                    }
                    
                    //If both chequings and savings are active, give user an option for both accounts.
                    if (cheq && sav) {
                        
                        //Make sure the user inputs a valid command
                        while (true) {
                            cout<<"\n\n\nWhich account would you like to deposit to?";
                            cout<<"\n\n1. Chequings\n\n2. Savings\n\n3. Exit\n\n~:";
                            cin>>account;
                        
                            switch (account) {
                                case '1':
                                    bankArray[user].chequing.deposit(depAmount);
                                    break;
                                
                                case '2':
                                    bankArray[user].savings.deposit(depAmount);
                                    break;
                                
                                case '3':
                                    cout<<"\n\nReturning to Main Menu.\n\n";
                                    sleep(2);
                                    managerMenu(user);
                                    return;
                                
                                default:
                                    cout<<"\n\nInvalid input. Try Again.";
                                    sleep(1);
                            }
                            break;
                        }
                        cout<<"\nReturning to Main Menu.\n\n";
                        sleep(1.5);
                        managerMenu(user);
                        return;
                        
                    }
                    
                    //If only chequings account is open, give the user that option.
                    else if (cheq) {
                        
                        while (true) {
                            cout<<"\n\n1. Chequing\n\n2. Exit\n\n~:";
                        
                            //Make sure the user inputs the correct data
                            cin>>account;
                        
                            switch (account) {
                                case '1':
                                    bankArray[user].chequing.deposit(depAmount);
                                    break;
                                
                                case '2':
                                    cout<<"\n\nGoing back to Main Menu.\n\n";
                                    sleep(2);
                                    managerMenu(user);
                                    return;
                                
                                default:
                                    cout<<"Invalid input. Try again.";
                            }
                            break;
                        }
                        managerMenu(user);
                        return;
                    }
                    
                    
                    
                    //If only savings account is open, give user that option.
                    else if (sav) {
                        
                        while (true) {
                            cout<<"\n\n1. Savings\n\n2. Exit\n\n~:";
                            
                            cin>>account;
                        
                            switch (account) {
                                case '1':
                                    bankArray[user].savings.deposit(depAmount);
                                    break;
                                
                                case '2':
                                    cout<<"\n\nGoing back to Main Menu.\n\n";
                                    sleep(2);
                                    managerMenu(user);
                                    return;
                                
                                default:
                                    cout<<"\n\nInvalid input. Try again.\n\n~:";
                            }
                            break;
                        }
                        
                        managerMenu(user);
                        return;
                    }
                    
                    
                    //Otherwise the user does not have any accounts open. Return to main menu.
                    else {
                        cout<<"\n\nYou do not have any accounts yet.\n";
                        sleep(1.5);
                        cout<<"\nReturning to Main Menu.\n\n";
                        sleep(1.5);
                        managerMenu(user);
                        return;
                    }
                    cout<<"Returning to Main Menu.\n\n";
                    sleep(1.5);
                    managerMenu(user);
                    return;
                }
            }
                break;
            
                

                
                //Case 4: If user wants to withdraw money.
            case '4': {
                double wdAmount;
                char account;
                bool cheq=false;        //cheq and sav are to check if the users chequing and savings accounts are activated.
                bool sav=false;
                
                cout<<"\n\n\nEnter the amount you would like to withdraw, or 0 to exit.\n\n~:";
                cin>>wdAmount;
                
                //Checks if the user wants to exit
                if (wdAmount==0) {
                    managerMenu(user);  //If user wants to exit, then go back to the main menu
                    return;
                }
                else {
                    //Check to see which accounts are active
                    if (bankArray[user].chequing.isActive()) {
                        cheq=true;
                    }
                    if (bankArray[user].savings.isActive()) {
                        sav=true;
                    }
                    
                    //If both chequings and savings are active, give user an option for both accounts.
                    if (cheq && sav) {
                        
                        //Make sure the user inputs a valid command
                        while (true) {
                            cout<<"\n\nWhich account would you like to withdraw from?";
                            cout<<"\n\n1. Chequings\n\n2. Savings\n\n3. Exit\n\n~:";
                            cin>>account;
                            
                            switch (account) {
                                case '1': {
                                    if (bankArray[user].chequing.withdraw(wdAmount)) {
                                        cout<<"\n\nReturning to Main Menu.";
                                        sleep(1.5);
                                        managerMenu(user);
                                        return;
                                    }
                                    else {
                                        cout<<"\n\nNo money was withdrawn.";
                                        sleep(1.5);
                                        cout<<"\nReturning to the Main Menu.\n";
                                        sleep(1.5);
                                        managerMenu(user);
                                        return;
                                    }
                                }
                                    
                                case '2': {
                                    if (bankArray[user].savings.withdraw(wdAmount)) {
                                        cout<<"\n\nReturning to Main Menu.";
                                        sleep(1.5);
                                        managerMenu(user);
                                        return;
                                    }
                                    else {
                                        cout<<"\n\nNo money was withdrawn.";
                                        sleep(1.5);
                                        cout<<"\nReturning to the Main Menu.\n";
                                        sleep(1.5);
                                        managerMenu(user);
                                        return;
                                    }
                                }
                                    
                                case '3':
                                    cout<<"\n\nReturning to Main Menu.\n\n";
                                    sleep(1.5);
                                    managerMenu(user);
                                    return;
                                    
                                default:
                                    cout<<"\n\nInvalid input. Try again.";
                                    sleep(1);
                            }
                            break;
                        }
                        cout<<"Returning to Main Menu.\n\n";
                        sleep(1.5);
                        managerMenu(user);
                        return;
                        
                    }
                    
                    
                    
                    //If only chequings account is open, give the user that option.
                    else if (cheq) {
                        
                        while (true) {
                            cout<<"\n\n1. Chequing\n\n2. Exit\n\n~:";
                        
                            //Make sure the user inputs the correct data
                            cin>>account;
                        
                            switch (account) {
                                case '1': {
                                    if (bankArray[user].chequing.withdraw(wdAmount)) {
                                        cout<<"\n\nReturning to Main Menu.";
                                        sleep(1.5);
                                        managerMenu(user);
                                        return;
                                    }
                                    else {
                                        cout<<"\n\nNo money was withdrawn.";
                                        sleep(1.5);
                                        cout<<"\nReturning to Main Menu.\n";
                                        sleep(1.5);
                                        managerMenu(user);
                                        return;
                                    }
                                }
                                
                                case '2':
                                    cout<<"\nReturning to Main Menu.\n\n";
                                    sleep(1.5);
                                    managerMenu(user);
                                    return;
                                
                                default:
                                    cout<<"\n\nInvalid input. Try again.";
                                    sleep(1);
                            }
                            break;
                        }
                        
                        cout<<"Returning to Main Menu.";
                        managerMenu(user);
                        return;
                    }
                    
                    
                    
                    //If only savings account is open, give user that option.
                    else if (sav) {
                        
                        while (true) {
                            cout<<"\n\n1. Savings\n\n2. Exit\n\n~:";
                            
                            cin>>account;
                            
                            switch (account) {
                                case '1':
                                    if (bankArray[user].savings.withdraw(wdAmount)) {
                                        cout<<"\n\nReturning to Main Menu.";
                                        sleep(1.5);
                                        managerMenu(user);
                                        return;
                                    }
                                    else {
                                        cout<<"\n\nNo money was withdrawn.";
                                        sleep(1.5);
                                        cout<<"\nReturning to the Main Menu.\n";
                                        sleep(1.5);
                                        managerMenu(user);
                                        return;
                                    }
                                    
                                case '2':
                                    cout<<"\n\nReturning to Main Menu.\n\n";
                                    sleep(2);
                                    managerMenu(user);
                                    return;
                                    
                                default:
                                    cout<<"\n\nInvalid input. Try again.\n\n~:";
                                    sleep(1);
                            }
                            break;
                        }
                        
                        managerMenu(user);
                        return;
                    }
                    
                    
                    //Otherwise the user does not have any accounts open. Return to main menu.
                    else {
                        cout<<"\n\nYou do not have any accounts yet.\n";
                        sleep(1.5);
                        cout<<"\nReturning to Main Menu.\n\n";
                        sleep(1.5);
                        managerMenu(user);
                        return;
                    }
                    cout<<"Returning to Main Menu.\n\n";
                    sleep(1.5);
                    managerMenu(user);
                    return;
                }
                
                break;
            }
                
             
            //If the user wants to make a direct payment
            case '5': {
                int input=0, accNum=0,accType=0,userAcc=0;
                double amount = 0;
                
                if (bankArray[user].chequing.isActive() && bankArray[user].savings.isActive()) {
                    while (true) {
                        cout<<"Which account would you like to use?\n1. Savings\n2.Chequing\n3. Exit\n\n~:";
                        cin>>input;
                        
                        switch (input) {
                            case 1:
                                userAcc = 1;
                                break;
                                
                            case 2:
                                userAcc = 2;
                                break;
                                
                            case 3:
                                managerMenu(user);
                                return;
                                
                            default:
                                cout<<"\n\nInvalid Input.\n\n";
                        }
                    }
                }
                else if (!bankArray[user].chequing.isActive() && bankArray[user].savings.isActive()) {
                    userAcc = 1;
                }
                else if (bankArray[user].chequing.isActive() && !bankArray[user].savings.isActive()) {
                    userAcc = 2;
                }
                else {
                    cout<<"\n\nYou don't have any active accounts. Returning to main menu.\n\n";
                    sleep(1.5);
                    managerMenu(user);
                    return;
                }
                
                while (true) {
                    cout<<"\nEnter the user's login that you want to send money to: ";
                    cin>>input;
                    accNum = findAccount(input);
                    
                    if (accNum == -1) {
                        cout<<"\n\nCould not find the user you were looking for.";
                    }
                    else {
                        while(true) {
                            cout<<"\n\nEnter the amount you would like to send: ";
                            cin>>amount;
                            
                            if (userAcc==1) {
                                if (!(bankArray[user].savings.getAccountBalance()>=amount)) {
                                    cout<<"\nInsufficient funds.\n";
                                    managerMenu(user);
                                }

                            } else if (userAcc==2) {
                                if (!(bankArray[user].chequing.getAccountBalance()>=amount)) {
                                    break;
                                    cout<<"\nInsufficient funds.\n";
                                    managerMenu(user);
                                }
                            }
                            
                            if (amount>0) {
                                break;
                            }
                            else {
                                cout<<"\nEnter an amount over 0.";
                            }
                        }
                        
                        
                        if (bankArray[accNum].chequing.isActive() && bankArray[accNum].savings.isActive()) {
                            while (true) {
                                cout<<"\n\nWhich account would you like to send it to?\n1. Savings\n2. Chequing\n3. Exit";
                                cin>>accType;
                                
                                switch (accType) {
                                    case 1: {
                                        accType = 1;
                                        break;
                                    }
                                        
                                    case 2: {
                                        accType = 2;
                                        break;
                                    }
                                        
                                    case 3: {
                                        managerMenu(user);
                                        return;
                                    }
                                        
                                    default: {
                                        cout<<"\n\nIncorrect input. Try again.\n\n~:";
                                    }
                                }
                            }
                        }
                        else if (bankArray[accNum].chequing.isActive() && !bankArray[accNum].savings.isActive()) {
                            accType = 2;
                            break;
                        }
                        else if (!bankArray[accNum].chequing.isActive() && bankArray[accNum].savings.isActive()) {
                            accType = 1;
                            break;
                        }
                        else {
                            cout<<"\n\nThis user does not have any active accounts.\n";
                            sleep(1.5);
                            cout<<"\n\nReturning to Main Menu.\n";
                            managerMenu(user);
                            return;
                        }
                        
                    }
                }
                if (userAcc==1) {
                    bankArray[user].savings.withdraw(amount);
                    
                    if (accType==1) {
                        bankArray[accNum].savings.deposit(amount);
                    }
                    else {
                        bankArray[accNum].chequing.deposit(amount);
                    }
                }
                else {
                    bankArray[user].chequing.withdraw(amount);
                    if (accType==1) {
                        bankArray[accNum].savings.deposit(amount);
                    }
                    else {
                        bankArray[accNum].chequing.deposit(amount);
                    }
                }
                
                cout<<"Returning to Main Menu.";
                managerMenu(user);
                return;
            }
                
                //Case 6: If the manager wants a balance inquiry for him/herself, or a client.
            case '6': {
                while (true) {
                    int select;
                    int acc;
                    cout<<"\n\nEnter the login information of the account you would like to inquire, 1 for all accounts, or 0 to exit.\n\n~:";
                    cin >> select;
                    
                    switch (select) {
                        case 0:
                            cout<<"\n\nReturning to Main Menu.\n\n";
                            sleep(1.5);
                            managerMenu(user);
                            return;
                            
                        case 1: {
                            summary();
                            cout<<"\n\nTo return to the Main Menu enter 1...\n\n~:";
                            char temp;
                            cin>>temp;
                            managerMenu(user);
                            return;
                        }
                            
                        default:
                            acc = findAccount(select);
                            if (acc == -1) {
                                cout<<"\n\nCouldn't find the account. Please try again.\n\n";
                                sleep(1.5);
                            }
                            else {
                                bool sav=false;         //Two bools which check if the user has any accounts open
                                bool cheq=false;
                                if (bankArray[acc].savings.isActive()) {
                                    bankArray[acc].savings.showAccount();
                                    sav = true;
                                }
                                if (bankArray[acc].chequing.isActive()) {
                                    bankArray[acc].chequing.showAccount();
                                    cheq=true;
                                }
                                if (!cheq && !sav) {
                                    cout<<"\nThis client has no accounts open.\n";
                                }
                                cout<<"\nTo return to the Main Menu, press 1...\n\n~:";
                                char temp;
                                cin>>temp;
                                managerMenu(user);
                                return;
                            }
                    }
                }
                
            }
                
                
                //Case 7, if the user wants to modify his/her or another account
            case '7': {
                int accNum;
                while(true) {
                    cout<<"\n\nEnter the account number you would like to modify, 1 to edit your own account, or 0 to exit.\n\n~:";
                    cin>>accNum;
                    if (accNum==0) {
                        cout<<"\nReturning to Main Menu.\n";
                        managerMenu(user);
                    }
                    else if (accNum==1) {
                        break;
                    }
                    else if (isAccount(accNum)) {
                        break;
                    }
                    
                    else {
                        cout<<"\n\nAccount could not be found.";
                        sleep(1.5);
                    }
                }
                
                while(true) {
                    //If the user wants to edit their own account give them different options
                    if (accNum == 1) {
                        int input;
                        char name;
                        while (true) {
                            cout<<"\n\nWhat would you like to edit?\n1. First Name\n2. Last Name\n3. Edit Password4. Exit\n\n~:";
                            cin>>input;
                            
                            switch (input) {
                                case 1:
                                    cout<<"\nEnter name:";
                                    cin>>name;
                                    bankArray[user].firstName = name;
                                    cout<<"Your name was changed to: "<<name;
                                    break;
                                    
                                case 2:
                                    cout<<"\nEnter last name:";
                                    cin>>name;
                                    bankArray[user].lastName = name;
                                    cout<<"Your name was changed to: "<<name;
                                    break;
                                    
                                case 3: {
                                    bool tf = bankArray[user].changePassword();
                                    if (tf) {
                                        cout<<"\nYour password was changed.";
                                    }
                                    else {
                                        cout<<"\nYour password was not changed.";
                                    }
                                    break;
                                }
                                    
                                case 4:
                                    managerMenu(user);
                                    return;
                                    
                                default:
                                    cout<<"Incorrect input. Try again.";
                            }
                            
                        }
                        
                        cout<<"\nReturning to main menu.\n";
                        sleep(1.5);
                        managerMenu(user);
                    }
                    
                    //If the user is editing another account
                    else {
                        cout<<"\n\nWhat would you like to edit?\n1. First Name\n2. Last Name\n3. Delete Account\n4. Exit\n\n\n~:";
                        cin>>input;
                        char name;
                        
                        switch (input) {
                            case 1:
                                cout<<"\nEnter user's first name:";
                                cin>>name;
                                bankArray[user].firstName = name;
                                cout<<"Users name was changed to: "<<name;
                                break;
                                
                            case 2:
                                cout<<"\nEnter user's last name:";
                                cin>>name;
                                bankArray[user].lastName = name;
                                cout<<"User's name was changed to: "<<name;
                                break;
                                
                            case 3: {
                                bool check = bankArray[user].deleteAccount();
                                if (check) {
                                    cout<<"\nAccount was removed.\n";
                                    
                                    sleep(1.5);
                                }
                                else {
                                    cout<<"\nAccount could not be removed. Returning to main menu.\n";
                                    managerMenu(user);
                                    return;
                                }
                            }
                                
                            case 4:
                                managerMenu(user);
                                return;
                                
                            default:
                                cout<<"Incorrect input. Try again.";
                        }
                        
                    }
                    
                    cout<<"\nReturning to main menu.\n";
                    sleep(1.5);
                    managerMenu(user);
                    
                }
                
            }
        
        
                //If the user wants to logout of his/her account
            case '8': {
                cout<<"\n\nSigning out...\n";
                sleep(1);
                cout<<"\nYou have successfully signed out.\n\n";
                sleep(1);
                cout<<"\n\n\n\n";
                startup();
                return;
            }
                
            default:
                cout<<"\n\nInvalid input. Try again.\n\n~:";
        }
    }
};

void BankSystem::clientMenu(int user) {
    cout<<"MAIN MENU";
    cout<<"\n\n1. Deposit";
    cout<<"\n\n2. Withdraw";
    cout<<"\n\n3. Balance Inquiry";
    cout<<"\n\n4. Make a Direct Payment";
    cout<<"\n\n5. Modify Your Account";
    cout<<"\n\n6. Logout\n\n~:";
    int option;
    
    while (true) {
        cin>>option;
        
        switch (option) {
                //Option if the user wants to deposit money
            case 1: {
                double depAmount;
                char account;
                bool cheq=false;        //cheq and sav are to check if the users chequing and savings accounts are activated.
                bool sav=false;
                
                cout<<"\n\n\nEnter the amount you would like to deposit, or 0 to exit.\n\n~:";
                cin>>depAmount;
                
                //Checks if the user wants to exit
                if (depAmount==0) {
                    clientMenu(user);  //If user wants to exit, then go back to the main menu
                    return;
                }
                
                
                else {  //Otherwise continue with the operation
                    //Check to see which accounts are active
                    if (bankArray[user].chequing.isActive()) {
                        cheq=true;
                    }
                    if (bankArray[user].savings.isActive()) {
                        sav=true;
                    }
                    
                    //If both chequings and savings are active, give user an option for both accounts.
                    if (cheq && sav) {
                        
                        //Make sure the user inputs a valid command
                        while (true) {
                            cout<<"\n\n\nWhich account would you like to deposit to?";
                            cout<<"\n\n1. Chequings\n\n2. Savings\n\n3. Exit\n\n~:";
                            cin>>account;
                            
                            switch (account) {
                                case '1':
                                    bankArray[user].chequing.deposit(depAmount);
                                    break;
                                    
                                case '2':
                                    bankArray[user].savings.deposit(depAmount);
                                    break;
                                    
                                case '3':
                                    cout<<"\n\nReturning to Main Menu.\n\n";
                                    sleep(2);
                                    clientMenu(user);
                                    return;
                                    
                                default:
                                    cout<<"\n\nInvalid input. Try Again.";
                                    sleep(1);
                            }

                        }
                        cout<<"\nReturning to Main Menu.\n\n";
                        sleep(1.5);
                        clientMenu(user);
                        return;
                        
                    }
                    
                    //If only chequings account is open, give the user that option.
                    else if (cheq) {
                        
                        while (true) {
                            cout<<"\n\n1. Chequing\n\n2. Exit\n\n~:";
                            
                            //Make sure the user inputs the correct data
                            cin>>account;
                            
                            switch (account) {
                                case '1':
                                    bankArray[user].chequing.deposit(depAmount);
                                    break;
                                    
                                case '2':
                                    cout<<"\n\nGoing back to Main Menu.\n\n";
                                    sleep(2);
                                    clientMenu(user);
                                    return;
                                    
                                default:
                                    cout<<"Invalid input. Try again.";
                            }
                            break;
                        }
                        clientMenu(user);
                        return;
                    }
                    
                    
                    
                    //If only savings account is open, give user that option.
                    else if (sav) {
                        
                        while (true) {
                            cout<<"\n\n1. Savings\n\n2. Exit\n\n~:";
                            
                            cin>>account;
                            
                            switch (account) {
                                case '1':
                                    bankArray[user].savings.deposit(depAmount);
                                    break;
                                    
                                case '2':
                                    cout<<"\n\nGoing back to Main Menu.\n\n";
                                    sleep(2);
                                    clientMenu(user);
                                    return;
                                    
                                default:
                                    cout<<"\n\nInvalid input. Try again.\n\n~:";
                            }
                            break;
                        }
                        
                        clientMenu(user);
                        return;
                    }
                    
                    
                    //Otherwise the user does not have any accounts open. Return to main menu.
                    else {
                        cout<<"\n\nYou do not have any accounts yet.\n";
                        sleep(1.5);
                        cout<<"\nReturning to Main Menu.\n\n";
                        sleep(1.5);
                        clientMenu(user);
                        return;
                    }
                    cout<<"Returning to Main Menu.\n\n";
                    sleep(1.5);
                    clientMenu(user);
                    return;
                }
                break;
            }
                
                //Option if the user wants to withdraw money
            case 2: {
                {
                    double wdAmount;
                    char account;
                    bool cheq=false;        //cheq and sav are to check if the users chequing and savings accounts are activated.
                    bool sav=false;
                    
                    cout<<"\n\n\nEnter the amount you would like to withdraw, or 0 to exit.\n\n~:";
                    cin>>wdAmount;
                    
                    //Checks if the user wants to exit
                    if (wdAmount==0) {
                        clientMenu(user);  //If user wants to exit, then go back to the main menu
                        return;
                    }
                    else {
                        //Check to see which accounts are active
                        if (bankArray[user].chequing.isActive()) {
                            cheq=true;
                        }
                        if (bankArray[user].savings.isActive()) {
                            sav=true;
                        }
                        
                        //If both chequings and savings are active, give user an option for both accounts.
                        if (cheq && sav) {
                            
                            //Make sure the user inputs a valid command
                            while (true) {
                                cout<<"\n\nWhich account would you like to withdraw from?";
                                cout<<"\n\n1. Chequings\n\n2. Savings\n\n3. Exit\n\n~:";
                                cin>>account;
                                
                                switch (account) {
                                    case '1': {
                                        if (bankArray[user].chequing.withdraw(wdAmount)) {
                                            cout<<"\n\nReturning to Main Menu.";
                                            sleep(1.5);
                                            clientMenu(user);
                                            return;
                                        }
                                        else {
                                            cout<<"\n\nNo money was withdrawn.";
                                            sleep(1.5);
                                            cout<<"\nReturning to the Main Menu.\n";
                                            sleep(1.5);
                                            clientMenu(user);
                                            return;
                                        }
                                    }
                                        
                                    case '2': {
                                        if (bankArray[user].savings.withdraw(wdAmount)) {
                                            cout<<"\n\nReturning to Main Menu.";
                                            sleep(1.5);
                                            clientMenu(user);
                                            return;
                                        }
                                        else {
                                            cout<<"\n\nNo money was withdrawn.";
                                            sleep(1.5);
                                            cout<<"\nReturning to the Main Menu.\n";
                                            sleep(1.5);
                                            clientMenu(user);
                                            return;
                                        }
                                    }
                                        
                                    case '3':
                                        cout<<"\n\nReturning to Main Menu.\n\n";
                                        sleep(1.5);
                                        clientMenu(user);
                                        return;
                                        
                                    default:
                                        cout<<"\n\nInvalid input. Try again.";
                                        sleep(1);
                                }
                                break;
                            }
                            cout<<"Returning to Main Menu.\n\n";
                            sleep(1.5);
                            clientMenu(user);
                            return;
                            
                        }
                        
                        
                        
                        //If only chequings account is open, give the user that option.
                        else if (cheq) {
                            
                            while (true) {
                                cout<<"\n\n1. Chequing\n\n2. Exit\n\n~:";
                                
                                //Make sure the user inputs the correct data
                                cin>>account;
                                
                                switch (account) {
                                    case '1': {
                                        if (bankArray[user].chequing.withdraw(wdAmount)) {
                                            cout<<"\n\nReturning to Main Menu.";
                                            sleep(1.5);
                                            clientMenu(user);
                                            return;
                                        }
                                        else {
                                            cout<<"\n\nNo money was withdrawn.";
                                            sleep(1.5);
                                            cout<<"\nReturning to Main Menu.\n";
                                            sleep(1.5);
                                            clientMenu(user);
                                            return;
                                        }
                                    }
                                        
                                    case '2':
                                        cout<<"\nReturning to Main Menu.\n\n";
                                        sleep(1.5);
                                        clientMenu(user);
                                        return;
                                        
                                    default:
                                        cout<<"\n\nInvalid input. Try again.";
                                        sleep(1);
                                }
                                break;
                            }
                            
                            cout<<"Returning to Main Menu.";
                            clientMenu(user);
                            return;
                        }
                        
                        
                        
                        //If only savings account is open, give user that option.
                        else if (sav) {
                            
                            while (true) {
                                cout<<"\n\n1. Savings\n\n2. Exit\n\n~:";
                                
                                cin>>account;
                                
                                switch (account) {
                                    case '1':
                                        if (bankArray[user].savings.withdraw(wdAmount)) {
                                            cout<<"\n\nReturning to Main Menu.";
                                            sleep(1.5);
                                            clientMenu(user);
                                            return;
                                        }
                                        else {
                                            cout<<"\n\nNo money was withdrawn.";
                                            sleep(1.5);
                                            cout<<"\nReturning to the Main Menu.\n";
                                            sleep(1.5);
                                            clientMenu(user);
                                            return;
                                        }
                                        
                                    case '2':
                                        cout<<"\n\nReturning to Main Menu.\n\n";
                                        sleep(2);
                                        clientMenu(user);
                                        return;
                                        
                                    default:
                                        cout<<"\n\nInvalid input. Try again.\n\n~:";
                                        sleep(1);
                                }
                                break;
                            }
                            
                            clientMenu(user);
                            return;
                        }
                        
                        
                        //Otherwise the user does not have any accounts open. Return to main menu.
                        else {
                            cout<<"\n\nYou do not have any accounts yet.\n";
                            sleep(1.5);
                            cout<<"\nReturning to Main Menu.\n\n";
                            sleep(1.5);
                            clientMenu(user);
                            return;
                        }
                        cout<<"Returning to Main Menu.\n\n";
                        sleep(1.5);
                        clientMenu(user);
                        return;
                    }
                    
                    
                }
                break;
            }
                
                //Option if the user wants to make a balance inquiry
            case 3:
                bankArray[user].chequing.showAccount();
                bankArray[user].savings.showAccount();
                char temp;
                cout<<"\nEnter 1 to return to Main Menu.\n~:";
                cin>>temp;
                clientMenu(user);
                return;
                
                //Option if the user wants to make a direct payment
            case 4: {
                int input=0, accNum=0,accType=0,userAcc=0;
                double amount = 0;
                
                if (bankArray[user].chequing.isActive() && bankArray[user].savings.isActive()) {
                    while (true) {
                        cout<<"Which account would you like to use?\n1. Savings\n2.Chequing\n3. Exit\n\n~:";
                        cin>>input;
                        
                        switch (input) {
                            case 1:
                                userAcc = 1;
                                break;
                                
                            case 2:
                                userAcc = 2;
                                break;
                                
                            case 3:
                                clientMenu(user);
                                return;
                                
                            default:
                                cout<<"\n\nInvalid Input.\n\n";
                        }
                    }
                }
                else if (!bankArray[user].chequing.isActive() && bankArray[user].savings.isActive()) {
                    userAcc = 1;
                }
                else if (bankArray[user].chequing.isActive() && !bankArray[user].savings.isActive()) {
                    userAcc = 2;
                }
                else {
                    cout<<"\n\nYou don't have any active accounts. Returning to main menu.\n\n";
                    sleep(1.5);
                    clientMenu(user);
                    return;
                }
                
                while (true) {
                    cout<<"\nEnter the user's login that you want to send money to: ";
                    cin>>input;
                    accNum = findAccount(input);
                    
                    if (accNum == -1) {
                        cout<<"\n\nCould not find the user you were looking for.";
                    }
                    else {
                        while(true) {
                            cout<<"\n\nEnter the amount you would like to send: ";
                            cin>>amount;
                            
                            if (userAcc==1) {
                                if (!(bankArray[user].savings.getAccountBalance()>=amount)) {
                                    cout<<"\nInsufficient funds.\n";
                                    clientMenu(user);
                                }
                                
                            } else if (userAcc==2) {
                                if (!(bankArray[user].chequing.getAccountBalance()>=amount)) {
                                    cout<<"\nInsufficient funds.\n";
                                    clientMenu(user);
                                }
                            }
                            
                            if (amount>0) {
                                break;
                            }
                            else {
                                cout<<"\nEnter an amount over 0.";
                            }
                        }
                        
                        
                        if (bankArray[accNum].chequing.isActive() && bankArray[accNum].savings.isActive()) {
                            while (true) {
                                cout<<"\n\nWhich account would you like to send it to?\n1. Savings\n2. Chequing\n3. Exit";
                                cin>>accType;
                                
                                switch (accType) {
                                    case 1: {
                                        accType = 1;
                                        break;
                                    }
                                        
                                    case 2: {
                                        accType = 2;
                                        break;
                                    }
                                    
                                    case 3: {
                                        clientMenu(user);
                                        return;
                                    }
                                        
                                    default: {
                                        cout<<"\n\nIncorrect input. Try again.\n\n~:";
                                    }
                                }
                            }
                        }
                        else if (bankArray[accNum].chequing.isActive() && !bankArray[accNum].savings.isActive()) {
                            accType = 2;
                            break;
                        }
                        else if (!bankArray[accNum].chequing.isActive() && bankArray[accNum].savings.isActive()) {
                            accType = 1;
                            break;
                        }
                        else {
                            cout<<"\n\nThis user does not have any active accounts.\n";
                            sleep(1.5);
                            cout<<"\nReturning to Main Menu.\n";
                            clientMenu(user);
                            return;
                        }
                        
                    }
                }
                if (userAcc==1) {
                    bankArray[user].savings.withdraw(amount);
                    
                    if (accType==1) {
                        bankArray[accNum].savings.deposit(amount);
                    }
                    else {
                        bankArray[accNum].chequing.deposit(amount);
                    }
                }
                else {
                    bankArray[user].chequing.withdraw(amount);
                    if (accType==1) {
                        bankArray[accNum].savings.deposit(amount);
                    }
                    else {
                        bankArray[accNum].chequing.deposit(amount);
                    }
                }
                
                cout<<"Returning to Main Menu.";
                clientMenu(user);
                return;
            }
                
                //Option if the user wants to modify his/her account
            case 5:
                int input;
                char name;
                
                while (true) {
                    cout<<"\n\nWhat would you like to edit?\n1. First Name\n2. Last Name\n3. Edit Password4. Exit\n\n~:";
                    cin>>input;
                    
                    switch (input) {
                        case 1:
                            cout<<"\nEnter name:";
                            cin>>name;
                            bankArray[user].firstName = name;
                            cout<<"Your name was changed to: "<<name;
                            break;
                            
                        case 2:
                            cout<<"\nEnter last name:";
                            cin>>name;
                            bankArray[user].lastName = name;
                            cout<<"Your name was changed to: "<<name;
                            break;
                            
                        case 3: {
                            bool tf = bankArray[user].changePassword();
                            if (tf) {
                                cout<<"\nYour password was changed.";
                            }
                            else {
                                cout<<"\nYour password was not changed.";
                            }
                            break;
                        }
                    }
                }
                cout<<"Returning to Main Menu.";
                clientMenu(user);
                
                //Option if the user wants to logout
            case 6:
                cout<<"\n\nSigning out...\n";
                sleep(1);
                cout<<"\nYou have successfully signed out.\n\n";
                sleep(1);
                cout<<"\n\n\n\n";
                startup();
                return;
                
            default:
                cout<<"\n\nInvalid input. Try again.\n\n~:";
                
        }
        
    }

}


void BankSystem::maintenanceMenu(int user) {
    
}



/*Method to add a manager or client account.*/
void BankSystem::createAccount(int user) {
    string fName;
    string lName;
    int login;
    int pword;
    int accountType;
    while (true) {      //Make sure correct input
        cout<<"\n\nIf you want to exit enter 0.\nIf this is a client account enter 1, manager account enter 2, maintenance account enter 3.\n\n~:";
        cin>>accountType;
        switch (accountType) {
            case 0:
                cout<<"\nReturning to Main Menu.\n\n";
                sleep(1);
                managerMenu(user);
                return;
                
            case 1:
                accountType=1;
                break;
                
            case 2:
                accountType=2;
                break;
                
            case 3:
                accountType=3;
                break;
                
            default:
                cout<<"\nYou did not enter correct data. Try again.\n\n";
        }
        
    }
    
    cout<<"\nEnter the first name: ";
    cin>>fName;
    cout<<"\nEnter the last name: ";
    cin>>lName;
    
    login = rand() % 99000 + 10000;
    cout<<"\nThe user's login is: "<<login;
    cout<<"\nLet the client choose a password (must be numbers): ";
    cin>>pword;
    
    person *newPerson = new person(fName, lName, login, pword, accountType);
    
    for (int i=0; i<20; i++) {
        if (bankArray[i].authorityType==-1) {
            bankArray[i] = *newPerson;
            break;
        }
    }
    
    cout<<"\n\nReturning to Main Menu.\n\n";
    sleep(1);
    
}


//Method which finds an account in the bank and returns its index.
int BankSystem::findAccount(int accNum) {
    //Search the array to find the user
    for (int i=0; i<20; i++) {
        if (bankArray[i].getLogin()==accNum) {
            return i;    //When found, return
        }
    }
    
    //If it isn't found, then create a new person with authority = -1 and return.
    return -1;
}


// Loops through bank accounts and checks if the parameter is a valid account number
bool BankSystem::isAccount(int accNum) {
    for (int i=0; i <20; i++) {
        if (bankArray[i].getLogin() == accNum) {
            return true;
        }
    }
    return false;
}


void BankSystem::makeChanges(person client) {
    for (int i=0; i<20; i++) {
        if (bankArray[i].getLogin()==client.getLogin()) {
            bankArray[i]=client;
        }
    }
}


//Method which returns a summary of the current users account
void BankSystem::summary() {
    
    double totalFunds=0;    //Variable to find the total funds of the bank
    int active=0;           //Variable which finds the total number of active accounts
    
    //Loops through the bank accounts
    for (int i=0;i<20; i++) {
        
        if (bankArray[i].chequing.isActive()) { //Checks if chequings account is active

            //If so print out the information of the account
            cout<<"\nAccount Holder: "<<bankArray[i].firstName<<" "<<bankArray[i].lastName;
            bankArray[i].chequing.showAccount();
            totalFunds+=bankArray[i].chequing.getAccountBalance();
            active+=1;
        }
        
        if (bankArray[i].savings.isActive()) {  //Checks if the savings account is active
            cout<<"\nAccount Holder: "<<bankArray[i].firstName<<" "<<bankArray[i].lastName;
            bankArray[i].savings.showAccount();
            totalFunds+=bankArray[i].savings.getAccountBalance();
            active+=1;
        }
    }
    cout<<"\n\nTotal Funds: $"<<fixed<<setprecision(2)<<totalFunds;
    cout<<"\nNumber of active accounts: "<<active;
}


#endif /* BankSystem_hpp */
