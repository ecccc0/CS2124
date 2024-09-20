// Provided
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

// Task 1
// Define an Account struct
struct AccountStruct{
    string name;
    int accountNumber;
};

// Task 2
// Define an Account class (use a different name than in Task 1)
class Account{
private:
    string name;
    int accountNumber;
public:
    Account(const string &name_new, int num) : name(name_new), accountNumber(num){}
    const string& getName() const {return name;}
    int getNumber() const {return accountNumber;}
    friend ostream& operator<<(ostream& os, const Account& acc);
};

// using getter
// ostream& operator<<(ostream& os, const Account& acc){
//     os << "Name: " << acc.getName() << ", Number: " << acc.getNumber();   
// }

// without using getter
ostream& operator<<(ostream& os, const Account& acc){
    os << "Name: " << acc.name << ", Number: " << acc.accountNumber;   
    return os;
}

// Task 3
// Define another Account class (use a different name than in Task
// 1&2) and a Transaction class. The Transaction class is to be
// defined outside of the Account class, i.e. it is not "nested".

class Transaction{
    private:
    string action;
    int amount;
    public:
    Transaction(const string &ac, int am) : action(ac), amount(am) {}
    friend ostream& operator<<(ostream& os, const Transaction& trans);
};

class TransactionAccount{
    private:
    int balance, account_number;
    string name;
    vector<Transaction> history;

    public:
    const string& getName() const{return name;}
    int getBalance() const{return balance;}
    int getAccount() const {return account_number;}
    TransactionAccount(const string &name, int accountNum) 
    : balance(0), name(name), account_number(accountNum) {}
    void deposit(int amount){
        balance += amount;
        history.emplace_back("Deposit", amount);
    }
    void withdraw(int amount){
        if (balance < amount){
            cout << "Not enough funds, transaction failed" << endl;
            return;
        }
        balance -=amount;
        history.emplace_back("Withdraw", amount);
    }
    friend ostream& operator<<(ostream& os, const TransactionAccount& acc);
};

ostream& operator<<(ostream& os, const Transaction& trans){
    os << "Action: " << trans.action << ", Amount: " << trans.amount;   
    return os;
}

ostream& operator<<(ostream& os, const TransactionAccount& acc){
    os << acc.name << ":" << endl;
    for (size_t i = 0; i< acc.history.size(); i++){
        os << acc.history[i] << endl;
    }
    return os;
}


// Task 4
// Define yet another Account class, this time with a nested public
// Transaction class. Again use a different name for the Account class
// than in the previous Tasks. Note that it is NOT necessary to rename
// the Transaction class, since it is nested.
class NestedAccount{
    private:
    int balance, account_number;
    string name;
    vector<Transaction> history;

    public:
    const string& getName() const{return name;}
    int getBalance() const{return balance;}
    int getAccount() const {return account_number;}
    NestedAccount(const string &nm, int n) : balance(0), name(nm), account_number(n) {}
    void deposit(int amount){
        balance += amount;
        history.emplace_back("Deposit", amount);
    }
    void withdraw(int amount){
        if (balance < amount){
            cout << "Not enough funds, transaction failed" << endl;
            return;
        }
        balance -=amount;
        history.emplace_back("Withdraw", amount);
    }
    friend ostream& operator<<(ostream& os, const NestedAccount& acc);
    class Transaction{
        private:
        string action;
        int amount;
        public:
        Transaction(const string &ac, int am) : action(ac), amount(am) {}
        friend ostream& operator<<(ostream& os, const Transaction& trans);
    };
};

ostream& operator<<(ostream& os, const NestedAccount::Transaction& trans){
    os << "Action: " << trans.action << ", Amount: " << trans.amount;
    return os;
}

ostream& operator<<(ostream& os, const NestedAccount& acc){
    os << acc.name << ":" << endl;
    for (size_t i = 0; i< acc.history.size(); i++){
        os << acc.history[i] << endl;
    }
    return os;
}



// Task 5
// Same as Task 4, but make the Transaction nested class private.
// Yes, the Account class needs a new name but, again, the Transaction
// class does not.

class NestedAccountPrivate{
    private:
    int balance, account_number;
    string name;
    vector<Transaction> history;
    class Transaction{
        private:
        string action;
        int amount;
        public:
        Transaction(const string &ac, int am) : action(ac), amount(am) {}
        friend ostream& operator<<(ostream& os, const Transaction& trans);
    };

    public:
    const string& getName() const{return name;}
    int getBalance() const{return balance;}
    int getAccount() const {return account_number;}
    NestedAccountPrivate(const string &nm, int n) : balance(0), name(nm), account_number(n) {}
    void deposit(int amount){
        balance += amount;
        history.emplace_back("Deposit", amount);
    }
    void withdraw(int amount){
        if (balance < amount){
            cout << "Not enough funds, transaction failed" << endl;
            return;
        }
        balance -=amount;
        history.emplace_back("Withdraw", amount);
    }
    friend ostream& operator<<(ostream& os, const Transaction& trans);
    friend ostream& operator<<(ostream& os, const NestedAccountPrivate& acc);

};

ostream& operator<<(ostream& os, const NestedAccountPrivate::Transaction& trans){
    os << "Action: " << trans.action << ", Amount: " << trans.amount;
    return os;
}

ostream& operator<<(ostream& os, const NestedAccountPrivate& acc){
    os << acc.name << ":" << endl;
    for (size_t i = 0; i< acc.history.size(); i++){
        os << acc.history[i] << endl;
    }
    return os;
}

