#include <iostream>
#include <string>
#include <vector>
#include <fstream>

class Institution{

    protected:
    std::fstream programOffered;
    std::string programName;
    bool programFound = false;

    public:
    Institution(){
        programOffered.open("CoursesOffered.txt", std::ios::out | std::ios::in | std::ios::app);
    }

    ~Institution(){
        if(programOffered.is_open()){
            programOffered.close();
        }
    }

    void viewOfferedProgram();
    void addProgram();
    void removeProgram();
};

void Institution::addProgram(){
    int number;
    std::cout << "Type how many Program to Add: ";
    std::cin >> number;
    std::cin.ignore();

    std::cout << "Adding Courses\n";
    for(; number > 0; number--){
        std::cout << "Course name: ";
        getline(std::cin, programName);
        programOffered << programName << "\n";
    }
}

void Institution::viewOfferedProgram(){
    std::cout << "\nOffered Program:\n\n";
    int i = 1;
    while(getline(programOffered, programName)){
        std::cout << i << ". " << programName << "\n";
        i++;
    }
    std::cout << "\n\n";

    system("pause");
}

void Institution::removeProgram(){

    std::vector<std::string> programs;
    std::string program;
    std::cout << "Program to Remove: ";
    getline(std::cin, program);

    while(getline(programOffered, programName)){
        if(program != programName){
            programs.push_back(programName);
        }
        else{
            programFound = true;
        }
    }

    programOffered.close();
    programOffered.open("CoursesOffered.txt", std::ios::out | std::ios::trunc);

    for(const auto &i: programs){
        programOffered << i << "\n";
    }

    if(programFound){
        std::cout << program << " has now been removed\n";
    }
    else{
        std::cerr << "Program not found\n";
    }

    programOffered.close();
    programOffered.open("CoursesOffered.txt", std::ios::out | std::ios::in | std::ios::app);   programFound = false;

    system("pause");
}

class Student: public Institution{

    private:
    std::string studentName;
    int StudentYear;
    std::string year;
    std::string EnrolledProgram;
    bool EnrollmentStatus = true;
    std::fstream studentList, studentProgram, studentYear;
    bool programFound = false;
    std::string name;


    public:
    Student(){
        studentList.open("StudentList.txt", std::ios::out | std::ios::in | std::ios::app);
        studentProgram.open("StudentProgram.txt", std::ios::out | std::ios::in | std::ios::app);
        studentYear.open("StudentYear.txt", std::ios::out | std::ios::in | std::ios::app);
    }

    ~Student(){
        if(studentList.is_open()){
            studentList.close();
        }
        if(studentProgram.is_open()){
            studentProgram.close();
        }
        if(studentYear.is_open()){
            studentYear.close();
        }
    }

    void registerStudent();
    void SeeStudentInformation();
    void ModifyStudentInfo();
    void viewEnrolledStudents();

};

void Student::registerStudent(){
    std::cout << "Student Name: ";
    getline(std::cin, name);

    while(getline(studentList, studentName)){
        if(studentName == name){
            std::cerr << "Cannot Register Student. This Student is Already Enrolled.\n";
            break;
        }

    }

    studentList.close();

    std::cout << "Student Year: ";
    std::cin >> StudentYear;
    std::cin.ignore();

    switch (StudentYear)
    {
    case 1:
        year = "1st Year";
        break;
    case 2:
        year = "2nd Year";
        break;
    case 3:
        year = "3rd Year";
        break;
    case 4:
        year = "4th Year";
        break;
    case 5:
        year = "5th Year";
        break;
    }

    std::cout << "See list of Programs?\n\t\t(1). yes\n\t\t(2). no\n\n";
    int decision;
    std::cin >> decision;
    std::cin.ignore();

    if(decision == 1){
        viewOfferedProgram();
    }

    std::cout << "Type Which Program to Enroll: ";
    getline(std::cin, EnrolledProgram);

    while(getline(programOffered, programName)){
        if(programName == EnrolledProgram){
            programFound = true;
            break;
        }
    }

    if(programFound){
        studentList.open("StudentList.txt", std::ios::app);
        studentList << name << "\n";
        studentProgram << EnrolledProgram << "\n";
        studentYear << year << "\n";

        std::cout << name << " is now enroll as a " << year << " of the " << EnrolledProgram << "\n"; 
    }
    else{
        int again;
        std::cerr << "Program is not offered.\n";
        std::cout << "Try Registering Again?\n\t(1). Yes\n\t(2). Exit\n";
        std::cin >> again;
        std::cin.ignore();

        if(again == 1){
            registerStudent();
        }
    }
    studentList.open("StudentList.txt", std::ios::out | std::ios::in | std::ios::app);
    system("PAUSE");
    system("CLS");

}

