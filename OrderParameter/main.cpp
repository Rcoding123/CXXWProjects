#include <iostream>
#include <string>

std::string getSymbol() {
  std::string symbol{};

  while (true) {
    std::cout << "Enter a symbol: ";
    std::cin >> symbol;

    if (symbol.length() < 1 || symbol.length() > 6) {
      std::cout << "Cannot be less than 1 or greater than 6" << '\n';
      continue;
    }

    bool is_valid{true};

    for (char l : symbol) {
      if (l >= '0' && l <= '9') {
        std::cout << "Enter only letters, no numbers!" << '\n';
        is_valid = false;
        break;
      }

      if (l >= 'a' && l <= 'z') {
        std::cout << "Letters have to be uppercase!" << '\n';
        is_valid = false;
        break;
      }

      if (l < 'A' || l > 'Z') {
        std::cout << "Enter only letters, no symbols!" << '\n';
        is_valid = false;
        break;
      }
    }

    if (!is_valid) {
      continue;
    }

    return symbol;
  }
}

std::string getSide() {
  std::string side{};

  while (true) {
    std::cout << "Enter side (BUY or SELL): ";
    std::cin >> side;

    if (side == "BUY" || side == "SELL") {
      return side;
    }

    std::cout << "Invalid side. Enter BUY or SELL only." << '\n';
  }
}

int getQuantity() {
  int quantity{};

  while (true) {
    std::cout << "Enter a quantity: (1 - 10000): ";
    std::cin >> quantity;

    if (std::cin.fail()) {
      std::cout << "Invalid input. Enter a whole number only." << '\n';
      std::cin.clear();
      std::cin.ignore(10000, '\n');
      continue;
    }

    if (quantity < 1) {
      std::cout << "Quantity cannot be less than 1." << '\n';
      continue;
    }

    if (quantity > 10000) {
      std::cout << "Quantity cannot be greater than 10000." << '\n';
      continue;
    }
    return quantity;
  }
}

double getPrice() {
  double price{};

  while (true) {
    std::cout << "Enter a price: $";
    std::cin >> price;

    if (std::cin.fail()) {
      std::cout << "Invalid input. Enter a valid price only." << '\n';
      std::cin.clear();
      std::cin.ignore(10000, '\n');
      continue;
    }

    if (price < 1.0) {
      std::cout << "Price must be at least $1.00." << '\n';
      continue;
    }

    if (price > 999999.99) {
      std::cout << "Price cannot be greater than $999,999.99." << '\n';
      continue;
    }

    return price;
  }
}

std::string getOrderType() {
  std::string order_type{};

  while (true) {
    std::cout << "Enter an order type (MARKET Or LIMIT): ";
    std::cin >> order_type;

    if (order_type == "MARKET" || order_type == "LIMIT") {
      return order_type;
    }

    std::cout << "Invalid order type. Enter MARKET or LIMIT only." << '\n';
  }
}

void displayOrder(const std::string &symbol, const std::string &side,
                  int quantity, double price, const std::string &order_type) {
  std::cout << '\n';
  std::cout << "=== Order Summary ===" << '\n';

  if (order_type == "MARKET") {
    std::cout << side << " " << quantity << " " << symbol << " @ MARKET" << " ["
              << order_type << "]" << '\n';
  } else if (order_type == "LIMIT") {
    std::cout << side << " " << quantity << " " << symbol << " @ $" << price
              << " [" << order_type << "]" << '\n';
  }
}

int main() {
  std::cout << "=== Order Validator ===" << '\n';

  std::string symbol = getSymbol();
  std::string side = getSide();
  int quantity = getQuantity();
  std::string order_type = getOrderType();

  double price{};

  if (order_type == "LIMIT") {
    price = getPrice();
  }

  displayOrder(symbol, side, quantity, price, order_type);

  return 0;
}
