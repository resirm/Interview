#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;

class PrizePool {
public:
    void send(string input) {
        cout << input;
    }
};

class ReviewEncourage {
public:
    ReviewEncourage(int n):len(n) {
        
    }  // 构造函数,n为中奖用户数

    void bonus(PrizePool prizePool) {
        for(int i = 1; i < len; i+=2){
            {
                unique_lock<mutex> ul(mtx_);
                cond_.wait(ul, [&,i]{return i == cnt+1; });
            }
            prizePool.send("A");
            ++cnt;
            cond_.notify_all();
        }
    }  // 仅能打印A，表示发放积分

    void coupon(PrizePool prizePool) {
        for(int i = 2; i < len; i+=4){
            {
                unique_lock<mutex> ul(mtx_);
                cond_.wait(ul, [&,i]{return i == cnt+1; });
            }
            prizePool.send("B");
            ++cnt;
            cond_.notify_all();
        }
    }  // 仅能打印B，表示发放优惠券

    void contribution(PrizePool prizePool) {
        for(int i = 4; i < len; i+=4){
            {
                unique_lock<mutex> ul(mtx_);
                cond_.wait(ul, [&,i]{return i == cnt+1; });
            }
            prizePool.send("C");
            ++cnt;
            cond_.notify_all();
        }
    }  // 仅能打印C，表示发放贡献值

private:
    mutex mtx_;
    condition_variable cond_;
    int cnt = 0;
    int len;
};

int main(){
    int n;
    cout << "Enter a int number: ";
    cin >> n;
    while(!cin){
        cerr << "\nEnter a int number: ";
        cin >> n;
    }
    ReviewEncourage re(n);
    PrizePool p;
    thread bonus([&,p](ReviewEncourage& re)->void{ re.bonus(p); }, std::ref(re));
    thread coupon([&,p](ReviewEncourage& re)->void{ re.coupon(p); }, std::ref(re));
    thread contribution([&,p](ReviewEncourage& re)->void{ re.contribution(p); }, std::ref(re));
    bonus.join();
    coupon.join();
    contribution.join();
    cout << endl;
    return 0;
}