void Student::SeeStudentInformation(){
    std::string record;
    std::cout << "Student Name: ";
    getline(std::cin, studentName);

    std::cout << "Student Information: \n";

    int tracker = 0;
    while(getline(studentList, name) && getline(studentYear, year) && getline(studentProgram, EnrolledProgram)){
        if(name == studentName){
            record = "Name: " + studentName + "\t\t\tProgram: " + EnrolledProgram + "\t\t\tYear:" + year + "\n";
            tracker = 1;
            break;
        }
    }

    if(!tracker){
        std::cout << studentName << " is not Enrolled\n";
    }else{
        std::cout << record;
    }

    system("PAUSE");
    system("CLS");

}

void Student::viewEnrolledStudents(){
    std::cout << "\nEnrolled Students:\n";
    while(getline(studentList, studentName) && getline(studentYear, year) && getline(studentProgram, EnrolledProgram)){
        std::cout << "Name: " + studentName + "\t\t\tProgram: " + EnrolledProgram + "\t\t\tYear:" + year + "\n";
    }

    system("PAUSE");
    system("CLR");
}

void Student::ModifyStudentInfo(){
    std::cout << "Enter Student Name: ";
    int mod;
    std::string mName, mYear, mProgram, changes;
    std::fstream modifiedName("name.txt", std::ios::out), modifiedProgram("program.txt", std::ios::out), modifiedYear("year.txt", std::ios::out);
    getline(std::cin, name);

    std::cout << "(1). Student Name\n(2). Student Program\n(3). Student Year\nWhat to modify: ";
    std::cin >> mod;
    std::cin.ignore();
    std::cout << "Modification: ";
    getline(std::cin, changes);

    switch(mod){
        case 1:
            mName = changes;
            break;
        case 2:
            mProgram = changes;
            break;
        case 3:
            mYear = changes;
            break;
    }
    
    while(getline(studentList, studentName) && getline(studentYear, year) && getline(studentProgram, EnrolledProgram)){
        if(studentName != name){
            modifiedName << studentName << "\n";
            modifiedProgram << EnrolledProgram << "\n";
            modifiedYear << year << "\n";
        }
        else{
            switch(mod){
            case 1:
                modifiedName << mName << "\n";
                modifiedProgram << EnrolledProgram << "\n";
                modifiedYear << year << "\n";
                break;
            case 2:
                modifiedName << studentName << "\n";
                modifiedProgram << mProgram << "\n";
                modifiedYear << year << "\n";
                break;
            case 3:
                modifiedName << studentName << "\n";
                modifiedProgram << EnrolledProgram << "\n";
                modifiedYear << mYear << "\n";
                break;
            }
        }
    }

    studentList.close();
    studentProgram.close();
    studentYear.close();
    modifiedName.close();
    modifiedProgram.close();
    modifiedYear.close();

    std::remove("StudentList.txt");
    std::remove("StudenProgram.txt");
    std::remove("StudentYear.txt");

    std::rename("name.txt","StudentList.txt");
    std::rename("program.txt","StudenProgram.txt");
    std::rename("year.txt","StudentYear.txt");

    std::remove("name.txt");
    std::remove("program.txt");
    std::remove("year.txt");
    
    studentList.open("StudentList.txt", std::ios::out | std::ios::in | std::ios::app);
    studentProgram.open("StudentProgram.txt", std::ios::out | std::ios::in | std::ios::app);
    studentYear.open("StudentYear.txt", std::ios::out | std::ios::in | std::ios::app);

    system("Pause");
}

int main(){
    bool operate = true;
    while(operate){
        std::cout << "\n\t\t_______________________\n\n";
        std::cout << "\t\t(1). Add Program\n\t\t(2). View Programs\n\t\t(3). Remove Program\n\t\t(4). Enroll Student\n\t\t(5). Get Student Info\n\t\t(6). View Enrolled Students\n\t\t(7) Modify Student Info\n\t\t(8). Exit";
        std::cout << "\n\t\t_______________________\n\n";

        char operation;
        std::cout << "Type what to perform: ";
        std::cin >> operation;
        std::cin.ignore();

        Institution univ;
        Student s;

        switch (operation)
        {
        case '1':
            univ.addProgram();
            break;
        case '2':
            univ.viewOfferedProgram();
            break;
        case '3': 
            univ.removeProgram();
            break;
        case '4':
            s.registerStudent();
            break;
        case '5':
            s.SeeStudentInformation();
            break;
        case '6':
            s.viewEnrolledStudents();
            break;
        case '7':
            s.ModifyStudentInfo();
            break;
        case '8':
            operate = false;
            break;
        }
    }


    return 0;
}