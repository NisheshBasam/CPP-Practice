#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

struct PizzaItem {
    std::string name;
    std::string size;
    std::string toppings;
    double price = 0.0;
};

class PizzaOrderingApp {
private:
    std::vector<PizzaItem> items;
    std::string customerName;
    std::string customerPhone;
    std::string orderType = "Pickup";
    std::string paymentMethod = "Cash";
    double subtotal = 0.0;
    double tax = 0.0;
    double deliveryFee = 0.0;
    double discount = 0.0;
    double total = 0.0;

    static constexpr double TAX_RATE = 0.08;
    static constexpr double DELIVERY_FEE_VALUE = 5.99;

    std::string toLower(std::string input) const {
        std::transform(input.begin(), input.end(), input.begin(),
                       [](unsigned char ch) { return static_cast<char>(std::tolower(ch)); });
        return input;
    }

    double getPriceForSize(const std::string& size) const {
        std::string normalized = toLower(size);

        if (normalized == "small") {
            return 10.99;
        }
        if (normalized == "large") {
            return 18.99;
        }
        return 14.99;
    }

    void resetOrder() {
        items.clear();
        customerName.clear();
        customerPhone.clear();
        orderType = "Pickup";
        paymentMethod = "Cash";
        subtotal = 0.0;
        tax = 0.0;
        deliveryFee = 0.0;
        discount = 0.0;
        total = 0.0;
    }

    int readValidChoice(const std::string& prompt, int min, int max) {
        std::string input;

        while (true) {
            std::cout << prompt;
            std::getline(std::cin, input);

            try {
                size_t pos = 0;
                int value = std::stoi(input, &pos);

                if (pos != input.length() || value < min || value > max) {
                    throw std::invalid_argument("out of range");
                }

                return value;
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

            std::string normalized = toLower(input);

            if (normalized == "y" || normalized == "yes") {
                return true;
            }
            if (normalized == "n" || normalized == "no") {
                return false;
            }

            std::cout << "Please enter yes or no.\n";
        }
    }

    std::string getPizzaName(int choice) const {
        switch (choice) {
            case 1: return "Margherita";
            case 2: return "Pepperoni";
            case 3: return "Veggie Supreme";
            case 4: return "Meat Lovers";
            default: return "Custom Pizza";
        }
    }

    std::string getSizeName(int choice) const {
        switch (choice) {
            case 1: return "small";
            case 2: return "medium";
            case 3: return "large";
            default: return "medium";
        }
    }

    std::string getPaymentMethod(int choice) const {
        switch (choice) {
            case 1: return "Cash";
            case 2: return "Card";
            case 3: return "Mobile Pay";
            default: return "Cash";
        }
    }

    void displayWelcome() const {
        std::cout << "\n===================================\n";
        std::cout << "      Welcome to Pizza Palace      \n";
        std::cout << "===================================\n";
    }

    void displayPizzaMenu() const {
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

    void displayPaymentMenu() const {
        std::cout << "\n=== Payment Method ===\n";
        std::cout << "1. Cash\n";
        std::cout << "2. Card\n";
        std::cout << "3. Mobile Pay\n";
        std::cout << "====================\n";
    }

    void addPizza() {
        displayPizzaMenu();
        int pizzaChoice = readValidChoice("Choose a pizza from the menu (1-5): ", 1, 5);

        if (pizzaChoice == 5) {
            std::cout << "Thanks for visiting! Exiting the order menu.\n";
            std::exit(0);
        }

        displaySizeMenu();
        int sizeChoice = readValidChoice("Choose a size (1-3): ", 1, 3);

        PizzaItem item;
        item.name = getPizzaName(pizzaChoice);
        item.size = getSizeName(sizeChoice);
        item.toppings = readRequiredText("What flavor or toppings would you like? ");
        item.price = getPriceForSize(item.size);

        items.push_back(item);
        subtotal += item.price;
    }

    void applyDiscount() {
        if (!readYesNo("Do you have a promo code? (y/n): ")) {
            return;
        }

        std::string code = readRequiredText("Enter promo code: ");
        std::string normalized = toLower(code);

        if (normalized == "save10") {
            discount = subtotal * 0.10;
            std::cout << "Promo code applied: SAVE10\n";
        } else if (normalized == "freeship") {
            discount = 0.0;
            deliveryFee = 0.0;
            std::cout << "Promo code applied: FREESHIP\n";
        } else {
            std::cout << "Invalid promo code. No discount applied.\n";
        }
    }

    void finalizeOrder() {
        displayOrderTypeMenu();
        int typeChoice = readValidChoice("Choose your order type (1-2): ", 1, 2);
        orderType = (typeChoice == 2) ? "Delivery" : "Pickup";

        if (orderType == "Delivery") {
            deliveryFee = DELIVERY_FEE_VALUE;
        }

        tax = (subtotal - discount) * TAX_RATE;
        total = subtotal - discount + tax + deliveryFee;
    }

    void choosePayment() {
        displayPaymentMenu();
        int paymentChoice = readValidChoice("Choose a payment method (1-3): ", 1, 3);
        paymentMethod = getPaymentMethod(paymentChoice);
        std::cout << "Payment method selected: " << paymentMethod << "\n";
    }

    void printReceipt() const {
        std::cout << "\n----- Pizza Receipt -----\n";
        std::cout << "Customer:         " << customerName << '\n';
        std::cout << "Phone:            " << customerPhone << '\n';
        std::cout << "Order Type:       " << orderType << '\n';
        std::cout << "Payment:          " << paymentMethod << '\n';

        for (std::size_t i = 0; i < items.size(); ++i) {
            const PizzaItem& item = items[i];
            std::cout << "\nPizza " << i + 1 << ":         " << item.name << " (" << item.size << ")\n";
            std::cout << "Flavor/Toppings:  " << item.toppings << '\n';
            std::cout << "Price:            $" << std::fixed << std::setprecision(2) << item.price << '\n';
        }

        std::cout << "\nSubtotal:         $" << std::fixed << std::setprecision(2) << subtotal << '\n';
        std::cout << "Discount:         $" << std::fixed << std::setprecision(2) << discount << '\n';
        std::cout << "Tax:              $" << std::fixed << std::setprecision(2) << tax << '\n';
        std::cout << "Delivery Fee:     $" << std::fixed << std::setprecision(2) << deliveryFee << '\n';
        std::cout << "Total Bill:       $" << std::fixed << std::setprecision(2) << total << '\n';
        std::cout << "-------------------------\n";
    }

public:
    void run() {
        while (true) {
            resetOrder();
            displayWelcome();

            customerName = readRequiredText("Enter customer name: ");
            customerPhone = readRequiredText("Enter phone number: ");

            do {
                addPizza();
            } while (readYesNo("Would you like to add another pizza? (y/n): "));

            applyDiscount();
            finalizeOrder();
            choosePayment();
            printReceipt();

            if (!readYesNo("Would you like to place another order? (y/n): ")) {
                std::cout << "\nThank you for ordering with Pizza Palace!\n";
                break;
            }
        }
    }
};

int main() {
    PizzaOrderingApp app;
    app.run();
    return 0;
}
