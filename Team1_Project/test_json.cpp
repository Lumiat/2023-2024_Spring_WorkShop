#include <iostream>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

int main()
{
    json j;                                                //���ȴ���һ���յ�json����
    j["pi"] = 3.141;                                       //Ȼ��ͨ������/ֵ�Եķ�ʽ���г�ʼ������ʱ����"pi"��Ӧ����ֵ����3.141
    j["happy"] = true;                                     //������"happy"��ֵΪtrue
    j["name"] = "Niels";                                   //���ַ���"Niels"�洢��"name"
    j["nothing"] = nullptr;                                //"nothing"��Ӧ���ǿ�ָ��
    j["answer"]["everything"] = 42;                        //�Զ����еĶ�����г�ʼ��
    j["list"] = { 1, 0, 2 };                                 //ʹ���б��ʼ���ķ�����"list"�����ʼ��
    j["object"] = { {"currency", "USD"}, {"value", 42.99} }; //�Զ�����г�ʼ��
    std::string s = j.dump();                              // {"happy":true,"pi":3.141}
    std::cout << j.dump(4) << std::endl;
    return 0;
}
