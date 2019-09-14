#include <iostream>

using namespace std;

class Prototype{
public:
    virtual Prototype* clone() const = 0;
    virtual int get_val() = 0;
};

class ProductA: public Prototype{
public:
    ProductA(int v = 0): val_(v){

    }
    ProductA(const ProductA& product){
        val_ = product.val_;
    }
    void init(int v){
        val_ = v;
    }
    ProductA* clone() const override{
        return new ProductA(*this);
    }
    int get_val() override{
        return val_;
    }
private:
    int val_ = 0;
};

class ProductB: public Prototype{
public:
    ProductB(int v = 0): val_(v){

    }
    ProductB(const ProductB& product){
        val_ = product.val_;
    }
    void init(int v){
        val_ = v;
    }
    ProductB* clone() const override{
        return new ProductB(*this);
    }
    int get_val() override{
        return val_;
    }
private:
    int val_ = 0;
};

class ProductC: public Prototype{
public:
    ProductC(int v = 0): val_(v){

    }
    ProductC(const ProductC& product){
        val_ = product.val_;
    }
    void init(int v){
        val_ = v;
    }
    ProductC* clone() const override{
        return new ProductC(*this);
    }
    int get_val() override{
        return val_;
    }
private:
    int val_ = 0;
};

class BetterProductC: public ProductC{
public:
    BetterProductC(int v1 = 0, int v2 = 0): val_(v1), val2_(v2){
        // cout << val_ << ", " << val2_ << endl;
    }
    BetterProductC(const BetterProductC& product): ProductC(product){
        val_ = product.val_;
        val2_ = product.val2_;
    }
    void init(int v1, int v2){
        val_ = v1;
        val2_ = v2;
    }
    BetterProductC* clone() const override{
        return new BetterProductC(*this);
    }
    int get_val() override{
        // cout << val_+val2_ << endl;
        return val_+val2_;
    }
private:
    int val_ = 0;
    int val2_ = 0;
};

class PrototypeFactory{
public:
    PrototypeFactory(ProductA* a, ProductB* b, ProductC* c){
        pa_ = a;
        pb_ = b;
        pc_ = c;
    }
    
    ProductA* makeA() const{
        ProductA* productA = pa_->clone();
        return productA;
    }
    ProductB* makeB() const{
        ProductB* productB = pb_->clone();
        return productB;
    }
    ProductC* makeC() const{
        ProductC* productC = pc_->clone();
        return productC;
    }
private:
    ProductA* pa_;
    ProductB* pb_;
    ProductC* pc_;
};

void client(PrototypeFactory& proto){
    ProductA* pa = proto.makeA();
    ProductB* pb = proto.makeB();
    ProductC* pc = proto.makeC();
    cout << "A: " << pa->get_val() << endl;
    cout << "B: " << pb->get_val() << endl;
    cout << "C: " << pc->get_val() << endl;
}

int main(){
    ProductA* pa = new ProductA(10);
    ProductB* pb = new ProductB(20);
    ProductC* pc = new ProductC(30);
    ProductC* pbc = new BetterProductC(30,40);
    PrototypeFactory proto(pa, pb, pbc);
    client(proto);

    return 0;
}