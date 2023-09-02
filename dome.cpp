#include <iostream>
#include <fstream>

int main() {
    std::cout << "Hello, World!" << std::endl;

     int hh2 = 0xFFFFFFFF;

    std::string json = "1111";


    int header;
    memmove(&header, &json[0], 4);

    memmove(&json[0], &hh2, 4);

    return 0;
}
