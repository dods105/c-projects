#include <iostream>
#include <string>
using namespace std;

class BankAccount{

    private:
    string Name;
    int Pin;
    float Balance;

    bool ConfirmPin(){
        int pinEntered;
        cout << "Enter Pin Code: ";
        cin >> pinEntered;

        if(Pin == pinEntered){
            return true;
        }
        else{
            cout << "Wrong Pin\n";
            return false;
        }
    }

    public:
    BankAccount(string name, int pin, int balance){
        Name = name;
        Pin = pin;
        Balance = balance;
    }

    void GetInfo(){
        cout << "Name: " << Name << endl;
        cout << "Balance: " << Balance << endl;
    }

    void BalanceInfo(){
        cout << "Your current balance is " << Balance  << " Pesos\n";
    }

    void Withdraw(){
        float amount;
        char retry;

        cout << "WITHDRAW\n";
        
        if (ConfirmPin()){
            BalanceInfo();
            cout << "Enter how much to withdraw: ";
            cin >> amount;
            if (Balance >= amount){
                Balance -= amount;
                cout << "Withdraw Successful\n"; 
                BalanceInfo();
            }
            else{
                cout << "Unsuccessful withdrawal\n";
                cout << "You do not have enough remaining balance\n";
                BalanceInfo();
                cout << "Would you like to withdraw with your current balance?\n(Y)es or (N)o: ";
                cin >> retry;

                if(retry == 'Y'){
                    Withdraw();
                }
            }
        }
    }

    void Deposit(){
        int amount;
        BalanceInfo();
        cout << "DEPOSIT\n";
        if(ConfirmPin()){
            cout << "How much do you want to deposit: ";
            cin >> amount;
            Balance += amount;
            cout << amount << " has been successfully deposited\n";
            BalanceInfo();
        }
    }

};

int main(){

    BankAccount user1("Stacy", 5669, 88);
    user1.Deposit();
    user1.Withdraw();
    user1.GetInfo();

    

    return 0;
}