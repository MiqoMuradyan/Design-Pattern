#include <iostream>
#include <memory>  
#include <string>

class Weapon {
public:
    virtual void wield() const = 0;  
    virtual ~Weapon() = default;      
};

class Warrior {
public:
    virtual void attack() const = 0;  
    virtual std::unique_ptr<Weapon> createWeapon() const = 0; 
    virtual ~Warrior() = default;      
};

class Sword : public Weapon {
public:
    void wield() const override {
        std::cout << "Wielding a sword!" << std::endl;
    }
};

class Bow : public Weapon {
public:
    void wield() const override {
        std::cout << "Wielding a bow!" << std::endl;
    }
};

class Staff : public Weapon {
public:
    void wield() const override {
        std::cout << "Wielding a staff!" << std::endl;
    }
};

class Knight : public Warrior {
public:
    void attack() const override {
        std::cout << "Knight swings his sword!" << std::endl;
    }
    
    std::unique_ptr<Weapon> createWeapon() const override {
        return std::make_unique<Sword>();
    }
};

class Archer : public Warrior {
public:
    void attack() const override {
        std::cout << "Archer shoots an arrow!" << std::endl;
    }

    std::unique_ptr<Weapon> createWeapon() const override {
        return std::make_unique<Bow>();
    }
};

class Mage : public Warrior {
public:
    void attack() const override {
        std::cout << "Mage casts a fireball!" << std::endl;
    }

    std::unique_ptr<Weapon> createWeapon() const override {
        return std::make_unique<Staff>();
    }
};

class WarriorFactory {
public:
    virtual std::unique_ptr<Warrior> createWarrior() const = 0;  
    virtual ~WarriorFactory() = default;                          
};

class KnightFactory : public WarriorFactory {
public:
    std::unique_ptr<Warrior> createWarrior() const override {
        return std::make_unique<Knight>();
    }
};

class ArcherFactory : public WarriorFactory {
public:
    std::unique_ptr<Warrior> createWarrior() const override {
        return std::make_unique<Archer>();
    }
};

class MageFactory : public WarriorFactory {
public:
    std::unique_ptr<Warrior> createWarrior() const override {
        return std::make_unique<Mage>();
    }
};

int main() {
    std::unique_ptr<WarriorFactory> knightFactory = std::make_unique<KnightFactory>();
    std::unique_ptr<Warrior> knight = knightFactory->createWarrior();
    knight->attack();
    std::unique_ptr<Weapon> knightWeapon = knight->createWeapon();
    knightWeapon->wield();

    std::unique_ptr<WarriorFactory> archerFactory = std::make_unique<ArcherFactory>();
    std::unique_ptr<Warrior> archer = archerFactory->createWarrior();
    archer->attack();
    std::unique_ptr<Weapon> archerWeapon = archer->createWeapon();
    archerWeapon->wield();

    std::unique_ptr<WarriorFactory> mageFactory = std::make_unique<MageFactory>();
    std::unique_ptr<Warrior> mage = mageFactory->createWarrior();
    mage->attack();
    std::unique_ptr<Weapon> mageWeapon = mage->createWeapon();
    mageWeapon->wield();

    return 0;
}