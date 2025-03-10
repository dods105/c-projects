#include <iostream>
#include <fstream>
#include <string>

class RegistrationSystem{
    std::string Name;
    std::string password;
    
    public:
    void registration();
    bool LogIn();
    bool verifyPassword(std::string name);
    bool existName(std::string userName);
    void menu();
    
};

void RegistrationSystem::registration(){
    std::cout << "Sign Up\n\n";

    std::cout << "Name: ";
    getline(std::cin, Name);
    std::cout << "Password: ";
    getline(std::cin, password);

   std::string credits = Name + ".txt";

    std::fstream user(credits, std::ios::out);
    user << password << "\n";
    user.close();

    std::cout << "Account created successfully.\n";
}

bool RegistrationSystem::LogIn(){
    std::cout << "LOG IN\n\n";

    std::string nameHolder;
    std::string passHolder;

    while(true){
        std::cout << "Type (1) to go back to Menu\n\n";
        std::cout << "Enter name: ";
        getline(std::cin, nameHolder);
        if(nameHolder == "1"){
            break;
        }
        int log = existName(nameHolder);
        int passkey;

        if(log){
            nameHolder += ".txt";
            passkey = verifyPassword(nameHolder);
        }

        if(passkey == 1){
            std::cout << "Log In Successful\n\n";
            return 1;
        }
        else{
            std::cout << "Incorrect Password\n\n";
        }
    }
    return 0;
}

bool RegistrationSystem::verifyPassword(std::string name){
    std::string userPassword;
    std::fstream userFile(name, std::ios::in); // open in read mode
    getline(userFile, userPassword);

    std::string passwordHolder;
    std::cout << "Type your password: ";
    getline(std::cin, passwordHolder);

    return (userPassword == passwordHolder)? 1 : 0;
}

bool RegistrationSystem::existName(std::string userName){
    userName += ".txt";
    std::fstream name(userName);

    if(!name.is_open()){
        std::cerr << "Account does not exists.\n";
        return 0;
    }
    
    return 1;
}

void RegistrationSystem::menu(){
    int choice, log; 
    while(true){
        std::cout << "\t\t\t\t(1). Sign Up\n\t\t\t\t(2). Log In\n\n";
        std::cin >> choice;
        std::cin.ignore();

        if(choice > 0 && choice < 3){
            break;
        }

    }
    switch (choice){
        case 1:
            registration();
            break;
        case 2:
            log = LogIn();
            break;
    }
}

int main(){

    RegistrationSystem user;
    while(true){
        user.menu();
    }


    return 0;
}