#include "discount.h"
/*#include<iostream>
#include<fstream>
#include<string>
#include<cmath>
#include<algorithm>
#include<vector>*/
using namespace std;

//User基类的函数实现
User::User(){
    /*注册（新建一个用户）时调用，函数包含注册时的交互信息
    注意判断新用户名与已有用户的用户名是否重合
    最后要获取UserName和PassWord这两个数据成员，并自动生成id*/

}

User::~User(){

}

bool User::LogIn(){
    /*判断用户名存在性--->判断密码与用户名的匹配
    匹配返回true，否则返回false，将尝试次数上限的逻辑在主函数交互完成*/
}

void User::LogOut(){

}

void User::Change_Name(){

}

void User::Change_Password(){

}

//Mall派生类实现
bool Mall::LogIn(){
    
}

void Mall::Show_Advertise()
{
    if (Shops.empty())
    {
        cout << "目前没有促销活动信息" << endl;
        system("pause");
        system("cls");
        return;
    }
    // 创建四个向量来分别存储不同类型的店铺指针
    vector<Brand*> foodShops;
    vector<Brand*> wearShops;
    vector<Brand*> marketShops;
    vector<Brand*> apperanceShops;

    for (auto shop : Shops) 
    {
       // dynamic_cast 是 C++ 中用于在运行时进行安全类型转换的操作符，通常用于将基类指针或引用转换为派生类指针或引用
        if (dynamic_cast<Food*>(shop)) //dynamic_cast<Food*>(shop) 尝试将基类 Brand 指针 shop 转换为派生类 Food 指针。
                                       //如果 shop 指向的是一个 Food 类型的对象，那么转换成功，返回一个非空的指针。
                                       //如果 shop 指向的不是一个 Food 类型的对象，那么转换失败，返回 nullptr。
        {
            foodShops.push_back(shop); // 如果是Food类型的店铺，添加到foodShops向量中
        }
        else if (dynamic_cast<Wear*>(shop)) 
        {
            wearShops.push_back(shop); // 如果是Wear类型的店铺，添加到wearShops向量中
        }
        else if (dynamic_cast<Market*>(shop))
        {
            marketShops.push_back(shop); // 如果是Market类型的店铺，添加到marketShops向量中
        }
        else if (dynamic_cast<Apperance*>(shop)) 
        {
            apperanceShops.push_back(shop); // 如果是Apperance类型的店铺，添加到apperanceShops向量中
        }
        // 显示食品店铺的折扣信息
        if (!foodShops.empty())
        { 
            cout << "食品店铺折扣信息：" << endl;
            for (size_t i = 0; i < foodShops.size(); ++i)  // 遍历每个食品店铺
            {
               foodShops[i]->Show_Discount(); // 显示当前店铺的折扣信息
               cout <<endl; // 分隔每个店铺的信息
            }
        }
        else 
        {
            cout << "目前没有食品店铺折扣信息。" << endl;
            system("pause");
            system("cls");
            return;
        }

        // 显示服装店铺的折扣信息
        if (!wearShops.empty()) 
        { // 检查是否有服装店铺
            cout << "服装店铺折扣信息：" << endl;
            for (size_t i = 0; i < wearShops.size(); ++i)
            { // 遍历每个服装店铺
                wearShops[i]->Show_Discount(); 
                cout << endl; 
            }
        }
        else
        {
            cout << "目前没有服装店铺折扣信息。" << endl;
            system("pause");
            system("cls");
            return;
        }

        // 显示超市店铺的折扣信息
        if (!marketShops.empty())
        { // 检查是否有超市店铺
            cout << "超市店铺折扣信息：" <<endl;
            for (size_t i = 0; i < marketShops.size(); ++i)
            { // 遍历每个超市店铺
                marketShops[i]->Show_Discount(); 
                cout << endl;
            }
        }
        else
        {
            cout << "目前没有超市店铺折扣信息。" << endl;
            system("pause");
            system("cls");
            return;
        }

        // 显示形象管理店铺的折扣信息
        if (!apperanceShops.empty())
        { // 检查是否有形象管理店铺
            cout << "形象管理店铺折扣信息：" << endl;
            for (size_t i = 0; i < apperanceShops.size(); ++i) 
            { // 遍历每个形象管理店铺
                apperanceShops[i]->Show_Discount(); 
                cout << endl;
            }
        }
        else
        {
           cout << "目前没有形象管理店铺折扣信息。" << endl;
           system("pause");
           system("cls");
           return;
        }
    }
}

