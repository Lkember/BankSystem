#include<iostream>
#include<fstream>
#include<string>
#include <sstream>
#include "Authority.hpp"
#include "account.hpp"
#include "BankSystem.hpp"
using namespace std;

/////////////////////////////////////////////////////////////////////////////
////////                           MAIN                             /////////
/////////////////////////////////////////////////////////////////////////////

int main() {
    BankSystem newBank = *new BankSystem();
    newBank.initialize("Logan", "Kember", 23971, 1234, 1, "John", "Doe", 12345, 1111, 0);      //Initialize a manager and client in the bank system
    newBank.startup();                                            //Start the login page
    return 0;
}