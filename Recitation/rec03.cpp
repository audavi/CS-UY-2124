/*
  Emily Lopez
  el4100
  rec03.cpp
  2024 Fall
 */

// Provided
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

// Task 1
// Define an Account struct
struct Account {
     string accountName;
     int accountNumber;
};

// Task 2
// Define an Account class (use a different name than in Task 1)
class AccountClass {
     friend ostream& operator << (ostream& os, const AccountClass& account);
public:
     AccountClass(const string& accountName, int accountNumber)
     : accountName(accountName), accountNumber(accountNumber){}

     //GETTERS TO ACCESS FIELDS IN ACCOUNTS
     const string& getAccName() const{
          return accountName;
     }
     int getAccNum() const{
          return accountNumber;
     }
private:
     string accountName;
     int accountNumber;
};

ostream& operator << (ostream& os, const AccountClass& account){
     //Getters:
     //os << account.getAccName() << " " << account.getAccNum();
     os << account.accountName << " " << account.accountNumber;
     return os;
}

// Task 3
// Define another Account class (use a different name than in Task
// 1&2) and a Transaction class. The Transaction class is to be
// defined outside of the Account class, i.e. it is not "nested".
class Transaction {
     friend ostream& operator <<(ostream& os, const Transaction& transaction);
public:
     Transaction(const string& transactionType, int amount)
          : transactionType(transactionType), amount(amount) {}
private:
     string transactionType;
     int amount;
};

ostream& operator <<(ostream& os, const Transaction& transaction) {
     os << transaction.transactionType << " " << transaction.amount<< endl;
     return os;
}

class AccountTransactions {
     friend ostream& operator <<(ostream& os, const AccountTransactions& account);
public:
     AccountTransactions(const string& accountName, int accountNumber)
          : accountName(accountName), accountNumber(accountNumber) {}

     void deposit(int amount) {
          transactionHistory.emplace_back("Deposited: ", amount);
          balance += amount;
     }
     void withdrawal(int amount) {
          if (amount > balance){
               cout << "Account #" << accountNumber << " has only " << balance
               << ". Insufficient for withdrawl of " << amount << endl;
          } else {
               transactionHistory.emplace_back("Withdrew: ", amount);
               balance -= amount;
          }
     }
     int getAccountNum() const{
          return accountNumber;
     }
private:
     string accountName;
     int accountNumber;
     vector<Transaction> transactionHistory;
     int balance;
};

ostream& operator <<(ostream& os, const AccountTransactions& account) {
     os << account.accountName << " " << account.accountNumber << endl;
     for (const Transaction& transaction : account.transactionHistory) {
          cout << "Transaction " << transaction;
     }
     return os;
}


// Task 4
// Define yet another Account class, this time with a nested public
// Transaction class. Again use a different name for the Account class
// than in the previous Tasks. Note that it is NOT necessary to rename
// the Transaction class, since it is nested.
class NestedAccount {
     friend ostream& operator <<(ostream& os, const NestedAccount& account);
public:
     //Nested Transaction class
     class newTransactionClass {
          friend ostream& operator <<(ostream& os, const newTransactionClass& transaction);
     public:
          newTransactionClass(const string& transactionType, int amount)
          : transactionType(transactionType), amount(amount){}
     private:
          string transactionType;
          int amount;
     };

     NestedAccount(const string& accountName, int accountNumber)
     : accountName(accountName), accountNumber(accountNumber){}
     void deposit(int amount) {
          history.emplace_back("Deposited: ", amount);
          balance += amount;
     }
     void withdrawal(int amount) {
          if (amount > balance){
               cout << "Account #" << accountNumber << " has only " << balance
               << ". Insufficient for withdrawl of " << amount << endl;
          } else {
               history.emplace_back("Withdrew: ", amount);
               balance -= amount;
          }
     }
     int getAccountNum() const{
          return accountNumber;
     }
private:
     vector<newTransactionClass> history;
     int balance;
     string accountName;
     int accountNumber;
};
ostream& operator <<(ostream& os, const NestedAccount& account) {
     os << account.accountName << " " << account.accountNumber << endl;
     for (const NestedAccount::newTransactionClass& transaction : account.history) {
          cout << "Transaction " << transaction;
     }
     return os;
}
ostream& operator <<(ostream& os, const NestedAccount::newTransactionClass& transaction) {
     os << transaction.transactionType << " " << transaction.amount<< endl;
     return os;
}
// Task 5
// Same as Task 4, but make the Transaction nested class private.
// Yes, the Account class needs a new name but, again, the Transaction
// class does not.


