#include <iostream>

using namespace std;

class AbstractProductA{
public:
    virtual void print() = 0;
};

class AbstractProductB{
public:
    virtual void print() = 0;
};

class ProductA1: public AbstractProductA{
public:
    void print() override{
        cout << "Product A1" << endl;
    }
};

class ProductA2: public AbstractProductA{
public:
    void print() override{
        cout << "Product A2" << endl;
    }
};

class ProductB1: public AbstractProductB{
public:
    void print() override{
        cout << "Product B1" << endl;
    }
};

class ProductB2: public AbstractProductB{
public:
    void print() override{
        cout << "Product B2" << endl;
    }
};

class AbstractFactory{
public:
    AbstractFactory(){
        cout << "Abstract Factory constructed." << endl;
    }
    virtual void print() = 0;
    virtual AbstractProductA* CreateProductA() = 0;
    virtual AbstractProductB* CreateProductB() = 0;
};

class Factory1: public AbstractFactory{
public:
    void print() override {
        cout << "Concrete Factory 1." << endl;
    }
    AbstractProductA* CreateProductA() override {
        return new ProductA1();
    }
    AbstractProductB* CreateProductB() override {
        return new ProductB1();
    }
};

class Factory2: public AbstractFactory{
public:
    void print() override {
        cout << "Concrete Factory 2." << endl;
    }
    AbstractProductA* CreateProductA() override {
        return new ProductA2();
    }
    AbstractProductB* CreateProductB() override {
        return new ProductB2();
    }
};

void client(AbstractFactory& factory){
    factory.print();
    AbstractProductA* productA = factory.CreateProductA();
    AbstractProductB* productB = factory.CreateProductB();
    productA->print();
    productB->print();
}

int main(){
    Factory1 factory1;
    Factory2 factory2;
    client(factory1);
    client(factory2);
    return 0;
}