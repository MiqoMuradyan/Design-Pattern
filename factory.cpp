#include <iostream>
#include <memory>  
#include <string>

class Warrior {
public:
    virtual void attack() const = 0;  
    virtual ~Warrior() = default;      
};


class Knight : public Warrior {
public:
    void attack() const override {
        std::cout << "Knight swings his sword!" << std::endl;
    }
};

class Archer : public Warrior {
public:
    void attack() const override {
        std::cout << "Archer shoots an arrow!" << std::endl;
    }
};

class Mage : public Warrior {
public:
    void attack() const override {
        std::cout << "Mage casts a fireball!" << std::endl;
    }
};

class WarriorFactory {
public:
    static std::unique_ptr<Warrior> createWarrior(const std::string& warriorType) {
        if (warriorType == "knight") {
            return std::make_unique<Knight>();
        } else if (warriorType == "archer") {
            return std::make_unique<Archer>();
        } else if (warriorType == "mage") {
            return std::make_unique<Mage>();
        } else {
            return nullptr; // Unknown warrior type
        }
    }
};

int main() {
    // Create different types of warriors
    std::unique_ptr<Warrior> warrior1 = WarriorFactory::createWarrior("knight");
    if (warrior1) warrior1->attack();

    std::unique_ptr<Warrior> warrior2 = WarriorFactory::createWarrior("archer");
    if (warrior2) warrior2->attack();

    std::unique_ptr<Warrior> warrior3 = WarriorFactory::createWarrior("mage");
    if (warrior3) warrior3->attack();

    // Attempt to create an unknown warrior type
    std::unique_ptr<Warrior> warrior4 = WarriorFactory::createWarrior("thief");
    if (!warrior4) {
        std::cout << "Unknown type." << std::endl;
    }

    return 0;
}