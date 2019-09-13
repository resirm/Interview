#include <iostream>
#include <string>
#include <map>
#include <iomanip>

using namespace std;

class Singleton{
public:
    static Singleton* getInstance(string name);
    virtual void print(){
        cout << "Singleton out" << endl;
    }
    static void reg(string name, Singleton* candidate){
        reg_[name] = candidate;
    }
    virtual void set_val(int v){
        val_ = v;
    }
    virtual int get_val(){
        return val_;
    }
protected:
    Singleton(){
        cout << "Singleton constructed." << endl;
    }
    static Singleton* lookup(string name){
        if(reg_.find(name) != reg_.end()){
            return reg_[name];
        }else{
            return nullptr;
        }
    }
private:
    static Singleton* instance_;
    static map<string, Singleton*> reg_;
    int val_;
};

class MySingleton1: public Singleton{
public:
    MySingleton1(){
        cout << "MySingleton1 constructed." << endl;
        Singleton::reg("MySingleton1", this);
    }
    void print() override {
        cout << "MySingleton1 out" << endl;
    }
    void set_val(int v) override{
        val_ = v;
    }
    int get_val() override{
        return val_;
    }
private:
    int val_;
};

class MySingleton2: public Singleton{
public:
    MySingleton2(){
        cout << "MySingleton2 constructed." << endl;
        Singleton::reg("MySingleton2", this);
    }
    void print() override {
        cout << "MySingleton2 out" << endl;
    }
    void set_val(int v) override{
        val_ = v;
    }
    int get_val() override{
        return val_;
    }
private:
    int val_;
};

class MySingleton3: public Singleton{
public:
    MySingleton3(){
        cout << "MySingleton3 constructed." << endl;
        Singleton::reg("MySingleton3", this);
    }
    void print() override {
        cout << "MySingleton3 out" << endl;
    }
    void set_val(int v) override{
        val_ = v;
    }
    int get_val() override{
        return val_;
    }
private:
    int val_;
};

Singleton* Singleton::instance_ = nullptr;
map<string, Singleton*> Singleton::reg_;
Singleton* Singleton::getInstance(string name){
    instance_ = lookup(name);
    return instance_;
}

static MySingleton1 mysingleton1;
static MySingleton2 mysingleton2;
static MySingleton3 mysingleton3;

int main(){
    Singleton* s1 = Singleton::getInstance("MySingleton1");
    Singleton* s2 = Singleton::getInstance("MySingleton2");
    Singleton* s3 = Singleton::getInstance("MySingleton3");
    Singleton* s4 = Singleton::getInstance("MySingleton1");
    Singleton* s5 = Singleton::getInstance("MySingleton2");
    Singleton* s6 = Singleton::getInstance("MySingleton3");
    cout << boolalpha << (s1 == s4) << ", " << (s2 == s5) << ", " << (s3 == s6) << endl;
    s1->print();
    s2->print();
    s3->print();
    s4->print();
    s5->print();
    s6->print();
    s1->set_val(1);
    s2->set_val(2);
    s3->set_val(3);
    cout << s1->get_val() << ", " << s2->get_val() << ", " << s3->get_val() << ", "
         << s4->get_val() << ", " << s5->get_val() << ", " << s6->get_val() << ", "
         << endl;
}