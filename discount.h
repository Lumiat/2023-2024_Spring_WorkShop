#ifndef _DISCOUNT_H_
#define _DISCOUNT_H_
#include<iostream>
#include<string>
#include<algorithm>
#include<fstream>
#include<vector>
#include<cmath>
#include<ctime>
#include <nlohmann/json.hpp>
#include <iomanip>

using json = nlohmann::json;
using namespace std;

fstream malls_data("I:/Discount_At_Your_Hand/Datas/Malls.json", ios::in | ios::out);
fstream buyers_data("I:/Discount_At_Your_Hand/Datas/Buyers.json", ios::in | ios::out);
fstream managers_data("I:/Discount_At_Your_Hand/Datas/Managers.json", ios::in | ios::out);

struct History{
    string date;
    int amount;
    double money;
} ;

struct Commodity{
    string what;
    string discount_message;
};

class Brand;
vector<Mall> Malls[50];
vector<Buyer> Buyers[50];

class User{
    protected:
    string UserName;
    string PassWord;
    int id;
    public:
    bool LogIn(fstream &ifs);//交互内容,如果用户名和密码都匹配,返回true;
    void LogOut(fstream &iofs,const string& logged_name);  //注销账号函数,用析构函数清除用户
    void Change_Name(fstream &iofs,const string& old_name);//更改用户名函数
    void Change_Password(fstream &iofs,const string &logged_name);//更改密码函数
};

class Mall:public User
{
protected:
    int Heat_Spot;  //热度点余额
    int Head_Now;   //目前热度
    vector<History> Pursuit_History; //热度点购买记录
    string Rate;    //商场评分
    int RatePeo;//当前参与评分人数
    vector<Brand*> Shops;   //所有有折扣商铺
    string Mall_name;
public:
    static int id1;
    void Show_Advertise();  //显示所有折扣信息
    void Set_Advertise();   //更改折扣信息
    void Delete_Advertise();//删除折扣信息
    void Pursue_Heat();     //购买热度点
    void Use_Heat();        //使用热度点
    void Show_Rate();       //显示评分
    void Update_Rate(double newRating);//更新评分
    void Show_Pursue_History();    //显示购买记录
    string GetMallName();
    static int get_id1();
    friend class manager;
};
int Mall::id1=10900000;

class Buyer:public User{
protected:
    vector<string> FootPrint;   //显示买家足迹
public:
    static int id2;
    void SearchItem();          //搜索特定商铺的折扣信息
    void Rating();              //买家有给商场评分的能力
    void Show_FootPrint();      //显示足迹（去过哪些商场）
    static int get_id2();
};
int Buyer::id2=19700000;

class Manager:public User{
private:
    static vector<History> Deposit_History;    //提款记录
    static int id3;
public:
    static double balance;             //钱包
    static void Show_Balance();                //显示钱包总额
    static void Deposit();                     //提款
    void Show_SpotSold_History();       //显示销售热度点记录
    static void Show_Deposit_History();        //显示提款记录
    void Trending();
    static int get_id3();
    void Show_Mall();
    void Show_Buyer();
    void Show_Manager();
    void Show_All();
};
double Manager::balance=0;
int Manager::id3=177000000;

class Brand{
    protected:
    string Kind;        //店铺所属类别：美食、服装配饰、生活超市、形象管理
    string Brand_Name;  //店名
    string Start_Date;     //折扣开始日期
    string End_Date;       //折扣结束日期
    string what_tem;
    string discount_tem;
    public:
    string Get_Brand_Name();
    virtual void Show_Discount() const=0;   //纯虚函数，显示折扣信息
    virtual void set_Date(string start_Date, string end_Date) const = 0;
};

class Food:public Brand{
    protected:
    vector<Commodity> Dish;     //餐厅具体折扣菜品
    public:
    string GetDish; 
    void Show_Dish();       //展示折扣菜品
    Food(string);
    void Set_Dish();        //更改折扣菜品
    void Add_Dish();        //新增折扣菜品
    void Delete_Dish();     //删除折扣菜品
    void Show_Discount();   //纯虚函数，显示折扣信息
    void set_Date(string start_Date, string end_Date);//纯虚函数，显示折扣日期
};

class Wear:public Brand{
    protected:
    vector<Commodity> Clothing; //服装店具体折扣服饰
    public:
    void Set_Clothing();    //更改折扣服饰
    void Add_Clothing();    //新增折扣服饰
    void Delete_Clothing();     //删除折扣服饰
    void Show_Discount();   //纯虚函数，显示折扣信息
    void set_Date(string start_Date, string end_Date);//纯虚函数，显示折扣日期
};

class Market:public Brand{
    protected:
    vector<Commodity> Groceries;//超市具体折扣百货
    public:
    void Show_Groceries();      //展示折扣百货
    void Set_Groceries();       //更改折扣百货
    void Add_Groceries();       //新增折扣百货
    void Delete_Groceries();    //删除折扣百货
    void Show_Discount();   //纯虚函数，显示折扣信息
    void set_Date(string start_Date, string end_Date);//纯虚函数，显示折扣日期
};

class Apperance:public Brand{
    protected:
    vector<Commodity> Service;  //形象管理具体折扣服务
    public:
    void Show_Service();        //展示折扣服务
    void Set_Service();         //更改折扣服务
    void Add_Service();         //新增折扣服务
    void Delete_Service();      //删除折扣服务
    void Show_Discount();   //纯虚函数，显示折扣信息
    void set_Date(string start_Date, string end_Date);//纯虚函数，显示折扣日期
};

void Register();
bool check_passwd_validity(int passwd_len,string passwd);
bool check_username_validity(string UserName);

#endif
