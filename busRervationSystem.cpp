#include <iostream>
#include <vector>
#include <string>

int busAvailable = 0;
void afterInput(){
    std::cin.ignore();
    std::cin.clear();
}

class Bus {
    private:
    std::string name, from, to;
    int fair, timeDeparture, seatAvailable = 50, numOfPassenger, busNum;

    public:
    void installBus();
    void show();
    void book();
    void exit();
};

std::vector<Bus> buses;

void Bus::installBus() {
    std::cout << "Bus Number: ";
    std::cin >> busNum;
    afterInput();
    std::cout << "From: ";
    std::cin >> from;
    afterInput();
    std::cout << "To: ";
    std::cin >> to;
    afterInput();
    std::cout << "Time of Depature: ";
    std::cin >> timeDeparture;
    afterInput();

    busAvailable++;
    system("PAUSE");
    system("CLS");
}

void Bus::show() {
    for (int i = 0; i < busAvailable; i++) {
        std::cout << "Bus Number: #" << buses[i].busNum << "\n";
        std::cout << "From: " << buses[i].from << "\n";
        std::cout << "To: " << buses[i].to << "\n";
        std::cout << "Time of Departure: " << buses[i].timeDeparture << " O'clock\n";
        std::cout << "Available seat: " << buses[i].seatAvailable << "\n";
    }
    system("PAUSE");
    system("CLS");
}

void Bus::book() {
    int busNumber, seatNum;
    do{
        std::cout << "Enter Bus No: ";
        std::cin >> busNumber;
        if(std::cin.fail()){
            std::cout << "Enter a valid number\n";
            afterInput();
        }
    }while(std::cin.fail());
    int i = 0;
    while (i < busAvailable) {
        if (buses[i].busNum == busNumber) {
            if (buses[i].seatAvailable <= 0) {
                std::cout << "There are no more available seats.\n";
            }
            if (buses[i].seatAvailable > 0) {
                std::cout << "Seats Available: " << buses[i].seatAvailable << "\n";
                std::cout << "Passenger Name: ";
                afterInput();
                std::getline(std::cin, name);
                do {
                    while(true){
                        std::cout << "Number of seats: ";
                        std::cin >> seatNum;
                        if(std::cin.fail()){
                            std::cout << "Enter a valid number\n";
                            afterInput();
                        }else{
                            break;
                        }
                    }
                } while (buses[i].seatAvailable - seatNum < 0);
                buses[i].seatAvailable -= seatNum;
                buses[i].numOfPassenger = seatNum;
            }
            break;
        }
        i++;
    }
    std::cout << "Purchase Completed\n";
    std::cout << "Passenger Name: " << name << "\n";
    std::cout << "Bus No: #" << buses[i].busNum << "\n";
    std::cout << "From: " << buses[i].from << "\n";
    std::cout << "Destination: " << buses[i].to << "\n";
    std::cout << "Time of Departure: " << buses[i].timeDeparture << "\n";
    std::cout << "Seats: " << buses[i].numOfPassenger << "\n";

    system("PAUSE");
    system("CLS");
}

int main() {
    bool operate = true;
    int option;
    while (operate) {
        std::cout << "\n\n\t\t\t\t===================================================" << std::endl;
        std::cout << "\t\t\t\t\t\tBus Ticketing System\n";
        std::cout << "\t\t\t\t===================================================" << std::endl;

        do {
            std::cout << "\t\t\t\t\t 1 => Install\n\t\t\t\t\t 2 => List Available Bus\n\t\t\t\t\t 3 => Book Tickets\n\t\t\t\t\t 4 => Exit";
            std::cout << "\n\n\t\t\t\t\t Enter your choice: ";
            std::cin >> option;
        } while (option < 1 || option > 4);

        switch (option) {
        case 1: {
            Bus newBus;
            newBus.installBus();
            buses.push_back(newBus);
            break;
        }
        case 2:
            if (!buses.empty()) {
                buses[0].show();
            }
            else{
                std::cout << "Sorry. There is no available bus\n";
            }
            break;
        case 3:
            if (!buses.empty()) {
                buses[0].book();
            }
            else{
                std::cout << "Sorry. There is no available bus\n";
            }
            break;
        case 4:
            operate = false;
        }
    }
    return 0;
}
