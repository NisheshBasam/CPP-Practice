#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

class PizzaOrder {
private:
    std::vector<std::string> pizzas;
    std::vector<std::string> sizes;
    std::vector<std::string> flavors;
    std::vector<double> itemCosts;
    std::string orderType = "Pickup";
    double subtotal = 0.0;
    double tax = 0.0;
    double deliveryFee = 0.0;
    double total = 0.0;
    const double taxRate = 0.08;

    double getPizzaPrice(const std::string& sizeName) const {
        std::string normalized = sizeName;
        std::transform(normalized.begin(), normalized.end(), normalized.begin(),
                       [](unsigned char ch) { return static_cast<char>(std::tolower(ch)); });

        if (normalized == "small") {
            return 10.99;
        }
        if (normalized == "large") {
            return 18.99;
        }
        return 14.99;
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

    void displayOrderTypeMenu() const {
        std::cout << "\n=== Order Type ===\n";
        std::cout << "1. Pickup\n";
        std::cout << "2. Delivery\n";
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

    bool readYesNo(const std::string& prompt) {
        std::string input;

        while (true) {
            std::cout << prompt;
            std::getline(std::cin, input);

            if (input.empty()) {
                std::cout << "Please answer yes or no.\n";
                continue;
            }

            std::transform(input.begin(), input.end(), input.begin(),
                           [](unsigned char ch) { return static_cast<char>(std::tolower(ch)); });

            if (input == "y" || input == "yes") {
                return true;
            }
            if (input == "n" || input == "no") {
                return false;
            }

            std::cout << "Please enter yes or no.\n";
        }
    }

    void getOrder() {
        pizzas.clear();
        sizes.clear();
        flavors.clear();
        itemCosts.clear();
        subtotal = 0.0;
        tax = 0.0;
        deliveryFee = 0.0;
        total = 0.0;
        orderType = "Pickup";

        while (true) {
            displayMenu();
            int menuChoice = readValidChoice("Choose a pizza from the menu (1-5): ", 1, 5);

            if (menuChoice == 5) {
                std::cout << "Thanks for visiting! Exiting the order menu.\n";
                std::exit(0);
            }

            std::string pizzaType;
            switch (menuChoice) {
                case 1:
                    pizzaType = "Margherita";
                    break;
                case 2:
                    pizzaType = "Pepperoni";
                    break;
                case 3:
                    pizzaType = "Veggie Supreme";
                    break;
                case 4:
                    pizzaType = "Meat Lovers";
                    break;
                default:
                    pizzaType = "Custom Pizza";
                    break;
            }

            displaySizeMenu();
            int sizeChoice = readValidChoice("Choose a size (1-3): ", 1, 3);

            std::string selectedSize;
            switch (sizeChoice) {
                case 1:
                    selectedSize = "small";
                    break;
                case 2:
                    selectedSize = "medium";
                    break;
                case 3:
                    selectedSize = "large";
                    break;
                default:
                    selectedSize = "medium";
                    break;
            }

            std::string selectedFlavor = readRequiredText("What flavor or toppings would you like? ");

            pizzas.push_back(pizzaType);
            sizes.push_back(selectedSize);
            flavors.push_back(selectedFlavor);

            double itemCost = getPizzaPrice(selectedSize);
            itemCosts.push_back(itemCost);
            subtotal += itemCost;

            if (!readYesNo("Would you like to add another pizza? (y/n): ")) {
                break;
            }
        }

        displayOrderTypeMenu();
        int orderTypeChoice = readValidChoice("Choose your order type (1-2): ", 1, 2);
        if (orderTypeChoice == 2) {
            orderType = "Delivery";
            deliveryFee = 5.99;
        }

        tax = subtotal * taxRate;
        total = subtotal + tax + deliveryFee;
    }

    void printReceipt() const {
        std::cout << "\n----- Pizza Receipt -----\n";
        for (std::size_t i = 0; i < pizzas.size(); ++i) {
            std::cout << "Pizza " << i + 1 << ":          " << pizzas[i] << " (" << sizes[i] << ")\n";
            std::cout << "Flavor/toppings: " << flavors[i] << '\n';
            std::cout << "Price:           $" << std::fixed << std::setprecision(2) << itemCosts[i] << '\n';
            std::cout << "-------------------------\n";
        }

        std::cout << "Order type:      " << orderType << '\n';
        std::cout << "Subtotal:        $" << std::fixed << std::setprecision(2) << subtotal << '\n';
        std::cout << "Tax:             $" << std::fixed << std::setprecision(2) << tax << '\n';
        std::cout << "Delivery fee:    $" << std::fixed << std::setprecision(2) << deliveryFee << '\n';
        std::cout << "Total bill:      $" << std::fixed << std::setprecision(2) << total << '\n';
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
