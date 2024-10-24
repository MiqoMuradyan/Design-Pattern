#include <iostream>
#include <vector>

class Item {
public:
    virtual ~Item() = default;
    virtual int getPrice() const = 0;
    virtual void showDetails() const = 0;
};

class SingleItem : public Item {
public:
    SingleItem(const std::string& name, int price) : name(name), price(price) {}

    int getPrice() const override {
        return price;
    }

    void showDetails() const override {
        std::cout << "item: " << name << ", price: " << price << "\n";
    }

private:
    std::string name;
    int price;
};

class ItemGroup : public Item {
public:
    void addItem(Item* item) {
        items.push_back(item);
    }

    int getPrice() const override {
        int total = 0;
        for (Item* item : items) {
            total += item->getPrice(); 
        }
        return total;
    }

    void showDetails() const override {
        std::cout << "item group, total price: " << getPrice() << "\n";
        for (Item* item : items) {
            item->showDetails(); 
        }
    }

    ~ItemGroup() {
        for (Item* item : items) {
            delete item;
        }
    }

private:
    std::vector<Item*> items;
};


int main() {

    Item* book = new SingleItem("book", 3500);
    Item* pen = new SingleItem("pen", 50);

    ItemGroup* group = new ItemGroup();
    group->addItem(book);
    group->addItem(pen);

    group->showDetails();

    delete group; 

    return 0;
}