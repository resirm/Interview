#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Packing{
public:
    virtual string pack() = 0;
};

class Wrapper: public Packing{
public:
    string pack() override {
        return "Wrapper";
    }
};

class Bottle: public Packing{
public:
    string pack() override {
        return "Bottle";
    }
};

class Item{
public:
    virtual string name() = 0;
    virtual Packing* packing() = 0;
    virtual float price() = 0;
};

class Burger: public Item{
public:
    Packing* packing() override{
        return new Wrapper();
    }
};

class Drink: public Item{
public:
    Packing* packing() override{
        return new Bottle();
    }
};

class VegBurger: public Burger{
public:
    string name() override{
        return "Veg Burger";
    }
    float price() override{
        return 20;
    }
};

class MeatBurger: public Burger{
public:
    string name() override{
        return "Meat Burger";
    }
    float price() override{
        return 25;
    }
};

class Coke: public Drink{
public:
    string name() override{
        return "Coke";
    }
    float price() override{
        return 7;
    }
};

class Pepsi: public Drink{
public:
    string name() override{
        return "Pepsi";
    }
    float price() override{
        return 7;
    }
};

class Package{
public:
    void add(Item* item){
        items.push_back(item);
    }

    float getCost(){
        float cost = 0;
        for(auto c : items){
            cost += c->price();
        }
        return cost;
    }

    void showItems(){
        for(auto c : items){
            cout << "Item: " << c->name() << endl
                 << "Packing: " << c->packing()->pack() << endl
                 << "Price: " << c->price() << endl;
        }
    }

private:
    vector<Item*> items;
};

class PackageBuilder{
public:
    Package* preparePackage1(){
        Package* package = new Package();
        package->add(new MeatBurger());
        package->add(new Coke());
        return package;
    }

    Package* preparePackage2(){
        Package* package = new Package();
        package->add(new MeatBurger());
        package->add(new MeatBurger());
        package->add(new Coke());
        return package;
    }

    Package* preparePackage3(){
        Package* package = new Package();
        package->add(new VegBurger());
        package->add(new Pepsi());
        return package;
    }

    Package* preparePackage4(){
        Package* package = new Package();
        package->add(new VegBurger());
        package->add(new MeatBurger());
        package->add(new Coke());
        package->add(new Pepsi());
        return package;
    }
};

int main(){
    PackageBuilder packageBuilder;
    Package* package1 = packageBuilder.preparePackage1();
    Package* package2 = packageBuilder.preparePackage2();
    Package* package3 = packageBuilder.preparePackage3();
    Package* package4 = packageBuilder.preparePackage4();

    cout << "Package 1: " << endl;
    package1->showItems();
    cout << "\nTotal cost: " << package1->getCost() << endl;

    cout << "\nPackage 2: " << endl;
    package2->showItems();
    cout << "\nTotal cost: " << package2->getCost() << endl;

    cout << "\nPackage 3: " << endl;
    package3->showItems();
    cout << "\nTotal cost: " << package3->getCost() << endl;

    cout << "\nPackage 4: " << endl;
    package4->showItems();
    cout << "\nTotal cost: " << package4->getCost() << endl;

    return 0;
}