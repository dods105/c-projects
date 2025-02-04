#include <iostream>
#include <string>
#include <vector>
#include <fstream>

class ToDoTask{

    public:
    std::fstream TaskFile;

    ToDoTask() {
    TaskFile.open("ToDoList.txt", std::ios::in | std::ios::out | std::ios::app);
        if (!TaskFile.is_open()) {
            std::cerr << "Failed to open the file!\n";
        }else{
            TaskFile.close();
        }
    }

    std::vector<std::string> tasks;
    void Add();
    void Delete();
    void Show();
    void Edit();
    void SaveTasks();
};

void ToDoTask::Add(){
    Show();
    int size;
    while(true){
        std::cout << "How many task do you want to add: ";
        std::cin >> size;
        
        if(std::cin.fail()){
            std::cout << "Invalid Input. Type a number\n";
            std::cin.clear();
            std::cin.ignore(INT_MAX, '\n');
        }
        else{
            break;
        }
    }
    std::cin.ignore();
    std::string task;

    for(int i = 0; i < size; i++){
        std::cout << "Add Task: ";
        getline(std::cin, task);
        tasks.push_back(task);
    }
    SaveTasks();
    Show();
    system("PAUSE");
}

void ToDoTask::Delete(){
    Show();
    int size, index;
    while(true){
        std::cout << "How many task do you want to remove: ";
        std::cin >> size;
        
        if(std::cin.fail()){
            std::cout << "Invalid Input. Type a number\n";
            std::cin.clear();
            std::cin.ignore(INT_MAX, '\n');
        }
        else{
            break;
        }
    }

    std::cin.ignore();

    for (int i = 0; i < size; i++){
        Show();
        std::cout << "Type the number of the task you want to delete: ";
        std::cin >> index;
        tasks.erase(tasks.begin() + (index-1));
    }
    SaveTasks();
    Show();
    system("PAUSE");
}

void ToDoTask::Edit(){
    Show();
    size_t index;
    while (true)
    {
        std::cout << "Which number of the task you want to edit: ";
        std::cin >> index;
        if(index > tasks.size()){
            std::cout << "Task does not exist\n";
            std::cin.clear();
        }
        else{
            break;
        }
    }
    std::cin.ignore();
    std::string task;
    std::cout << index << ". " << tasks[index-1] <<"\n";
    std::cout << "Edit: ";
    getline(std::cin, task);
    tasks[index-1] = task;

    SaveTasks();
    Show();

}

void ToDoTask::Show(){
    std::cout << "\t\t\t\tTo-Do List\n\n";
    std::string line;
    tasks.clear();
    TaskFile.open("ToDoList.txt", std::ios::in);
    while(getline(TaskFile, line)){
        tasks.push_back(line);

    }
    TaskFile.close();

    for (size_t i = 0; i < tasks.size(); ++i) {
        std::cout << "\t\t\t\t" << i + 1 << ". " << tasks[i] << "\n";
    }
    std::cout << "\n";
}

void ToDoTask::SaveTasks() {
    if (TaskFile.is_open()) {
        TaskFile.close();
    }

    TaskFile.open("ToDoList.txt", std::ios::out | std::ios::trunc);
    if (!TaskFile.is_open()) {
        std::cerr << "Failed to open the file!\n";
        return;
    }

    for (const auto &task : tasks) {
        TaskFile << task << "\n";
    }

    TaskFile.close();
}

bool CheckContent(){
    std::fstream File("ToDoList.txt", std::ios::in);
    File.seekg(0, std::ios::end);
    if(File.tellg() == 0){
        File.close();
        return false;
    }
    
    File.close();
    return true;

}

int main(){

    ToDoTask taskList;

    int option;

    while(true){
        std::cout << "\t\t\t\tMenu\n";
        std::cout << "\t\t\t\t1. Add Task\n\t\t\t\t2. Delete task\n\t\t\t\t3. Edit\n\t\t\t\t4. Show Tasks\n\n";
        while(true){
        std::cout << "Type what to perform: ";
        std::cin >> option;;
        
        if(std::cin.fail()||option < 1 ||option > 4){
            std::cout << "Invalid Input. Type a number from the Menu\n";
            std::cin.clear();
            std::cin.ignore(INT_MAX, '\n');
        }
        else{
            break;
        }
    }
        switch (option)
        {
        case 1:
            taskList.Add();
            break;
        case 2:
            if(CheckContent()){
                taskList.Delete();
            }
            else{
                std::cout << "Tasks is empty. Cannot remove any element\n\n";
            }
            break;
        case 3:
            if(CheckContent()){
                taskList.Edit();
            }
            else{
                std::cout << "Cannot be edited. Tasks is empty\n\n";
            }
            break;
        case 4:
            if(CheckContent()){
                taskList.Show();
            }
            else{
                std::cout << "Tasks is empty. Add a task\n\n";
            }
            break;
        }

    }
    
    return 0;
}