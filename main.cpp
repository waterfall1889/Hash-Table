#include <iostream>
#include "HashTable.h"

using namespace std;

void TestCorrectness1(){
    cout << "[Test 01]" <<endl;
    HashTable table(3);
    table.readFromfile("testData\\testData01.txt");
    if(table.getSize() == 5){
        cout << "SizeTest -> Pass" <<endl;
    }
    else{
        cout << "SizeTest -> Fail" <<endl;
    }
    std::string n = "popcorn";
    table.insert(6,n);
    if(table.getSize() == 6 && table.search(6)){
        cout << "InsertTest -> Pass" <<endl;
    }
    else{
        cout << "InsertTest -> Fail" <<endl;
    }
    table.remove(3);
    if(table.getSize() == 5 && !table.search(3)){
        cout << "RemoveTest -> Pass" <<endl;
    }
    else{
        cout << "RemoveTest -> Fail" <<endl;
    }
};
int main() {
    TestCorrectness1();
}