void Mall::Set_Advertise()
{
    if (Shops.empty()) 
    {
        cout << "目前没有店铺。" << endl;
        system("pause");
        system("cls");
        return;
    }

    cout << "请选择需要更改折扣信息的店铺：" << endl;
    for (int i = 0; i < Shops.size(); i++)
    {
        cout << i + 1 << ". " << Shops[i]->GetBrandName() << endl; // 显示店铺序号和类型
    }

    int choice;
    cin >> choice;
    if (choice < 1 || choice > Shops.size()) {
        cout << "选择无效。" << endl;
        return;
    }

    Brand* selectedShop = Shops[choice - 1];

    // 检查店铺类型并调用相应的设置方法
    if (Food* foodShop = dynamic_cast<Food*>(selectedShop))
    {
        foodShop->Set_Dish();
    }
    else if (Wear* wearShop = dynamic_cast<Wear*>(selectedShop)) 
    {
        wearShop->Set_Clothing();
    }
    else if (Market* marketShop = dynamic_cast<Market*>(selectedShop))
    {
        marketShop->Set_Groceries();
    }
    else if (Apperance* apperanceShop = dynamic_cast<Apperance*>(selectedShop)) 
    {
        apperanceShop->Set_Service();
    }
    else
    {
        cout << "未知店铺类型。" << endl;
    }
    cout << "店铺：" << Shops[choice - 1]->GetBrandName() << "的信息已经修改" << endl;
    system("pause");
    system("cls");
    return;
}

void Mall::Delete_Advertise()
{
    if (Shops.empty())
    {
        cout << "目前没有店铺。" << endl;
        system("pause");
        system("cls");
        return;
    }

    cout << "请选择需要删除折扣信息的店铺：" << endl;
    for (int i = 0; i < Shops.size(); i++) 
    {
        cout << i + 1 << ". " << Shops[i]->GetBrandName() << endl; // 显示店铺序号和类型
    }

    int choice;
    cin >> choice;
    if (choice < 1 || choice > Shops.size()) {
        cout << "选择无效。" << endl;
        return;
    }

    Brand* selectedShop = Shops[choice - 1];

    // 检查店铺类型并调用相应的删除方法
    if (Food* foodShop = dynamic_cast<Food*>(selectedShop))
    {
        foodShop->Delete_Dish();
    }
    else if (Wear* wearShop = dynamic_cast<Wear*>(selectedShop))
    {
        wearShop->Delete_Clothing();
    }
    else if (Market* marketShop = dynamic_cast<Market*>(selectedShop))
    {
        marketShop->Delete_Groceries();
    }
    else if (Apperance* apperanceShop = dynamic_cast<Apperance*>(selectedShop)) 
    {
        apperanceShop->Delete_Service();
    }
    else
    {
        cout << "未知店铺类型。" << endl;
    }

    cout << "店铺 " << Shops[i-1]->GetBrandName() << " 的折扣信息已删除。" << endl;
    system("pause");
    system("cls");
    return;
}

void Mall::Pursue_Heat()
{
    int amount;
    cout << "请输入购买热度点数: ";
    cin >> amount;

    // 更新热度点余额
    Heat_Spot += amount;

    // 获取当前日期
    time_t t = time(nullptr);
    //转换为当地时间
    tm* now = localtime(&t);
    char date[11]; 
    //格式化时间
    strftime(date, sizeof(date), "%Y-%m-%d", now);

    // 计算购买金额，这里假设每个热度点的价格为1单位货币
    double money = static_cast<double>(amount);

    // 更新购买记录
    History history = { date, amount, money };
    Pursuit_History.push_back(history);

    // 更新balance
    Manager::balance += money;

    // 提示用户购买成功
    cout << "成功购买了 " << amount << " 热度点。" << endl;
    system("pause");
    system("cls");
    return;
}

void Mall::Use_Heat()
{
    cout << "******************************************" << endl;
    cout << "************* 热度点使用规则 ***************" << endl;
    cout << "**        充值100，霸占热度榜一天          **" << endl;
    cout << "**        充值300，霸占热度榜四天          **" << endl;
    cout << "**        充值500，霸占热度榜一周          **" << endl;
    cout << "**        充值900，霸占热度榜两周          **" << endl;
    cout << "******************************************" << endl;
    int amount;
    cout << "请输入使用热度点数: ";
    cin >> amount;
    if (amount <= Heat_Spot)
    {
        if (amount!=100||amount!=500||amount!=900||amount!=300)
        {
            cout << "非法输入" << endl;
        }
        else if (amount == 100)
        {
            cout << "您已充值100热度点，即将霸占热榜一天" << endl;
        }
        else if (amount == 300)
        {
            cout << "您已充值300热度点，即将霸占热榜四天" << endl;
        }
        else if (amount == 500)
        {
            cout << "您已充值500热度点，即将霸占热榜一周" << endl;
        }
        else if (amount == 900)
        {
            cout << "您已充值900热度点，即将霸占热榜两周" << endl;
        }
        Heat_Spot -= amount;
        system("pause");
        system("cls");
        return;
    }
    else
    {
        cout << "热度点余额不足！" << endl;
        system("pause");
        system("cls");
        return;
    }
}

void Mall::Show_Rate()
{
    cout << Mall_name << "的评分为：" << Rate << endl;
}

void Mall::Show_Pursue_History()
{
    for (const auto& history : Pursuit_History)
    {
        cout << "日期: " << history.date << ", 数量: " << history.amount << ", 金额: " << history.money << endl;
    }
}

int Mall::get_id1()
{
    return id1;
}

//Buyer派生类实现
bool Buyer::LogIn(){

}

