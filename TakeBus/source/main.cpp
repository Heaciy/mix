#include <iostream>
#include "menu.h"

using namespace std;

int main() {
    loadMapData();//加载数据
    int choice = 0;
    while (true) {
        printMenu();
        cin >> choice;
        if (choice != 0) {
            run(choice);
            cout << "按回车键继续:";
            cin.get();
            cin.get();
        } else {
            cout << "退出" << endl;
            break;
        }
    }
    return 0;
}
