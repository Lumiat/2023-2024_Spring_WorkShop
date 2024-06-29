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

void Mall::Show_Advertise(){

}

void Mall::Set_Advertise(){

}

void Mall::Delete_Advertise(){

}

void Mall::Pursue_Heat(){

}

void Mall::Use_Heat(){

}

void Mall::Show_Rate(){

}

void Mall::Show_Pursue_History(){

}

int Mall::get_id1(){

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
void Food::Show_Dish(){

}

void Food::Set_Dish(){

}

void Food::Add_Dish(){

}

void Food::Delete_Dish(){

}

void Food::Show_Discount(){

}

//Wear派生类实现
void Wear::Show_Clothing(){

}

void Wear::Set_Clothing(){

}

void Wear::Add_Clothing(){

}

void Wear::Delete_Clothing(){

}

void Wear::Show_Discount(){

}

//Market派生类实现
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
