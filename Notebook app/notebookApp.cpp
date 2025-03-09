#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <cstdio>

class Notebook{
    std::string Title;
    int Day, Month, Year;
    std::string Notes, FullNote;
    bool returnMenu = 0;

public:
    void addEntry();
    void editEntry();
    void deleteEntry();
    void showEntry();
};

void Notebook::showEntry(){
    std::cin.ignore();
    while(true){
        std::cout << "Type (1) to go back to Menu.\n";
        std::cin.clear();
        std::cout << "Enter the Title Of The Page: ";
        getline(std::cin, Title);

        if(Title == "1"){
            break;
        }

        Title+= ".txt";

        std::fstream pageTitle(Title, std::ios::in); //in -> read mode
        if(pageTitle.is_open()){
            std::string lines;

            std::cout << "\nReading from " << Title << ":\n";
            while (std::getline(pageTitle, lines)) {
                std::cout << lines << '\n';
            }
            pageTitle.close();
            break;
        }
        else{
            std::cerr << "Title does not exist.\n";
        }
    }

    system("PAUSE");

}

void Notebook::addEntry(){
    std::fstream pageTitle;
    bool exists = 0;
    while (!exists)
    {
        std::cout << "Type (1) to go back to Menu.\n";
        std::cin.ignore();
        std::cout << "Page Title: ";
        getline(std::cin, Title);

        if(Title == "1"){
            system("PAUSE");
        }

        Title += ".txt";
        pageTitle.open(Title);

        if(pageTitle.is_open()){
            std::cerr << "Note \"" + Title + "\" is already created.\n\n"; 
        }
        else{
            break;
        }
    }

    pageTitle.open(Title, std::ios::out); //out -> write mode
    std::cout << "notes: \n";
    while(true){
        getline(std::cin, Notes);

        if("END" == Notes){
            break;
        }

        FullNote += Notes + "\n";
    }

    pageTitle << FullNote;
    pageTitle.close();
    std::cout << "Notes now written." << "\n";

    system("PAUSE");

}

void Notebook::deleteEntry(){
    while(true){
        std::cout << "Type (1) to go back to Menu\n\n";
        std::cin.clear();
        std::cout << "Type Title of Note to Delete: ";
        getline(std::cin, Title);
        if(Title == "1"){
            returnMenu = 1;
            break;
        }
        Title += ".txt";
        std::fstream file(Title);
        if(file.is_open()){
            file.close();
            break;
        }
        else{
            std::cerr << "Note does not exist.\n\n";
        }
    }

    if(!returnMenu){
        if(remove(Title.c_str()) == 0){
            std::cout << "Note \"" + Title + "\" successfully deleted\n";
        }
        else{
            std::cout << "failed to delete \"" + Title + "\n\n";
        }
    }
    system("Pause");
}

int main(){
    while(true){
        char operation;
        while(true){
            std::cout << "\t\t\t\t(1) Add Notes\n\t\t\t\t(2) Read Notes\n\t\t\t\t(3) Delete Notes\n\n";
            std::cout << "Type what to perform: ";
            std::cin >> operation;
            if(operation == '1' || operation == '2' || operation == '3'){
                break;
            }
            std::cout << "Invalid Operation\n\n";
            std::cin.clear();
        }

        Notebook notes;

        switch (operation)
        {
        case '1':
            notes.addEntry();;
            break;
        case '2':
            notes.showEntry();
            break;
        case '3':
            notes.deleteEntry();
        }
        
    }
}