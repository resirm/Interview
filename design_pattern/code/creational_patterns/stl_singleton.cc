#include <iostream>
#include <mutex>
#include <future>

using namespace std;

class Singleton{
public:
    
    static shared_ptr<Singleton> getSingleton() {
        call_once(oc, []{pSingleton = shared_ptr<Singleton>(new Singleton());});
        return pSingleton;
    }
    void setVal(int v){
        val = v;
    }
    int getVal() const{
        return val;
    }

private:
    static once_flag oc;
    int val;
    static shared_ptr<Singleton> pSingleton;
    Singleton(){
        cout << "Singleton constructed." << endl;
    }
};

shared_ptr<Singleton> Singleton::pSingleton = nullptr;
once_flag Singleton::oc;

int main(){
    shared_ptr<Singleton> p = Singleton::getSingleton();
    shared_ptr<Singleton> p2 = Singleton::getSingleton();
    auto f1 = async(Singleton::getSingleton);
    auto f2 = async(Singleton::getSingleton);
    shared_ptr<Singleton> p3 = f1.get();
    shared_ptr<Singleton> p4 = f2.get();
    p->setVal(3);
    cout << p4->getVal() << endl;
    return 0;
}