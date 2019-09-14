#include <iostream>

using namespace std;

class Product{
public:
    virtual void print() = 0;
};

class ProductA: public Product{
public:
    void print() override{
        cout << "ProductA" << endl;
    };
};

class ProductB: public Product{
public:
    void print() override{
        cout << "ProductB" << endl;
    };
};

class ProductC: public Product{
public:
    void print() override{
        cout << "ProductC" << endl;
    };
};

class Creator{
public:
    virtual Product* create() = 0;
    virtual void print() = 0;
};

class CreatorA: public Creator{
public:
    Product* create() override {
        return new ProductA();
    }
    void print() override{
        cout << "Creator A" << endl;
    }
};

class CreatorB: public Creator{
public:
    Product* create() override {
        return new ProductB();
    }
    void print() override{
        cout << "Creator B" << endl;
    }
};

class CreatorC: public Creator{
public:
    Product* create() override {
        return new ProductC();
    }
    void print() override{
        cout << "Creator C" << endl;
    }
};

void client(Creator& creator){
    creator.print();
    Product* productA = creator.create();
    productA->print();
}

int main(){
    CreatorA creatorA;
    CreatorB creatorB;
    CreatorC creatorC;
    client(creatorA);
    client(creatorB);
    client(creatorC);
    return 0;
}