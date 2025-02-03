#include <iostream>
#include <string>
#include <vector>

class ToDoTask{

    public:
    std::vector<std::string> tasks;
    void Add();
    void Delete();
    void Show();
    void Edit();
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
    std::cout << "Test if loop skipped\n";
    for(int i = 0; i < size; i++){
        std::cout << "Add Task: ";
        getline(std::cin, task);
        tasks.push_back(task);
    }
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

    Show();

}

void ToDoTask::Show(){
    std::cout << "\t\t\t\tTo-Do List\n\n";
    if(tasks.empty()){
        std::cout << "\t\t\t\tList is empty\n\n";
    }
    else{
        for(size_t i = 0; i < tasks.size(); i++){
            std::cout << "\t\t\t\t" << i+1 << ". " << tasks[i] << "\n";
        }
    }
    std::cout << "\n";
}

int main(){

    ToDoTask taskList;

    int option;

    while(true){
        std::cout << "\t\t\t\tMenu\n";
        std::cout << "\t\t\t\t1. Add Task\n\t\t\t\t2. Delete task\n\t\t\t\t3. Edit\n\n";
        while(true){
        std::cout << "Type what to perform: ";
        std::cin >> option;;
        
        if(std::cin.fail()||option < 1 ||option > 3){
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
            if(!taskList.tasks.empty()){
                taskList.Delete();
            }
            else{
                std::cout << "Tasks is empty. Cannot remove any element\n\n";
            }
            break;
        case 3:
            if(!taskList.tasks.empty()){
                taskList.Edit();
            }
            else{
                std::cout << "Cannot be edited. Tasks is empty\n\n";
            }
            break;
        }

    }
    
    return 0;
}