#include <iostream>
#include <string>
#include <unordered_map>
#include <memory>

class Shape {
public:
    virtual ~Shape() = default;
    virtual std::unique_ptr<Shape> clone() const = 0;  // Clone method
    virtual void draw() const = 0;  // Display shape details
};

class Circle : public Shape {
    int radius;
public:
    Circle(int r) : radius(r) {}
    Circle(const Circle& other) : radius(other.radius) {}  

    std::unique_ptr<Shape> clone() const override {
        return std::make_unique<Circle>(*this); 
    }

    void draw() const override {
        std::cout << "Drawing a Circle with radius: " << radius << '\n';
    }
};

class Rectangle : public Shape {
    int width, height;
public:
    Rectangle(int w, int h) : width(w), height(h) {}
    Rectangle(const Rectangle& other) : width(other.width), height(other.height) {}  // Copy constructor

    std::unique_ptr<Shape> clone() const override {
        return std::make_unique<Rectangle>(*this);  // Cloning itself
    }

    void draw() const override {
        std::cout << "Drawing a Rectangle with width: " << width
                  << " and height: " << height << '\n';
    }
};

class PrototypeRegistry {
    std::unordered_map<std::string, std::unique_ptr<Shape>> prototypes;

public:
    void registerPrototype(const std::string& key, std::unique_ptr<Shape> prototype) {
        prototypes[key] = std::move(prototype);
    }

    std::unique_ptr<Shape> create(const std::string& key) const {
        if (prototypes.find(key) != prototypes.end()) {
            return prototypes.at(key)->clone();  // Clone the stored prototype
        }
        return nullptr;
    }
};

int main() {
    PrototypeRegistry registry;

    registry.registerPrototype("circle", std::make_unique<Circle>(10));
    registry.registerPrototype("rectangle", std::make_unique<Rectangle>(20, 10));

    auto shape1 = registry.create("circle");
    auto shape2 = registry.create("rectangle");

    if (shape1) shape1->draw();
    if (shape2) shape2->draw();

    return 0;
}