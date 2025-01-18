#include <iostream>
#include <string>
#include <algorithm>
#include <cstdlib>

std::string GeneratePassword(size_t length, std::string hasLetters="Y", std::string hasNumbers="N", std::string hasPunctuation="N"){

    std::string letters = "QWERTYUIOPASDFGHJKLZXCVBNMqwertyuiopasdfghjklzxcvbnm";
    std::string numbers = "1234567890";
    std::string punctuation = "!\"#$%&'()*+,-./:;<=>?@[\]^_`{|}~";

    std::string password = "";

    while (password.size() < length){
        int getLetterIndex = rand() % letters.length();
        char randomLetter = letters[getLetterIndex];
        int getNumberIndex = rand() % numbers.length();
        char randomNumber = numbers[getNumberIndex];
        int getPuncIndex = rand() % punctuation.length();
        char randomPunc = punctuation[getPuncIndex];

        if(hasLetters == "Y" && hasNumbers == "Y" && hasPunctuation == "Y"){
            password += randomLetter;
            password += randomNumber;
            password += randomPunc;
        }
        else if(hasLetters == "Y" && hasNumbers == "Y" && hasPunctuation == "N"){
            password += randomLetter;
            password += randomNumber;
        }
        else if(hasLetters == "N" && hasNumbers == "Y" && hasPunctuation == "Y"){
            password += randomLetter;
            password += randomPunc;
        }
        else if(hasLetters == "N" && hasNumbers == "Y" && hasPunctuation == "Y"){
            password += randomNumber;
            password += randomPunc;
        }
        else if(hasLetters == "N" && hasNumbers == "Y" && hasPunctuation == "N"){
            password += randomNumber;
        }
        else if(hasLetters == "N" && hasNumbers == "N" && hasPunctuation == "Y"){
            password += randomPunc;
        }
        else{
            password += randomLetter;
        }
    }

    return password;

}

int main(){
    srand(time(0));

    std::string hasLetters = "Y", hasNumbers, hasPunctuation;
    int length;

    std::cout << "Length for the password: ";
    std::cin >> length;
    std::cout << "Do you want to include letters (Y) or (N): ";
    std::cin >> hasLetters;
    std::cout << "Do you want to include numbers (Y) or (N): ";
    std::cin >> hasNumbers;
    std::cout << "Do you want to include punctuation (Y) or (N): ";
    std::cin >> hasPunctuation;

    std::transform(hasLetters.begin(), hasLetters.end(), hasLetters.begin(), ::toupper);
    std::transform(hasNumbers.begin(), hasNumbers.end(), hasNumbers.begin(), ::toupper);
    std::transform(hasPunctuation.begin(), hasPunctuation.end(), hasPunctuation.begin(), ::toupper);

    std::string password = GeneratePassword(length, hasLetters, hasNumbers, hasPunctuation);

    std::cout << "Your Password is: " << password;


}