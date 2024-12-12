#include <iostream>
#include <memory>
#include <string>

class Color {
public:
    virtual ~Color() = default;
    virtual std::string getColor() = 0;
};

class Red : public Color {
public:
    std::string getColor() override {
        return "Red";
    }
};

class Blue : public Color {
public:
    std::string getColor() override {
        return "Blue";
    }
};

class Shape {
protected:
    std::shared_ptr<Color> color; 
public:
    explicit Shape(std::shared_ptr<Color> col) : color(std::move(col)) {}
    virtual ~Shape() = default;
    virtual void draw() = 0; 
};

class Circle : public Shape {
public:
    explicit Circle(std::shared_ptr<Color> col) : Shape(std::move(col)) {}
    void draw() override {
        std::cout << "Drawing a " << color->getColor() << " Circle" << std::endl;
    }
};

class Square : public Shape {
public:
    explicit Square(std::shared_ptr<Color> col) : Shape(std::move(col)) {}
    void draw() override {
        std::cout << "Drawing a " << color->getColor() << " Square" << std::endl;
    }
};

int main() {
    auto red = std::make_shared<Red>();
    auto blue = std::make_shared<Blue>();

    std::shared_ptr<Shape> redCircle = std::make_shared<Circle>(red);
    std::shared_ptr<Shape> blueSquare = std::make_shared<Square>(blue);

    redCircle->draw();
    blueSquare->draw();

    std::shared_ptr<Shape> blueCircle = std::make_shared<Circle>(blue);
    blueCircle->draw();

    return 0;
}