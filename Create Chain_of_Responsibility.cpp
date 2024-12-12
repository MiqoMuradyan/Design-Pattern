#include <iostream>
#include <memory>
#include <string>

class SupportHandler {
protected:
    std::shared_ptr<SupportHandler> nxtHandler; 

public:
    virtual ~SupportHandler() = default;

    void setNextHandler(std::shared_ptr<SupportHandler> handler) {
        nxtHandler = std::move(handler);
    }

    virtual void handleRequest(const std::string& issue) const {
        if (nxtHandler) {
            nxtHandler->handleRequest(issue);
        } 
        else {
            std::cout << "No handler available for the issue: " << issue << std::endl;
        }
    }
};

// Concrete Handlers
class TechnicalSupport : public SupportHandler {
public:
    void handleRequest(const std::string& issue) const override {
        if (issue == "Technical") {
            std::cout << "Technical Support: Handling the issue." << std::endl;
        } 
        else if (nxtHandler) {
            nxtHandler->handleRequest(issue);
        }
    }
};

class BillingSupport : public SupportHandler {
public:
    void handleRequest(const std::string& issue) const override {
        if (issue == "Billing") {
            std::cout << "Billing Support: Handling the issue." << std::endl;
        } 
        else if (nxtHandler) {
            nxtHandler->handleRequest(issue);
        }
    }
};

class GeneralSupport : public SupportHandler {
public:
    void handleRequest(const std::string& issue) const override {
        if (issue == "General") {
            std::cout << "General Support: Handling the issue." << std::endl;
        } 
        else if (nxtHandler) {
            nxtHandler->handleRequest(issue);
        }
    }
};

int main() {
    auto technical = std::make_shared<TechnicalSupport>();
    auto billing = std::make_shared<BillingSupport>();
    auto general = std::make_shared<GeneralSupport>();

    general->setNextHandler(billing);
    billing->setNextHandler(technical);

    std::string issues[] = {"General", "Billing", "Technical", "Unknown"};

    for (const auto& issue : issues) {
        std::cout << "Processing issue is: " << issue << std::endl;
        general->handleRequest(issue);
        std::cout << std::endl;
    }

    return 0;
}