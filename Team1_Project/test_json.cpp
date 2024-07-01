#include <iostream>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

int main()
{
    json j;                                                //首先创建一个空的json对象
    j["pi"] = 3.141;                                       //然后通过名称/值对的方式进行初始化，此时名称"pi"对应的数值就是3.141
    j["happy"] = true;                                     //将名称"happy"赋值为true
    j["name"] = "Niels";                                   //将字符串"Niels"存储到"name"
    j["nothing"] = nullptr;                                //"nothing"对应的是空指针
    j["answer"]["everything"] = 42;                        //对对象中的对象进行初始化
    j["list"] = { 1, 0, 2 };                                 //使用列表初始化的方法对"list"数组初始化
    j["object"] = { {"currency", "USD"}, {"value", 42.99} }; //对对象进行初始化
    std::string s = j.dump();                              // {"happy":true,"pi":3.141}
    std::cout << j.dump(4) << std::endl;
    return 0;
}
