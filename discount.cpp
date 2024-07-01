#include "discount.h"
#include<iostream>
#include<fstream>

bool check_passwd_validity(int passwd_len, string passwd) {
    bool upper = false;
    bool lower = false;
    bool number = false;
    if (passwd_len < 8 || passwd_len>16) {
        cout << "密码长度不合法！长度不超过16且不小于8" << endl;
        cout << "请重新设置";
        return false;
    }
    for (int i = 0; i < passwd_len; i++) {
        if (passwd[i] >= 65 && passwd[i] <= 90)
            upper = true;
        if (passwd[i] >= 97 && passwd[i] <= 122)
            lower = true;
        if (passwd[i] >= 48 && passwd[i] <= 57)
            number = true;
        if (upper & lower & number) return true;
    }
        cout << "密码必须包含大小写字母和阿拉伯数字，请重新设置";
    return false;
}

bool check_username_validity(string UserName) {
    //ifstream ifs("I:/Discount_At_Your_Hand/Datas/Malls.json");
    json data;
    malls_data >> data;
    for (const auto& mall : data["malls"]) {
        string name = mall["username"];
        if (UserName == name) {
            cout << "已有用户使用相同名称！请重试" << endl;
            return false;
        }
    }
    buyers_data >> data;
    for (const auto& buyer : data["buyers"]) {
        string name =  buyer["username"];
        if (UserName == name) {
            cout << "已有用户使用相同名称！请重试" << endl;
            return false;
        }
    }
    managers_data >> data;
    for (const auto& manager : data["managers"]) {
        string name = manager["username"];
        if (UserName == name) {
            cout << "已有用户使用相同名称！请重试" << endl;
            return false;
        }
    }
    return true;
}
//User基类的函数实现
void Register(){
    /*注册（新建一个用户）时调用，函数包含注册时的交互信息
    注意判断新用户名与已有用户的用户名是否重合
    最后要获取UserName和PassWord这两个数据成员，并自动生成id*/
    /*目前缺少重名问题判断，等数据存储格式规定一起完成*/
    string passwd;
    int passwd_len;
    string UserName;
    int choice;
    cout<<"探索独家优惠，从这里开始！";
    cout << "请选择您的身份：1.我是商场方 2.我是购物者 3.我是平台管理员" << endl;
    cin >> choice;

    switch (choice) {
    case 1:
    NAME_AGAIN1:
        cout << "商场名：";
        cin >> UserName;
        if (!check_username_validity(UserName))
            goto NAME_AGAIN1;
    PASSWORD_AGAIN1:
        cout << endl;
        cout << "密码：";
        cin >> passwd;
        passwd_len = passwd.size();
        if (!check_passwd_validity(passwd_len, passwd))
            goto PASSWORD_AGAIN1;
        cout << "密码设置成功" << endl;
        /*写入新的用户到Malls.json*/
        json data;
        malls_data >> data;
        json new_mall = {
            {"username",UserName},
            {"passwd",passwd},
            {"id",10900001},
            {"heat_spot",0},
            {"heat_now",0},
            {"pursue_history",json::array()},
            {"rate","待评价"},
            {"shops",json::array()}
        };

        // 将新商场成员添加到 "malls" 数组中
        data["malls"].push_back(new_mall);

        // 将更新后的 JSON 数据写入文件
        malls_data << setw(4) << data << std::endl;
        break;
    case 2:
    NAME_AGAIN2:
        cout << "用户名：";
        cin >> UserName;
        if (!check_username_validity(UserName))
            goto NAME_AGAIN2;
    PASSWORD_AGAIN2:
        cout << endl;
        cout << "密码：";
        cin >> passwd;
        passwd_len = passwd.size();
        if (!check_passwd_validity(passwd_len, passwd))
            goto PASSWORD_AGAIN2;
        cout << "密码设置成功" << endl;
        /*写入新的用户到Malls.json*/
        json data;
        buyers_data >> data;
        json new_buyer = {
            {"username",UserName},
            {"passwd",passwd},
            {"id",19700001},
            {"foot_print",json::array()}
        };

        // 将新商场成员添加到 "malls" 数组中
        data["buyers"].push_back(new_buyer);

        // 将更新后的 JSON 数据写入文件
        buyers_data << setw(4) << data << endl;
        break;
    case 3:
    NAME_AGAIN3:
        cout << "用户名：";
        cin >> UserName;
        if (!check_username_validity(UserName))
            goto NAME_AGAIN3;
    PASSWORD_AGAIN3:
        cout << endl;
        cout << "密码：";
        cin >> passwd;
        passwd_len = passwd.size();
        if (!check_passwd_validity(passwd_len, passwd))
            goto PASSWORD_AGAIN3;
        cout << "密码设置成功" << endl;
        /*写入新的用户到Malls.json*/
        json data;
        managers_data >> data;
        json new_manager = {
            {"username",UserName},
            {"passwd",passwd},
            {"id",19700001},
            {"diposit_history",json::array()}
        };

        // 将新商场成员添加到 "malls" 数组中
        data["managers"].push_back(new_manager);

        // 将更新后的 JSON 数据写入文件
        managers_data << setw(4) << data << endl;
        break;
    }
        cout << "注册成功，欢迎加入我们！" << endl;
}

