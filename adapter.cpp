#include <string>
#include <iostream>

class NewPrinter {
public:
    virtual void print(const std::string& text) = 0;
    virtual ~NewPrinter() = default;
};


class OldPrinter {
public:
    void printOld(const std::string& text) {
        std::cout << "Old Printer: " << text << std::endl;
    }
};


class PrinterAdapter : public NewPrinter {
public:
    PrinterAdapter(OldPrinter* oldPrinter) : oldPrinter(oldPrinter) {}

    void print(const std::string& text) override {
        oldPrinter->printOld(text);
    }

private:
    OldPrinter* oldPrinter;

};


int main() {
    OldPrinter oldPrinter;
    PrinterAdapter adapter(&oldPrinter);

    adapter.print("printing");

    return 0;
}