int main() {
    // Task 1: account as struct
    //      1a
    cout << "Task1a:\n"
         << "Filling vector of struct objects, define a local struct instance\n"
         << "and set fields explicitly:\n";
     //Open file
     ifstream file("accounts.txt");
     if (!file) {
          cerr << "Error opening file.\n";
          exit(1);
     }
     //Define local variables corresponding to each data item
     string accountName;
     int accountNumber;
     vector<Account> totalAccounts;

     while (file >> accountName >> accountNumber) {
          Account newAccount;
          newAccount.accountName = accountName;
          newAccount.accountNumber = accountNumber;
          totalAccounts.push_back(newAccount);
     }
     file.close();
     //Display all of the objects.
     for (const Account& account : totalAccounts) {
          cout << account.accountName << " " << account.accountNumber << endl;
     }

    //      1b
    cout << "Task1b:\n"
         << "Filling vector of struct objects, using {} initialization:\n";
     totalAccounts.clear();
     file.open("accounts.txt");
     if (!file) {
          cerr << "Error opening file.\n";
          exit(1);
     }
     while (file >> accountName >> accountNumber) {
          Account newAccount{accountName, accountNumber};
          totalAccounts.push_back(newAccount);
     }
     file.close();
     //Testing 1b
     for (const Account& account : totalAccounts) {
          cout << account.accountName << " " << account.accountNumber << endl;
     }
     totalAccounts.clear();
    //==================================
    // Task 2: account as class
    //      2a
    cout << "==============\n";
    cout << "\nTask2a:"
         << "\nFilling vector of class objects, using local class object:\n";

     vector<AccountClass> newTotalAccount;

     file.open("accounts.txt");
     if (!file) {
          cerr << "Error opening file.\n";
          exit(1);
     }
     while (file >> accountName >> accountNumber) {
          AccountClass newAccount(accountName, accountNumber);
          newTotalAccount.push_back(newAccount);
     }
     file.close();
     for (AccountClass& account : newTotalAccount) {
          cout << account.getAccName() << " " << account.getAccNum() << endl;;
     }


    cout << "\nTask2b:\n";
    cout << "output using output operator with getters\n";
     //Use getters for the fields you are displaying.
     for (AccountClass& account : newTotalAccount) {
          cout << account << endl;;
     }

    cout << "\nTask2c:\n"
         << "output using output operator as friend without getters\n";
     for (const AccountClass& account : newTotalAccount) {
          cout << account << endl;
     }

    cout << "\nTask2d:\n"
         << "Filling vector of class objects, using temporary class object:\n";
     newTotalAccount.clear();
     file.open("accounts.txt");
     if (!file) {
          cerr << "Error opening file.\n";
          exit(1);
     }
     while (file >> accountName >> accountNumber) {
          newTotalAccount.push_back(AccountClass(accountName, accountNumber));
     }
     for (const AccountClass& account : newTotalAccount) {
          cout << account << endl;
     }
    file.close();

    cout << "\nTask2e:\n"
         << "Filling vector of class objects, using emplace_back:\n";
     newTotalAccount.clear();
     file.open("accounts.txt");
     if (!file) {
          cerr << "Error opening file.\n";
          exit(1);
     }
     while (file >> accountName >> accountNumber) {
          newTotalAccount.emplace_back(accountName, accountNumber);
     }
     file.close();
     for (const AccountClass& account : newTotalAccount) {
          cout << account << endl;
     }

    cout << "==============\n"
         << "\nTask 3:\nAccounts and Transaction:\n";

     file.open("transactions.txt");
     if (!file) {
          cerr << "Error opening file.\n";
          exit(1);
     }

     string command;
     int amount;
     vector<AccountTransactions> moreAccounts;

     while (file >> command) {
          if (command == "Account") {
               file >> accountName >> accountNumber;
               moreAccounts.emplace_back(accountName, accountNumber);
          } else {
               file >> accountNumber >> amount;
               for (size_t i = 0; i < moreAccounts.size(); i++) {
                    //You will have to locate the account in your collection of accounts.
                    if (moreAccounts[i].getAccountNum() == accountNumber ) {
                         if (command == "Deposit") {
                              moreAccounts[i].deposit(amount);
                         } else {// withdrawl
                              moreAccounts[i].withdrawal(amount);
                         }
                    }
               }
          }
     }
     file.close();
     for (const AccountTransactions& account: moreAccounts){
          cout << account << endl;
     }

    cout << "==============\n"
         << "\nTask 4:\nTransaction nested in public section of Account:\n";
     file.open("transactions.txt");
     if (!file) {
          cerr << "Error opening file.\n";
          exit(1);
     }
     vector<NestedAccount> nestedAccounts;
     while(file >> command) {
          if(command == "Account") {
               file >> accountName >> accountNumber;
               nestedAccounts.emplace_back(accountName, accountNumber);
          } else {
               file >> accountNumber >> amount;
               for (size_t i = 0; i < nestedAccounts.size(); i++) {
                    //You will have to locate the account in your collection of accounts.
                    if (nestedAccounts[i].getAccountNum() == accountNumber ) {
                         if (command == "Deposit") {
                              nestedAccounts[i].deposit(amount);
                         } else {// withdrawl
                              nestedAccounts[i].withdrawal(amount);
                         }
                    }
               }
          }
     }
     file.close();
     for (const NestedAccount& account: nestedAccounts){
          cout << account << endl;
     }
    cout << "==============\n"
         << "\nTask 5:\nTransaction nested in private section of Account:\n";


}
