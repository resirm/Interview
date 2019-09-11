# 美团点评 2020校招 后台方向在线考试

### 时间：2019.09.11

## 编程题|20.0分1/2

## **数字转换问题**

* 时间限制：C/C++语言 1000MS；其他语言 3000MS
* 内存限制：C/C++语言 65536KB；其他语言 589824KB

题目描述：
> 美团点评商家端系统里，客户在商家店里消费完成后，需要开消费发票。在开据消费发票过程中需需要将阿拉伯数字转成中文大写数字。举例来说：200.00需要转换成贰佰元整。现需要通过程序实现转换功能，以提升商家开发票的效率。

输入
>一维的字符串数组，数组里每一项为阿拉伯数字，数字保留两位小数点且最大值不超过1000000000000（万亿）；输入示例（注意：数组符[]也为输入项）：["200.00", "201.15"]

输出
>转换后对应的一维数组；


样例输入  
```["200.00","201.15","1015","200001010200"]```  
样例输出  
```["贰百元整", "贰百零壹元壹角伍分", "壹千零壹十伍元整", "贰千亿零壹百零壹万零贰百元整"]```

提示
> 1. 单位参考：壹、贰、叁、肆、伍、陆、柒、捌、玖、十、百、千、万、亿、元、角、分、零、整；
> 2. 当数据为整数值或者小数部分为零时，需要添加XX元整。如：10表示为壹十元整， 200.00表示为贰百元整；

## **Python代码**
```Python
def conv(num):
  return num
```


## 编程题|20.0分2/2

## **评价运营活动激励发放**

* 时间限制：C/C++语言 1000MS；其他语言 3000MS
* 内存限制：C/C++语言 65536KB；其他语言 589824KB

题目描述：  
>为了激励更多的用户发表点评，大众点评在近期组织了一次促评排行榜的活动。在活动期间, 写评价数排名靠前的用户将获得对应的奖励，奖励分为积分、优惠券、贡献值三类。为了让活动更有趣味性，不同排名的用户将获得不同类型的激励。同时，为了保证激励发放效率，这三类激励会并行发放。  
我们把问题简单描述一下，假定有一个激励发放的类，如下所示：
```Java
class ReviewEncourage {

  public ReviewEncourage(int n) { ... }      // 构造函数,n为中奖用户数

/*

    PrizePool类仅有一个send方法，实现如下：

    public class PrizePool {

        public void send(String input) {

            System.out.print(input);

        }

    }

  */

  public void bonus(PrizePool prizePool) { ... }  // 仅能打印A，表示发放积分

  public void coupon(PrizePool prizePool) { ... }  // 仅能打印B，表示发放优惠券

  public void contribution(PrizePool prizePool) { ... }  // 仅能打印C，表示发放贡献值

}
```

>同一个ReviewEncourage实例将会传递给三个不同的线程用于激励发放：  
>1. 积分发放线程将会调用bonus方法发放积分  
>2. 优惠券发放线程将会调用coupon方法发放优惠券  
>3. 贡献值发放线程将会调用contribution方法发放贡献值  

>要求依次对不同排位的用户发放不同类型的奖励，其中排位为奇数的用户发放积分，排位为偶数的用户交替发放优惠券和贡献值。 
例如一共5个中奖用户，要求对第一个用户发放积分，第二个用户发放优惠券，第三个用户发放积分，第四个用户发放贡献值，第五个用户发放积分，即输出ABACA  
要求补全以上代码，输出指定字符串序列

输入
>获奖用户数n，n大于0，小于等于100

输出
>由A、B、C组成的字符串，长度为n，奇数位为A，偶数位交替为B和C

提示  
>三个激励发放线程异步执行，不保证执行顺序

样例
>样例输入  
1  
样例输出  
A  
输入样例2  
4  
输出样例2  
ABAC  
输入样例3  
5  
输出样例3  
ABACA  
输入样例4  
10  
输出样例4  
ABACABACAB  

## **C++代码**
```C++
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
```