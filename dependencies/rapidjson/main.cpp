//
// Created by asus on 2020/6/2.
//

#include <cstdlib>
#include <iostream>
#include <stringbuffer.h>
#include <writer.h>

int main() {
    std::cout << "hello world!" << std::endl;
    rapidjson::StringBuffer s;
    rapidjson::Writer<rapidjson::StringBuffer> jsonWriter = rapidjson::Writer<rapidjson::StringBuffer>(s);
    jsonWriter.StartObject();

    jsonWriter.EndObject();
    std::string jsonString = s.GetString(); 
    std::cout << jsonString << std::endl;
    system("pause");
    return 0;
}