int main() {

    // Task 1: account as struct
    //      1a
    cout << "Task1a:\n"
         << "Filling vector of struct objects, define a local struct instance\n"
         << "and set fields explicitly:\n";
    ifstream ifs;
    ifs.open("accounts.txt");
    vector<AccountStruct> accounts_vec_struct;
    string name;
    int num;
    while(ifs >> name >> num){
        AccountStruct cur;
        cur.accountNumber = num;
        cur.name = name;
        accounts_vec_struct.push_back(cur);
    }
    ifs.close();
    for (size_t i = 0; i < accounts_vec_struct.size(); i++){
        cout << "Name: " << accounts_vec_struct[i].name << ", Number: " << accounts_vec_struct[i].accountNumber << endl;
    }

    //      1b
    cout << "Task1b:\n"
         << "Filling vector of struct objects, using {} initialization:\n";
    accounts_vec_struct.clear();
    ifs.open("accounts.txt");
    while(ifs >> name >> num){
        AccountStruct cur{name, num};
        accounts_vec_struct.push_back(cur);
    }
    ifs.close();
    for (size_t i = 0; i < accounts_vec_struct.size(); i++){
        cout << "Name: " << accounts_vec_struct[i].name << ", Number: " << accounts_vec_struct[i].accountNumber << endl;
    }

    //==================================
    // Task 2: account as class

    //      2a
    cout << "==============\n";
    cout << "\nTask2a:"
         << "\nFilling vector of class objects, using local class object:\n";
    ifs.open("accounts.txt");
    vector<Account> accounts_vec;
    while(ifs >> name >> num){
        Account a(name, num);
        accounts_vec.push_back(a);
    }
    ifs.close();
    for (size_t i = 0; i < accounts_vec_struct.size(); i++){
        cout << "Name: " << accounts_vec[i].getName() << ", Number: " << accounts_vec[i].getNumber() << endl;
    }

    
    cout << "\nTask2b:\n";
    cout << "output using output operator with getters\n";
    for (size_t i = 0; i < accounts_vec_struct.size(); i++){
        cout << accounts_vec[i] << endl;
    }
    

    cout << "\nTask2c:\n"
         << "output using output operator as friend without getters\n";
    cout << "output using output operator with getters\n";
    for (size_t i = 0; i < accounts_vec_struct.size(); i++){
        cout << accounts_vec[i] << endl;
    }

    cout << "\nTask2d:\n"
         << "Filling vector of class objects, using temporary class object:\n";
    accounts_vec.clear();
    ifs.open("accounts.txt");
    while (ifs >> name >> num){
        accounts_vec.push_back(Account(name, num));
    }
    ifs.close();
    

    cout << "\nTask2e:\n"
         << "Filling vector of class objects, using emplace_back:\n";
    accounts_vec.clear();
    ifs.open("accounts.txt");
    while (ifs >> name >> num){
        accounts_vec.emplace_back(name, num);
    }
    ifs.close();

    cout << "==============\n"
         << "\nTask 3:\nAccounts and Transaction:\n";
    ifs.open("transactions.txt");
    string command;
    int amount;
    vector<TransactionAccount> t_account_vec;
    while (ifs >> command){
        if (command == "Account"){
            ifs >> name >> num;
            t_account_vec.emplace_back(name, num);
        }
        if (command == "Withdraw"){
            ifs >> num >> amount;
            for (size_t i = 0; i < t_account_vec.size(); i++){
                if (t_account_vec[i].getAccount() == num){
                    t_account_vec[i].withdraw(amount);
                    break;
                }
            }
        }
        if (command == "Deposit"){
            ifs >> num >> amount;
            for (size_t i = 0; i < t_account_vec.size(); i++){
                if (t_account_vec[i].getAccount() == num){
                    t_account_vec[i].deposit(amount);
                    break;
                }
            }
        }
    }
    ifs.close();
    for (size_t i = 0; i < t_account_vec.size(); i++){
        cout << t_account_vec[i] << endl;
    }
    

    cout << "==============\n"
         << "\nTask 4:\nTransaction nested in public section of Account:\n";
    ifs.open("transactions.txt");
    t_account_vec.clear();
    while (ifs >> command){
        if (command == "Account"){
            ifs >> name >> num;
            t_account_vec.emplace_back(name, num);
        }
        if (command == "Withdraw"){
            ifs >> num >> amount;
            for (size_t i = 0; i < t_account_vec.size(); i++){
                if (t_account_vec[i].getAccount() == num){
                    t_account_vec[i].withdraw(amount);
                    break;
                }
            }
        }
        if (command == "Deposit"){
            ifs >> num >> amount;
            for (size_t i = 0; i < t_account_vec.size(); i++){
                if (t_account_vec[i].getAccount() == num){
                    t_account_vec[i].deposit(amount);
                    break;
                }
            }
        }
    }
    ifs.close();
    for (size_t i = 0; i < t_account_vec.size(); i++){
        cout << t_account_vec[i] << endl;
    }

    
    cout << "==============\n"
         << "\nTask 5:\nTransaction nested in private section of Account:\n";
    ifs.open("transactions.txt");
    t_account_vec.clear();
    while (ifs >> command){
        if (command == "Account"){
            ifs >> name >> num;
            t_account_vec.emplace_back(name, num);
        }
        if (command == "Withdraw"){
            ifs >> num >> amount;
            for (size_t i = 0; i < t_account_vec.size(); i++){
                if (t_account_vec[i].getAccount() == num){
                    t_account_vec[i].withdraw(amount);
                    break;
                }
            }
        }
        if (command == "Deposit"){
            ifs >> num >> amount;
            for (size_t i = 0; i < t_account_vec.size(); i++){
                if (t_account_vec[i].getAccount() == num){
                    t_account_vec[i].deposit(amount);
                    break;
                }
            }
        }
    }
    ifs.close();
    for (size_t i = 0; i < t_account_vec.size(); i++){
        cout << t_account_vec[i] << endl;
    }
}
