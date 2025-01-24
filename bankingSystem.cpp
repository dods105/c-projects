#include <iostream>
#include <vector>
#include <string>
#include <cctype>

class BankSystem{
    private:
    std::string Name, PIN;
    int Balance, AccountNumber;

    public:
    void createAccount();
    void resetPIN(int index);
    bool validatePIN(std::string action, int index);
    void withdraw();
    void transferMoney();
    void deposit();
    int accountIndex(const std::vector<BankSystem>& accounts);
    bool isValidPIN(std::string PIN);

};

std::vector<BankSystem> accounts;

bool BankSystem::isValidPIN(std::string PIN){
    if (PIN.length() == 4) {
        for (char c : PIN) {
            if (!isdigit(c)) {
                return false;
            }
        }
    }
    else{
        return false;
    }
    return true;
}

void BankSystem::resetPIN(int index){
    
    std::string PIN1, PIN2;
    bool operate = validatePIN("reset PIN", index);
    while(operate){
        do{
            std::cout << "Type new PIN: ";
            std::cin >> PIN1;
            if(isValidPIN(PIN1) == false){
                std::cout << "PIN must be 4 numberic character long.\n";
                std::cin.clear();
            }
        } while(isValidPIN(PIN1) == false);

        do{
            std::cout << "Confirm new PIN: ";
            std::cin >> PIN2;
            if(isValidPIN(PIN2) == false){
                std::cout << "PIN must be 4 numberic character long.\n";
                std::cin.clear();
            }
        } while(isValidPIN(PIN1) == false);

        if(PIN1 == PIN2){
            accounts[index].PIN = PIN1;
            break;
        }
        else{
            std::cout << "PIN does not match\n";
        }
    } 
    system("PAUSE");
    system("CLS");
}


int BankSystem::accountIndex(const std::vector<BankSystem>& accounts){
    int accountHolder;

    do{
        std::cout << "Account No. # ";
        std::cin >> accountHolder;
        if(std::cin.fail()){
            std::cout << "Enter your four numberic character account number\n";
            std::cin.clear();
            std::cin.ignore();
        }
        else{
            std::cin.ignore();
        }

        for(size_t i = 0; i < accounts.size(); i++){
            if(accountHolder == accounts[i].AccountNumber){
                return i;
            }
        }

        std::cout << "Invalid Account Number\n";
    }while(true);
}

void BankSystem::createAccount(){
    do{
        std::cout << "Enter Account No: # ";
        std::cin >> AccountNumber;
        if(std::cin.fail()){
            std::cout << "Invalid Account Number.\n";
            std::cin.clear();
        }
    }while(std::cin.fail());

    std::cin.ignore();
    std::cout << "Enter Name: ";
    std::getline(std::cin, Name);

    do{
        std::cout << "Enter PIN: ";
        std::cin >> PIN;
        if(isValidPIN(PIN) == false){
            std::cout << "PIN must be 4 numberic character long.\n";
            std::cin.clear();
        }
    }while(isValidPIN(PIN) == false);
    
    std::cout << "Amount to deposit: ";
    std::cin >> Balance;

    system("PAUSE");
    system("CLS");
}

void BankSystem::deposit(){
    int amount;
    int index = accountIndex(accounts);
    if(validatePIN("desposit", index)){
        do{
            std::cout << "Enter money to deposit: ";
            std::cin >> amount;
            if(std::cin.fail() || accounts[index].Balance < 0){
                std::cout << "Deposit Unsuccessful. Try again\n";
                std::cin.clear();
            }
            else{
                accounts[index].Balance += amount;
                std::cout << "Money deposited.\nAvailable balance: " << accounts[index].Balance << "\n";
            }
        }while(std::cin.fail() || accounts[index].Balance < 0);
    }
    std::cin.ignore();
    system("PAUSE");
    system("CLS");
}

