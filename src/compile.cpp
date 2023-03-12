#include <iostream>

int main(){
    system("cl /c /EHsc Lib/JSON.cpp");
    system("lib JSON.obj");
    system("cl /EHsc main.cpp /link JSON.lib");
    return 0;
}
