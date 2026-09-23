#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <stdexcept>
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
        std::cout << "5. Exit\n";
        std::cout << "==================\n";
    }

    void displaySizeMenu() const {
        std::cout << "\n=== Size Menu ===\n";
        std::cout << "1. Small\n";
        std::cout << "2. Medium\n";
        std::cout << "3. Large\n";
        std::cout << "================\n";
    }

    int readValidChoice(const std::string& prompt, int min, int max) {
        std::string input;

        while (true) {
            std::cout << prompt;
            std::getline(std::cin, input);

            try {
                size_t pos = 0;
                int choice = std::stoi(input, &pos);

                if (pos != input.length() || choice < min || choice > max) {
                    throw std::invalid_argument("out of range");
                }

                return choice;
            } catch (const std::exception&) {
                std::cout << "Invalid input. Please enter a number between "
                          << min << " and " << max << ".\n";
            }
        }
    }

    std::string readRequiredText(const std::string& prompt) {
        std::string input;

        while (true) {
            std::cout << prompt;
            std::getline(std::cin, input);

            if (!input.empty()) {
                return input;
            }

            std::cout << "This field cannot be blank. Please try again.\n";
        }
    }

    void getOrder() {
        while (true) {
            displayMenu();
            int menuChoice = readValidChoice("Choose a pizza from the menu (1-5): ", 1, 5);

            if (menuChoice == 5) {
                std::cout << "Thanks for visiting! Exiting the order menu.\n";
                std::exit(0);
            }

            switch (menuChoice) {
                case 1:
                    pizza = "Margherita";
                    break;
                case 2:
                    pizza = "Pepperoni";
                    break;
                case 3:
                    pizza = "Veggie Supreme";
                    break;
                case 4:
                    pizza = "Meat Lovers";
                    break;
            }

            displaySizeMenu();
            int sizeChoice = readValidChoice("Choose a size (1-3): ", 1, 3);

            switch (sizeChoice) {
                case 1:
                    size = "small";
                    break;
                case 2:
                    size = "medium";
                    break;
                case 3:
                    size = "large";
                    break;
            }

            flavor = readRequiredText("What flavor or toppings would you like? ");
            calculateCost();
            return;
        }
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