/*只用读取外存文件*/
bool User::LogIn(const fstream &ifs)
{
    /*判断用户名存在性--->判断密码与用户名的匹配
    匹配返回true，否则返回false，将尝试次数上限的逻辑在主函数交互完成*/
    json data;
    ifs >> data;
    string UserName;
    string passwd;
    string supposed_passwd;
    string master_key = data.begin().key();
    int name_try=0;
    int pin_try = 0;
    bool flag = false;

TRY_NAME_AGAIN:
    if (name_try == 3) return false;
    cout << "用户名：";
    cin >> UserName;
    
    for (const auto& kind : data[master_key]) {
        string name = kind.at("username");
        if (UserName == name) {
            supposed_passwd = kind.at("passwd");
            flag = true;
            break;
        }
    }
    if (!flag) {
        cout << "该用户不存在！";
        name_try++;
        goto TRY_NAME_AGAIN;
    }
TRY_PASSWD_AGAIN:
    if (pin_try == 3) return false;
    cout << endl << "密码：";
    cin >> passwd;
    if (passwd != supposed_passwd) {
        cout << "密码错误！请重新输入";
        pin_try++;
        goto TRY_PASSWD_AGAIN;
    }
    return true;
}

/*先验证身份再更改*/
void User::Change_Name(fstream &iofs){

}

void User::Change_Password(){

}

