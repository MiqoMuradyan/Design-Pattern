#include <iostream>

class Singleton {
public:

    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

    static Singleton* getInstance() {
        if (instance == nullptr) {
            instance = new Singleton();  
        }
        return instance;
    }

    void someFunction() {
        std::cout << "Singleton instance some function!!!!!!!" << std::endl;
    }

private:
    static Singleton* instance; 
    Singleton() {}  
};

Singleton* Singleton::instance = nullptr;

int main() {

    Singleton* s1 = Singleton::getInstance();
    s1->someFunction();

    Singleton* s2 = Singleton::getInstance();
    std::cout << (s1 == s2 ? "Same instance" : "Different instances") << std::endl;

    return 0;
}