#include <iostream>
#include <string>

class House {
public:
    void setFoundation(const std::string& foundation) {
        this->foundation = foundation;
    }

    void setStructure(const std::string& structure) {
        this->structure = structure;
    }

    void setRoof(const std::string& roof) {
        this->roof = roof;
    }

    void show() const {
        std::cout << "House built with:\n";
        std::cout << "Foundation: " << foundation << "\n";
        std::cout << "Structure: " << structure << "\n";
        std::cout << "Roof: " << roof << "\n";
    }

private:
    std::string foundation;
    std::string structure;
    std::string roof;
};

class HouseBuilder {
public:
    virtual ~HouseBuilder() {}
    virtual void buildFoundation() = 0;
    virtual void buildStructure() = 0;
    virtual void buildRoof() = 0;
    virtual House* getHouse() = 0;
};

class ConcreteHouseBuilder : public HouseBuilder {
public:
    ConcreteHouseBuilder() {
        house = new House();
    }

    void buildFoundation() override {
        house->setFoundation("Concrete Foundation");
    }

    void buildStructure() override {
        house->setStructure("Concrete Structure");
    }

    void buildRoof() override {
        house->setRoof("Concrete Roof");
    }

    House* getHouse() override {
        return house;
    }

private:
    House* house;
};

class HouseDirector {
public:
    HouseDirector(HouseBuilder* builder) : builder(builder) {}

    void constructHouse() {
        builder->buildFoundation();
        builder->buildStructure();
        builder->buildRoof();
    }

private:
    HouseBuilder* builder;
};

int main() {
    HouseBuilder* builder = new ConcreteHouseBuilder();
    HouseDirector director(builder);

    director.constructHouse();
    House* house = builder->getHouse();
    house->show();

    delete house;
    delete builder;
    return 0;
}