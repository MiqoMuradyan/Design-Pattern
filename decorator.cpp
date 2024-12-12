#include <iostream>
#include <memory>
#include <string>

class Beverage {
public:
    virtual ~Beverage() = default;
    virtual std::string getDescription() const = 0;
    virtual double cost() const = 0;
};

class Coffee : public Beverage {
public:
    std::string getDescription() const override {
        return "Coffee";
    }
    double cost() const override {
        return 2.0;
    }
};


class BeverageDecorator : public Beverage {
protected:
    std::shared_ptr<Beverage> beverage; 
public:
    explicit BeverageDecorator(std::shared_ptr<Beverage> bev) : beverage(std::move(bev)) {}
};

class Milk : public BeverageDecorator {
public:
    explicit Milk(std::shared_ptr<Beverage> bev) : BeverageDecorator(std::move(bev)) {}

    std::string getDescription() const override {
        return beverage->getDescription() + ", Milk";
    }

    double cost() const override {
        return beverage->cost() + 0.5;
    }
};

class Sugar : public BeverageDecorator {
public:
    explicit Sugar(std::shared_ptr<Beverage> bev) : BeverageDecorator(std::move(bev)) {}

    std::string getDescription() const override {
        return beverage->getDescription() + ", Sugar";
    }

    double cost() const override {
        return beverage->cost() + 0.2;
    }
};

int main() {
    std::shared_ptr<Beverage> beverage = std::make_shared<Coffee>();
    std::cout << beverage->getDescription() << " - $" << beverage->cost() << std::endl;

    beverage = std::make_shared<Milk>(beverage);
    std::cout << beverage->getDescription() << " - $" << beverage->cost() << std::endl;

    beverage = std::make_shared<Sugar>(beverage);
    std::cout << beverage->getDescription() << " - $" << beverage->cost() << std::endl;

    beverage = std::make_shared<Sugar>(beverage); 
    std::cout << beverage->getDescription() << " - $" << beverage->cost() << std::endl;

    return 0;
}