void BankSystem::withdraw(){
    int amount;
    int index = accountIndex(accounts);
    if(validatePIN("withdraw", index)){
        do{
            std::cout << "Current Balance: " << accounts[index].Balance << "\n";
            std::cout << "Enter how much to withdraw: ";
            std::cin >> amount;
            if (std::cin.fail() || accounts[index].Balance - amount < 0){
                std::cout << "Withdrawal Unsuccessful. Try Again\n";
                std::cin.clear();
            }
            else{
                accounts[index].Balance -= amount;
                std::cout << "Withdrawal Successful\nYour current balance is: " << accounts[index].Balance << "\n";
                std::cin.ignore();
                break;
            }
        }while(1);
    }
    system("PAUSE");
    system("CLS");
}

bool BankSystem::validatePIN(std::string action, int index){
    std::string temp;
    int attempt = 0;
    bool valid = false;
    std::cout << "You have 3 attempts to validate your PIN\n";
    do{
        std::cout << "Enter PIN to " + action + "\n";
        std::cout << "PIN: ";
        std::cin >> temp;
        if(accounts[index].PIN == temp){
            valid = true;
            break;
        }
        else{
            std::cout << "PIN is Incorrect\n";
        }
        attempt++;
    }while(attempt < 3);
    return valid;
}

void BankSystem::transferMoney(){
    int ownerIndex = accountIndex(accounts);
    std::cout << "(Recipient) ";
    int amount;
    int recipientIndex = accountIndex(accounts);
    while(validatePIN("Transfer Money", ownerIndex)){
        std::cout << "Your current balance is " << accounts[ownerIndex].Balance << "\n";
        std::cout << "How much do you want to transfer: ";
        std::cin >> amount;
        if (std::cin.fail() || accounts[ownerIndex].Balance < amount){
            std::cout << "Transfer Unsuccessful\n";
            std::cin.clear();
        }
        else{
            accounts[ownerIndex].Balance -= amount;
            accounts[recipientIndex].Balance += amount;
            std::cout << "Transfer Successful\n";
            break;
        }
    }
    system("PAUSE");
    system("CLS");
}


int main(){

    bool operate = true;
    int option;
    while (operate) {
        std::cout << "\n\n\t\t\t\t===================================================" << std::endl;
        std::cout << "\t\t\t\t\t\tBanking Management System\n";
        std::cout << "\t\t\t\t===================================================" << std::endl;

        do {
            std::cout << "\t\t\t\t\t 1 => Create Account\n\t\t\t\t\t 2 => Deposit\n\t\t\t\t\t 3 => Withdraw\n\t\t\t\t\t 4 => Transfer Money\n\t\t\t\t\t 5 => Reset PIN\n\t\t\t\t\t 6 => Close Account\n\t\t\t\t\t 7 => Exit";
            std::cout << "\n\n\t\t\t\t\t Enter your choice: ";
            std::cin >> option;
        } while (option < 1 || option > 7);

        BankSystem bankAccount;

        switch (option) {
        case 1: 
            bankAccount.createAccount();
            accounts.push_back(bankAccount);
            break;
        case 2:
            if (!accounts.empty()){
                bankAccount.deposit();
            }
            else{
                std::cout << "There is no available account. Create one\n";
            }
            break;
        case 3:
            if (!accounts.empty()) {
                bankAccount.withdraw();
            }
            else{
                std::cout << "There is no available account. Create one\n";
            }
            break;
        case 4:
            if (!accounts.empty()) {
                bankAccount.transferMoney();
            }
            else{
                std::cout << "There is no available account. Create one\n";
            }
            break;
        case 5:
            if (!accounts.empty()) {
                int index = bankAccount.accountIndex(accounts);
                bankAccount.resetPIN(index);
            }
            else{
                std::cout << "There is no available account. Create one\n";
            }
            break;
        case 6:
            if (!accounts.empty()) {
                int index = bankAccount.accountIndex(accounts);
                if (index != -1) { //index != -1 -> index is not invalid
                    accounts.erase(accounts.begin() + index);
                }
            }
            else{
                std::cout << "There is no available account. Create one\n";
            }
            break;
        case 7:
            operate = false;
        }
    }
    return 0;
}