//Mall派生类实现
void Mall::LogOut() {

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

void Mall::Update_Rate(double newRating)
{
    double totalRating = Rate * RatePeo;
    totalRating += newRating;
    RatePeo++;
    Rate = double(totalRating / RatePeo);
}

int Mall::get_id1()
{
    return id1;
}

string Mall::GetMallName()
{
    return  Mall_name;
}

//Buyer派生类实现
bool Buyer::LogIn(){

}

void Buyer::SearchItem()
{
    string BrandName;
    cout << "请输入您想要查询的店铺： ";
    cin >> BrandName;
    for (const auto& mall : Malls) {
        for (const auto& shop : mall.Shops) {
            if (shop->GetBrandName() == brandName) {
                shop->Show_Discount();
                FootPrint.push_back(BrandName);
                return;
            }
        }
    }
    cout << "非常抱歉，未查询到该店铺的信息。" << endl;
}

void Buyer::Rating()
{
    string mallName;
    double rating;
    cout << "请输入您想要评分的商场：";
    cin >> mallName;
    cout << "请输入评分 (0.0 - 5.0)：";
    cin >> rating;
    if (rating < 0.0 || rating > 5.0) {
        cout << "评分无效，请输入 0.0 到 5.0 之间的数值。" << endl;
        return;
    }

    for (auto& mall : Malls) {
        if (mall.GetMallName() == mallName) {
            mall.UpdateRate(rating);
            cout << "评分已提交。" << endl;
            return;
        }
    }
    cout << "未找到指定的商场。" << endl;
}

void Buyer::Show_FootPrint()
{
    cout << "您浏览过的店铺：" << endl;
    for (const auto& brandName : FootPrint) 
    {
        bool found = false;
        for (const auto& mall : Malls) 
        {
            for (const auto& shop : mall.Shops) 
            {
                if (shop->GetBrandName() == brandName)
                {
                    shop->Show_Discount();
                    found = true;
                    break;
                }
            }
            if (found) break;
        }
        if (!found) {
            cout << "商铺 " << brandName << " 当前没有活动。" << endl;
        }
    }
}

int Buyer::get_id2()
{
    return id2;
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
<<<<<<< HEAD
=======
void Food::Show_Discount(){
    for (auto it=Dish.begin(); i !=Dish.end(); i++) {
        cout << "商品名称： " << it.what << "; 折扣： " << it.discount_message;
        cout<<"折扣日期： "<<
        cout << endl;
    }
>>>>>>> 60390c39b75e480c818b3c403bdb1734baf1fe4d
string Food::GetBrandName()
{
    return Brand_Name;
}

void Food::Show_Dish(){

<<<<<<< HEAD
=======
void Food::Show_Discount(){
    for (auto it=Dish.begin(); i !=Dish.end(); i++) {
        cout << "商品名称： " << it.what << "; 折扣： " << it.discount_message;
        cout<<"折扣日期： "<<
        cout << endl;
    }
>>>>>>> origin/DFish
=======
>>>>>>> 60390c39b75e480c818b3c403bdb1734baf1fe4d
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
<<<<<<< HEAD
=======
void Wear::Show_Discount() {
    for (auto it = Clothing.begin(); i != Clothing.end(); i++) {
        cout << "商品名称： " << it.what << "; 折扣： " << it.discount_message;
        cout << endl;
    }
>>>>>>> 60390c39b75e480c818b3c403bdb1734baf1fe4d
string Wear::GetBrandName()
{
    return Brand_Name;
}

void Wear::Show_Clothing(){

<<<<<<< HEAD
=======
void Wear::Show_Discount() {
    for (auto it = Clothing.begin(); i != Clothing.end(); i++) {
        cout << "商品名称： " << it.what << "; 折扣： " << it.discount_message;
        cout << endl;
    }
>>>>>>> origin/DFish
=======
>>>>>>> 60390c39b75e480c818b3c403bdb1734baf1fe4d
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
struct GroceryItem {  
    string name;  
    double discount;  
  
    GroceryItem(const string& name, double discount)  
        : name(name), discount(discount) {}  
};  
class Market {  
private:     
    string discountInformation; 
    vector<GroceryItem> groceries;  
    
public:
string Market::GetBrandName()
{
    return Brand_Name;
}

void Market::Show_Groceries(){
    for (const auto& grocery : groceries) {  
            cout << grocery << endl;  
}

void Market::Set_Groceries(const vector<GroceryItem>& newGroceries){
    groceries.clear();  
        for (const auto& grocery : newGroceries) {  
            groceries.push_back(grocery);  
        }  
}

void Market::Add_Groceries(const string& name, double discount){
        groceries.push_back(GroceryItem(name, discount));
}

void Market::Delete_Groceries(const string& grocery){
    auto it = find(groceries.begin(),groceries.end(),grocery);
    if(it != groceries.end()){
        groceries.erase(it);
    }
}

void Market::Show_Discount(){
    cout << "折扣为：" << discountInformation<< endl;
}
}

//Apperance派生类实现
struct ServiceItem {  
    string name;  
    double discount;  
  
    ServiceItem(const string& name, double discount)  
        : name(name), discount(discount) {}  
};  
class Appearance {  
private:     
    string discountInformation; 
    vector<ServiceItem> services;  
    
void Appearance::Show_Service(){
    for (const auto& ServiceItem : services) {  
            cout << service << endl;  
}

void Appearance::Set_Service(const vector<ServiceItem>& newService){
    services.clear();  
        for (const auto& service : newService) {  
            services.push_back(service);  
        }  
}

void Appearance::Add_Service(const string& name, double discount){
        services.push_back(ServiceItem(name, discount));
}

void Appearance::Delete_Service(const string& grocery){
    auto it = find(services.begin(),services.end(),service);
    if(it != services.end()){
        services.erase(it);
    }
}

void Appearance::Show_Discount(){
    cout << "折扣为：" << discountInformation<< endl;
}
