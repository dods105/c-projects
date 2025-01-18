#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int Menu();

void design(string text){
    cout << "\n";
    size_t i = 0, j = i;
    while (i < text.size()){
        cout << "=";
        i++;
    }
    cout << endl << text << endl;
    while (j < text.size()){
        cout << "=";
        j++;
    }
    cout << endl << endl;
}

class Bank{

    private:
    int AccountNumber;
    string Name;
    int Pin;
    int Balance;

    void CreatePin(){
        cout << "Enter Pin: ";
        cin >> Pin;
    }

    bool PinChecker(){
        int enteredPin;
        cout << "Enter PIN: ";
        cin >> enteredPin;
        if (enteredPin == Pin){
            return true;
        }
        else{
            return false;
        }
    }

    public:
    Bank(int accountNo, string name){
        AccountNumber = accountNo;
        Name = name;
        cout << "\t"; 
        CreatePin();
        cout << "\t";
        cout << "Enter amount to be deposited: ";
        cin >> Balance;
    }

    void ResetPin(){
        design("RESET PIN");
        cout << "\nYou have 3x to enter your old pin.\nIf you have reached the maximum, your account will be put on hold\n";

        int tempPin, finalPin;

        for(int attempt = 1; attempt <= 4; attempt++){
            if (attempt == 4){
                OnHoldText();
                break;
            }
            if (PinChecker()){
                while(true){
                    cout << "Enter New Pin: ";
                    cin >> tempPin;
                    cout << "Enter Pin Again to Confirm: ";
                    cin >> finalPin;
                    if(tempPin == finalPin){
                        Pin = finalPin;
                        cout << "Password Changed\n";
                        break;
                    }
                }
                break;
            }
        }
    }

    void OnHoldText(){
        cout << "You have reached the maximum trial to enter your Password. Your accouont will be put on hold\n";
    }

    void Inquiry(){
        design("ACCOUNT INQUIRY");
        cout << endl;
        cout << "\tName: " << Name << endl;
        cout << "\tAccount Number: " << AccountNumber << endl; 
        cout << "\tBalance: " << Balance << "\n\n";
    }

    void Deposit(){
        int deposit;
        design("DEPOSIT");

        if (PinChecker()){
            cout << "\nEnter how much to deposit: ";
            cin >> deposit;
            Balance += deposit;
            cout << endl << deposit << " pesos has been deposited in your account.\n";
        }
    }

    void Withdraw(){
        int withdraw;
        design("WITHDRAW");

        for(int attempt = 1; attempt <= 4; attempt++){
            if (attempt == 4){
                OnHoldText();
                break;
            }
            if(PinChecker()){
                cout << "Enter how much to withdraw: ";
                cin >> withdraw;

                if (Balance >= withdraw){
                    Balance -= withdraw;
                    cout << "Withdrawal Successful\n";
                    Inquiry();
                }
                else{
                    cout << "Withdrawal Unsuccessful\n";
                    Inquiry();
                }
                break;
            }
        }
    }

    void SendMoney(){
        design("SEND MONEY");
        int receiverAccountNumber, amount;
        string confirm = "Y";

        if (PinChecker()){
            cout << "\nEnter Account No. to send money to: ";
            cin >> receiverAccountNumber;

            while(confirm == "Y"){
                cout << "Enter amount to send: ";
                cin >> amount;
                transform(confirm.begin(), confirm.end(), confirm.begin(), ::toupper);
                if(Balance >= amount){
                    Balance-= amount;
            
                    cout << endl << amount << " has been sent to Account No. " << receiverAccountNumber << endl;
                    cout << amount << " was deducted from your balance\n";
                    cout << "Your remaining balance: " << Balance << endl;
                    break;
                }
                else{
                    cout << "\nYou have insufficient balance.\n";
                    cout << "Your remaining balance: " << Balance << endl;
                    cout << "Would you like to send with your current balance (Y) or (N): ";
                    cin >> confirm;
                }
            }
        }
        Menu();
    }

};

int Menu(){
    int option = 0;

        cout << "Menu: \n";
        cout << "\t(1) Check Inquiry\n";
        cout << "\t(2) Deposit\n";
        cout << "\t(3) Withdraw\n";
        cout << "\t(4) Send Money\n";
        cout << "\t(5) Change Pin Code\n";
        cout << "\t(6) Close Account\n\n";

        cout << "Type the number of operation you would like to perform: ";
        cin >> option;

    return option;
}

int main(){

    string openAccount;
    int option, accountNumber;
    string name;

    design("BANKING SYSTEM");
    cout << "Welcome to Stacy's Bank\n";
    cout << "Open a bank account (Y) or (N): ";
    cin >> openAccount;

    transform(openAccount.begin(), openAccount.end(), openAccount.begin(), ::toupper);

    if (openAccount == "Y"){
        design("ACCOUNT CREATION");
        cout << "Create Account: \n\n";
        cout << "\tEnter Account No: ";
        cin >> accountNumber;
        int * accNo = &accountNumber;
        cin.ignore();

        cout << "\tEnter Name: ";
        getline(cin, name);

        Bank accountNumber(*accNo, name);

        cout << "\nThank you for opening an account!\n";
        bool menuOn = true;

        while (menuOn){
            option = Menu();

            if (option == 1){
                accountNumber.Inquiry();
            }
            else if (option == 2){
                accountNumber.Deposit();
            }
            else if (option == 3){
                accountNumber.Withdraw();
            }
            else if(option == 4){
                accountNumber.SendMoney();
            }
            else if (option == 5){
                accountNumber.ResetPin();
            }

            char decision;

            cout << "Would you like to see the Menu (Y) or (N): ";
            cin >> decision;

            if (decision == 'n' or decision == 'N'){
                menuOn = false;
            }
        }
    }
    
    cout << "Thank You for coming to Stacy's Bank\n";
    
    return 0;
}