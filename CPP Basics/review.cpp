#include <iomanip>
#include <iostream>
#include <string>

class PizzaOrder {
private:
    std::string pizza;
    std::string size;
    std::string flavor;
    double cost = 0.0;

    void calculateCost() {
        if (size == "small" || size == "Small") {
            cost = 10.99;
        } else if (size == "large" || size == "Large") {
            cost = 18.99;
        } else {
            cost = 14.99;
        }
    }

public:
    void displayMenu() const {
        std::cout << "\n=== Pizza Menu ===\n";
        std::cout << "1. Margherita\n";
        std::cout << "2. Pepperoni\n";
        std::cout << "3. Veggie Supreme\n";
        std::cout << "4. Meat Lovers\n";
        std::cout << "==================\n";
    }

    void displaySizeMenu() const {
        std::cout << "\n=== Size Menu ===\n";
        std::cout << "1. Small\n";
        std::cout << "2. Medium\n";
        std::cout << "3. Large\n";
        std::cout << "================\n";
    }

    void getOrder() {
        int menuChoice;
        int sizeChoice;

        do {
            displayMenu();
            std::cout << "Choose a pizza from the menu (1-4): ";
            std::cin >> menuChoice;

            if (menuChoice == 1) {
                pizza = "Margherita";
            } else if (menuChoice == 2) {
                pizza = "Pepperoni";
            } else if (menuChoice == 3) {
                pizza = "Veggie Supreme";
            } else if (menuChoice == 4) {
                pizza = "Meat Lovers";
            } else {
                std::cout << "Invalid choice. Please select a valid menu option.\n";
                pizza = "";
            }
        } while (pizza.empty());

        do {
            displaySizeMenu();
            std::cout << "Choose a size (1-3): ";
            std::cin >> sizeChoice;

            if (sizeChoice == 1) {
                size = "small";
            } else if (sizeChoice == 2) {
                size = "medium";
            } else if (sizeChoice == 3) {
                size = "large";
            } else {
                std::cout << "Invalid size. Please select a valid option.\n";
                size = "";
            }
        } while (size.empty());

        std::cout << "What flavor or toppings would you like? ";
        std::getline(std::cin >> std::ws, flavor);

        calculateCost();
    }

    void printReceipt() const {
        std::cout << "\n----- Pizza Receipt -----\n";
        std::cout << "Pizza:           " << pizza << '\n';
        std::cout << "Size:            " << size << '\n';
        std::cout << "Flavor/toppings: " << flavor << '\n';
        std::cout << "Price:           $" << std::fixed << std::setprecision(2) << cost << '\n';
        std::cout << "Total bill:      $" << cost << '\n';
        std::cout << "-------------------------\n";
    }
};

int main() {
    int a = 5; // Declare an integer variable 'a' and initialize it with the value 5
    double b = 3.14; // Declare a double variable 'b' and initialize it with the value 3.14
    char c = 'A'; // Declare a char variable 'c' and initialize it with the character 'A'
    bool d = true; // Declare a boolean variable 'd' and initialize it with the value true

    std::cout << "Integer: " << a << std::endl; // Output the value of 'a'
    std::cout << "Double: " << b << std::endl; // Output the value of 'b'
    std::cout << "Character: " << c << std::endl; // Output the value of 'c'
    std::cout << "Boolean: " << d << std::endl; // Output the value of 'd'

    PizzaOrder order;
    order.getOrder();
    order.printReceipt();

    return 0; // Return 0 to indicate successful execution
}
