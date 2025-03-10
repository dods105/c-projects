#include <iostream>
#include <string>
#include <fstream>
#include <vector>

class Market{
    std::string productName, price, product;
    std::fstream marketProduct;
    std::vector <std::string>products;
    bool productFound = false;

    public:
    void ShowProduct();
    void Changeprice();
    void AddProduct();
    void DeleteProduct();
    void searchProduct();

    Market(){
        marketProduct.open("BillingSystem.txt", std::ios::in | std::ios::out | std::ios::app);
    }

    ~Market (){
        if(marketProduct.is_open()){
            marketProduct.close();
        }
    }
};

void Market::AddProduct(){
    int repeat;
    std::cout << "Type how many product to add: ";
    std::cin >> repeat;
    std::cin.ignore();
    std::cout << "Add Product\n";

    for(int i = 0; i < repeat; i++){
        std::cout << "Product: ";
        getline(std::cin, productName);
        std::cout << "Price: ";
        getline(std::cin, price);

        marketProduct << productName << "\n";
        marketProduct << price << "\n";
    }
}

void Market::DeleteProduct(){
    std::cout << "Delete Product\n";
    std::string name;

    std::fstream newBill("tempFile.txt", std::ios::out);

    std::cout << "Type Product Name: ";
    getline(std::cin, name);

    while(getline(marketProduct, productName) && getline(marketProduct, price)){

        if(name != productName){
            newBill << productName <<"\n";
            newBill << price << "\n";
        }
        else{
            productFound = true;
        }
    }

    if(productFound){
        std::cout << "Product Deleted.\n";
    }
    else{
        std::cerr << "Product does not exist.\n";
    }

    marketProduct.close();
    newBill.close();

    std::remove("BillingSystem.txt");
    std::rename("tempFile.txt", "BillingSystem.txt");

    marketProduct.open("Billing System.txt", std::ios::in | std::ios::out | std::ios::app);
    productFound = false;
}

void Market::ShowProduct(){
    while(getline(marketProduct, productName) && getline(marketProduct, price)){

        std::cout << productName << "------" << price << "\n";
    }
}

void Market::Changeprice(){
    std::string newPrice;
    std::fstream tempFile("tempFile.txt", std::ios::out);

    std::cout << "Change Product Price\n";
    std::cout << "Product Name: ";
    getline(std::cin, product);
    std::cout << "New Product Price: ";
    getline(std::cin, newPrice);

    while(getline(marketProduct, productName) && getline(marketProduct, price)){
        if(product == productName){
            tempFile << productName << "\n";
            tempFile << newPrice << "\n";

            productFound = true;
        }
        else{
            tempFile << productName << "\n";
            tempFile << price << "\n";
        }
    }

    if(productFound){
        std::cout << productName << " is now " << newPrice << "\n";
    }
    else{
        std::cerr << "Product not found\n";
    }

    marketProduct.close();
    tempFile.close();

    std::remove("BillingSystem.txt");
    std::rename("tempFile.txt", "BillingSystem.txt");

    marketProduct.open("BillingSystem.txt", std::ios::out | std::ios::in | std::ios::app);

    productFound = false;

}

void Market::searchProduct(){
    std::cout << "Search Product\n";
    std::cout << "Product Name: ";
    getline(std::cin, product);

    while(getline(marketProduct, productName) && getline(marketProduct, price)){
        if(product == productName){
            std::cout << productName << "------" << price << "\n";
            productFound = true;
        }
    }

    if(!productFound){
        std::cout << "Product Does Not Exist.\n";
    }
}

int main(){
    std::cout << "\n\t\t_______________________\n\n";
    std::cout << "\t\t(1). Add Products\n\t\t(2). Show Products\n\t\t(3). Change Product Price\n\t\t(4). Delete Product\n\t\t(5). Search Product\n\t\t(6). Exit";
    std::cout << "\n\t\t_______________________\n\n";

    int operation;
    std::cout << "Type what to perform: ";
    std::cin >> operation;
    std::cin.ignore();

    Market bill;
    bool operate = 1;
    while(operate){
        switch(operation){
        case 1:
            bill.AddProduct();
            break;
        case 2:
            bill.ShowProduct();
            break;
        case 3:
            bill.Changeprice();
            break;
        case 4:
            bill.DeleteProduct();
            break;
        case 5:
            bill.searchProduct();
            break;
        case 6:
            operate = 0;
            break;
        }
    }

    std::cout << "Billing System by Stacy Jordan.\n";

    return 0;
}