void Buyer::SearchItem(){

}

void Buyer::Rating(){

}

void Buyer::Show_FootPrint(){

}

int Buyer::get_id2(){

}

//Manager类实现
bool Manager::LogIn(){

}

void Manager::Show_Balance(){
    for (auto it = Malls.begin(); it != Malls.end(); it++) {
        cout<<it.Mall_name
    }
}

void Manager::Deposit(){

}

void Manager::Show_SpotSold_History(){

}

void Manager::Show_Deposit_History(){

}

int Manager::get_id3(){

}

void Manager::Trending(){

}

void Manager::Show_Mall(){

}

void Manager::Show_Buyer(){

}

void Manager::Show_Manager(){

}

void Manager::Show_All(){

}


//Food派生类实现
<<<<<<< HEAD
string Food::GetBrandName()
{
    return Brand_Name;
}

void Food::Show_Dish(){

=======
void Food::Show_Discount(){
    for (auto it=Dish.begin(); i !=Dish.end(); i++) {
        cout << "商品名称： " << it.what << "; 折扣： " << it.discount_message;
        cout<<"折扣日期： "<<
        cout << endl;
    }
>>>>>>> origin/DFish
}

void Food::Set_Dish(){
    cout << "请输入您想要设置的商品名称： "；
    string what_tem;
    cin >> what_tem;
    for (auto it = Dish.begin(); it != Dish.end(); it++) {
        if (it.what == what_tem) {
            cout << "请输入您想设置的该商品折扣： ";
            string discount_tem;
            cin >> discount_tem;
            it.discount_tem = discount_tem;
            cout << "修改成功！" << endl;
        }
        else {
            cout << "抱歉，未找到相关商品" << endl;
        }
    }

}

void Food::Add_Dish(){
    cout << "输入您想增加的商品名称： ";
    cin >> what_tem;
    cout << "输入您想增加的该商品的折扣： ";
    cin >> discount_tem;
    struct Commodity { what_tem,discount_tem; };
    Dfish.push_back(Commodity);
    cout << "添加成功！" << endl;
}

void Food::Delete_Dish(){
    cout << "请输入您想删除的商品名称： ";
    cin >> what_tem;
    for (auto it = Dish.begin(); it != Dish.end(); it++) {
        if (it.what == what_tem) {
            cout << "确认删除？Y/N"<<endl；
                string test;
            if (test == Y) {
                Dish.erase(it);
                cout << "删除成功！" << endl;
            }
            else if (test == N) {
                return 0;
            }
            else {
                cout << "输入错误！请重试……" << endl;
            }
        }
    }
}


//Wear派生类实现
<<<<<<< HEAD
string Wear::GetBrandName()
{
    return Brand_Name;
}

void Wear::Show_Clothing(){

=======
void Wear::Show_Discount() {
    for (auto it = Clothing.begin(); i != Clothing.end(); i++) {
        cout << "商品名称： " << it.what << "; 折扣： " << it.discount_message;
        cout << endl;
    }
>>>>>>> origin/DFish
}


void Wear::Set_Clothing(){
    cout << "请输入您想要设置的商品名称： "；
        string what_tem;
    cin >> what_tem;
    for (auto it = Clothin.begin(); it != Clothin.end(); it++) {
        if (it.what == what_tem) {
            cout << "请输入您想设置的该商品折扣： ";
            string discount_tem;
            cin >> discount_tem;
            it.discount_tem = discount_tem;
            cout << "修改成功！" << endl;
        }
        else {
            cout << "抱歉，未找到相关商品" << endl;
        }
    }
}

void Wear::Add_Clothing(){
    cout << "输入您想增加的商品名称： ";
    cin >> what_tem;
    cout << "输入您想增加的该商品的折扣： ";
    cin >> discount_tem;
    struct Commodity { what_tem, discount_tem; };
    Clothing.push_back(Commodity);
    cout << "添加成功！" << endl;
}

void Wear::Delete_Clothing(){
    cout << "请输入您想删除的商品名称： ";
    cin >> what_tem;
    for (auto it = Clothingh.begin(); it != Clothing.end(); it++) {
        if (it.what == what_tem) {
            cout << "确认删除？Y/N" << endl；
                string test;
            if (test == Y) {
                Clothing.erase(it);
                cout << "删除成功！" << endl;
            }
            else if (test == N) {
                return 0;
            }
            else {
                cout << "输入错误！请重试……" << endl;
            }
        }
    }
}


//Market派生类实现
string Market::GetBrandName()
{
    return Brand_Name;
}

void Market::Show_Groceries(){

}

void Market::Set_Groceries(){

}

void Market::Add_Groceries(){

}

void Market::Delete_Groceries(){

}

void Market::Show_Discount(){

}

//Apperance派生类实现
string Apperance::GetBrandName()
{
    return Brand_Name;
}

void Apperance::Show_Service(){

}

void Apperance::Set_Service(){

}

void Apperance::Add_Service(){

}

void Apperance::Delete_Service(){

}

void Apperance::Show_Discount(){
    
}
